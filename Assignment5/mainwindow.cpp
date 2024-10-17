#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include <vector>
using namespace std;

QImage img(500,500,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::black);
    pixmap = QPixmap::fromImage(img);
    ui->label_2->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int order = ui->order->toPlainText().toInt(&ok);
    if(ok){
        vector<int> x = {250,150,350,250};
        vector<int> y = {50,223,223,50};
        for(int i=0; i<x.size()-1;i++){
            koch(order,x[i],y[i],x[i+1],y[i+1]);
        }
    }
}

void MainWindow::DDA(int x1, int y1, int x2, int y2)
{
    float dx,dy;
    dx = x2-x1;
    dy = y2-y1;
    float steps = 0;
    if(abs(dy)>abs(dx)){
        steps = abs(dy);
    }
    else{
        steps = abs(dx);
    }

    float xInc=0,yInc=0;
    if(steps!=0){
        xInc = dx/steps;
        yInc = dy/steps;
    }
    float x=x1,y=y1;

    for(int i=0; i<steps; i++){
        img.setPixel(x,y,col);
        x += xInc;
        y += yInc;
    }

    pixmap = QPixmap::fromImage(img);
    ui->label_2->setPixmap(pixmap);


}

void MainWindow::koch(int order,int x1, int y1, int x5, int y5)
{
    if(order==0){
        DDA(x1,y1,x5,y5);
    }
    else{
        int x2,y2,x3,y3,x4,y4;
        int dx = (x5-x1)/3;
        int dy = (y5-y1)/3;

        x2 = x1 + dx;
        y2 = y1 + dy;

        x4 = x1 + 2*dx;
        y4 = y1 + 2*dy;

        x3 = (x1+x5)/2 + (sqrt(3)*(y1-y5))/6;
        y3 = (y1+y5)/2 + (sqrt(3)*(x5-x1))/6;

        koch(order-1,x1,y1,x2,y2);
        koch(order-1,x2,y2,x3,y3);
        koch(order-1,x3,y3,x4,y4);
        koch(order-1,x4,y4,x5,y5);

    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QColorDialog dialog;
    QColor color = dialog.getColor();
    col = color.rgb();
}

