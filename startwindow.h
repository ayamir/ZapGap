#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSlider>
#include "sound.h"
#include "constant.h"
#include "mainwindow.h"


class StartWindow : public QWidget     //开始窗口
{
    Q_OBJECT

public:
    StartWindow(QWidget* parent = nullptr);
    ~StartWindow();

private slots:
    void slotsStartGame();             //开始游戏
    void slotsQuitGame();              //退出游戏
    void slotsGameRule();              //游戏规则
    void slotsSettingsShow();          //设置窗口弹出
    void slotsClearGame();             //游戏通关
    void slotsBGMSelect();             //背景音乐选择
    void slotsSetBGMVolume();          //背景音乐音量设置
    void slotsSetEffectVolume();       //游戏音效音量设置

private:
    MainWindow* mainwindow;             //游戏窗口

    Sound* BGM;                         //背景音乐
    Sound* startMusic;                  //开始游戏按钮音效
    Sound* quitMusic;                   //退出游戏按钮音效
    Sound* settingsMusic;               //设置按钮音效

    QPushButton* startButton;           //开始游戏按钮
    QPushButton* quitButton;            //退出游戏按钮音效
    QPushButton* settingsButton;        //设置按钮音效

    QWidget* settingsWindow;            //设置窗口
    /*
     * 以下为设置窗口控件
    */
    QWidget* BGMWidget;
    QWidget* effectWidget;
    QWidget* buttonWidget;

    QLabel* BGMLabel;
    QLabel* effectLabel;

    QSpinBox* BGMSpinBox;
    QSpinBox* effectSpinBox;

    QSlider* BGMSlider;
    QSlider* effectSlider;

    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QPushButton* ruleButton;
    QPushButton* BGMSelectButton;

    QHBoxLayout* BGMLayout;
    QHBoxLayout* effectLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* settingsLayout;
};


#endif // STARTWINDOW_H
