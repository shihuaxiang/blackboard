#ifndef BBVIEW_H
#define BBVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsPixmapItem>

#include "blackboardcore_global.h"

class BbScene;
class BbLine;
class BbText;

class BLACKBOARDCORESHARED_EXPORT BbView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BbView(QWidget *parent = 0, double w = 1280, double h = 720, int pageNum = 1);
    ~BbView();
    bool isFixedRatio();
    void setFixedRatio(bool fixedRatio);

    enum OperateMode   //模式
    {
        DrawMode,     //绘制模式
        SelectMode,   //选择模式
        ViewMode,     //浏览模式
        TextMode,
        PointMode
    };

    BbScene* getScene();
    BbView::OperateMode getMode();
    void setMode(BbView::OperateMode operateMode);
    void print();
    void replay();

    void turnNextPage();
    void turnPrevPage();
    void setViewRect();

    void changeCurveMode(int curveMode);
    int getCurveMode();

signals:

public slots :
    void drawRecvPoint();

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void drawBackground(QPainter* painter, const QRectF& rect);

private:
    BbView::OperateMode mode;

    BbLine* line;
    BbText* textItem;

    int		_pageIndex;
    int		_pageNum;
    bool	_fixedRatio;

    QTimer* _drawTimer;
	QPointF _drawPoint;

    // 0 -- lineto
    // 1 -- quadTo
    // 2 -- cubicTo
    int     _curveMode = 0;
};

#endif // BBVIEW_H
