#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

typedef enum{
    RED,
    GREEN,
    BLUE
}plane;

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void histDisplay(Mat image, plane RGB);

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

inline QImage MatToQImage(const Mat &input);
inline Mat QImageToMat(const QImage &input);

#endif // MAINWINDOW_H
