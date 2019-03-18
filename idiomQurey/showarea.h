#ifndef SHOWAREA_H
#define SHOWAREA_H

#include <QWidget>

#include "clicklabel.h"
#include "type.h"

class ShowArea : public QWidget
{
    Q_OBJECT
public:
    explicit ShowArea(QWidget *parent = 0);
    ~ShowArea();
    void setText(QString text);
    void setText(charPtr text);
    void setStyShe(QString sheet);
    ClickLabel *getLabelAt(int index);
private:
    ClickLabel *labels[4];
signals:
    void clickedNum(int flag=-1);
public slots:
    void sendSignal(QString name,bool click=true);
};

#endif // SHOWAREA_H
