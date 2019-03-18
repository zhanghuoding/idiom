#include "idiom.h"
#include <iostream>


Idiom::Idiom()
{
    qDebug()<<"idiom对象正在构造。\t现在是Idiom::Idiom()";
    header.comFlag=false;
    header.length=0;
    header.next=NULL;
    tailNode=NULL;
}
Idiom::~Idiom()
{
    qDebug()<<"idiom对象正在析构。\t现在是Idiom::~Idiom()";
    linkNode *p=NULL,*pt=header.next;
    while(pt)
    {
        p=pt;
        pt=pt->next;
        if(p->code)
            delete p->code;
        if(p->value)
            delete p->value;
        delete p;
    }
}
linkHead *Idiom::getHeader()
{
    return &header;
}

void Idiom::addItem(linkNode *node)
{
    QMutexLocker locker(&mutex);
    if(header.length==0)
    {
        header.next=node;
    }else
    {
        tailNode->next=node;
    }
    node->next=NULL;
    tailNode=node;
    header.length++;
}
linkNode Idiom::getItemAt(int index)
{
    int k=header.length;
    linkNode *p=header.next;
    if(index<0 || index>=k)
        return linkNode{-1,NULL,NULL,NULL};
    for(int i=0;i<index && i<k && p->next;i++)
        p=p->next;
    return *p;
}

void Idiom::complete()
{
    QMutexLocker locker(&mutex);
    header.comFlag=true;
}
bool Idiom::isComplete()
{
    return header.comFlag;
}
