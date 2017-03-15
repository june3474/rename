/****************************************************************************
**
** Copyright (c) 2007 Trolltech ASA <info@trolltech.com>
**
** Use, modification and distribution is allowed without limitation,
** warranty, liability or support of any kind.
**
** - modified by dks. Mar 2017.
**
****************************************************************************/
#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QIcon>

#define ICON_SIZE QSize(22,22)

class QToolButton;

class MyLineEdit : public QLineEdit
{    
    Q_OBJECT

public:
    MyLineEdit(QWidget *parent = 0);
    ~MyLineEdit();

    enum State {DEFAULT, OK, ERROR};
    void setIcon(State state);

protected:
    void resizeEvent(QResizeEvent *);
    void focusOutEvent(QFocusEvent *e);

signals:
    void focusOut();
    void buttonClicked(bool checked);

private slots:
    void buttonClick(bool checked);

private:
    QToolButton *button;

    static QIcon iconOK;
    static QIcon iconError;
    static QIcon iconDefault;

    const static uchar OK_ICON_DATA[794];
    const static uchar ERROR_ICON_DATA[1251];
};

#endif // MYLINEEDIT_H
