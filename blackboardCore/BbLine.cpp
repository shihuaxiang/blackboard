#include "BbLine.h"
#include "BbUtil.h"

BbLine::BbLine(BbScene* scene, QGraphicsItem *parent)
    : QGraphicsPathItem(parent),_scene(scene)
{
    _lineWidth = 5;
    _lineColor = Qt::green;

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

BbLine::~BbLine()
{

}

void BbLine::startDraw(QPointF& point)
{
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(this);
    _scene->addItem(item);

    QPen pen = BbUtil::createPen(_lineWidth,_lineColor);
    this->setPen(pen);

    QPainterPath path;
    path.moveTo(point);
    path.lineTo(point);
    setPath(path);
}

void BbLine::drawing(QPointF& point)
{
    QPainterPath path = this->path();
    path.lineTo(point);
    setPath(path);
}

void BbLine::finishDraw(QPointF& point)
{
    QPainterPath path = this->path();
    path.lineTo(point);
    setPath(path);
}
