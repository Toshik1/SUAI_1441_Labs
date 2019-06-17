
#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H

#include <QPainter>
#include <QAbstractItemDelegate>
#include <QApplication>
#include <QStyledItemDelegate>

class ListDelegate : public QAbstractItemDelegate
{
    public:
        ListDelegate(QObject *parent = 0);
        void paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
        QSize sizeHint ( const QStyleOptionViewItem &option, const QModelIndex &index ) const;
        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
        void details( QString text, const QFont font, const QStyleOptionViewItem &option, int *lineCount, int *widthUsed ) const;

        virtual ~ListDelegate();
};


//#include <QStyledItemDelegate>
#include <QLabel>
//#include <QPainter>
//#include <QApplication>

class ListViewDelegate : public QStyledItemDelegate
{
public:
    enum datarole { HeaderRole = Qt::UserRole + 100, SubheaderRole};

    ListViewDelegate();
    ~ListViewDelegate();

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const;

    static QSize iconSize;
    static int padding;
};

#endif // LISTVIEWDELEGATE_H
