#include "object.h"

Object::Object(ObjectType o, QColor c, int s, int l, QWidget* parent)
    : QWidget {parent}, sign{s}, color{c}, type{o}, level{l}
{
    switch (type) {               //根据类型分别调用对应函数
    case ObjectType::Rail:
        SetRailPos();
        return;
    case ObjectType::Ball:
        SetBallPos();
        return;
    case ObjectType::Line:
        SetLinePos();
        return;
    }
}

QRectF Object::boundingRect() const
{
    switch (type) {
    case ObjectType::Rail:
        return QRectF(-RAIL_WIDTH / 2 - 2, -WINDOW_HEIGHT / 2 - 2, RAIL_WIDTH + 4, WINDOW_HEIGHT + 4);
    case ObjectType::Ball:
        return QRectF(-BALL_RADIUS - 2, -BALL_RADIUS - 2, 2 * BALL_RADIUS + 4, 2 * BALL_RADIUS + 4);
    case ObjectType::Line:
        return QRectF(-RAIL_WIDTH / 2 - 2, -2, RAIL_WIDTH + 4, 4);
    }
}

void Object::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    switch (type) {
    case ObjectType::Rail:
        PaintRail(painter);
        return;
    case ObjectType::Ball:
        PaintBall(painter);
        return;
    case ObjectType::Line:
        PaintLine(painter);
        return;
    }
}


void Object::PaintRail(QPainter* painter)
{
    painter->setPen(QPen(Qt::black));
    QLinearGradient lg{static_cast<qreal>(startx), static_cast<qreal>(WINDOW_HEIGHT),  //渐变色处理
                       static_cast<qreal>(startx + RAIL_WIDTH), 0};
    lg.setColorAt(0.2, color);
    lg.setColorAt(0.6, Qt::white);
    lg.setColorAt(1.0, color);
    painter->setBrush(QBrush(lg));
    painter->drawRect(0, 0, RAIL_WIDTH, WINDOW_HEIGHT);
}

void Object::PaintBall(QPainter* painter)
{
    QPen pen;
    pen.setWidth(10);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawEllipse(0, 0, 2 * BALL_RADIUS, 2 * BALL_RADIUS);
}

void Object::PaintLine(QPainter* painter)
{
    QPen pen;
    pen.setWidth(0);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawRect(0, 0, RAIL_WIDTH, 4);
}

void Object::SetRailPos(void)
{
    height = -WINDOW_HEIGHT / 2;
    switch (level) {
    case 2:
    case 1:
        startx = STARTX_OF_RAIL[0][static_cast<unsigned int>(sign)];
        break;
    case 4:
    case 3:
        startx = STARTX_OF_RAIL[2][static_cast<unsigned int>(sign)];
        break;
    case 5:
        startx = STARTX_OF_RAIL[4][static_cast<unsigned int>(sign)];
        break;
    }
}

void Object::SetBallPos(void)
{
    height = -WINDOW_HEIGHT / 2;
    switch (level) {
    case 2:
    case 1:
        startx = STARTX_OF_RAIL[0][static_cast<unsigned int>(sign)] + RAIL_WIDTH / 2 - BALL_RADIUS;
        break;
    case 4:
    case 3:
        startx = STARTX_OF_RAIL[2][static_cast<unsigned int>(sign)] + RAIL_WIDTH / 2 - BALL_RADIUS;
        break;
    case 5:
        startx = STARTX_OF_RAIL[4][static_cast<unsigned int>(sign)] + RAIL_WIDTH / 2 - BALL_RADIUS;
        break;
    }
}

void Object::SetLinePos(void)
{
    height = LINE_HEIGHT;
    switch (level) {
    case 2:
    case 1:
        startx = STARTX_OF_RAIL[0][static_cast<unsigned int>(sign)];
        break;
    case 4:
    case 3:
        startx = STARTX_OF_RAIL[2][static_cast<unsigned int>(sign)];
        break;
    case 5:
        startx = STARTX_OF_RAIL[4][static_cast<unsigned int>(sign)];
        break;
    }
}

ObjectType Object::TypeInfo() { return type; }
