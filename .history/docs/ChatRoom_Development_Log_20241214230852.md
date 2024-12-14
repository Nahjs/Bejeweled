# 聊天室开发记录

## 1. 项目概述

本聊天室是基于Qt框架开发的一个简单的在线聊天系统,采用C/S(客户端/服务器)架构。主要实现了基本的文字聊天、用户在线状态显示等功能。

## 2. 技术栈

- 开发语言: C++
- 开发框架: Qt 5
- 网络通信: Qt Network模块(QTcpServer/QTcpSocket)
- 数据持久化: SQLite数据库
- 界面设计: Qt Designer

## 3. 系统架构

### 3.1 服务器端(ChatServer)
- 基于QTcpServer实现