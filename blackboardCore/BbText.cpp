#include <QPainterPath>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QTextCursor>
#include <QBuffer>
#include <QTextDocument>
#include <QStyleOptionGraphicsItem>
#include <QTimer>
#include <QDateTime>
#include <QApplication>
#include <QClipboard>
#include <QGraphicsSceneMouseEvent>
#include <QThread>

#include "BbText.h"
#include "BbUtil.h"

BbText::BbText(BbScene* scene, QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
    , m_scene(scene)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemAcceptsInputMethod, true);
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption, true);

    QFont font = QFont("Microsoft YaHei");
    font.setPixelSize(m_fontPixelSize);

    this->setFont(font);
    this->setDefaultTextColor(m_textColor);
}

BbText::~BbText()
{

}

void BbText::startDraw(QPointF& point)
{
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(this);
    m_scene->addItem(item);

    startEdit();
}

void BbText::drawing(QPointF& point)
{
    if (m_textContent != this->toPlainText())
    {
        m_textContent = this->toPlainText();
    }
}

void BbText::finishDraw(QPointF& point)
{
    stopEdit();
}

void BbText::startEdit()
{
    //qDebug() << __FUNCTION__ << this->toPlainText() << this->getId();

    if (!m_isEditing)
    {
        setTextInteractionFlags(Qt::TextEditorInteraction);

        QTextCursor c = textCursor();
        c.movePosition(QTextCursor::EndOfLine);
        setTextCursor(c);

        setFocus(Qt::MouseFocusReason);

        m_isEditing = true;
    }
}

void BbText::stopEdit()
{
    if (m_isEditing)
    {
        //qDebug() << __FUNCTION__ << this->toPlainText() << this->getId();

        m_isEditing = false;
        setTextInteractionFlags(Qt::NoTextInteraction);

        if (this->toPlainText().isEmpty())
        {
            QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(this);
            this->m_scene->removeItem(item);
        }
        else
        {
            // this code is needed to remove un-confirmed charactors
            QString text = this->toPlainText();
            this->setPlainText(text);
        }

        //QTextCursor cursor = this->textCursor();
        //cursor.clearSelection();
        //this->setTextCursor(cursor);
        this->setSelected(false);
    }
}

void BbText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    //qDebug() << __FUNCTION__ << this->toPlainText();

    startEdit();

    //QGraphicsTextItem::mouseDoubleClickEvent(event);  //fix bug: infinite loop in mini-blackboard
}


