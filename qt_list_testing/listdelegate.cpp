#include "listdelegate.h"
#include <QTextLayout>

ListDelegate::ListDelegate(QObject *parent) : QAbstractItemDelegate(parent){}

void ListDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
    QRect r = option.rect;

    //Color: #C4C4C4
    QPen linePen(QColor::fromRgb(211,211,211), 1, Qt::SolidLine);

    //Color: #005A83
    QPen lineMarkedPen(QColor::fromRgb(0,90,131), 1, Qt::SolidLine);

    //Color: #333
    QPen fontPen(QColor::fromRgb(51,51,51), 1, Qt::SolidLine);

    //Color: #fff
    QPen fontMarkedPen(Qt::white, 1, Qt::SolidLine);

    if(option.state & QStyle::State_Selected){
        QLinearGradient gradientSelected(r.left(),r.top(),r.left(),r.height()+r.top());
        gradientSelected.setColorAt(0.0, QColor::fromRgb(119,213,247));
        gradientSelected.setColorAt(0.9, QColor::fromRgb(27,134,183));
        gradientSelected.setColorAt(1.0, QColor::fromRgb(0,120,174));
        painter->setBrush(gradientSelected);
        painter->drawRect(r);

        //BORDER
        painter->setPen(lineMarkedPen);
        painter->drawLine(r.topLeft(),r.topRight());
        painter->drawLine(r.topRight(),r.bottomRight());
        painter->drawLine(r.bottomLeft(),r.bottomRight());
        painter->drawLine(r.topLeft(),r.bottomLeft());

        painter->setPen(fontMarkedPen);

    } else {
        //BACKGROUND
                       //ALTERNATING COLORS
        painter->setBrush( (index.row() % 2) ? Qt::white : QColor(252,252,252) );
        painter->drawRect(r);

        //BORDER
        painter->setPen(linePen);
        painter->drawLine(r.topLeft(),r.topRight());
        painter->drawLine(r.topRight(),r.bottomRight());
        painter->drawLine(r.bottomLeft(),r.bottomRight());
        painter->drawLine(r.topLeft(),r.bottomLeft());

        painter->setPen(fontPen);
    }
    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(QRectF(9.5, 9.5, 100, 50), 5, 5);
    QPen pen(QColor(35, 38, 41), 0);
    painter->setPen(pen);
    painter->fillPath(path, QColor(35, 38, 41));
    painter->drawPath(path);

    //option.WrapText;
    //option.ElideRight;
    //GET TITLE, DESCRIPTION AND ICON
    QIcon ic = QIcon(qvariant_cast<QPixmap>(index.data(Qt::DecorationRole)));
    QString title = index.data(Qt::DisplayRole).toString();
    QString description = index.data(Qt::UserRole + 1).toString();

    int imageSpace = 10;
    if (!ic.isNull()) {
        //ICON
        r = option.rect.adjusted(5, 10, -10, -10);
        ic.paint(painter, r, Qt::AlignVCenter|Qt::AlignLeft);
        imageSpace = 55;
    }

    //TITLE
    r = option.rect.adjusted(imageSpace, 0, -10, -30);
    painter->setFont( QFont( "Lucida Grande", 12, QFont::Bold ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft, title, &r);

    //DESCRIPTION
    r = option.rect.adjusted(imageSpace, 30, -10, 0);
    painter->setFont( QFont( "Lucida Grande", 10, QFont::Normal ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, description, &r);
}

QSize ListDelegate::sizeHint ( const QStyleOptionViewItem &option, const QModelIndex &index ) const{
    //return QSize(200, 60); // very dumb value
    int widthUsed, lineCount;
    QStyledItemDelegate kek;
    //Try and word wrap strings
    if(index.data().canConvert(QMetaType::QString))
    {
        //Update the size based on the number of lines (original size of a single line multiplied
        //by the number of lines)
        QString text = index.data(Qt::DisplayRole).toString();
        details(text, QApplication::font(), option, &lineCount, &widthUsed);

        QSize size = kek.sizeHint(option, index);
        size.setHeight(lineCount * 60/* size.height()*/);

        return size;
    }
    else
    {
        //Fall back on original size hint of item
        return sizeHint(option, index);
    }
}

void ListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const{
    int lineCount, widthUsed;

    //Fix editor's geometry and produce the word-wrapped effect for strings...
    if(index.data().canConvert(QMetaType::QString))
    {
        //We need to expand our editor accordingly (not really necessary but looks nice)
        QString text = index.data(Qt::DisplayRole).toString();
        details(text, QApplication::font(), option, &lineCount, &widthUsed);

        //Expand
        QSize extraSize = QSize(option.rect.width(), lineCount * option.rect.height());
        QRect extraRect = option.rect;
        extraRect.setSize(extraSize);
        editor->setGeometry(option.rect);
    }
    else
    {
        //Fall back on original update
        updateEditorGeometry(editor, option, index);
    }
}

void ListDelegate::details( QString text, const QFont font, const QStyleOptionViewItem &option, int *lineCount, int *widthUsed ) const{
    //Use text layout to word-wrap and provide informmation about line counts and width's
    QTextLayout textLayout(text);

    *widthUsed = 0;
    *lineCount = 0;
    textLayout.setFont(font);
    textLayout.beginLayout();
    while (*lineCount < 5)
    {
        *lineCount = *lineCount + 1;
        QTextLine line = textLayout.createLine();
        if (!line.isValid())
            break;

        line.setLineWidth(option.rect.width());
        *widthUsed = (*widthUsed + line.naturalTextWidth());
    }
    textLayout.endLayout();
    *widthUsed = (*widthUsed + option.rect.width());
}

ListDelegate::~ListDelegate(){}






#include "listdelegate.h"

QSize ListViewDelegate::iconSize = QSize(60, 60);
int ListViewDelegate::padding = 5;

ListViewDelegate::ListViewDelegate()
{
}

ListViewDelegate::~ListViewDelegate()
{
}

QSize ListViewDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                                        const QModelIndex & index) const
{
    if(!index.isValid())
        return QSize();

    QString headerText = index.data(HeaderRole).toString();
    QString subheaderText = index.data(SubheaderRole).toString();

    QFont headerFont = QApplication::font();
    headerFont.setBold(true);
    QFont subheaderFont = QApplication::font();
    QFontMetrics headerFm(headerFont);
    QFontMetrics subheaderFm(subheaderFont);

    /* No need for x,y here. we only need to calculate the height given the width.
     * Note that the given height is 0. That is because boundingRect() will return
     * the suitable height if the given geometry does not fit. And this is exactly
     * what we want.
     */
    QRect headerRect = headerFm.boundingRect(0, 0,
                                             option.rect.width() - iconSize.width(), 0,
                                             Qt::AlignLeft|Qt::AlignTop|Qt::TextWordWrap,
                                             headerText);
    QRect subheaderRect = subheaderFm.boundingRect(0, 0,
                                                   option.rect.width() - iconSize.width(), 0,
                                                   Qt::AlignLeft|Qt::AlignTop|Qt::TextWordWrap,
                                                   subheaderText);

    QSize size(option.rect.width(), headerRect.height() + subheaderRect.height() +  3*padding);

    /* Keep the minimum height needed in mind. */
    if(size.height()<iconSize.height())
        size.setHeight(iconSize.height());

    return size;
}

