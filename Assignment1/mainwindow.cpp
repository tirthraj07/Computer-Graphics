#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QImage>
#include <QPixmap>

/*

Geometry of First Figure:
Triange Coordinates:
    (250,120),(150,293),(350,293)
Incircle Coordinates:
    radius = 57
    Center : (250,236)
Circumcircle Coordinates:
    radius = 114
    Center : (250,236)


Geometry of Second Figure:
Outer Rectangle Coordinates:
    (50,135),(50,365),(450,365),(450,135)
Inner Rectangle Coordinates:
    (250,135),(50,250),(250,365),(450,250)
Inner Circle Coordinates:
    Center : (250,250)
    Radius : 100


 */




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
    int x1 = ui->x1->toPlainText().toInt();
    int y1 = ui->y1->toPlainText().toInt();
    int x2 = ui->x2->toPlainText().toInt();
    int y2 = ui->y2->toPlainText().toInt();
    undoLine.push(x1);
    undoLine.push(y1);
    undoLine.push(x2);
    undoLine.push(y2);

    DDA(x1,y1,x2,y2,qRgb(255,255,255));
}

void MainWindow::DDA(int x1, int y1, int x2, int y2,QRgb color)
{
    float dx,dy;
    dx = x2-x1;
    dy = y2-y1;
    float steps;
    if(abs(dy)>abs(dx)) steps = abs(dy);
    else steps = abs(dx);

    float xInc=0, yInc=0;
    if(steps!=0){
        xInc = dx/steps;
        yInc = dy/steps;
    }

    float x = x1, y = y1;
    for(int i=0; i<steps; i++){
        img.setPixel(x,y,color);
        x+=xInc;
        y+=yInc;
    }

    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);

}


void MainWindow::on_pushButton_3_clicked()
{
    int x1,y1,x2,y2;
    if(undoLine.size()>=4){
        y2 = undoLine.top();
        undoLine.pop();
        x2 = undoLine.top();
        undoLine.pop();
        y1 = undoLine.top();
        undoLine.pop();
        x1 = undoLine.top();
        undoLine.pop();
        DDA(x1,y1,x2,y2,qRgb(0,0,0));
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    img.fill(Qt::black);
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
}


void MainWindow::on_pushButton_2_clicked()
{
    int xc,yc,r;
    xc = ui->xc->toPlainText().toInt();
    yc = ui->yc->toPlainText().toInt();
    r = ui->r->toPlainText().toInt();
    undoCircle.push(xc);
    undoCircle.push(yc);
    undoCircle.push(r);

    bresenham(xc,yc,r,qRgb(255,255,255));
}

void MainWindow::bresenham(int xc, int yc, int r, QRgb color)
{
    int x = 0;
    int y = r;
    drawCircle(xc,yc,x,y,color);
    int d = 3 - 2*r;
    while(y>=x){
        x++;

        if(d>0){
            y--;
            d = d + 4*(x-y)+10;
        }
        else{
            d = d + 4*x + 6;
        }

        drawCircle(xc,yc,x,y,color);
    }
}

void MainWindow::drawCircle(int xc, int yc, int x, int y, QRgb color)
{
    img.setPixel(xc+x,yc+y,color);
    img.setPixel(xc+x,yc-y,color);
    img.setPixel(xc-x,yc+y,color);
    img.setPixel(xc-x,yc-y,color);
    img.setPixel(xc+y,yc+x,color);
    img.setPixel(xc+y,yc-x,color);
    img.setPixel(xc-y,yc+x,color);
    img.setPixel(xc-y,yc-x,color);
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
}


void MainWindow::on_pushButton_4_clicked()
{
    if(undoCircle.size()>=3){
        int r,yc,xc;
        r = undoCircle.top();
        undoCircle.pop();
        yc = undoCircle.top();
        undoCircle.pop();
        xc = undoCircle.top();
        undoCircle.pop();
        bresenham(xc,yc,r,qRgb(0,0,0));
    }
}

