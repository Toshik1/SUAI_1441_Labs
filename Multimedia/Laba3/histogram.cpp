#include "histogram.h"
#include "ui_histogram.h"

inline QImage MatToQImage(const Mat &input)
{
    QImage image(input.data,
                 input.cols, input.rows,
                 static_cast<int>(input.step),
                 QImage::Format_RGB888);
    return image.rgbSwapped();
}

Histogram::Histogram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Histogram)
{
    ui->setupUi(this);
}

Histogram::~Histogram()
{
    delete ui;
}

void Histogram::histDisplay(Mat image, plane RGB)
{
    int hist[256];
    memset(hist, , 256 * sizeof(*hist));
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            hist[(int)image.at<uchar>(y,x)]++;
    int hist_w = 256;
    int hist_h = ui->label_3->size().height();
    int bin_w = cvRound((double) hist_w/256);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(50, 50, 50));
    int max = hist[0];
    for(int i = 1; i < 256; i++)
        if(max < hist[i])
            max = hist[i];
    for(int i = 0; i < 256; i++)
        hist[i] = ((double)hist[i]/max)*histImage.rows;
    switch ( RGB ) {
    case RED:
        for(int i = 0; i < 256; i++)
                line(histImage, Point(bin_w*(i), hist_h),
                                      Point(bin_w*(i), hist_h - hist[i]),
                     Scalar(0, 0, 255));
        ui->label_3->setPixmap(QPixmap::fromImage(MatToQImage(histImage)));
        ui->label_3->show();
        break;
    case GREEN:
        for(int i = 0; i < 256; i++)
                line(histImage, Point(bin_w*(i), hist_h),
                                      Point(bin_w*(i), hist_h - hist[i]),
                     Scalar(0, 255, 0));
        ui->label_4->setPixmap(QPixmap::fromImage(MatToQImage(histImage)));
        ui->label_4->show();
        break;
    case BLUE:
        for(int i = 0; i < 256; i++)
                line(histImage, Point(bin_w*(i), hist_h),
                                      Point(bin_w*(i), hist_h - hist[i]),
                     Scalar(255, 0, 0));
        ui->label_5->setPixmap(QPixmap::fromImage(MatToQImage(histImage)));
        ui->label_5->show();
        break;
    case GRAYSCALE:
        for(int i = 0; i < 256; i++)
                line(histImage, Point(bin_w*(i), hist_h),
                                      Point(bin_w*(i), hist_h - hist[i]),
                     Scalar(255, 255, 255));
        ui->label_3->setPixmap(QPixmap::fromImage(MatToQImage(histImage)));
        ui->label_3->show();
        ui->label_4->hide();
        ui->label_5->hide();
        break;
    default:
        break;
    }
}
