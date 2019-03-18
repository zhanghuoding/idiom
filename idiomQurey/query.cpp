#include "query.h"

Query::Query(QObject *parent) : QObject(parent)
{
    currentThread=NULL;
}

void Query::doWork(void *link, char ah, int flag,QThread *thread)
{
    currentThread=thread;
    ptrLink *tmp=NULL;
    linkNode *pn=NULL,*lastPn=NULL;
    ptrLink *ps=NULL,*lastPs=NULL;
    if(flag==1)
    {//第一笔
        linkHead *header=(linkHead*)link;
        pn=header->next;
        if(!pn)
        {
            int i=2;
            while(!pn&&i)
            {
                if(currentThread)
                    currentThread->msleep(100);
                pn=header->next;
                i--;
            }
            if(!pn && !i)
            {
                idiom->complete();
                resLink1->complete();
                return;
            }
        }
        while(true)
        {
            lastPn=pn;
            if(!(pn->code[0]^ah))
            {
                tmp=new ptrLink{pn,NULL};
                resLink1->addItem(tmp);
                tmp=NULL;
            }
            pn=lastPn->next;
            if(!pn)
            {
                if(!idiom->isComplete())
                    while(!pn)
                    {
                        if(currentThread)
                            currentThread->msleep(100);
                        pn=lastPn->next;
                    }
                else if(idiom->isComplete())
                    break;
            }
        }
        resLink1->complete();
    }else if(flag==2)
    {//第二笔
        ptrHead *header=(ptrHead*)link;
        ps=header->next;
        if(!ps)
        {
            int i=2;
            while(!ps && i)
            {
                if(currentThread)
                    currentThread->msleep(100);
                ps=header->next;
                i--;
            }
            if(!pn && !i)
            {
                resLink1->complete();
                resLink2->complete();
                return;
            }
        }
        while(true)
        {
            lastPs=ps;
            if(!(ps->node->code[1]^ah))
            {
                tmp=new ptrLink{ps->node,NULL};
                resLink2->addItem(tmp);
                tmp=NULL;
            }
            ps=lastPs->next;
            if(!ps)
            {
                if(!idiom->isComplete())
                    while(!ps)
                    {
                        if(currentThread)
                            currentThread->msleep(100);
                        ps=lastPs->next;
                    }
                else if(idiom->isComplete())
                    break;
            }
        }
        resLink2->complete();
    }else if(flag==3)
    {//第三笔
        ptrHead *header=(ptrHead*)link;
        ps=header->next;
        if(!ps)
        {
            int i=0;
            while(!ps && i)
            {
                if(currentThread)
                    currentThread->msleep(100);
                ps=header->next;
                i--;
            }
            if(!pn && !i)
            {
                resLink2->complete();
                resLink3->complete();
                return;
            }
        }
        while(true)
        {
            lastPs=ps;
            if(!(ps->node->code[2]^ah))
            {
                tmp=new ptrLink{ps->node,NULL};
                resLink3->addItem(tmp);
                tmp=NULL;
            }
            ps=lastPs->next;
            if(!ps)
            {
                if(!idiom->isComplete())
                    while(!ps)
                    {
                        if(currentThread)
                            currentThread->msleep(100);
                        ps=lastPs->next;
                    }
                else if(idiom->isComplete())
                    break;
            }
        }
        resLink3->complete();
    }else if(flag==4)
    {//第四笔
        ptrHead *header=(ptrHead*)link;
        ps=header->next;
        if(!ps)
        {
            int i=2;
            while(!ps && i)
            {
                if(currentThread)
                    currentThread->msleep(100);
                ps=header->next;
                i--;
            }
            if(!pn && !i)
            {
                resLink3->complete();
                resLink4->complete();
                return;
            }
        }
        while(true)
        {
            lastPs=ps;
            if(!(ps->node->code[3]^ah))
            {
                tmp=new ptrLink{ps->node,NULL};
                resLink4->addItem(tmp);
                tmp=NULL;
            }
            ps=lastPs->next;
            if(!ps)
            {
                if(!idiom->isComplete())
                    while(!ps)
                    {
                        if(currentThread)
                            currentThread->msleep(100);
                        ps=lastPs->next;
                    }
                else if(idiom->isComplete())
                    break;
            }
        }
        resLink4->complete();
    }
}
