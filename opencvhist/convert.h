#ifndef CONVERT_H
#define CONVERT_H

#include <QImage>
#include <QPixmap>
#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

namespace QCV {
    inline QImage MatToQImage(const cv::Mat &input){
        switch(input.type()){
        case CV_8UC4:{
            QImage image(input.data,
                         input.cols, input.rows,
                         static_cast<int>(input.step),
                         QImage::Format_ARGB32);
            return image;
        }
        case CV_8UC3:{
            QImage image(input.data,
                         input.cols, input.rows,
                         static_cast<int>(input.step),
                         QImage::Format_RGB888);
            return image.rgbSwapped();
        }
        case CV_8UC1:{
            static QVector<QRgb> sColorTable(256);
            if(sColorTable.isEmpty())
                for(int i = 0; i < 256; ++i)
                    sColorTable[i] = qRgb(i, i, i);
            QImage image(input.data,
                         input.cols, input.rows,
                         static_cast<int>(input.step),
                         QImage::Format_Indexed8);
            image.setColorTable(sColorTable);
            return image;
        }
        default:
            qWarning() << "QCV::MatToImage - cv::Mat image type is not spicified: " << input.type();
            break;
        }
        return QImage();
    }
    inline QPixmap MatToQPixmap(const cv::Mat &input){
        return  QPixmap::fromImage(MatToQImage(input));
    }
    inline cv::Mat QImageToMat( const QImage &input, bool CloneImageData = true ){
        switch (input.format()){
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:{
            cv::Mat mat(input.height(), input.width(),
                        CV_8UC4,
                        const_cast<uchar*>(input.bits()),
                        static_cast<size_t>(input.bytesPerLine())
                       );
            return (CloneImageData ? mat.clone() : mat);
        }
        case QImage::Format_RGB32:
        case QImage::Format_RGB888:{
            if(!CloneImageData)
                qWarning() << "QCV::QImageToMat() - Conversion requires cloning because we use a temporary QImage";
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
        case QImage::Format_Indexed8:{
            cv::Mat mat(input.height(), input.width(),
                        CV_8UC1,
                        const_cast<uchar*>(input.bits()),
                        static_cast<size_t>(input.bytesPerLine())
                       );
            return (CloneImageData ? mat.clone() : mat);
        }
        default:
            qWarning() << "QCV::QImageToMat() - QImage format is not specified:" << input.format();
            break;
        }
        return cv::Mat();
    }
    inline cv::Mat QPixmapToMat( const QPixmap &input, bool CloneImageData = true ){
        return QImageToMat(input.toImage(), CloneImageData );
    }
}

#endif // CONVERT_H
