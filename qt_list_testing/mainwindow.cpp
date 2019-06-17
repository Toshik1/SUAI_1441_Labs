#include "mainwindow.h"
#include <QStandardItemModel>


/*void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        emit customContextMenuRequested(event->pos());
    }
    else
        //QListView::mousePressEvent(event);
        myListWidget->mousePressEvent(event);
}*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //connect(myListWidget, SIGNAL())

    setupUi(this);
    //myListWidget->setWordWrap(true);
    //myListWidget->setTextElideMode(Qt::ElideRight);
    //myListWidget->setItemDelegate(new ListDelegate(myListWidget));
    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setData(ListViewDelegate::HeaderRole, "Title");
    item2->setData(ListViewDelegate::SubheaderRole, "Description");
    //myListWidget->addItem(item2);
    //QListWidgetItem *item1 = new QListWidgetItem();
    //item1->setData(Qt::DecorationRole, QPixmap("/home/toshiki/Templates/chat_test_iq/client/user.png"));
    //item1->setData(Qt::DisplayRole, "Username");
    //item1->setData(Qt::UserRole + 1, "Usermessage!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                                    // "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                                     //"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                                   //  "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                                   //  "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    //myListWidget->addItem(item1);
    //new QListWidgetItem(QPixmap("/home/toshiki/Templates/chat_test_iq/client/user.png"), "<b>ASASAS<\b>\nasddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd", myListWidget);

    QStandardItemModel *model = new QStandardItemModel();
    model = new QStandardItemModel();

    ListViewDelegate *listdelegate = new ListViewDelegate();
    listdelegate = new ListViewDelegate();

    //listView->setItemDelegate(listdelegate);
    listView->setModel(model);

    //myListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    myListWidget->addItem(item2);

    //myListWidget->setItemDelegate(listdelegate);
    //QStandardItem *item3 = new QStandardItem();
    //QListWidgetItem *item = new QListWidgetItem();
    //item->setData(ListViewDelegate::DecorationRole, QPixmap("/home/toshiki/Templates/chat_test_iq/client/user.png"));
    //item->setData(ListViewDelegate::HeaderRole, "Some Header");
    //item->setData(ListViewDelegate::SubheaderRole, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    //model->appendRow(item);

    //myListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(myListWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
    myListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    myListWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    myListWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
    //myListWidget->setCurrentIndex(QModelIndex(myListWidget->rootIndex()));
    myListWidget->setItemDelegate(listdelegate);
    //myListWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    /*QPalette palette;
    palette.setColor(QPalette::Highlight, myListWidget->palette().color(QPalette::Base));
    palette.setColor(QPalette::HighlightedText, myListWidget->palette().color(QPalette::Text));
    myListWidget->setPalette(palette);*/
    QListWidgetItem *item = new QListWidgetItem();
    //item->setCheckState(Qt::Checked);
    /*item->setFlags(Qt::ItemIsEditable|
                   Qt::ItemIsSelectable|
                   Qt::ItemIsUserCheckable|
                   Qt::ItemIsTristate|
                   Qt::ItemIsDragEnabled);*/
    item->setData(ListViewDelegate::HeaderRole, "Some Header");
    item->setData(ListViewDelegate::SubheaderRole, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    myListWidget->addItem(item);

    //QWidget *widget;
    QVBoxLayout *la = new QVBoxLayout;
    QLabel lbl("Label");
    lbl.setTextInteractionFlags(Qt::TextSelectableByMouse);
    la->addWidget(&lbl);
    QWidget *wgt = new QWidget;
    widget->setLayout(la);
    widget->show();
    QListWidgetItem *item3 = new QListWidgetItem();
    item3->setSizeHint(wgt->sizeHint());
    myListWidget->setItemWidget(item3, wgt);
    //connect(myListWidget, &QListWidget::itemClicked, this, &MainWindow::on_myListWidget_itemClicked);
}

void MainWindow::customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(tr("Context Menu"), this);

    QAction action1("Copy", this);
    action1.setShortcuts(QKeySequence::Copy);
    //connect(action1, action1.triggered(), [this]()->void{QApplication::clipboard();});
    /*connect(&action1, SIGNAL(triggered()), this, SLOT());
    contextMenu.addAction(&action1);*/

    contextMenu.exec(mapToGlobal(pos));
}

void MainWindow::on_myListWidget_itemClicked(QListWidgetItem *item)
{
    //QListWidgetItem *temp = myListWidget->currentItem();
    /*QString string = item->text();
    QClipboard *p_Clipboard = QApplication::clipboard();
    p_Clipboard->setText(string, QClipboard::Clipboard);*/

    /*QAbstractItemModel *model1 = myListWidget->model();
    QItemSelectionModel *selection = myListWidget->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QString selected_text;
    QModelIndex previous = indexes.first();
    indexes.removeFirst();
    foreach (QModelIndex current, indexes) {
        QVariant data = model1->data(current);
        QString text = data.toString();
        selected_text.append(text);
        if (current.row() != previous.row()){
            selected_text.append('\n');
        } else {
               selected_text.append('\t');
        }
        previous = current;
    }
    QClipboard *p_Clipboard = QApplication::clipboard();
    p_Clipboard->setText(selected_text, QClipboard::Clipboard);*/
}
