#include "clicklabel.h"
#include <QDebug>

ClickLabel::ClickLabel(QWidget *parent) : QLabel(parent)
{
}
ClickLabel::~ClickLabel()
{

}
void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    // 如果单击了就触发clicked信号
    if ( event->button() == Qt::LeftButton )
    {
        qDebug()<<"label被点击  "<<objectName()<<"\t现在是void ClickLabel::mousePressEvent(QMouseEvent *event)";
        emit clicked(objectName(),true);
    }
    // 将该事件传给父类处理
    QLabel::mousePressEvent(event);
}
void ClickLabel::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(true);

    // 将该事件传给父类处理
    QLabel::mouseMoveEvent(event);
}

