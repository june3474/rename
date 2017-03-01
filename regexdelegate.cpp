#include "regexdelegate.h"
#include <QPainter>
#include <QtDebug>

RegExDelegate::RegExDelegate(QObject *parent, Type type, \
                             const QRegExp &regEx, const QString &after, \
                             const Qt::GlobalColor bgColor, const Qt::GlobalColor fgColor) :
    QStyledItemDelegate(parent), type(type), regEx(regEx), after(after), \
    bgColor(bgColor), fgColor(fgColor)
{

}

RegExDelegate::~RegExDelegate()
{

}

// CORE part of this class
void RegExDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, \
                          const QModelIndex &index) const
{
    if(type == Match){
        paintMatch(painter, option, index);
    }
    else{ // if regEx!= Empty() && type == RegExDelegateType::Replace
        paintReplace(painter, option, index);
    }
}


void RegExDelegate::paintMatch(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(regEx.isEmpty()){
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    //rect is the area in which the text will be drawn
    QRect rect = option.rect;
    rect.adjust(PADDING_LEFT, 0, 0, 0);

    QStringList l = splitString(QString(index.data().toString()));

    // draw the first part
    painter->drawText(rect, l[0]);
    rect.adjust(QFontMetrics(option.font).width(l[0]),0,0,0);

    // draw the second part
    painter->save();
    painter->setPen(QColor(fgColor));
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->setBackground(QBrush(bgColor));
    painter->drawText(rect, l[1]);
    rect.adjust(QFontMetrics(option.font).width(l[1]),0,0,0);
    painter->restore();

    // draw the rest
    painter->drawText(rect, l[2]);

}

void RegExDelegate::paintReplace(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(after.isEmpty() || regEx.isEmpty()){
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QRect rect = option.rect;
    rect.adjust(PADDING_LEFT, 0, 0, 0);

    QStringList l = splitString(QString(index.data().toString()));
    QString replacedStr = index.data().toString().replace(regEx, after);

    // draw the first part
    painter->drawText(rect, l[0]);
    rect.adjust(QFontMetrics(option.font).width(l[0]),0,0,0);

    // draw the second part
    painter->save();
    painter->setPen(QColor(fgColor));
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->setBackground(QBrush(bgColor));
    QString replaced = replacedStr.mid(l[0].size(), \
                       replacedStr.size() - l[0].size() - l[2].size());
    painter->drawText(rect, replaced);
    rect.adjust(QFontMetrics(option.font).width(replaced),0,0,0);
    painter->restore();

    // draw the rest
    painter->drawText(rect, l[2]);
}

/*
 * Split string, eg. filename, with the given regular expression.
 * The return value is a stringlist composed of 3 parts.
 * The first part will be the prior section to the matching part.
 * The second will be the matching part.
 * The third part will be the remaining after the matching part.
 */
QStringList RegExDelegate::splitString(const QString &str) const
{
    QStringList result;
    int pos = regEx.indexIn(str);

    if(pos != -1){
        result << str.left(pos)
               << str.mid(pos, regEx.matchedLength())
               << str.mid(pos + regEx.matchedLength());
    } else {
        // make sure that we always have 3 strings
        result << str << "" << "";
    }

    return result;
}

Qt::GlobalColor RegExDelegate::getBgColor() const
{
    return bgColor;
}

void RegExDelegate::setBgColor(const Qt::GlobalColor &color)
{
    bgColor = color;
}

Qt::GlobalColor RegExDelegate::getFgColor() const
{
    return fgColor;
}

void RegExDelegate::setFgColor(const Qt::GlobalColor &color)
{
    fgColor = color;
}

QRegExp RegExDelegate::getRegEx() const
{
    return regEx;
}

void RegExDelegate::setRegEx(const QRegExp &regEx)
{
    this->regEx = regEx;
}

QString RegExDelegate::getAfter() const
{
    return after;
}

void RegExDelegate::setAfter(const QString &str)
{
    after = str;
}
