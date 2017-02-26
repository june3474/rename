#ifndef REGEXDELEGATE_H
#define REGEXDELEGATE_H
#include <QStyledItemDelegate>

const int PADDING_LEFT = 5;

class RegExDelegate : public QStyledItemDelegate
{
public:
    RegExDelegate(QObject *parent = 0, QRegExp *regEx = (new QRegExp()), \
                  const Qt::GlobalColor bgColor = Qt::darkBlue, const Qt::GlobalColor fgColor = Qt::white);
    ~RegExDelegate();

    // function overload
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QStringList splitString(const QString &str) const;


    Qt::GlobalColor getBgColor() const;
    void setBgColor(const Qt::GlobalColor &color);

    Qt::GlobalColor getFgColor() const;
    void setFgColor(const Qt::GlobalColor &color);

    QRegExp *getRegEx() const;
    void setRegEx(QRegExp *regEx);

private:
    Qt::GlobalColor bgColor;
    Qt::GlobalColor fgColor;
    QRegExp *regEx;
};

#endif // REGEXDELEGATE_H
