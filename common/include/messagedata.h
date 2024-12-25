#ifndef MESSAGEDATA_H
#define MESSAGEDATA_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "messagetypes.h"  // 包含消息类型定义

// 基类定义
class MessageData {
public:
    virtual ~MessageData() = default;
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject& json) = 0;
    virtual QString serialize() const = 0;
    virtual bool deserialize(const QString& data) = 0;
};

// 登录消息数据
struct LoginData : public MessageData {
    QString username;
    QString password;
    
    QJsonObject toJson() const override {
        QJsonObject json;
        json["username"] = username;
        json["password"] = password;
        return json;
    }
    
    void fromJson(const QJsonObject& json) override {
        username = json["username"].toString();
        password = json["password"].toString();
    }
};

// 游戏移动数据
struct MoveData : public MessageData {
    int fromX;
    int fromY;
    int toX;
    int toY;
    
    QJsonObject toJson() const override {
        QJsonObject json;
        json["fromX"] = fromX;
        json["fromY"] = fromY;
        json["toX"] = toX;
        json["toY"] = toY;
        return json;
    }
    
    void fromJson(const QJsonObject& json) override {
        fromX = json["fromX"].toInt();
        fromY = json["fromY"].toInt();
        toX = json["toX"].toInt();
        toY = json["toY"].toInt();
    }
};

// 交换操作数据
class SwapData : public MessageData {
public:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    
    QJsonObject toJson() const override {
        QJsonObject json;
        json["fromRow"] = fromRow;
        json["fromCol"] = fromCol;
        json["toRow"] = toRow;
        json["toCol"] = toCol;
        return json;
    }
    
    void fromJson(const QJsonObject& json) override {
        fromRow = json["fromRow"].toInt();
        fromCol = json["fromCol"].toInt();
        toRow = json["toRow"].toInt();
        toCol = json["toCol"].toInt();
    }

    QString serialize() const override {
        return QString("%1,%2,%3,%4")
            .arg(fromRow)
            .arg(fromCol)
            .arg(toRow)
            .arg(toCol);
    }

    bool deserialize(const QString& data) override {
        QStringList parts = data.split(',');
        if (parts.size() != 4) return false;
        
        bool ok;
        fromRow = parts[0].toInt(&ok); if (!ok) return false;
        fromCol = parts[1].toInt(&ok); if (!ok) return false;
        toRow = parts[2].toInt(&ok); if (!ok) return false;
        toCol = parts[3].toInt(&ok); if (!ok) return false;
        
        return true;
    }
};

// 道具数据
class PropData : public MessageData {
public:
    enum Type {
        BOOM = 1,     // 爆炸道具
        ROW_CLEAR,    // 行消除
        COL_CLEAR,    // 列消除
        COLOR_CLEAR   // 同色消除
    };

    Type type;
    int targetRow;
    int targetCol;
    
    QJsonObject toJson() const override {
        QJsonObject json;
        json["type"] = static_cast<int>(type);
        json["targetRow"] = targetRow;
        json["targetCol"] = targetCol;
        return json;
    }
    
    void fromJson(const QJsonObject& json) override {
        type = static_cast<Type>(json["type"].toInt());
        targetRow = json["targetRow"].toInt();
        targetCol = json["targetCol"].toInt();
    }

    QString serialize() const override {
        return QString("%1,%2,%3")
            .arg(static_cast<int>(type))
            .arg(targetRow)
            .arg(targetCol);
    }

    bool deserialize(const QString& data) override {
        QStringList parts = data.split(',');
        if (parts.size() != 3) return false;
        
        bool ok;
        type = static_cast<Type>(parts[0].toInt(&ok)); if (!ok) return false;
        targetRow = parts[1].toInt(&ok); if (!ok) return false;
        targetCol = parts[2].toInt(&ok); if (!ok) return false;
        
        return true;
    }
};

// 游戏状态数据
struct GameStateData : public MessageData {
    int gameId;
    QVector<QVector<int>> board;  // 游戏板数据
    int player1Score;
    int player2Score;
    struct PlayerProps {
        int boomCount;      // 爆炸道具数量
        int rowClearCount;  // 行消除道具数量
        int colClearCount;  // 列消除道具数量
        int colorClearCount;// 同色消除道具数量
    } player1Props, player2Props;
    
