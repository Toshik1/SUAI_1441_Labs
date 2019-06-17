#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include "listdelegate.h"
#include <QApplication>
#include <QClipboard>
#include <QModelIndex>
#include <QMimeData>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //~MainWindow();

    void keyPressEvent(QKeyEvent *k)
    {
        if (k->matches(QKeySequence::Copy))
        {
            QString clipboardString;
                QModelIndexList selectedIndexes = myListWidget->selectionModel()->selectedIndexes();

                for (int i = 0; i < selectedIndexes.count(); ++i)
                {
                    QModelIndex current = selectedIndexes[i];
                    QString displayText = current.data(Qt::DisplayRole).toString();

                    // If there exists another column beyond this one.
                    if (i + 1 < selectedIndexes.count())
                    {
                        QModelIndex next = selectedIndexes[i+1];

                        // If the column is on different row, the clipboard should take note.
                        if (next.row() != current.row())
                        {
                            displayText.append("\n");
                        }
                        else
                        {
                            // Otherwise append a column separator.
                            displayText.append(" | ");
                        }
                    }
                    clipboardString.append(displayText);
                }

                QClipboard *p_Clipboard = QApplication::clipboard();
                p_Clipboard->setText(clipboardString, QClipboard::Clipboard);
                //QApplication::clipboard()->setText(clipboardString);
        }
    }

    void mousePressEvent(QMouseEvent *event){
        if(event->button() == Qt::RightButton)
        {
            QAbstractItemModel *model1 = myListWidget->model();
            QItemSelectionModel * selection = myListWidget->selectionModel();
                QModelIndexList indexes = selection->selectedIndexes();

                if(indexes.size() < 1)
                    return;

                // QModelIndex::operator < sorts first by row, then by column.
                // this is what we need
                std::sort(indexes.begin(), indexes.end());
                //std::sort(indexes);

                // You need a pair of indexes to find the row changes
                QModelIndex previous = indexes.first();
                indexes.removeFirst();
                QString selected_text_as_html;
                QString selected_text;
                selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");
                QModelIndex current;
                Q_FOREACH(current, indexes)
                {
                    QVariant data = model1->data(current);
                    QString text = data.toString();
                    selected_text.append(text);
                    text.replace("\n","<br>");
                    // At this point `text` contains the text in one cell
                    selected_text_as_html.append(text);

                    // If you are at the start of the row the row number of the previous index
                    // isn't the same.  Text is followed by a row separator, which is a newline.
                    if (current.row() != previous.row())
                    {
                        selected_text_as_html.append("</td></tr><tr><td>");
                        selected_text.append(QLatin1Char('\n'));
                    }
                    // Otherwise it's the same row, so append a column separator, which is a tab.
                    else
                    {
                        selected_text_as_html.append("</td><td>");
                        selected_text.append(QLatin1Char('\t'));
                    }
                    previous = current;
                }

                // add last element
                selected_text_as_html.append(model1->data(current).toString());
                selected_text.append(model1->data(current).toString());
                selected_text_as_html.append("</td></tr>");
                QMimeData * md = new QMimeData;
                md->setHtml(selected_text_as_html);
            //    qApp->clipboard()->setText(selected_text);
                md->setText(selected_text);
                qApp->clipboard()->setMimeData(md);

            //    selected_text.append(QLatin1Char('\n'));
            //    qApp->clipboard()->setText(selected_text);

            //emit customContextMenuRequested(event->pos());
        }
        else
            //QListView::mousePressEvent(event);
            this->mousePressEvent(event);
    }

private slots:
    void customContextMenuRequested(const QPoint &pos);


    void on_myListWidget_itemClicked(QListWidgetItem *item);

private:
    //Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
