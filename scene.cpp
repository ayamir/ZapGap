#include "scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene {parent}
{
    e.seed(static_cast<unsigned>(time(nullptr)));                        //设置种子
    score = new Score{};
    connect(&ballTime, SIGNAL(timeout()), this, SLOT(slotsInitBall()));
    connect(&refreshTime, &QTimer::timeout, this, &Scene::advance);
    correctSound = new Sound(false, CORRECT_WAV, this);
    incorrectSound = new Sound(false, INCORRECT_WAV, this);
}

Scene::~Scene()
{
    refreshTime.stop();
    ballTime.stop();
    for(auto& i : railVec)
        i->deleteLater();
    for(auto& i : ballList)
        i->deleteLater();
    for(auto& i : lineVec)
        i->deleteLater();
}

void Scene::setLevel(int l)
{
    level = l;
    switch (level) {          //轨道数量设置
    case 5:
        numofRail = 4;
        break;
    case 4:
    case 3:
        numofRail = 3;
        break;
    case 2:
    case 1:
        numofRail = 2;
        break;
    }
}

void Scene::ClearScene()
{
    QList<QGraphicsItem*> listItem = items();
    while(!listItem.empty())
    {
        removeItem(listItem.at(0));
        listItem.removeAt(0);
    }
    for(auto& i : railVec)
        i->deleteLater();
    railVec.clear();
    for(auto& i : lineVec)
        i->deleteLater();
    lineVec.clear();
    for(auto& i : ballList)
        i->deleteLater();
    ballList.clear();
    ispress.at(Qt::Key_Q) = ispress.at(Qt::Key_W) = false;       //按键状态重置
    ispress.at(Qt::Key_E) = ispress.at(Qt::Key_R) = false;
}