    QJsonObject toJson() const override {
        QJsonObject json;
        json["gameId"] = gameId;
        json["player1Score"] = player1Score;
        json["player2Score"] = player2Score;
        
        // 序列化游戏板
        QJsonArray boardArray;
        for (const auto& row : board) {
            QJsonArray rowArray;
            for (int cell : row) {
                rowArray.append(cell);
            }
            boardArray.append(rowArray);
        }
        json["board"] = boardArray;
        
        // 序列化道具数据
        QJsonObject p1Props;
        p1Props["boom"] = player1Props.boomCount;
        p1Props["row"] = player1Props.rowClearCount;
        p1Props["col"] = player1Props.colClearCount;
        p1Props["color"] = player1Props.colorClearCount;
        json["player1Props"] = p1Props;
        
        QJsonObject p2Props;
        p2Props["boom"] = player2Props.boomCount;
        p2Props["row"] = player2Props.rowClearCount;
        p2Props["col"] = player2Props.colClearCount;
        p2Props["color"] = player2Props.colorClearCount;
        json["player2Props"] = p2Props;
        
        return json;
    }
    
    void fromJson(const QJsonObject& json) override {
        gameId = json["gameId"].toInt();
        player1Score = json["player1Score"].toInt();
        player2Score = json["player2Score"].toInt();
        
        // 解析游戏板数据
        QJsonArray boardArray = json["board"].toArray();
        board.resize(boardArray.size());
        for (int i = 0; i < boardArray.size(); ++i) {
            QJsonArray rowArray = boardArray[i].toArray();
            board[i].resize(rowArray.size());
            for (int j = 0; j < rowArray.size(); ++j) {
                board[i][j] = rowArray[j].toInt();
            }
        }
        
        // 解析道具数据
        QJsonObject p1Props = json["player1Props"].toObject();
        player1Props.boomCount = p1Props["boom"].toInt();
        player1Props.rowClearCount = p1Props["row"].toInt();
        player1Props.colClearCount = p1Props["col"].toInt();
        player1Props.colorClearCount = p1Props["color"].toInt();
        
        QJsonObject p2Props = json["player2Props"].toObject();
        player2Props.boomCount = p2Props["boom"].toInt();
        player2Props.rowClearCount = p2Props["row"].toInt();
        player2Props.colClearCount = p2Props["col"].toInt();
        player2Props.colorClearCount = p2Props["color"].toInt();
    }
};

// 消除结果数据
struct MatchData : public MessageData {
    struct Match {
        QVector<int> rows;
        QVector<int> cols;
        int matchType;  // 3连=3, 4连=4, 5连=5, L形=6, T形=7
    };
    QVector<Match> matches;
    int score;
    int chainLevel;
    
    QJsonObject toJson() const override {
        QJsonObject json;
        QJsonArray matchArray;
        for (const auto& match : matches) {
            QJsonObject matchObj;
            QJsonArray rowArray, colArray;
            for (int r : match.rows) rowArray.append(r);
            for (int c : match.cols) colArray.append(c);
            matchObj["rows"] = rowArray;
            matchObj["cols"] = colArray;
            matchObj["type"] = match.matchType;
            matchArray.append(matchObj);
        }
        json["matches"] = matchArray;
        json["score"] = score;
        json["chainLevel"] = chainLevel;
        return json;
    }
    
    void fromJson(const QJsonObject& json) override {
        QJsonArray matchArray = json["matches"].toArray();
        matches.clear();
        for (const auto& matchVal : matchArray) {
            QJsonObject matchObj = matchVal.toObject();
            Match match;
            QJsonArray rowArray = matchObj["rows"].toArray();
            QJsonArray colArray = matchObj["cols"].toArray();
            for (const auto& r : rowArray) match.rows.append(r.toInt());
            for (const auto& c : colArray) match.cols.append(c.toInt());
            match.matchType = matchObj["type"].toInt();
            matches.append(match);
        }
        score = json["score"].toInt();
        chainLevel = json["chainLevel"].toInt();
    }
};

// 方块下落数据
struct DropData : public MessageData {
    struct DropItem {
        int fromRow;
        int fromCol;
        int toRow;
        int toCol;
    };
    QVector<DropItem> drops;
    
    QJsonObject toJson() const override {
        QJsonObject json;
        QJsonArray dropArray;
        for (const auto& drop : drops) {
            QJsonObject dropObj;
            dropObj["fromRow"] = drop.fromRow;
            dropObj["fromCol"] = drop.fromCol;
            dropObj["toRow"] = drop.toRow;
            dropObj["toCol"] = drop.toCol;
            dropArray.append(dropObj);
        }
        json["drops"] = dropArray;
        return json;
    }
    
    void fromJson(const QJsonObject& json) override {
        QJsonArray dropArray = json["drops"].toArray();
        drops.clear();
        for (const auto& dropVal : dropArray) {
            QJsonObject dropObj = dropVal.toObject();
            DropItem item;
            item.fromRow = dropObj["fromRow"].toInt();
            item.fromCol = dropObj["fromCol"].toInt();
            item.toRow = dropObj["toRow"].toInt();
            item.toCol = dropObj["toCol"].toInt();
            drops.append(item);
        }
    }
};

#endif // MESSAGEDATA_H
