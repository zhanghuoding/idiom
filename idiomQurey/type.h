#ifndef TYPE
#define TYPE

#include <QDebug>

typedef unsigned char key_type;//键盘按键代码的数据类型
typedef char* charPtr;

typedef struct linknode
{
    int index;//成语在excel表中的ID值
    charPtr value;//成语本身的字符串
    charPtr code;//成语的编码code
    charPtr code1;//成语的编码code1
    linknode *next;//下一条成语的指针
}linkNode;
typedef struct linkhead
{
    int length;//链表的总长度
    bool comFlag;//链表是否创建完成的标志
    linkNode *next;//链表的第一个节点的指针
}linkHead;
typedef struct ptrlink
{
    linkNode *node;
    ptrlink *next;
}ptrLink;
typedef struct ptrhead
{
    int length;
    bool comFlag;
    ptrLink *next;
}ptrHead;

#endif // TYPE