void Scene::advance()
{
    if(ballList.empty() &&                                       //小球数量判断
       BALL_OF_LEVEL[static_cast<unsigned>(level - 1)] <= sumofBall)
    {
        passLevel();
        return;
    }
    if(changingStatusofRail != 0)                 //变轨判断
    {
        if(ballTime.isActive())
            ballTime.stop();
        Railadvance(railVec[static_cast<unsigned>(signofChangingRail_1)], railVec[static_cast<unsigned>(signofChangingRail_2)]);
    } else if((signofChangingRail_1 = u(e) % 95) < numofRail &&
       (signofChangingRail_2 = u(e) % 95) < numofRail &&
        signofChangingRail_1 != signofChangingRail_2)        //变轨随机
    {
        changingStatusofRail = -1;
    } else signofChangingRail_1 = signofChangingRail_2 = -1;
    if(!ballTime.isActive())
        ballTime.start();
    auto i = ballList.begin();
    while(i != ballList.end())
    {
        auto temp = i++;
        if(!Balladvance(*temp))
        {
            i = ballList.erase(temp);
        }
    }
    for(auto& i : lineVec)
        Lineadvance(i);
    Scoreadvance();
    update(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Scene::Railadvance(Object *&rail_1, Object*& rail_2)
{
    removeItem(rail_1);
    removeItem(rail_2);
    rail_1->height -= RAIL_SPEED * changingStatusofRail;
    rail_2->height -= RAIL_SPEED * changingStatusofRail;
    if(rail_2->height >= WINDOW_HEIGHT / 2)
    {
        std::swap(rail_1->color, rail_2->color);
        changingStatusofRail = 1;
    }
    addItem(rail_1);
    addItem(rail_2);
    rail_1->setPos(rail_1->startx, rail_1->height);
    rail_2->setPos(rail_2->startx, rail_2->height);
    if(rail_2->height <= -WINDOW_HEIGHT / 2 && changingStatusofRail == 1)
    {
        rail_1->height = rail_2->height = -WINDOW_HEIGHT / 2;
        changingStatusofRail = 0;
        signofChangingRail_1 = signofChangingRail_2 = -1;
    }
}

bool Scene::Balladvance(Object*& ball)
{
    if(changingStatusofRail != 0) return true;
    removeItem(ball);
    if(ispress.at(KEY[static_cast<unsigned>(ball->sign)]) &&
       ball->height + BALL_RADIUS + 30 >= LINE_HEIGHT &&
       ball->height - BALL_RADIUS + 30 <= LINE_HEIGHT + 4)
    {
        if(ball->color == railVec[static_cast<unsigned>(ball->sign)]->color)
        {
            score->iscore += INCORRECT_SCORE;
            incorrectSound->start();              //音效播放
            incorrectSound->wait();
        }
        else {
            score->iscore += CORRECT_SCORE;
            correctSound->start();
            correctSound->wait();
        }
        ball->deleteLater();
        return false;
    } else if(ball->height > WINDOW_HEIGHT / 2)
    {
        if(ball->color == railVec[static_cast<unsigned>(ball->sign)]->color)
            score->iscore += CORRECT_SCORE;
        else {
            score->iscore += INCORRECT_SCORE;
            incorrectSound->start();
            incorrectSound->wait();
        }
        ball->deleteLater();
        return false;
    }
    ball->height += BALL_SPEED;               //小球移动
    addItem(ball);
    ball->setPos(ball->startx, ball->height);
    return true;
}

void Scene::Lineadvance(Object*& line)
{
    if(line->isplace &&
       (!ispress.at(KEY[static_cast<unsigned>(line->sign)]) ||
       (changingStatusofRail != 0)))
    {
        removeItem(line);
        line->isplace = false;
    } else if(ispress.at(KEY[static_cast<unsigned>(line->sign)]) && !line->isplace && changingStatusofRail == 0)  //按键状态及放置状态判断
    {
        addItem(line);
        line->setPos(line->startx, line->height);
        line->isplace = true;
    }
}

void Scene::Scoreadvance(void)
{
    removeItem(score);
    score->QStrscore.setNum(score->iscore);
    addItem(score);
    score->setPos(2 * RAIL_WIDTH, -WINDOW_HEIGHT / 2);
}

void Scene::slotsInitScore(void)
{
    addItem(score);
    score->setPos(2 * RAIL_WIDTH, -WINDOW_HEIGHT / 2);
}

void Scene::slotsInitBall(void)
{
    if(currentBall > MAX_CUR_OF_BALL) return;               //同屏小球数量判断
    if(sumofBall > BALL_OF_LEVEL[static_cast<unsigned>(level - 1)]) return;
    int sign = u(e) % numofRail;                             //随机轨道
    QColor color = COLOR[u(e) % 4];                          //随机颜色
    auto ball = new Object{ObjectType::Ball, color, sign, level};
    ballList.push_back(ball);
    addItem(ball);
    ball->setPos(ball->startx, ball->height);
    ball->isplace = true;
    ++sumofBall;
}

void Scene::slotsInitRail(void)
{
    for(int i = 0; i < numofRail; ++i)
    {
        Object* rail = new Object{ObjectType::Rail, COLOR[static_cast<unsigned>(i)], i, level};
        railVec.push_back(rail);
        addItem(rail);
        rail->setPos(rail->startx, rail->height);
        rail->isplace = true;
    }
}

void Scene::slotsInitLine(void)
{
    for(int i = 0; i < numofRail; ++i)
    {
        Object* line = new Object{ObjectType::Line, Qt::white, i, level};
        line->isplace = false;
        lineVec.push_back(line);
    }
}

void Scene::passLevel(void)
{
    ClearScene();
    refreshTime.stop();
    ballTime.stop();
    update(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
    if(score->iscore > PASS_SCORE[static_cast<unsigned>(level - 1)])                     //通关条件判断
    {
        if(score->iscore > EVALUATION_SCORE[static_cast<unsigned>(level - 1)][2].first)  //评价条件判断
            QMessageBox::about(dynamic_cast<QWidget*>(parent()), tr("EVALUATION"),
                               EVALUATION_SCORE[static_cast<unsigned>(level - 1)][2].second);
        else if (score->iscore > EVALUATION_SCORE[static_cast<unsigned>(level - 1)][1].first)
            QMessageBox::about(dynamic_cast<QWidget*>(parent()), tr("EVALUATION"),
                               EVALUATION_SCORE[static_cast<unsigned>(level - 1)][1].second);
        else QMessageBox::about(dynamic_cast<QWidget*>(parent()), tr("EVALUATION"),
                                EVALUATION_SCORE[static_cast<unsigned>(level - 1)][0].second);
        ++level;
    }
    else QMessageBox::about(dynamic_cast<QWidget*>(parent()), tr("SORRY"), tr("很遗憾,您没有过关."));
    if(level > MAX_LEVEL)
    {
        QMessageBox::about(dynamic_cast<QWidget*>(parent()), tr("CONGRATULATION"), tr("恭喜你,通关了！！！"));
        slotsClearGame();
        return;
    }
    setLevel(level);
    slotsInitRail();
    slotsInitLine();
    score->iscore = 0;
    slotsInitScore();
    sumofBall = 0;
    update(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
    ballTime.start(FREQUENCY_OF_BALL[static_cast<unsigned>(level - 1)]);
    refreshTime.start(TIME_PER_FRAME);
}

void Scene::slotsStartGame()
{
    refreshTime.start(TIME_PER_FRAME);
    slotsInitRail();
    slotsInitLine();
    score->iscore = 0;
    slotsInitScore();
    sumofBall = 0;
    ballTime.start(FREQUENCY_OF_BALL[static_cast<unsigned>(level - 1)]);
}

void Scene::slotsClearGame()
{
    ballTime.stop();
    refreshTime.stop();
    emit GameClear();
}
