#include "key.h"
#include <QSize>
#include "tool.h"

Key::Key(key_type value,QWidget *parent) : QLabel(parent)
{
    this->value=value;
    //this->setIconSize(Tool::size(50,50));
    this->setStyleSheet(QString("QLabel{border-radius:60px}"));
}
Key::~Key()
{

}
key_type Key::getTypeOfKey()
{
    return value;
}

void Key::mousePressEvent(QMouseEvent *event)
{
    // 如果单击了就触发clicked信号
    if ( event->button() == Qt::LeftButton )
    {
        emit clicked(this->value,true);
    }
    // 将该事件传给父类处理
    QLabel::mousePressEvent(event);
}
