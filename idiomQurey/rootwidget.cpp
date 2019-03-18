#include "rootwidget.h"
#include "Singleton/singleton.h"
#include "keyboard.h"
#include "tool.h"
#include "readexcel.h"

#include <QRect>

//#include <control.h>

RootWidget::RootWidget(QWidget *parent) : QWidget(parent)
{
    rootLayout=new QVBoxLayout(this);
    currentLabel=0;
    readExceler=new ReadExcel;
    keyBoardReset=true;//默认情况下允许键盘重置
    codeIndex=0;

    qu1=new Query;
    qu2=new Query;
    qu3=new Query;
    qu4=new Query;

    strokesWidget=new QWidget(this);
    strokesLayout=new QHBoxLayout(strokesWidget);//点击笔画之后,显示四个笔画的横向布局管理器
    strokesWidget->setGeometry(Tool::rect(10,120,160,40));
    strokesWidget->setStyleSheet(QString("QWidget{border: 1px solid  #000000}"));

    showArea=new ShowArea(this);//显示搜索到的成语的标签
    showArea->setText("成语查询");
    QString idiomLabelStyle("QLabel{font-family:'Century Schoolbook';font-size:");
    idiomLabelStyle.append(QString::number(Tool::fontSize(idiomLabelFontSize)).toLatin1().data()).append("px;color:#000000;background-color:#ffffff;border: 4px solid  #000000}");
    showArea->setStyShe(idiomLabelStyle);
    showArea->setGeometry(Tool::rect(10,30,160,40));
    connect(showArea,SIGNAL(clickedNum(int)),this,SLOT(nextDifferItem(int)));

    for(int i=0;i<4;i++)
    {
        labels[i]=new QLabel;
        strokesLayout->addWidget(labels[i]);
    }

    Singleton<KeyBoard>::instance().setParent(this);
    Singleton<KeyBoard>::instance().setGeometry(Tool::rect(10,170,160,128));

    connect(&Singleton<KeyBoard>::instance(),SIGNAL(keyWasPressed(key_type)),this,SLOT(whitchKeyWasPrassed(key_type)));

    readExceler->moveToThread(&readExcelThread);readExceler->doWork();
    //connect(&readExcelThread, SIGNAL(finished()), readExceler, SLOT(deleteLater()));
    //connect(this, SIGNAL(operate()), readExceler, SLOT(doWork()));
    readExcelThread.start();
    emit operate();

    if(!qu1)
        qu1=new Query;
    qu1->moveToThread(&queryThread1);
    connect(&queryThread1,SIGNAL(finished()), qu1, SLOT(deleteLater()));
    connect(this,SIGNAL(operate1(void*,char,int,QThread*)),qu1,SLOT(doWork(void*,char,int,QThread*)));

    if(!qu2)
        qu2=new Query;
    qu2->moveToThread(&queryThread2);
    connect(&queryThread2,SIGNAL(finished()), qu2, SLOT(deleteLater()));
    connect(this,SIGNAL(operate2(void*,char,int,QThread*)),qu2,SLOT(doWork(void*,char,int,QThread*)));

    if(!qu3)
        qu3=new Query;
    qu3->moveToThread(&queryThread3);
    connect(&queryThread3,SIGNAL(finished()), qu3, SLOT(deleteLater()));
    connect(this,SIGNAL(operate3(void*,char,int,QThread*)),qu3,SLOT(doWork(void*,char,int,QThread*)));

    if(!qu4)
        qu4=new Query;
    qu4->moveToThread(&queryThread4);
    connect(&queryThread4,SIGNAL(finished()), qu4, SLOT(deleteLater()));
    connect(this,SIGNAL(operate4(void*,char,int,QThread*)),qu4,SLOT(doWork(void*,char,int,QThread*)));
}
RootWidget::~RootWidget()
{
    if(strokesLayout)
        delete strokesLayout;
    if(strokesWidget)
        delete strokesWidget;
    if(showArea)
        delete showArea;
    for(int i=0;i<4;i++)
        if(labels[i])
            delete labels[i];
}
void RootWidget::whitchKeyWasPrassed(key_type value)
{
    if(value==8)
    {//退格键
        if(currentLabel<=0)
            return;
        //labels[--currentLabel]->setIcon(QPixmap(QString("")));
        if(currentLabel==1)
        {
            stopQuery1();
        }else if(currentLabel==2)
        {
            stopQuery2();
        }else if(currentLabel==3)
        {
            stopQuery3();
        }else if(currentLabel==4)
        {
            stopQuery4();
        }
        labels[--currentLabel]->setStyleSheet(QString("QLabel{border-image: url()}"));
        keyBoardReset=true;
        codeIndex=0;
    }else if(value==13)
    {//回车键
        while(currentLabel)
        {
            labels[--currentLabel]->setStyleSheet(QString("QLabel{border-image: url()}"));
        }
        resLink1->update();
        resLink2->update();
        resLink3->update();
        resLink4->update();
        showArea->setText("成语查询");
        keyBoardReset=true;
        codeIndex=0;
    }else
    {
        if(currentLabel<0)
            return;

        repeat:
        ptrLink *temppp=NULL;
        if(!keyBoardReset && currentLabel==4)
        {
            temppp=resLink4->getItemAccordCode1(value,++codeIndex);

            qDebug()<<"resLink4是否创建完毕"<<resLink4->isComplete()<<"\t表长是"<<resLink4->getHeader()->length<<"\t现在是void RootWidget::whitchKeyWasPrassed(key_type value)";

            if(temppp && temppp->node)
            {
                showArea->setText(temppp->node->value);
            }
            if(!temppp)
                codeIndex--;
            return;
        }
        switch (currentLabel)
        {
        case 0:
            queryThread1.start();
            emit operate1(idiom->getHeader(),value,1,&queryThread1);
            while(!(temppp=resLink1->getNextItem()) && !resLink1->isComplete())
            {
                for(int i=0;i<10000;i++);
            }
            break;
        case 1:
            queryThread2.start();
            emit operate2(resLink1->getHeader(),value,2,&queryThread2);
            while(!(temppp=resLink2->getNextItem()) && !resLink2->isComplete())
            {
                for(int i=0;i<10000;i++);
            }
            break;
        case 2:
            queryThread3.start();
            emit operate3(resLink2->getHeader(),value,3,&queryThread3);
            while(!(temppp=resLink3->getNextItem()) && !resLink3->isComplete())
            {
                for(int i=0;i<10000;i++);
            }
            break;
        case 3:
            queryThread4.start();
            emit operate4(resLink3->getHeader(),value,4,&queryThread4);
            while(!(temppp=resLink4->getNextItem()) && !resLink4->isComplete())
            {
                for(int i=0;i<10000;i++);
            }
            break;
        case 4:
            while(currentLabel)
            {
                labels[--currentLabel]->setStyleSheet(QString("QLabel{border-image: url()}"));
            }
            resLink1->update();
            resLink2->update();
            resLink3->update();
            resLink4->update();
            goto repeat;
            break;

        default:
            temppp=NULL;
            break;
        }

        labels[currentLabel]->setStyleSheet(QString("QLabel{border-image: url(").append(getImagePath(value)).append(")}"));

        if(temppp && temppp->node)
        {
            showArea->setText(temppp->node->value);
        }else
        {
            showArea->setText("没有成语");
        }

        currentLabel++;
    }
}
QString RootWidget::getImagePath(key_type t)
{
    char a[2]={t,'\0'};
    QString str(picRootPath+QString("KeyBoard/").append(a).append(".png"));
    return str;
}
QString RootWidget::getIdiom(key_type *a)
{
    return QString("");
}
void RootWidget::reset()
{
    currentLabel=0;
    keyBoardReset=true;
    codeIndex=0;
}
void RootWidget::stopQuery1()
{
    resLink1->update();
    showArea->setText("成语查询");
}
void RootWidget::stopQuery2()
{
    resLink2->update();
    ptrLink *temppp=NULL;
    while(!(temppp=resLink1->getLastItem()) && !resLink1->isComplete())
    {
        for(int i=0;i<10000;i++);
    }
    if(temppp && temppp->node)
    {
        showArea->setText(temppp->node->value);
    }else
    {
        showArea->setText("没有成语");
    }
}

