#include "BbLine.h"
#include "BbUtil.h"

//interpolated point on line AB
//point position on line: A --- P1 ------ P2 --- B
//adjacent point distance:   k      1-2k      k
void lineInterpolate(const QPointF& pointA, const QPointF& pointB,
    QPointF& pointP1, QPointF& pointP2)
{
    const int k = 0.4;

    double deltaX = pointB.x() - pointA.x();
    double deltaY = pointB.y() - pointA.y();

    pointP1.setX(deltaX * k + pointA.x());
    pointP1.setY(deltaY * k + pointA.y());

    pointP2.setX(deltaX * (1 - k) + pointA.x());
    pointP2.setY(deltaY * (1 - k) + pointA.y());
}

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

void BbLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    QGraphicsPathItem::paint(painter, option, widget);
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

    m_points.push_back(point);
}

void BbLine::drawing(QPointF& point)
{
    if (m_drawMode == 0)
    {
        QPainterPath path = this->path();
        path.lineTo(point);
        setPath(path);

        m_points.push_back(point);
    }
    else if (m_drawMode == 1)
    {
        m_points.push_back(point);

        QPainterPath path = this->path();
        int n = m_points.size();
        QPointF lastPoint = m_points[n - 2];
        QPointF pointP1, pointP2;
        if (n == 2)
        {
            lineInterpolate(lastPoint, point, pointP1, pointP2);
            path.lineTo(pointP2);
            setPath(path);
        }
        else
        {
            lineInterpolate(lastPoint, point, pointP1, pointP2);
            path.quadTo(lastPoint, pointP1);
            path.lineTo(pointP2);
            setPath(path);
        }
    }
}

void BbLine::finishDraw(QPointF& point)
{
    if (m_drawMode == 0)
    {
        QPainterPath path = this->path();
        path.lineTo(point);
        setPath(path);
    }
    else if (m_drawMode == 1)
    {
        m_points.push_back(point);

        QPainterPath path = this->path();
        int n = m_points.size();
        QPointF lastPoint = m_points[n - 2];
        QPointF pointP1, pointP2;
        lineInterpolate(lastPoint, point, pointP1, pointP2);
        path.quadTo(lastPoint, pointP1);
        path.lineTo(point);
        setPath(path);
    }

    m_finished = true;
}
