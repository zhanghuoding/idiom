#ifndef IDIOM_H
#define IDIOM_H

#include "type.h"
#include <QMutex>
#include <QMutexLocker>

class Idiom
{
public:
    Idiom();
    ~Idiom();

    linkHead *getHeader();
    void addItem(linkNode *node);
    linkNode getItemAt(int index);
    void complete();
    bool isComplete();
private:
    linkHead header;
    linkNode *tailNode;//链表最后一个节点的指针
    QMutex mutex;//线程互斥变量

};

#endif // IDIOM_H
