#ifndef OBJECT_H
#define OBJECT_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include "constant.h"

class Object : public QWidget, public QGraphicsItem           //场景元素
{
    Q_OBJECT

public:
    Object() = delete;
    Object(ObjectType, QColor, int, int, QWidget* parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    inline ObjectType TypeInfo();                             //返回场景元素类型
    bool isplace = false;                                     //是否放置
    qreal startx;                                             //左边界横坐标
    qreal height;                                             //高度
    int sign;                                                 //所在轨道标志
    QColor color;                                             //颜色

private:
    void PaintRail(QPainter*);                                //轨道绘制
    void PaintBall(QPainter*);                                //小球绘制
    void PaintLine(QPainter*);                                //线绘制
    void SetRailPos(void);                                    //轨道坐标设置
    void SetBallPos(void);                                    //小球坐标设置
    void SetLinePos(void);                                    //线坐标设置
    ObjectType type;                                          //元素类型
    int level;                                                //当前关卡
};

#endif // OBJECT_H
