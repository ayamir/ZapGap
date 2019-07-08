#include "gamecontroller.h"

GameController::GameController(Scene* s, QObject* parent)
    : QObject {parent}, scene{s}
{
    scene->installEventFilter(this);                        //注册事件过滤器
}

bool GameController::eventFilter(QObject *, QEvent *e)
{
    if(e->type() == QEvent::KeyPress)                       //键盘按下
    {
        auto k = dynamic_cast<QKeyEvent*>(e);
        KeyEvent(k, true);
        return true;
    }
    else if (e->type() == QEvent::KeyRelease)               //键盘松开
    {
        auto k = dynamic_cast<QKeyEvent*>(e);
        if(!k->isAutoRepeat())                              //长按判断
        {
            KeyEvent(k, false);
            return true;
        }
    }
    return false;
}

void GameController::KeyEvent(QKeyEvent *e, bool b)
{
    switch (e->key()) {
    case Qt::Key_Q:
        scene->ispress.at(Qt::Key_Q) = b;                  //按键状态改变
        break;
    case Qt::Key_W:
        scene->ispress.at(Qt::Key_W) = b;
        break;
    case Qt::Key_E:
        scene->ispress.at(Qt::Key_E) = b;
        break;
    case Qt::Key_R:
        scene->ispress.at(Qt::Key_R) = b;
        break;
    default:
        break;
    }
}
