#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QDialog>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

using namespace cv;

typedef enum{
    RED,
    GREEN,
    BLUE,
    GRAYSCALE
}plane;

namespace Ui {
class Histogram;
}

class Histogram : public QDialog
{
    Q_OBJECT

public:
    explicit Histogram(QWidget *parent = 0);
    ~Histogram();
    void histDisplay(Mat image, plane RGB);

private:
    Ui::Histogram *ui;
};

#endif // HISTOGRAM_H
