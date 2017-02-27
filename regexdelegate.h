#ifndef REGEXDELEGATE_H
#define REGEXDELEGATE_H
#include <QStyledItemDelegate>

const int PADDING_LEFT = 5;

enum class RegExDelegateType {
    Replace,
    Match
};

class RegExDelegate : public QStyledItemDelegate
{
public:
    RegExDelegate(QObject *parent = 0, \
                  QRegExp *regEx = (new QRegExp()), RegExDelegateType type = RegExDelegateType::Match,\
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
    QRegExp *regEx;
    RegExDelegateType type;
    Qt::GlobalColor bgColor;
    Qt::GlobalColor fgColor;

    void paint_match(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint_replace(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // REGEXDELEGATE_H
