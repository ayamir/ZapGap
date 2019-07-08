#include "score.h"

Score::Score(QWidget* parent) : QWidget{parent}
{
    iscore = 0;
    QStrscore = QString::number(iscore);
}


QRectF Score::boundingRect(void) const
{
    return QRectF(-3 * WORD_SIZE - 2, -2 * WORD_SIZE - 2, 6 * WORD_SIZE + 4, 4 * WORD_SIZE + 4);
}

void Score::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    pen.setWidth(WORD_SIZE);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setBrush(Qt::black);
    painter->setFont(QFont("Snap ITC", WORD_SIZE, QFont::Bold));              //字体
    painter->drawText(0, 0, 4 * WORD_SIZE, 2 * WORD_SIZE, false, QStrscore);
}
