#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "histogram.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Histogram hist;

};

inline QImage MatToQImage(const Mat &input);
inline Mat QImageToMat(const QImage &input);

#endif // MAINWINDOW_H
