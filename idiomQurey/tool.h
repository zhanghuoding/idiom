#ifndef TOOL_H
#define TOOL_H

#include <QSize>
#include <QString>
#include <QRect>

#include "variable.h"


class Tool
{
public:
    Tool();
    static QSize size(int width,int height);//计算并返回一个与计算机屏幕成一定比例的尺寸
    static QRect rect(int ax=0, int ay=0, int aw=0, int ah=0);//返回一个与16:9屏幕成比例的图形的位置和尺寸
    static int width(int width);//根据计算机屏幕的水平宽度，返回一个成比例的整型值
    static int height(int height);//根据计算机屏幕的竖直高度，返回一个成比例的整型值
    static char *rateWidthToChar(int x);//将传入的x按屏幕的宽比例换算后，转换成字符串返回
    static char *rateHeightToChar(int y);//将传入的y按屏幕的高比例换算后，转换成字符串返回
    static int fontSize(int size);//按照屏幕的宽来按比例计算字体的大小
};

#endif // TOOL_H
