#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <random>
#include <QTimer>
#include <list>
#include <ctime>
#include <QMessageBox>
#include "constant.h"
#include "object.h"
#include "sound.h"
#include "score.h"

class Scene : public QGraphicsScene     //主场景
{
    Q_OBJECT
    friend class GameController;
    friend class MainWindow;

public:
    Scene(QObject* parent = nullptr);
    ~Scene();
    void ClearScene(void);              //清屏

public slots:
    void advance();                     //画面刷新
    void slotsInitBall(void);           //初始化生成小球
    void slotsInitRail(void);           //初始化生成轨道
    void slotsInitLine(void);           //初始化生成线
    void slotsInitScore(void);          //初始化生成记分板

private:
    int level;                          //关卡
    int currentBall;                    //同屏小球数量
    int numofRail;                      //轨道数量
    int sumofBall;                      //小球总量
    int signofChangingRail_1 = -1;      //变轨轨道标志
    int signofChangingRail_2 = -1;
    int changingStatusofRail = 0;      //变轨状态
    Sound* correctSound;               //正确音效
    Sound* incorrectSound;             //错误音效
    QTimer ballTime;                    //生成小球时间间隔
    QTimer refreshTime;                 //画面刷新时间
    Score* score;                       //记分板
    std::default_random_engine e;       //随机引擎
    std::uniform_int_distribution<int> u;
    std::vector<Object*> railVec;       //轨道容器
    std::vector<Object*> lineVec;       //线容器
    std::list<Object*> ballList;        //小球链表
    std::map <int, bool> ispress {      //按键状态
        {Qt::Key_Q, false}, {Qt::Key_W, false},
        {Qt::Key_E, false}, {Qt::Key_R, false}
    };
    void Railadvance(Object*&, Object*&);//轨道刷新
    bool Balladvance(Object*&);         //小球刷新
    void Lineadvance(Object*&);         //线刷新
    void Scoreadvance(void);            //记分板刷新
    void passLevel(void);               //过关判断
    void setLevel(int);                 //关卡设置

private slots:
    void slotsStartGame();              //游戏开始
    void slotsClearGame();              //游戏通关

signals:
    void GameClear();                   //游戏通关信号
};

#endif // SCENE_H
