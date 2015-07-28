#ifndef BBUTIL_H
#define BBUTIL_H

#include <QObject>
#include <QPen>

class BbUtil : public QObject
{
    Q_OBJECT
public:
    explicit BbUtil(QObject *parent = 0);
    ~BbUtil();

    static QPen createPen(int lineWidth,QColor lineColor);

signals:

public slots:

};

#endif // BBUTIL_H
