#include <iostream>
#include <ctime>
#include <cstdlib> // for exit
#include <sstream>
#include <vector>
#include <windows.h>

#include "cgamelogic.h"

void DisplayMenu() {
    std::cout << "请输入要交换的两个宝石的位置 (行 列 行 列)，例如 '0 1 0 2' 表示交换第1行第2列和第1行第3列的宝石。\n";
    std::cout << "输入 'exit' 退出游戏。\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    srand(static_cast<unsigned int>(time(0))); // 初始化随机数种子

    CGameLogic game;
    game.setgame_running(true); //初始设置游戏处于运行状态
    const int gemspecies = 5; // 宝石种类数量
    game.BuildMap(gemspecies);

    while (true) {
        std::cout << "\n当前地图:\n";
        game.DisplayMap();

        DisplayMenu();
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "感谢游玩！再见。\n";
            break;
        }

        int a, b, m, n;
        char dummy;
        std::istringstream iss(input);
        if (!(iss >> a >> b >> m >> n)) {
            std::cout << "输入格式错误，请重新输入。\n";
            continue;
        }

        // 尝试交换宝石
        bool swapResult = game.swap(a, b, m, n);
        if (swapResult) {
            std::cout << "成功交换宝石。\n";

            // 交换后检查更新后的地图
            bool hasMatch = game.checkmap();  // 这里会判断交换后的地图
            if (hasMatch) {
                std::cout << "有可消除的组合。\n";

                // 调用消除函数
                bool anyChanges = game.eliminate(false);  // 消除并更新地图

                // 输出结果
                if (anyChanges) {
                    std::cout << "消除后宝石下落，并更新了地图：\n";
                    // 调用下移函数补位，直到没有更多变化
                    do {
                        if (!game.down()) {
                            break;
                        }
                    } while (true);
                    game.DisplayMap();  // 显示更新后的地图
                } else {
                    std::cout << "消除没有产生任何变化，可能是因为没有更多的消除组合。\n";
                }
            } else {
                std::cout << "交换未导致任何可消除的组合。\n";
            }
        } else {
            std::cout << "无效的交换或未形成可消除的组合。\n";
        }
    }

    return 0;
}