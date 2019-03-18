#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "key.h"
#include "variable.h"

class KeyBoard : public QWidget
{
    Q_OBJECT
public:
    explicit KeyBoard(QWidget *parent = 0);
    ~KeyBoard();
    QLabel *getBackground();

private:
    QLabel *background;//软键盘的背景
    QGridLayout *rootLayout;//键盘的布局管理器
    Key *keys[keyAmount];//键盘上的30个按键
    key_type keyIndex[keyAmount];//键盘上15个按键在keys数组中对应的指针的下标
    key_type currentKeyType;//刚刚按过的键的值

    Key *findKeyPointer(key_type keyType);//根据传入的按键的ASCII码值，找到对应的按键的指针
    void initKeys();//初始化键盘中的按键
    void putKeys();//摆放软键盘上的30个按键
    void setKeys(Key *k,int x,int y,int w, int h);//根据传入的值，设置对应按键在键盘中的位置以及尺寸
    void hiddenKeys();//从键盘上将所有按键移除，使其不显示
    void showKeys();//显示所有按键

signals:
    void keyWasPressed(key_type value);//当回车键被按下时，键盘发出此次信号

public slots:
    void whitchKeyClicked(key_type value,bool isClicked=true);//槽函数，监听键盘中被按下的按键
    void reset();//重置键盘中的所有参数
};

#endif // KEYBOARD_H
