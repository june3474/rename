#ifndef REGEXDELEGATE_H
#define REGEXDELEGATE_H
#include <QStyledItemDelegate>

const int PADDING_LEFT = 5;




class RegExDelegate : public QStyledItemDelegate
{
public:
    enum Type {Replace, Match};
    RegExDelegate(QAbstractItemView *parent = 0, Type type = Match,\
                  const Qt::GlobalColor bgColor = Qt::darkBlue, const Qt::GlobalColor fgColor = Qt::white,\
                  const QRegExp &regEx = QRegExp(), const QString &newPhrase = QString());
    ~RegExDelegate();

    // function overload
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    // getter & setter
    Qt::GlobalColor getBgColor() const;
    void setBgColor(const Qt::GlobalColor &color);

    Qt::GlobalColor getFgColor() const;
    void setFgColor(const Qt::GlobalColor &color);

    QRegExp getRegEx() const;
    void setRegEx(const QRegExp &regEx);

    QString getAfter() const;
    void setAfter(const QString &str);

    // helper function
    static QStringList splitString(const QRegExp regEx, const QString &str);

public slots:
    void refresh();

private:
    Type type;
    QRegExp regEx;
    QString newPhrase;
    Qt::GlobalColor bgColor;
    Qt::GlobalColor fgColor;


    void paintMatch(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintReplace(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // REGEXDELEGATE_H
