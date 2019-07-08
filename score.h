#ifndef SCORE_H
#define SCORE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include "constant.h"

class Score : public QWidget, public QGraphicsItem   //记分板
{
    Q_OBJECT
    friend class Scene;

public:
    Score(QWidget* parent = nullptr);
    QRectF boundingRect(void) const;

protected:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

private:
    QString QStrscore;           //得分字符串
    int iscore;                  //得分整型
};

#endif // SCORE_H
