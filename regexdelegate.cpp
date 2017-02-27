#include "regexdelegate.h"
#include <QPainter>
#include <QtDebug>

RegExDelegate::RegExDelegate(QObject *parent, QRegExp *regEx, RegExDelegateType type, \
                             const Qt::GlobalColor bgColor, const Qt::GlobalColor fgColor) :
    QStyledItemDelegate(parent), regEx(regEx), bgColor(bgColor), fgColor(fgColor)
{
    if(!regEx)
        regEx = new QRegExp();

    this->type = type;

    //setRegEx(new QRegExp("\\.o"));
}

RegExDelegate::~RegExDelegate()
{
    if(regEx)
        delete regEx;
}

void RegExDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, \
                          const QModelIndex &index) const
{

    if(regEx->isEmpty()){
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    //rect is the area in which the text will be drawn
    QRect rect = option.rect;
    rect.adjust(PADDING_LEFT, 0, 0, 0);

    // Split string, eg. filename, with the given regular expression.
    // The return value is a stringlist composed of 3 parts.
    // The first part will be the prior section to the matching part.
    // The second will be the matching part.
    // The third part will be the remaining after the matching part.
    QStringList l = splitString(QString(index.data().toString()));

    if(type == RegExDelegateType::Match){
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
    else{ // if regEx!= Empty() && type == RegExDelegateType::Replace
        QString replacedStr = index.data().toString().replace(regEx);

        painter->drawText(rect, l[0]);
        rect.adjust(QFontMetrics(option.font).width(l[0]),0,0,0);

        // draw the second part
        painter->save();
        painter->setPen(QColor(fgColor));
        painter->setBackgroundMode(Qt::OpaqueMode);
        painter->setBackground(QBrush(bgColor));
        painter->drawText(rect, replacedStr.mid());
        rect.adjust(QFontMetrics(option.font).width(l[1]),0,0,0);
        painter->restore();

        // draw the rest
        painter->drawText(rect, l[2]);

    }

}

QStringList RegExDelegate::splitString(const QString &str) const
{
    QStringList result;
    int pos = regEx->indexIn(str);

    if(pos != -1){
        result << str.left(pos)
               << str.mid(pos, regEx->matchedLength())
               << str.mid(pos + regEx->matchedLength());
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

QRegExp *RegExDelegate::getRegEx() const
{
    return regEx;
}

void RegExDelegate::setRegEx(QRegExp *regEx)
{
    this->regEx = regEx;
}

void RegExDelegate::paint_match(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void RegExDelegate::paint_replace(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