void ListViewDelegate::paint(QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    QString headerText = index.data(HeaderRole).toString();
    QString subheaderText = index.data(SubheaderRole).toString();

    QFont headerFont = QApplication::font();
    headerFont.setBold(true);
    QFont subheaderFont = QApplication::font();
    QFontMetrics headerFm(headerFont);
    QFontMetrics subheaderFm(subheaderFont);

    /*
     * The x,y coords are not (0,0) but values given by 'option'. So, calculate the
     * rects again given the x,y,w.
     * Note that the given height is 0. That is because boundingRect() will return
     * the suitable height if the given geometry does not fit. And this is exactly
     * what we want.
     */
    QRect headerRect =
            headerFm.boundingRect(option.rect.left() + iconSize.width(), option.rect.top() + padding,
                                  option.rect.width() - iconSize.width(), 0,
                                  Qt::AlignLeft|Qt::AlignTop|Qt::TextWordWrap,
                                  headerText);
    QRect subheaderRect =
            subheaderFm.boundingRect(headerRect.left(), headerRect.bottom()+padding,
                                     option.rect.width() - iconSize.width(), 0,
                                     Qt::AlignLeft|Qt::AlignTop|Qt::TextWordWrap,
                                     subheaderText);

    painter->setPen(Qt::black);

    painter->setFont(headerFont);
    painter->drawText(headerRect, Qt::AlignLeft|Qt::AlignTop|Qt::TextWordWrap, headerText);

    painter->setPen(Qt::magenta);
    painter->setFont(subheaderFont);
    painter->drawText(subheaderRect, Qt::AlignLeft|Qt::AlignTop|Qt::TextWordWrap, subheaderText);

    painter->restore();
}
