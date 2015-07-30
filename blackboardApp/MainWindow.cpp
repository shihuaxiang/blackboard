#include <QActionGroup>
#include <QDebug>
#include <QSignalMapper>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    createActionGroup();
    createTestAction();

    //this->setGeometry(100,100,1282,778);
	this->setGeometry(100, 100, 300, 200);

    bbView = new BbView(this,1280,720,3);
    this->setCentralWidget(bbView);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::createTestAction()
{
    {
        QAction* tempAction = new QAction("Add", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    }

    {
        QAction* tempAction = new QAction("Print", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotPrint()));
    }

    {
        QAction* tempAction = new QAction("1280", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotSize1280X720()));
    }

    {
        QAction* tempAction = new QAction("800", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotSize800X600()));
    }

    {
        QAction* tempAction = new QAction("600", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotSize600X600()));
    }

    {
        QAction* tempAction = new QAction("zoomin", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotZoomin()));
    }

    {
        QAction* tempAction = new QAction("zoomout", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotZoomout()));
    }

    QSignalMapper *signalMapper = new QSignalMapper(this);

    for (int i = 0; i < 3; i++)
    {
        QString text = QString("test%1").arg(i);

        QAction* actionTest = new QAction(this);
        actionTest->setText(text);
        mainToolBar->addAction(actionTest);

        connect(actionTest, SIGNAL(triggered()), signalMapper, SLOT(map()));
        signalMapper->setMapping(actionTest, i);
    }

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(slotTest(int)));
}

void MainWindow::createActionGroup()
{
    {
        actionPen = new QAction(this);
        actionPen->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/tool_pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPen->setIcon(icon);

        mainToolBar->addAction(actionPen);
        connect(actionPen, SIGNAL(triggered()), this, SLOT(on_actionPen_triggered()));
    }

    {
        actionArrow = new QAction(this);
        actionArrow->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/tool_arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionArrow->setIcon(icon);

        mainToolBar->addAction(actionArrow);
        connect(actionArrow, SIGNAL(triggered()), this, SLOT(on_actionArrow_triggered()));
    }

    {
        actionPoint = new QAction("P",this);
        actionPoint->setCheckable(true);

        mainToolBar->addAction(actionPoint);
        connect(actionPoint, SIGNAL(triggered()), this, SLOT(on_actionPoint_triggered()));
    }

    actionGroup = new QActionGroup(this);
    actionGroup->addAction(actionPen);
    actionGroup->addAction(actionArrow);
    actionGroup->addAction(actionPoint);
    actionArrow->setChecked(true);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "MainWindow Size:" << this->size();

    QMainWindow::resizeEvent(event);
}

void MainWindow::on_actionPen_triggered()
{
    if(actionPen->isChecked())
        bbView->setMode(BbView::OperateMode::DrawMode);
}

void MainWindow::on_actionArrow_triggered()
{
    if(actionArrow->isChecked())
        bbView->setMode(BbView::OperateMode::SelectMode);
}

void MainWindow::on_actionPoint_triggered()
{
    if (actionPoint->isChecked())
        bbView->setMode(BbView::OperateMode::PointMode);
}

void MainWindow::slotSize1280X720()
{
    QRect theRect = bbView->contentsRect();

    int dw = 1280 - theRect.width();
    int dh = 720 - theRect.height();

    this->resize(width()+dw,height()+dh);
}

void MainWindow::slotSize800X600()
{
    QRect theRect = bbView->contentsRect();

    int dw = 800 - theRect.width();
    int dh = 600 - theRect.height();

    this->resize(width() + dw, height() + dh);
}

void MainWindow::slotSize600X600()
{
    QRect theRect = bbView->contentsRect();

    int dw = 600 - theRect.width();
    int dh = 600 - theRect.height();

    this->resize(width() + dw, height() + dh);
}

void MainWindow::slotZoomin()
{
    bbView->scale(2, 2);
}

void MainWindow::slotZoomout()
{
    bbView->scale(0.5, 0.5);
}

void MainWindow::slotPrint()
{
    //qDebug() << "MainWindow rect:" << this->rect();
    //qDebug() << "bbView rect:" << bbView->rect();
    //qDebug() << "bbView contentsRect:" << bbView->contentsRect();

    bbView->print();
}

void MainWindow::slotAdd()
{
    bbView->getScene()->testAddRect();
    bbView->getScene()->testAddText();
    bbView->getScene()->testAddPixmap();
}

void MainWindow::slotTest(int index)
{
    qDebug() << index;

	switch (index)
	{
	case 0:
		bbView->turnNextPage();
		break;

	case 1:
		bbView->turnPrevPage();
		break;

	case 2:
		bbView->replay();
		break;

	default:
		break;
	}
}
