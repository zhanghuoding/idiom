#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget *parent = 0);
    virtual ~ClickLabel();

signals:
    void clicked(QString name,bool click=true);
    void mouseMoved(bool);

protected:
    virtual void mousePressEvent ( QMouseEvent * event )Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent( QMouseEvent * event );
};

#endif // CLICKLABEL_H
