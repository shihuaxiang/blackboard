#include "BbUtil.h"

BbUtil::BbUtil(QObject *parent) : QObject(parent)
{

}

BbUtil::~BbUtil()
{

}

QPen BbUtil::createPen(int lineWidth,QColor lineColor)
{
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    //pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    return pen;
}
