#include<QApplication>
#include<QWidget>
#include<QHBoxLayout>
#include<QLabel>
#include<iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QImage       img("/home/toshiki/files/1280.png");
    QWidget      wgt;
    QHBoxLayout* phbx = new QHBoxLayout;
    QLabel*      plbl = new QLabel;

    phbx->setMargin(0);
    phbx->setSpacing(0);
    plbl->setPixmap(QPixmap::fromImage(img.scaled(img.width()/3,img.height()/3,Qt::KeepAspectRatio)));
    phbx->addWidget(plbl);
    wgt.setLayout(phbx);

    qint32      height  = img.height();
    qint32      width   = img.width();
    for(qint32 y = 0; y < height; ++y){
        QRgb* tempLine = reinterpret_cast<QRgb*>(img.scanLine(y));
        for(qint32 x = 0; x < width; ++x){
            int alpha   = qAlpha(*tempLine);
            *tempLine++ = qRgba(0, 0, 0, alpha);
        }
    }

    QLabel*     plbl2 = new QLabel;
    plbl2->setPixmap(QPixmap::fromImage(img.scaled(img.width()/3,img.height()/3,Qt::KeepAspectRatio)));
    phbx->setDirection(QBoxLayout::Down);
    phbx->addWidget(plbl2);
    wgt.setLayout(phbx);

    wgt.show();

    return app.exec();
}
