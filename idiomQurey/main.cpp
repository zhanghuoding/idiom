#include "mainwindow.h"
#include "variable.h"
#include "tool.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include "readexcel.h"
#include "macro.h"

#ifdef DESKTOP
QString picRootPath("../idiomQurey/image/");
QString resourceRootPath("../idiomQurey/resource/");
QString appSdardPath("../idiomQurey/");
#endif
#ifdef ANDROID
QString picRootPath("assets:/image/");
QString resourceRootPath("assets:/resource/");
QString appSdardPath("/sdcard/idiomQurey/");
#endif
QString databaseName("idiom.db");
QString databasePath("resource/");
QString logPath("log/");
QString logName("idiomQurey.log");
QSize *screenSize;
QSize *keyBoardSize;
QSize *keysAreaSize;
QSize *editBoxSize;
QSize *windowSize;
short idiomLabelFontSize=20;
Idiom *idiom;
ResultLink *resLink1=new ResultLink;
ResultLink *resLink2=new ResultLink;
ResultLink *resLink3=new ResultLink;
ResultLink *resLink4=new ResultLink;

void init();
void customMessageHandler(QtMsgType type, const QMessageLogContext& Context, const QString &sMsg);

int main(int argc, char *argv[])
{
#ifdef DESKTOP
    QApplication::addLibraryPath("./plugins");
#endif
    QApplication a(argc, argv);
    init();
    MainWindow w;
    w.show();

    return a.exec();
}
void init()
{
    QDir dir;

#ifdef ANDROID
    QByteArray data;
    QFile oriDb(resourceRootPath + databaseName);
    QFile finalDb(appSdardPath + databasePath + databaseName);
    dir.mkpath(appSdardPath + databasePath);//Create multi-level directory
    dir.mkpath(appSdardPath + logPath);


    //first check whether the database file exist,if no,create folder and copy it from "assest:/resource/"
    if(finalDb.exists() && QFileInfo(finalDb.fileName()).isFile() && finalDb.size())//if the file exist
    {
        goto neednotCreatFile;
    }

    if(finalDb.exists())
    {
        if(QFileInfo(finalDb.fileName()).isFile())
            finalDb.remove();
        else
            dir.rmdir(finalDb.fileName());
    }

    if(oriDb.open(QFile::ReadOnly))
    {
        data = oriDb.readAll();
        oriDb.close();
    }else
    {
        qDebug() << oriDb.fileName() << " file open failed " << oriDb.errorString();
    }

    if(finalDb.open(QFile::WriteOnly))
    {
        finalDb.write(data);
        finalDb.close();
    }else
    {
        qDebug() << finalDb.fileName() << " file open failed" << finalDb.errorString();
    }

    neednotCreatFile:

#endif

    QFile logFile(appSdardPath + logPath + logName);
    if(logFile.exists() && QFileInfo(logFile.fileName()).isFile() && logFile.size())
        logFile.remove();
    else if(logFile.exists())
        {
            if(QFileInfo(logFile.fileName()).isDir())
                dir.rmdir(logFile.fileName());
        }

#ifndef DEBUG
    qInstallMessageHandler(customMessageHandler);//注册日志处理回调函数
#endif
    qDebug()<<"当前的图片资源路径是 "<<picRootPath<<"\t现在是void init()";
    qDebug()<<"当前的数据资源路径是 "<<resourceRootPath<<"\t现在是void init()";
    idiom=new Idiom;//初始化成语链表的对象
    int width=QApplication::desktop()->width();
    int height=QApplication::desktop()->height();
#ifdef ANDROID
    windowSize=new QSize(width,height);
#endif
#ifdef DESKTOP
    windowSize=new QSize(360,640);
#endif
    screenSize=new QSize(windowSize->width(),windowSize->height());//初始化屏幕尺寸记录变量
}
void customMessageHandler(QtMsgType type, const QMessageLogContext& Context, const QString &sMsg)
{
    QString txt;
    switch (type)
    {//调试信息提示
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(sMsg);
        break;
        //一般的warning提示
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(sMsg);
        break;
        //严重错误提示
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(sMsg);
        break;
        //致命错误提示
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(sMsg);
        abort();
    }
    QFile logFile(appSdardPath + logPath + logName);
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&logFile);
    ts << "\r\n" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd") <<'\t' << txt << endl;
}
