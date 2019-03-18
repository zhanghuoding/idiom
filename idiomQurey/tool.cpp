#include "tool.h"

Tool::Tool()
{

}
QSize Tool::size(int width, int height)
{
    int w=0,h=0;
    w=width*(screenSize->width()/180.0)+0.5;//加0.5就是做四舍五入的运算
    h=height*(screenSize->height()/320.0)+0.5;
    return QSize(w,h);
}
int Tool::width(int width)
{
    return width*(screenSize->width()/180.0)+0.5;
}
int Tool::height(int height)
{
    return height*(screenSize->height()/320.0)+0.5;
}
char *Tool::rateWidthToChar(int x)
{
    return QString::number(width(x)).toLatin1().data();
}
char *Tool::rateHeightToChar(int y)
{
    return QString::number(height(y)).toLatin1().data();
}
QRect Tool::rect(int ax, int ay, int aw, int ah)
{
    return QRect(width(ax),height(ay),width(aw),height(ah));
}
int Tool::fontSize(int size)
{
    return size*(screenSize->width()/180.0)+0.5;
}
