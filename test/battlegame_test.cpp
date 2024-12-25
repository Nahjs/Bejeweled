#include <QApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "../battlegame.h"
#include  "Client/chatclient.h"

class TestClient : public ChatClient {
public:
    explicit TestClient(QObject* parent = nullptr) : ChatClient(parent) {
        connect(this, &ChatClient::messageReceived, this, &TestClient::onMessageReceived);
        connect(this, &ChatClient::connected, this, &TestClient::onConnected);
        connect(this, &ChatClient::disconnected, this, &TestClient::onDisconnected);
        connect(this, &ChatClient::error, this, &TestClient::onError);
    }

private slots:
    void onMessageReceived(const QString& type, const QString& data) {
        qDebug() << "收到消息 - 类型:" << type;
        if (type == "MATRIX_SYNC") {
            qDebug() << "收到矩阵同步消息:" << data;
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            if (!doc.isNull() && doc.isObject()) {
                QJsonObject obj = doc.object();
                qDebug() << "玩家ID:" << obj["playerId"].toString();
            }
        }
    }

    void onConnected() {
        qDebug() << "=== 已连接到服务器 ===";
    }

    void onDisconnected() {
        qDebug() << "=== 与服务器断开连接 ===";
    }

    void onError(const QString& error) {
        qDebug() << "错误:" << error;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建测试用客户端
    TestClient* client = new TestClient();
    
    // 连接到服务器
    qDebug() << "正在连接到服务器...";
    client->connectToServer("localhost", 5371);
   // client->connectToServer("cn-hk-bgp-4.ofalias.net", 26493);

    // 创建游戏窗口
    BattleGame* game = new BattleGame(client);
    game->show();

    // 输出测试说明
    qDebug() << "3. 验证矩阵变化和分数更新";
    qDebug() << "=== BattleGame 测试程序 ===";
    qDebug() << "1. 点击左侧矩阵进行操作";
    qDebug() << "2. 观察控制台输出的消息";
    qDebug() << "3. 验证矩阵变化和分数更新";
    qDebug() << "4. 检查同步消息的格式";
    qDebug() << "========================";

    return app.exec();
}
