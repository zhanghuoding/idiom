#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTime>
#include "rootwidget.h"
#include "macro.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    RootWidget *rootWidget;
    QTime time;
protected:
#ifdef ANDROID
    void keyPressEvent(QKeyEvent * event)Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent * event)Q_DECL_OVERRIDE;
#endif
signals:
};

#endif // MAINWINDOW_H
