#include "showarea.h"
#include "tool.h"



ShowArea::ShowArea(QWidget *parent) : QWidget(parent)
{
    int c=0;
    for(int i=0;i<4;i++)
    {
        labels[i]=new ClickLabel(this);
        labels[i]->setObjectName(QString::number(i));
        labels[i]->setGeometry(Tool::rect(c,1,38,38));
        connect(labels[i],SIGNAL(clicked(QString,bool)),this,SLOT(sendSignal(QString,bool)));
        c+=40;
    }
}
ShowArea::~ShowArea()
{
    for(int i=0;i<4;)
        if(labels[i])
            delete labels[i++];
}
void ShowArea::setText(QString text)
{
    char *value=NULL;
    value=new char[strlen(text.toStdString().c_str())+1];
    strcpy(value,text.toStdString().data());
    setText(value);
}
void ShowArea::setText(charPtr text)
{
    char *p=new char[4]{'\0','\0','\0','\0'};
    int po=0;
    int num=strlen(text)/4;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<num;j++)
        {
            if(po<=strlen(text))
            {
                p[j]=text[po++];
            }
        }
        if(strlen(p)==num)
        {
            labels[i]->setText(p);
        }else
        {
            labels[i]->setText("");
        }
        p[0]='\0';
        p[1]='\0';
        p[2]='\0';
        p[3]='\0';
    }
}
void ShowArea::setStyShe(QString sheet)
{
    for(int i=0;i<4;i++)
    {
        labels[i]->setStyleSheet(sheet);
    }
    setStyleSheet(QString("QWidget{background-color:#ffffff}"));
}
ClickLabel *ShowArea::getLabelAt(int index)
{
    if(index<0 || index>4)
        return new ClickLabel;
    else
        return labels[index];
}
void ShowArea::sendSignal(QString name, bool click)
{
    qDebug()<<"ShowArea在响应。 \t现在是void ShowArea::sendSignal(QString name, bool click)";
    emit clickedNum(name.toInt());
}
