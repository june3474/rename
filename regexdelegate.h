#ifndef REGEXDELEGATE_H
#define REGEXDELEGATE_H
#include <QStyledItemDelegate>

const int PADDING_LEFT = 5;




class RegExDelegate : public QStyledItemDelegate
{
public:
    enum Type {Replace, Match};
    RegExDelegate(QObject *parent = 0, Type type = Match,\
                  const QRegExp &regEx = QRegExp(), const QString &after = QString(), \
                  const Qt::GlobalColor bgColor = Qt::darkBlue, const Qt::GlobalColor fgColor = Qt::white);
    ~RegExDelegate();

    // function overload
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QStringList splitString(const QString &str) const;

    // getter & setter
    Qt::GlobalColor getBgColor() const;
    void setBgColor(const Qt::GlobalColor &color);

    Qt::GlobalColor getFgColor() const;
    void setFgColor(const Qt::GlobalColor &color);

    QRegExp getRegEx() const;
    void setRegEx(const QRegExp &regEx);

    QString getAfter() const;
    void setAfter(const QString &str);

private:
    Type type;
    QRegExp regEx;
    QString after;
    Qt::GlobalColor bgColor;
    Qt::GlobalColor fgColor;

    void paintMatch(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintReplace(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // REGEXDELEGATE_H
