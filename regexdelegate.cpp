#include "regexdelegate.h"
#include <QPainter>
#include <QAbstractItemView>

RegExDelegate::RegExDelegate(QAbstractItemView *parent, Type type,\
                             const Qt::GlobalColor bgColor, const Qt::GlobalColor fgColor,\
                             const QRegExp &regEx, const QString &newPhrase) :
    QStyledItemDelegate(parent)
{
    this->type = type;
    this->regEx = regEx;
    this->newPhrase = newPhrase;
    this->bgColor = bgColor;
    this->fgColor = fgColor;
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

void RegExDelegate::refresh()
{
    qobject_cast<QAbstractItemView *>(parent())->viewport()->repaint();
}

void RegExDelegate::paintMatch(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // use parent's paint method
    if(regEx.isEmpty() || (option.state & QStyle::State_Selected)){
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    //rect is the area in which the text will be drawn
    QRect rect = option.rect;
    rect.adjust(PADDING_LEFT, 0, 0, 0);

    QStringList l = splitString(regEx, index.data().toString());

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
    if(regEx.isEmpty() || (option.state & QStyle::State_Selected)){
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QRect rect = option.rect;
    rect.adjust(PADDING_LEFT, 0, 0, 0);

    QStringList l = splitString(regEx, index.data().toString());

    // draw the first part
    painter->drawText(rect, l[0]);
    rect.adjust(QFontMetrics(option.font).width(l[0]),0,0,0);

    // draw the second part
    painter->save();
    painter->setPen(QColor(fgColor));
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->setBackground(QBrush(bgColor));
    QString replacedStr = l[1].replace(regEx, newPhrase);
    // QString.replace() replaces EVERY occurrence of the regular expression.
    painter->drawText(rect, replacedStr);
    rect.adjust(QFontMetrics(option.font).width(replacedStr),0,0,0);
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
QStringList RegExDelegate::splitString(const QRegExp regEx, const QString &str)
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
    if(bgColor == color)
        return;

    bgColor = color;
    refresh();
}

Qt::GlobalColor RegExDelegate::getFgColor() const
{
    return fgColor;
}

void RegExDelegate::setFgColor(const Qt::GlobalColor &color)
{
    if(fgColor == color)
        return;

    fgColor = color;
    refresh();
}

QRegExp RegExDelegate::getRegEx() const
{
    return regEx;
}

void RegExDelegate::setRegEx(const QRegExp &regEx)
{
    if(this->regEx == regEx)
        return;

    this->regEx = regEx;
    refresh();
}

QString RegExDelegate::getAfter() const
{
    return newPhrase;
}

void RegExDelegate::setAfter(const QString &str)
{
    if(newPhrase == str)
        return;

    newPhrase = str;
    if(type == RegExDelegate::Replace && !regEx.isEmpty()){
        refresh();
    }
}
