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
}

inline int overflow(int value){
    return value>255?255:value<0?0:value;
}

QImage brightness_contrast(QImage &input, double alpha, int beta){
    QImage temp = input;
    qint32      height  = input.height();
    qint32      width   = input.width();
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            QColor pix = temp.pixel(x,y);
            int r = overflow(pix.red()+beta);
            int g = overflow(pix.green()+beta);
            int b = overflow(pix.blue()+beta);
            int a = pix.alpha();
            QRgb rgb = qRgba(r, g, b, a);
            temp.setPixel(x,y,rgb);
        }
    }
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            QColor pix = temp.pixel(x,y);
            int r = overflow(((pix.red()/255 - 0.5)*alpha + 0.5)*255);
            int g = overflow(((pix.green()/255 - 0.5)*alpha + 0.5)*255);
            int b = overflow(((pix.blue()/255 - 0.5)*alpha + 0.5)*255);
            //int g = overflow((((pix.red()*0.299 + pix.green()*0.587 + pix.blue()*0.114)/255-0.5)*alpha+0.5)*255);
            int a = pix.alpha();
            QRgb rgb = qRgba(r, g, b, a);
            temp.setPixel(x,y,rgb);
        }
    }
    return temp;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    double alpha = (100.0 + value) / 100;
    alpha = alpha * alpha;
    ui->label_3->setText(QString::number(value));
    QImage temp(brightness_contrast(
                    img, alpha, 0).scaled(
                        img.width()/2, img.height()/2,Qt::KeepAspectRatio));
    ui->label->setPixmap(QPixmap::fromImage(temp));
    Mat tmp = QImageToMat(temp);
    std::vector<Mat> rgb_planes;
    split(tmp, rgb_planes);
    if(ui->checkBox->checkState() == Qt::Checked){
        hist.show();
        hist.histDisplay(rgb_planes[2], RED);
        hist.histDisplay(rgb_planes[1], GREEN);
        hist.histDisplay(rgb_planes[0], BLUE);
    } else {
        hist.hide();
   }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int beta = value * 2.55;
    ui->label_2->setText(QString::number(value)+"%");
    QImage temp(brightness_contrast(img, 1, beta).scaled(
                    img.width()/2, img.height()/2,Qt::KeepAspectRatio));
    ui->label->setPixmap(QPixmap::fromImage(temp));
    Mat tmp = QImageToMat(temp);
    std::vector<Mat> rgb_planes;
    split(tmp, rgb_planes);
    if(ui->checkBox->checkState() == Qt::Checked){
        hist.show();
        hist.histDisplay(rgb_planes[2], RED);
        hist.histDisplay(rgb_planes[1], GREEN);
        hist.histDisplay(rgb_planes[0], BLUE);
    } else {
        hist.hide();
    }
}

void MainWindow::on_pushButton_pressed()
{
    QImage input   = ui->label->pixmap()->toImage();
    qint32 height  = input.height();
    qint32 width   = input.width();
    for(qint32 y = 0; y < height; ++y){
        QRgb* tempLine = reinterpret_cast<QRgb*>(input.scanLine(y));
        for(qint32 x = 0; x < width; ++x){
            int alpha = qAlpha(*tempLine);
            int GS = qRed(*tempLine)   * 0.299 +
                     qGreen(*tempLine) * 0.587 +
                     qBlue(*tempLine)  * 0.114;
            *tempLine++ = qRgba(GS, GS, GS, alpha);
        }
    }
    if(ui->checkBox->checkState() == Qt::Checked){
        hist.show(); hist.histDisplay(QImageToMat(input), GRAYSCALE);
    }
    ui->label->setPixmap(QPixmap::fromImage(input).scaled(
                             img.width()/2, img.height()/2, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_2_pressed()
{
    QImage input = ui->label->pixmap()->toImage();
    QVector<QRgb> vec;
    for(int h = 1; h < input.height()-1; h++)
        for(int w = 1; w < input.width()-1; w++){
            vec.append(input.pixel(w-1,h-1));
            vec.append(input.pixel(w,h-1));
            vec.append(input.pixel(w+1,h-1));
            vec.append(input.pixel(w-1,h));
            vec.append(input.pixel(w,h));
            vec.append(input.pixel(w+1,h));
            vec.append(input.pixel(w-1,h+1));
            vec.append(input.pixel(w,h+1));
            vec.append(input.pixel(w+1,h+1));

            qSort(vec.begin(),vec.end());
            input.setPixel(w,h,vec.at(4));
            vec.clear();
        }
    Mat tmp = QImageToMat(input);
    std::vector<Mat> rgb_planes;
    split(tmp, rgb_planes);
    if(ui->checkBox->checkState() == Qt::Checked){
        hist.show();
        hist.histDisplay(rgb_planes[2], RED);
        hist.histDisplay(rgb_planes[1], GREEN);
        hist.histDisplay(rgb_planes[0], BLUE);
    } else {
        hist.hide();
    }
    ui->label->setPixmap(QPixmap::fromImage(input).scaled(
                             img.width()/2, img.height()/2, Qt::KeepAspectRatio));
}
