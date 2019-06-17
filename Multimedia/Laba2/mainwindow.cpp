#include "mainwindow.h"
#include "ui_mainwindow.h"

Mat image = imread("/home/toshiki/files/картинки/PNG for LS/kek.png");

inline QImage MatToQImage(const Mat &input)
{
    QImage image(input.data,
                 input.cols, input.rows,
                 static_cast<int>(input.step),
                 QImage::Format_RGB888);
    return image.rgbSwapped();
}

QImage img = MatToQImage(image);

inline Mat QImageToMat(const QImage &input)
{
    QImage   swapped;
    if(input.format() == QImage::Format_RGB32 )
        swapped = input.convertToFormat( QImage::Format_RGB888 );
    swapped = input.rgbSwapped();
    return cv::Mat(swapped.height(), swapped.width(),
                   CV_8UC3,
                   const_cast<uchar*>(swapped.bits()),
                   static_cast<size_t>(swapped.bytesPerLine())
                  ).clone();
}

void MainWindow::histDisplay(Mat image, plane RGB)
{
    int hist[256];
    memset(hist, 0, 256*sizeof(*hist));
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            hist[(int)image.at<uchar>(y,x)]++;
    int hist_w = 256; int hist_h = ui->label_3->size().height();
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
                     Scalar(0,0,255));
        ui->label_3->setPixmap(QPixmap::fromImage(MatToQImage(histImage)));
        ui->label_3->show();
        break;
    case GREEN:
        for(int i = 0; i < 256; i++)
                line(histImage, Point(bin_w*(i), hist_h),
                                      Point(bin_w*(i), hist_h - hist[i]),
                     Scalar(0,255,0));
        ui->label_4->setPixmap(QPixmap::fromImage(MatToQImage(histImage)));
        ui->label_4->show();
        break;
    case BLUE:
        for(int i = 0; i < 256; i++)
                line(histImage, Point(bin_w*(i), hist_h),
                                      Point(bin_w*(i), hist_h - hist[i]),
                     Scalar(255,0,0));
        ui->label_5->setPixmap(QPixmap::fromImage(MatToQImage(histImage)));
        ui->label_5->show();
        break;
    default:
        break;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayout->setSpacing(0);
    ui->verticalLayout->setMargin(0);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
            this, SLOT(on_horizontalSlider_valueChanged(int)));
    ui->label->setPixmap(QPixmap::fromImage(img).scaled(
                             img.width()/2, img.height()/2, Qt::KeepAspectRatio));
    ui->label->setMinimumWidth(img.width()/2);
    ui->label->setMinimumHeight(img.height()/2);
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
}

QImage brightness(Mat input, int ratio)
{
    Mat new_image = Mat::zeros(input.size(), input.type());
    for(int y = 0; y < input.rows; y++)
        for(int x = 0; x < input.cols; x++)
            for(int c = 0; c < 3; c++)
                new_image.at<Vec3b>(y,x)[c] =
                        saturate_cast<uchar>((input.at<Vec3b>(y,x)[c]) + ratio);
    QImage image = MatToQImage(new_image);
    return image;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int ratio = value * 2.55;
    ui->label_2->setText(QString::number(value)+"%");
    QImage temp(brightness(image,ratio).scaled(
                    img.width()/2, img.height()/2,Qt::KeepAspectRatio));
    ui->label->setPixmap(QPixmap::fromImage(temp));
    Mat tmp = QImageToMat(temp);
    std::vector<Mat> rgb_planes;
    split(tmp, rgb_planes);
    if(ui->checkBox->checkState() == Qt::Checked){
        histDisplay(rgb_planes[2], RED);
        histDisplay(rgb_planes[1], GREEN);
        histDisplay(rgb_planes[0], BLUE);
    } else {
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();
    }

}
