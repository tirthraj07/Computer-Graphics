#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>


QImage img(500,500,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::black);
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int xPoint, yPoint;
    bool xbool,ybool;
    xPoint = ui->x->toPlainText().toInt(&xbool);
    yPoint = ui->y->toPlainText().toInt(&ybool);

    if(xbool&&ybool){
        x.push_back(xPoint);
        y.push_back(yPoint);
        img.setPixel(xPoint,yPoint,qRgb(255,255,255));
        pixmap = QPixmap::fromImage(img);
        ui->label->setPixmap(pixmap);
    }

}

void MainWindow::DDA(int x1, int y1, int x2, int y2,QRgb color)
{
    float dx,dy;
    dx = x2-x1;
    dy = y2-y1;
    float step;
    if(abs(dy)>abs(dx)) step = abs(dy);
    else step = abs(dx);

    float xInc=0,yInc=0;
    if(step!=0){
        xInc = dx/step;
        yInc = dy/step;
    }
    float x = x1,y = y1;
    for(int i=0; i<step; i++){
        img.setPixel(x,y,color);
        x+=xInc;
        y+=yInc;
    }
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
}


void MainWindow::on_pushButton_2_clicked()
{
    x.push_back(x[0]);
    y.push_back(y[0]);

    for(int i=0; i<x.size()-1;i++){
        DDA(x[i],y[i],x[i+1],y[i+1],qRgb(255,255,255));
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QColorDialog dialog;
    QColor color = dialog.getColor();

    polygonColor = color.rgb();
}


void MainWindow::on_pushButton_4_clicked()
{
    float dx,dy;
    for(int i=0; i<x.size()-1;i++){
        dx = x[i+1] - x[i];
        dy = y[i+1] - y[i];
        if(dy==0) slope.push_back(1);
        else if(dx==0) slope.push_back(0);
        else slope.push_back(dx/dy);
    }

    vector<int> xIntersections;

    for(int scanline=0; scanline<500; scanline++){
        xIntersections.clear();

        for(int i=0; i<y.size(); i++){
            if(((y[i]<=scanline)&&(scanline<y[i+1]))||((y[i+1]<=scanline)&&(scanline<y[i]))){
                int xAtScanline = x[i] + slope[i]*(scanline-y[i]);
                xIntersections.push_back(xAtScanline);
            }
        }

        sort(xIntersections.begin(),xIntersections.end());
        reverse(xIntersections.begin(),xIntersections.end());

        if(xIntersections.size()>1){
            for(int i=0; i<xIntersections.size()-1;i=i+2){
                if(i==xIntersections.size()-1) break;
                DDA(xIntersections[i],scanline,xIntersections[i+1],scanline,polygonColor);
            }

        }


    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if(x.size()>=1){
        img.setPixel(x[x.size()-1],y[y.size()-1],qRgb(0,0,0));
        x.pop_back();
        y.pop_back();
        pixmap = QPixmap::fromImage(img);
        ui->label->setPixmap(pixmap);
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    img.fill(Qt::black);
    x.clear();
    y.clear();
    slope.clear();
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
}

