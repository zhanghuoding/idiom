#ifndef ROOTWIDGET_H
#define ROOTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QThread>

#include "clicklabel.h"
#include "variable.h"
#include "type.h"
#include "readexcel.h"
#include "query.h"
#include "showarea.h"

#include <QPushButton>

class RootWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RootWidget(QWidget *parent = 0);
    ~RootWidget();

    QString getImagePath(key_type t);//根据传入的按键的代码，返回该按键的图片
    QString getIdiom(key_type *a);//根据传入的按键代码的数组，返回搜索到的对应的成语链表

private:
    QHBoxLayout *strokesLayout;//点击笔画之后,显示四个笔画的横向布局管理器
    QWidget *strokesWidget;//点击笔画之后，显示四个笔画的容器
    ShowArea *showArea;//显示搜索到的成语的标签
    QVBoxLayout *rootLayout;//该组件中的根布局管理器
    QLabel *labels[4];//显示四个点击笔画的label的数组
    short currentLabel;//记录当前还未显示的label在labels中的下标
    bool keyBoardReset;//键盘是否清空的标记
    short codeIndex;//在进行加速检索的时候进行键盘点击次数的计数

    ReadExcel *readExceler;
    QThread readExcelThread;

    QThread queryThread4;
    QThread queryThread3;
    QThread queryThread2;
    QThread queryThread1;

    Query *qu1;
    Query *qu2;
    Query *qu3;
    Query *qu4;

signals:
    void operate();

    void operate1(void *link,char ah,int flag,QThread *thread);
    void operate2(void *link,char ah,int flag,QThread *thread);
    void operate3(void *link,char ah,int flag,QThread *thread);
    void operate4(void *link,char ah,int flag,QThread *thread);
public slots:
    void whitchKeyWasPrassed(key_type value);//接收键盘发出的哪个按键被点按下的按键代码的信号。
    void reset();//重置函数
    void stopQuery1();//每个笔画对应的查询成语的函数
    void stopQuery2();
    void stopQuery3();
    void stopQuery4();
    void nextDifferItem(int flag=-1);

};

#endif // ROOTWIDGET_H
