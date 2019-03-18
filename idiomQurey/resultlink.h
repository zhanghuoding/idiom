#ifndef RESULTLINK_H
#define RESULTLINK_H

#include "type.h"
#include <QObject>
#include <QMutex>

class ResultLink : public QObject
{
    Q_OBJECT
public:
    explicit ResultLink(QObject *parent = 0);
    ~ResultLink();
    void update();

    ptrHead *getHeader();
    void addItem(ptrLink *node);
    ptrLink *getItemAt(int index);
    ptrLink *getNextItem();
    ptrLink *getLastItem();
    ptrLink *getCurrentItem();
    ptrLink *getDifferItem(int flag);
    ptrLink *getItemAccordCode1(char c,short loc);
    int currentIndex();
    void complete();
    bool isComplete();
private:
    ptrHead header;
    ptrLink *tailNode;//链表最后一个节点的指针
    QMutex mutex;//线程互斥变量
    int currentItIn;
    bool compare(charPtr s1,charPtr s2,int flag);

signals:

public slots:
};

#endif // RESULTLINK_H
