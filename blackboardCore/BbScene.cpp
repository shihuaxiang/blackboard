#include <QDebug>
#include <QGraphicsRectItem>
#include "BbScene.h"
#include "BbUtil.h"

BbScene::BbScene(double w, double h, int pageNum, QObject *parent)
    : QGraphicsScene(parent),
    _pixmapItem(NULL)
{	
	_width = w;
	_height = h * pageNum;

    QRectF theRect(-w / 2, -h / 2, w, h);
    setSceneRect(theRect);
}

BbScene::~BbScene()
{

}

double BbScene::getPageWidth()
{
	return _width;
}

double BbScene::getPageHeight()
{
	return _height;
}

QRectF BbScene::getPageRect(int pageIndex)
{
	QPointF pt = sceneRect().topLeft();

	return QRectF(pt.rx(), 
		pt.y() + pageIndex * getPageHeight(),
		getPageWidth(), 
		getPageHeight());
}

void BbScene::testAddRect()
{
	QGraphicsRectItem* item = new QGraphicsRectItem;

	QPen thePen = BbUtil::createPen(5, Qt::red);
	item->setPen(thePen);

	double ww = getPageWidth() - 20;
	double hh = getPageHeight() - 20;
	QRectF theRect(-ww / 2, -hh / 2, ww, hh);
	item->setRect(theRect);

	addItem(item);	
}

void BbScene::testAddText()
{
	QGraphicsTextItem* item = new QGraphicsTextItem;

	QFont font = QFont("Microsoft YaHei");
	font.setPointSize(20);
	item->setFont(font);
	item->setPlainText("I am a clever mouse");
	item->setPos(0, 0);

	addItem(item);
}

void BbScene::testAddPixmap()
{
	QPixmap* pixmap = new QPixmap;
	
    bool b = pixmap->load(":/images/cur_g.png");

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
	item->setPixmap(*pixmap);
	item->setPos(100, 100);

	addItem(item);
}

void BbScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void BbScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void BbScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void BbScene::drawBackground(QPainter* painter, const QRectF& rect)
{
	//qDebug() << "\n BbScene::drawBackground " << rect;

	QGraphicsScene::drawBackground(painter, rect);
}

void BbScene::startDrawingCursor()
{
    if (_pixmapItem == NULL)
    {
        QPixmap* pixmap = new QPixmap(":/images/arrowcursor.png");
        _pixmapItem = new QGraphicsPixmapItem;
        _pixmapItem->setPixmap(*pixmap);
    }

    addItem(_pixmapItem);
}

void BbScene::moveDrawingCursor(QPointF& point)
{
    _pixmapItem->setPos(point);
}

void BbScene::stopDrawingCursor()
{
    removeItem(_pixmapItem);
}