void RootWidget::stopQuery3()
{
    resLink3->update();
    ptrLink *temppp=NULL;
    while(!(temppp=resLink2->getLastItem()) && !resLink2->isComplete())
    {
        for(int i=0;i<10000;i++);
    }
    if(temppp && temppp->node)
    {
        showArea->setText(temppp->node->value);
    }else
    {
        showArea->setText("没有成语");
    }
}

void RootWidget::stopQuery4()
{
    resLink4->update();
    ptrLink *temppp=NULL;
    while(!(temppp=resLink3->getLastItem()) && !resLink3->isComplete())
    {
        for(int i=0;i<10000;i++);
    }
    if(temppp && temppp->node)
    {
        showArea->setText(temppp->node->value);
    }else
    {
        showArea->setText("没有成语");
    }
}
void RootWidget::nextDifferItem(int flag)
{
    qDebug()<<"现在是void RootWidget::nextDifferItem(int flag)";
    if(currentLabel!=4)
    {
        qDebug()<<"currentLabel!=4,函数直接返回。\t现在是void RootWidget::nextDifferItem(int flag)";
        return;
    }
    ptrLink *temppp=resLink4->getDifferItem(flag);

    qDebug()<<"resLink4是否创建完毕"<<resLink4->isComplete()<<"\t表长是"<<resLink4->getHeader()->length<<"\t现在是void RootWidget::nextDifferItem(int flag)";

    if(temppp && temppp->node)
    {
        qDebug()<<"resLink4->getDifferItem(flag)返回的temppp不为空。并且其value是\""<<temppp->node->value<<"\"\t现在是void RootWidget::nextDifferItem(int flag)";
        showArea->setText(temppp->node->value);
        keyBoardReset=false;
    }else
    {
        qDebug()<<"resLink4->getDifferItem(flag)返回的temppp为空。\t现在是void RootWidget::nextDifferItem(int flag)";
    }
}

