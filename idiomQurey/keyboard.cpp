#include "keyboard.h"
#include "tool.h"

KeyBoard::KeyBoard(QWidget *parent) : QWidget(parent)
{
    currentKeyType=0;
    rootLayout=new QGridLayout(this);

    background=new QLabel();
    //background->setStyleSheet(QString("QLabel{border: 1px solid  #000000}"));
    //background->setScaledContents(true);
    //background->setPixmap(QPixmap(picRootPath+QString("/public/minKeyboard.png")));
    rootLayout->addWidget(background,0,0,16,20);

    initKeys();
    putKeys();
}
KeyBoard::~KeyBoard()
{
    if(background)
        delete background;
    for(int i=0;i<keyAmount;i++)
        if(keys[i])
            delete keys[i];
    if(rootLayout)
        delete rootLayout;
}
QLabel *KeyBoard::getBackground()
{
    return background;
}
void KeyBoard::whitchKeyClicked(key_type value,bool isClicked)
{
    emit keyWasPressed(value);
}
void KeyBoard::initKeys()
{
    char a[2]={'\0','\0'};
    for(int k=0;k<keyAmount-2;k++)
    {
        keys[k]=new Key('a'+k);
        a[0]='a'+k;
        //keys[k-1]->setIcon(QPixmap(picRootPath+QString("KeyBoard/").append(a).append(".png")));
        keys[k]->setStyleSheet(QString("QLabel{border-image: url(")+picRootPath+QString("KeyBoard/").append(a).append(".png").append(")}"));
        keyIndex[k]=keys[k]->getTypeOfKey();
    }
    keys[keyAmount-2]=new Key(13);//回车键
    //keys[keyAmount-2]->setIcon(QPixmap(picRootPath+QString("KeyBoard/enter.png")));
    keys[keyAmount-2]->setStyleSheet(QString("QLabel{border-image: url(")+picRootPath+QString("KeyBoard/enter.png").append(")}"));
    keyIndex[keyAmount-2]=keys[keyAmount-2]->getTypeOfKey();

    keys[keyAmount-1]=new Key(8);//退格键
    //keys[keyAmount-1]->setIcon(QPixmap(picRootPath+QString("KeyBoard/backspace.png")));
    keys[keyAmount-1]->setStyleSheet(QString("QLabel{border-image: url(")+picRootPath+QString("KeyBoard/backspace.png").append(")}"));
    keyIndex[keyAmount-1]=keys[keyAmount-1]->getTypeOfKey();

    for(int j=0;j<keyAmount;j++)
        connect(keys[j],SIGNAL(clicked(key_type,bool)),this,SLOT(whitchKeyClicked(key_type,bool)));
}
Key *KeyBoard::findKeyPointer(key_type keyType)
{//如果该按键存在，则返回该按键的指针，否则，返回空
    int i=0;
    for(i=0;i<keyAmount&&keyIndex[i]!=keyType;i++);
    if(i<keyAmount&&i>=0)
    {
        return keys[i];
    }
    else
    {
        return NULL;
    }
}
void KeyBoard::reset()
{
    currentKeyType=0;
}

void KeyBoard::putKeys()
{//设置键盘中的按键的位置
    /*
     * 该键盘中，字母按键的尺寸均为56*56
     * 按键与按键之间的间距为7
     * 按键与键盘上下边框距离为30，左右边框的距离为40
     */
    rootLayout->addWidget(findKeyPointer('a'),4,0,4,4);
    rootLayout->addWidget(findKeyPointer('b'),4,4,4,4);
    rootLayout->addWidget(findKeyPointer('c'),4,8,4,4);
    rootLayout->addWidget(findKeyPointer('d'),4,12,4,4);
    rootLayout->addWidget(findKeyPointer('e'),4,16,4,4);
    rootLayout->addWidget(findKeyPointer('f'),8,0,4,4);
    rootLayout->addWidget(findKeyPointer('g'),8,4,4,4);
    rootLayout->addWidget(findKeyPointer('h'),8,8,4,4);
    rootLayout->addWidget(findKeyPointer('i'),8,12,4,4);
    rootLayout->addWidget(findKeyPointer('j'),8,16,4,4);
    rootLayout->addWidget(findKeyPointer('k'),12,0,4,4);
    rootLayout->addWidget(findKeyPointer('l'),12,4,4,4);
    rootLayout->addWidget(findKeyPointer('m'),12,8,4,4);
    rootLayout->addWidget(findKeyPointer('n'),12,12,4,4);
    rootLayout->addWidget(findKeyPointer('o'),12,16,4,4);
    rootLayout->addWidget(findKeyPointer(8),0,12,4,4);
    rootLayout->addWidget(findKeyPointer(13),0,16,4,4);
}
void KeyBoard::setKeys(Key *k, int x, int y, int w, int h)
{
    ;
}

void KeyBoard::hiddenKeys()
{
    for(int i=0;i<keyAmount;i++)
        keys[i]->setVisible(false);
}
void KeyBoard::showKeys()
{
    for(int i=0;i<keyAmount;i++)
        keys[i]->setVisible(true);
}
