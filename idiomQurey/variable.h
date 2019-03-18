#ifndef VARIABLE
#define VARIABLE

#include <QString>
#include <QSize>
#include <QDebug>
#include "idiom.h"
#include "resultlink.h"

short const keyAmount=17;//键盘中按键总数
extern QString picRootPath;//图片资源的根目录
extern QString resourceRootPath;//资源文件的根目录
//#ifndef DESKTOP
extern QString appSdardPath;//Application's root folder
//#endif
extern QString databaseName;//Application's database name
extern QString databasePath;//database's path
extern QString logPath;
extern QString logName;

extern QSize *screenSize;//设备的屏幕尺寸
extern QSize *windowSize;//窗口尺寸
extern QSize *keyBoardSize;//软键盘打开时的尺寸

extern short idiomLabelFontSize;//成语标签的字体
extern Idiom *idiom;//成语链表

extern ResultLink *resLink1;//第一个按键对应的成语链表
extern ResultLink *resLink2;//第二个按键对应的成语链表
extern ResultLink *resLink3;//第三个按键对应的成语链表
extern ResultLink *resLink4;//第四个按键对应的成语链表

#endif // VARIABLE

