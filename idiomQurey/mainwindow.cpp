#include "mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    time.start();
    rootWidget=new RootWidget(this);
    this->setMinimumSize(windowSize->width(),windowSize->height());
    this->setCentralWidget(rootWidget);
}

MainWindow::~MainWindow()
{

}

#ifdef ANDROID
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //if the "Back" key on android was pressed two consecutive times in 2 seconds,
    //then,the application will exit.
    if(event->key() == Qt::Key_Back)
        ;//do nothing
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Back)
    {
        //when the "Back" key on android was released,record the time or exit application(when pressed toe consecutive times in 2 seconds
        if(time.elapsed()/1000.0 > 2)//if time interval more than 2 seconds,restart the timer
            time.restart();
        else//if time interval less or equal to 2 seconds,then exit the application
            exit(0);
    }
}
#endif
