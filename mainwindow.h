#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "constant.h"
#include "scene.h"
#include "gamecontroller.h"

class MainWindow : public QMainWindow       //游戏主窗口
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Scene* scene;                           //主场景
    QGraphicsView* view;                    //主视图
    GameController* game;

public slots:
    void slotsStartGame();                  //游戏开始
    void slotsClearGame();                  //游戏通关

protected:
    void closeEvent(QCloseEvent*);          //窗口关闭事件

signals:
    void GameClear();                       //游戏通关信号
};

#endif // MAINWINDOW_H
