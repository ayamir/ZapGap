#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include "constant.h"
#include "object.h"
#include "scene.h"

class GameController : public QObject                  //游戏控制类
{
    Q_OBJECT

public:
    GameController() = delete;
    GameController(Scene*, QObject* parent = nullptr);

private:
    Scene* scene;
    void KeyEvent(QKeyEvent* ,bool);                   //按键事件处理

protected:
    bool eventFilter(QObject*, QEvent*);               //事件判断
};

#endif // GAMECONTROLLER_H
