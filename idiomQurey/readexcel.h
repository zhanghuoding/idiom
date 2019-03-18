#ifndef READEXCEL_H
#define READEXCEL_H

#include <type.h>
#include <QObject>
#include <QThread>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class ReadExcel : public QObject
{
    Q_OBJECT
public:
    ReadExcel();
    ~ReadExcel();
public slots:
    void doWork();
private:
    linkNode *tmp;
    QSqlDatabase db;
    QSqlQuery *query;
};

#endif // READEXCEL_H
