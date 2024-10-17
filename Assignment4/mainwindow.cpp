#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <math.h>
using namespace std;

QImage img(500,500,QImage::Format_RGB888);
QRgb white = qRgb(255,255,255);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::black);
    DDA(250,0,250,500,white);
    DDA(0,250,500,250,white);
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int xPoint,yPoint;
    xPoint = ui->x->toPlainText().toInt();
    yPoint = ui->y->toPlainText().toInt();

    x.push_back(xPoint);
    y.push_back(yPoint);

    img.setPixel(250+xPoint,250-yPoint,white);
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
}

void MainWindow::DDA(int x1, int y1, int x2, int y2, QRgb color)
{
    float dx,dy;
    dx = x2-x1;
    dy = y2-y1;
    float step = 0;
    if(abs(dy)>abs(dx)){
        step = abs(dy);
    }
    else step = abs(dx);

    float xInc=0,yInc=0;
    if(step!=0){
        xInc = dx/step;
        yInc = dy/step;
    }

    float x=x1,y = y1;
    for(int i=0; i<step; i++){
        img.setPixel(x,y,color);
        x += xInc;
        y += yInc;
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    drawPolygon(x,y,white);
}

void MainWindow::drawPolygon(vector<int> xPoint, vector<int> yPoint, QRgb color)
{
    xPoint.push_back(xPoint[0]);
    yPoint.push_back(yPoint[0]);

    for(int i=0; i<xPoint.size()-1;i++){
        DDA(250+xPoint[i],250-yPoint[i],250+xPoint[i+1],250-yPoint[i+1],color);
    }

    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);

}


void MainWindow::on_pushButton_5_clicked()
{
    vector<int> xTrans;
    vector<int> yTrans;

    xTrans.clear();
    yTrans.clear();

    int tx = ui->tx->toPlainText().toInt();
    int ty = ui->ty->toPlainText().toInt();


    for(int i=0; i<x.size(); i++){
        xTrans.push_back(x[i]+tx);
        yTrans.push_back(y[i]+ty);
    }

    QRgb red = QColor(Qt::red).rgb();
    drawPolygon(xTrans,yTrans,red);

}


void MainWindow::on_pushButton_3_clicked()
{
    x.clear();
    y.clear();
}


void MainWindow::on_pushButton_6_clicked()
{
    vector<int>xScale,yScale;
    float sx = ui->sx->toPlainText().toFloat();
    float sy = ui->sy->toPlainText().toFloat();

    for(int i=0; i<x.size(); i++){
        xScale.push_back(int(sx*x[i]));
        yScale.push_back(int(sy*y[i]));
    }

    QRgb blue = QColor(Qt::blue).rgb();
    drawPolygon(xScale,yScale,blue);

}


void MainWindow::on_pushButton_7_clicked()
{
    float angle = ui->angle->toPlainText().toFloat();
    angle = angle*0.01745;
    float cosA = cos(angle);
    float sinA = sin(angle);

    vector<int> xRotated,yRotated;
    for(int i=0; i<x.size();i++){
        xRotated.push_back(x[i]*cosA-y[i]*sinA);
        yRotated.push_back(x[i]*sinA+y[i]*cosA);
    }

    QRgb yellow = QColor(Qt::yellow).rgb();
    drawPolygon(xRotated,yRotated,yellow);

}

