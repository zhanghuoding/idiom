#include "readexcel.h"
#include <QMessageBox>
#include <QVariant>
#include <QDir>
#include "type.h"
#include "variable.h"



ReadExcel::ReadExcel() : QObject()
{

}
ReadExcel::~ReadExcel()
{
    if(query)
        delete query;
}
void ReadExcel::doWork()
{
    tmp=NULL;
    query=NULL;
    if(!idiom)
        idiom=new Idiom;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(appSdardPath + databasePath + databaseName);qDebug()<<appSdardPath + databasePath + databaseName;
    if ( db.open())
    {
        query=new QSqlQuery(db);
        query->exec("select ID,Name,code,code1 from idiom");
        charPtr value=NULL,code=NULL,code1=NULL;int index=0;
        QString qv,qc,qc1;
        while (query->next())
        {
            index=query->value(0).toString().toInt();
            qv=query->value(1).toString();
            qc=query->value(2).toString();
            qc1=query->value(3).toString();
            value=new char[strlen(qv.toStdString().c_str())+1];
            code=new char[strlen(qc.toStdString().c_str())+1];
            code1=new char[strlen(qc1.toStdString().c_str())+1];
            strcpy(value,qv.toStdString().data());
            strcpy(code,qc.toStdString().data());
            strcpy(code1,qc1.toStdString().data());

            tmp=new linkNode{index,value,code,code1,NULL};
            idiom->addItem(tmp);
            index=0;
            value=NULL;
            code=NULL;
            code1=NULL;
            tmp=NULL;
        }
        idiom->complete();
        db.close();
    }else
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),db.lastError().text());
    }
}
