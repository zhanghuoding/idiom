#include "resultlink.h"



ResultLink::ResultLink(QObject *parent) : QObject(parent)
{
    qDebug()<<"ResultLink对象正在构造。\t现在是ResultLink::ResultLink(QObject *parent) : QObject(parent)";
    header.comFlag=false;
    header.length=0;
    header.next=NULL;
    tailNode=NULL;
    currentItIn=0;
}
ResultLink::~ResultLink()
{
    qDebug()<<"ResultLink对象正在析构。\t现在是ResultLink::~ResultLink()";
    ptrLink *p=NULL,*pt=header.next;
    header.next=NULL;
    while(pt)
    {
        p=pt;
        pt=pt->next;
        delete p;
    }
}
void ResultLink::update()
{
    qDebug()<<"ResultLink对象正在更新。\t现在是void ResultLink::update()";
    ptrLink *p=NULL,*pt=header.next;
    while(pt)
    {
        p=pt;
        pt=pt->next;
        delete p;
    }
    header.comFlag=false;
    header.length=0;
    header.next=NULL;
    tailNode=NULL;
    currentItIn=0;
}

ptrHead *ResultLink::getHeader()
{
    return &header;
}

void ResultLink::addItem(ptrLink *node)
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
ptrLink *ResultLink::getItemAt(int index)
{
    qDebug()<<"运行到 1"<<"\t现在是ptrLink *ResultLink::getItemAt(int index)";
    int k=header.length;
    ptrLink *p=header.next;
    if(index<0 || index>=k)
    {
        qDebug()<<"运行到 2"<<"\tindex的值为 "<<index<<"\theader.length的值为 "<<k<<"\tcurrentItIn的值为 "<<currentItIn<<"\t现在是ptrLink *ResultLink::getItemAt(int index)";
        return NULL;
    }
    for(int i=0;i<index && i<k && p->next;i++)
        p=p->next;
    return p;
}

void ResultLink::complete()
{
    QMutexLocker locker(&mutex);
    header.comFlag=true;
}
bool ResultLink::isComplete()
{
    return header.comFlag;
}
ptrLink *ResultLink::getNextItem()
{
    int k=header.length;
    ptrLink *p=header.next;
    if(currentItIn<0 || currentItIn>=k)
        return NULL;
    for(int i=0;i<currentItIn && i<k && p->next;i++)
        p=p->next;
    qDebug()<<"运行到 1"<<"\t当前的currentItIn值是"<<currentItIn<<"\t现在是ptrLink *ResultLink::getNextItem()";
    if(p && p->next)
        currentItIn++;
    qDebug()<<"运行到 2"<<"\t当前的currentItIn值是"<<currentItIn<<"\t现在是ptrLink *ResultLink::getNextItem()";
    return p;
}
ptrLink *ResultLink::getLastItem()
{
    int k=header.length;
    ptrLink *p=header.next;
    if(currentItIn<0 || currentItIn>=k)
        return NULL;
    if(currentItIn>0)
        currentItIn--;
    for(int i=0;i<currentItIn && i<k && p->next;i++)
        p=p->next;
    return p;
}
ptrLink *ResultLink::getCurrentItem()
{
    int k=header.length;
    ptrLink *p=header.next;
    if(currentItIn<0 || currentItIn>=k)
        return NULL;
    for(int i=0;i<currentItIn && i<k && p->next;i++)
        p=p->next;
    return p;
}
ptrLink *ResultLink::getDifferItem(int flag)
{
    ptrLink *p1=NULL,*p2=NULL;
    charPtr s1=NULL, s2=NULL;
    p1=getItemAt(currentItIn-1);

    qDebug()<<"运行到 1"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";

    if(!p1 || !p1->node || !p1->node->value)
    {
        qDebug()<<"运行到 2"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
        if(!p1)
            qDebug()<<"p1为空\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
        else if(!p1->node)
            qDebug()<<"p1->node为空\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
        else if(!p1->node->value)
            qDebug()<<"p1->node->value为空\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
        return NULL;
    }
    s1=p1->node->value;
    for(int i=0; ;i++)
    {
        qDebug()<<"运行到 3"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
        p2=getItemAt(currentItIn+i);
        if(!p2 || !p2->node || !p2->node->value)
        {
            qDebug()<<"运行到 4"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
            return NULL;
        }
        s2=p2->node->value;
        for(int j=0;j<flag;j++)
        {
            qDebug()<<"运行到 5"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
            if(!compare(s1,s2,j))
            {
                qDebug()<<"运行到 6"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
                return NULL;
            }
        }
        if(!compare(s1,s2,flag))
        {
            qDebug()<<"运行到 7"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
            currentItIn+=i;
            break;
        }
    }
    qDebug()<<"运行到 8"<<"\t现在是ptrLink *ResultLink::getDifferItem(int flag)";
    return getNextItem();
}
ptrLink *ResultLink::getItemAccordCode1(char c, short loc)
{
    if(loc<=0 || loc>2)
        return NULL;
    ptrLink *p1=NULL;
    charPtr s1=NULL;
    p1=getCurrentItem();
    if(!p1 || !p1->node)
    {
        return NULL;
    }
    s1=p1->node->code1;
    if(strlen(s1)<loc)
        return getNextItem();
    for(int i=0; ;i++)
    {
        if(!(c^s1[loc-1]))
        {
            currentItIn+=i;
            break;
        }
        p1=getItemAt(currentItIn+i+1);
        if(!p1 || !p1->node)
        {
            return NULL;
        }
        s1=p1->node->code1;
        if(strlen(s1)<loc)
            return getCurrentItem();
    }
    qDebug()<<"现在是ptrLink *ResultLink::getItemAccordCode1(char c, short loc)";
    return getNextItem();
}

bool ResultLink::compare(charPtr s1, charPtr s2, int flag)
{
    if(flag<0 || flag >3)
        return false;
    int num=strlen(s1)/4,index=0;
    for(int i=0;i<num;i++)
    {
        index=num*flag+i;
        if(s1[index]^s2[index])
            return false;
    }
    return true;
}

int ResultLink::currentIndex()
{
    return currentItIn;
}

