#include <QDebug>

#include "BbView.h"
#include "BbScene.h"
#include "BbLine.h"
#include "BbUtil.h"

BbView::BbView(QWidget *parent, double w, double h, int pageNum)
    : QGraphicsView(parent),
      mode(BbView::OperateMode::SelectMode),
      _pageIndex(0),
      _pageNum(pageNum),
      _fixedRatio(0),
      line(NULL),
      _drawTimer(NULL)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    BbScene* theScene = new BbScene();
    this->setScene(theScene);

    setViewRect();
}

BbView::~BbView()
{

}

bool BbView::isFixedRatio()
{
    return _fixedRatio;
}

void BbView::setFixedRatio(bool fixedRatio)
{
    _fixedRatio = fixedRatio;
}

BbView::OperateMode BbView::getMode()
{
    return mode;
}

void BbView::setMode(BbView::OperateMode operateMode)
{
    mode = operateMode;
}

BbScene* BbView::getScene()
{
    return dynamic_cast<BbScene*>(scene());
}

void BbView::mousePressEvent(QMouseEvent *event)
{
    QPointF point;
    point = mapToScene(event->pos());
    //qDebug() << "BbView::mousePressEvent eventPos: " << event->pos() << "scenePoint:" << point;

    if(getMode() == OperateMode::DrawMode)
    {
        if (event->button() == Qt::LeftButton)
        {
            line = new BbLine(getScene());
            line->startDraw(point);

            return;
        }
    }
    else if(getMode() == OperateMode::PointMode)
    {
        qDebug() << "BbView::mousePressEvent eventPos: " << event->pos() << "scenePoint:" << point;
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

void BbView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF point;
    point = mapToScene(event->pos());
    //qDebug() << "BbView::mouseMoveEvent eventPos: " << event->pos() << "scenePoint:" << point;

    if(getMode() == OperateMode::DrawMode)
    {
        if( (event->buttons()&Qt::LeftButton))
        {
            line->drawing(point);

            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void BbView::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF point;
    point = mapToScene(event->pos());
    //qDebug() << "BbView::mouseReleaseEvent eventPos: " << event->pos() << "scenePoint:" << point;

    if(getMode() == OperateMode::DrawMode)
    {
        if (event->button() == Qt::LeftButton)
        {
            line->finishDraw(point);

            return;
        }
    }
    else if(getMode() == OperateMode::PointMode)
    {
        qDebug() << "BbView::mouseReleaseEvent eventPos: " << event->pos() << "scenePoint:" << point;
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

void BbView::paintEvent(QPaintEvent *event)
{ 
    QGraphicsView::paintEvent(event);
}

void BbView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    QRectF viewRect = this->sceneRect();
    double width = event->size().width();
    double xscale = width / viewRect.width();

    double height = event->size().height();
    double yscale = height / viewRect.height();

    this->resetMatrix();
    this->scale(xscale, yscale);
}

void BbView::drawBackground(QPainter* painter,const QRectF& rect)
{	
    QGraphicsView::drawBackground(painter,rect);

    //QPen thePen = BbUtil::createPen(10, Qt::yellow);
    //painter->setPen(thePen);

    //QRectF theRect = rect;
    //theRect.adjust(5, 5, -5, -5);
    //painter->drawRect(theRect);


}

void BbView::turnNextPage()
{
    _pageIndex++;

    if (_pageIndex >= _pageNum)
        _pageIndex = 0;

    setViewRect();
}

void BbView::turnPrevPage()
{
    _pageIndex--;

    if (_pageIndex < 0)
        _pageIndex = _pageNum - 1;

    setViewRect();
}

void BbView::setViewRect()
{
    QRectF viewRect = getScene()->getPageRect(_pageIndex);

    qDebug() << "\n\nBbView::setViewRect " << viewRect;

    this->setSceneRect(viewRect);
}

void BbView::print()
{
    qDebug() << "BbView sceneRect" << this->sceneRect();
    qDebug() << "theScene sceneRect" << this->scene()->sceneRect();
}

void BbView::replay()
{
    if (_drawTimer == NULL)
    {
        _drawTimer = new QTimer(this);
        connect(_drawTimer, SIGNAL(timeout()), this, SLOT(drawRecvPoint()));

		_drawPoint = mapToScene(this->width() / 2, this->height() / 2);

        line = new BbLine(getScene());
		line->startDraw(_drawPoint);

        getScene()->startDrawingCursor();

        _drawTimer->start(300);
    }
    else
    {
        _drawTimer->stop();
        killTimer(_drawTimer->timerId());
        delete _drawTimer;
		_drawTimer = NULL;
    
        getScene()->stopDrawingCursor();
		
		_drawPoint = mapToScene(this->width() / 2, this->height() / 2);
		line->finishDraw(_drawPoint);
    }
}

void BbView::drawRecvPoint()
{
	int x = -50 + qrand() % 100;// this->width();
	int y = -50 + qrand() % 100;// this->height();

	_drawPoint += QPointF(x,y);
    getScene()->moveDrawingCursor(_drawPoint);
	line->drawing(_drawPoint);
}
