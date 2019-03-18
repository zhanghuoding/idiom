#ifndef KEY_H
#define KEY_H

#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include "variable.h"
#include "type.h"

class Key : public QLabel
{
    Q_OBJECT
public:
    explicit Key(key_type value, QWidget *parent = 0);
    virtual ~Key();
    key_type getTypeOfKey();
private:
    key_type value;//该按键所代表的按键类型的编码

signals:
    void clicked(key_type value,bool isClicked=true);

protected:
    virtual void mousePressEvent ( QMouseEvent * event )Q_DECL_OVERRIDE;
};

#endif // KEY_H
