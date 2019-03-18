#ifndef QUERY_H
#define QUERY_H

#include <QObject>
#include "type.h"
#include "variable.h"
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

class Query : public QObject
{
    Q_OBJECT
public:
    explicit Query(QObject *parent = 0);
private:
    QThread *currentThread;
    QMutex mutex;

signals:

public slots:
    void doWork(void *link,char ah,int flag,QThread *thread);
};

#endif // QUERY_H
