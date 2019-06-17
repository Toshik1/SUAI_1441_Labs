#include <QApplication>
#include <QtWidgets>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_grid.h>
#include <qwt/qwt_symbol.h>
#include <qwt/qwt_legend.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "convert.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc < 2)
        return 1;

    //Read input image
    //cv::Mat img = cv::imread(argv[1]);

    QImage       im(argv[1]);
    QWidget      wgt;
    QLabel*      plbl = new QLabel;
    plbl->setPixmap(QPixmap::fromImage(im.scaled(plbl->width()/2, plbl->height()/2, Qt::KeepAspectRatio), 0));
    QHBoxLayout* phbx = new QHBoxLayout;
    phbx->addWidget(plbl);
    wgt.setLayout(phbx);
    wgt.show();
    cv::Mat img(QCV::QImageToMat(im,true));

    //Convert to grayscale
    if (img.data && img.channels() == 3)
        cv::cvtColor(img, img, CV_BGR2GRAY);
    else
        return 1;

    int histSize[1] = {256}; // number of bins
    float hranges[2] = {0.0, 255.0}; // min and max pixel value
    const float* ranges[1] = {hranges};
    int channels[1] = {0}; // only 1 channel used

    cv::MatND hist;
    // Compute histogram
    cv::calcHist(&img, 1, channels, cv::Mat(), hist, 1, histSize,ranges);

    double minVal, maxVal;
    cv::minMaxLoc(hist, &minVal, &maxVal);//Locate max and min values

    QwtPlot plot; //Create plot widget
    plot.setTitle( "Plot Demo" ); //Name the plot
    plot.setCanvasBackground( Qt::black ); //Set the Background colour
    plot.setAxisScale( QwtPlot::yLeft, minVal, maxVal ); //Scale the y-axis
    plot.setAxisScale(QwtPlot::xBottom,0,255); //Scale the x-axis
    plot.insertLegend(new QwtLegend()); //Insert a legend

    QwtPlotCurve *curve = new QwtPlotCurve(); // Create a curve
    curve->setTitle("Count"); //Name the curve
    curve->setPen( Qt::white, 2);//Set colour and thickness for drawing the curve
    //Use Antialiasing to improve plot render quality
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    /*Insert the points that should be plotted on the graph in a
    Vector of QPoints or a QPolgonF */
    QPolygonF points;
    for( int h = 0; h < histSize[0]; ++h) {
        float bin_value = hist.at<float>(h);
        points << QPointF((float)h, bin_value);
    }

    curve->setSamples( points ); //pass points to be drawn on the curve
    curve->attach( &plot ); // Attach curve to the plot
    plot.resize( 600, 400 ); //Resize the plot
    plot.show(); //Show plot


    return a.exec();

}
