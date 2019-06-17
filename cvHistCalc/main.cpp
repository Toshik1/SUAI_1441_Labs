#include <iostream>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QtCore>

using std::cout;
using std::cin;
using std::endl;

using namespace cv;

Mat image = imread("/home/toshiki/files/картинки/PNG for LS/kek.png");
QImage img = MatToQimage(image);

inline QImage MatToQimage(const Mat &input){
    QImage image(input.data,
                 input.cols, input.rows,
                 static_cast<int>(input.step),
                 QImage::Format_RGB888);
    return image.rgbSwapped();
}

void histDisplay(Mat image, const char* name){
    int hist[256];
    memset(hist, 0, 256*sizeof(*hist));
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            hist[(int)image.at<uchar>(y,x)]++;
    int hist_w = 256; int hist_h = 100;
    int bin_w = cvRound((double) hist_w/256);
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));
    int max = hist[0];
    for(int i = 1; i < 256; i++)
        if(max < hist[i])
            max = hist[i];
    for(int i = 0; i < 256; i++)
        hist[i] = ((double)hist[i]/max)*histImage.rows;
    for(int i = 0; i < 256; i++){
        line(histImage, Point(bin_w*(i), hist_h),
                              Point(bin_w*(i), hist_h - hist[i]),
             Scalar(0,0,0));
    }
    namedWindow(name, CV_WINDOW_AUTOSIZE);
    imshow(name, histImage);
}

QImage brightness(Mat input, int ratio){
    Mat new_image = Mat::zeros(input.size(), input.type());
    for( int y = 0; y < input.rows; y++ )
        for( int x = 0; x < input.cols; x++ )
            for( int c = 0; c < 3; c++ )
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( 1*( input.at<Vec3b>(y,x)[c] ) + ratio );
    QImage image = MatToQimage(new_image);
    return image;
}

void on_Slider_valueChanged(int arg1){
    int ratio = arg1*2.55;
    plbl2->setPixmap(QPixmap::fromImage(brightness(image, ratio).scaled(img.width()/2, img.height()/2, Qt::KeepAspectRatio)));
}

int main(int argc, char *argv[]){
    //Mat image = imread("/home/toshiki/files/картинки/PNG for LS/kek.png");
    /*Mat new_image = Mat::zeros( image.size(), image.type() );
    for( int y = 0; y < image.rows; y++ )
        for( int x = 0; x < image.cols; x++ )
            for( int c = 0; c < 3; c++ )
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( 1*( image.at<Vec3b>(y,x)[c] ) + 20 );*/
    /*std::vector<Mat>(rgb_planes);
    split(image, rgb_planes);
    histDisplay(rgb_planes[0], "red_Original");
    namedWindow("Original Image");
    imshow("Original Image", image);
    histDisplay(image, "Original Histogram");
    split(new_image, rgb_planes);
    namedWindow("Equilized Image");
    imshow("Equilized Image",new_image);
    histDisplay(rgb_planes[0], "Equilized Histogram");
    waitKey();*/
    QApplication app(argc, argv);
    QWidget      wgt;
    QWidget      wgt1;
    QHBoxLayout* phbx = new QHBoxLayout;
    QLabel*      plbl = new QLabel;
    QLabel*      plbl2 = new QLabel;
    QSlider*     slide = new QSlider;
    slide->setMinimum(-100);
    slide->setMaximum(100);
    slide->setValue(0);
    QObject::connect(slide,SIGNAL(valueChanged(int)),wgt,SLOT(on_Slider_valueChanged(int arg1)));
    phbx->setMargin(0);
    phbx->setSpacing(0);
    //QImage img = MatToQimage(image);
    plbl->setPixmap(QPixmap::fromImage(img.scaled(img.width()/2, img.height()/2, Qt::KeepAspectRatio)));
    phbx->addWidget(plbl);
    wgt.setLayout(phbx);
    plbl2->setPixmap(QPixmap::fromImage(brightness(image, 20).scaled(img.width()/2, img.height()/2, Qt::KeepAspectRatio)));
    phbx->addWidget(plbl2);
    wgt.setLayout(phbx);
    phbx->addWidget(slide);
    wgt.setLayout(phbx);
    wgt.show();
    return app.exec();
}
