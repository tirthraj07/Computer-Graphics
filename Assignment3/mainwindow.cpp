#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QColorDialog>

QImage img(500,500,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::black);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label_2->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    xMin = ui->xMin->toPlainText().toInt();
    yMin = ui->yMin->toPlainText().toInt();
    xMax = ui->xMax->toPlainText().toInt();
    yMax = ui->yMax->toPlainText().toInt();
    DDA(xMin,yMin,xMin,yMax,color);
    DDA(xMin,yMin,xMax,yMin,color);
    DDA(xMax,yMax,xMin,yMax,color);
    DDA(xMax,yMax,xMax,yMin,color);
    pixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(pixmap);
    ui->label_2->setPixmap(pixmap);
}

void MainWindow::DDA(int x1, int y1, int x2, int y2, QRgb color)
{
    float dx,dy;
    dx = x2 - x1;
    dy = y2 - y1;
    float step=0;

    if(abs(dy)>abs(dx)) step = abs(dy);
    else step = abs(dx);

    float xInc=0,yInc=0;
    if(step!=0){
        xInc = dx/step;
        yInc = dy/step;
    }
    float x=x1,y=y1;
    for(int i=0; i<step; i++){
        img.setPixel(x,y,color);
        x+=xInc;
        y+=yInc;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    int x1,x2,y1,y2;
    x1 = ui->x1->toPlainText().toInt();
    y1 = ui->y1->toPlainText().toInt();
    x2 = ui->x2->toPlainText().toInt();
    y2 = ui->y2->toPlainText().toInt();

    DDA(x1,y1,x2,y2,color);
    ui->label->setPixmap(QPixmap::fromImage(img));

    cohenSuderland(x1,y1,x2,y2);
}

void MainWindow::cohenSuderland(int x1, int y1, int x2, int y2)
{
    int code1 = codeCompute(x1,y1);
    int code2 = codeCompute(x2,y2);
    bool accept = false;
    while(true){
        if(code1==0&&code2==0){
            accept = true;
            break;
        }
        else if(code1&code2){
            break;
        }
        else{
            int code;
            int x,y;

            if(code1!=0){
                code = code1;
            }
            else{
                code = code2;
            }

            if(code&TOP){
                x = x1 + (yMax-y1)*(x2-x1)/(y2-y1);
                y = yMax;
            }
            else if(code&BOTTOM){
                x = x1 + (yMin-y1)*(x2-x1)/(y2-y1);
                y = yMin;
            }
            else if(code&RIGHT){
                y = y1 + (xMax-x1)*(y2-y1)/(x2-x1);
                x = xMax;
            }
            else if(code&LEFT){
                y = y1 + (xMin-x1)*(y2-y2)/(x2-x1);
                x = xMin;
            }
            if(code == code1){
                x1 = x;
                y1 = y;
                code1 = codeCompute(x1,y1);
            }
            else{
                x2 = x;
                y2 = y;
                code2 = codeCompute(x2,y2);
            }
        }
    }
    if(accept){
        //Reset Image

        QPainter painter(&pixmap);
        QPen pen(qtcolor);
        painter.setPen(pen);
        painter.drawLine(x1,y1,x2,y2);
        ui->label_2->setPixmap(pixmap);

    }
}

int MainWindow::codeCompute(int x, int y)
{
    int code = INSIDE;
    if(y>yMax){
        code |= TOP;
    }
    else if(y<yMin){
        code |= BOTTOM;
    }
    if(x>xMax){
        code |= RIGHT;
    }
    else if(x<xMin){
        code |= LEFT;
    }
    return code;
}


void MainWindow::on_pushButton_4_clicked()
{
    QColorDialog dialog;
    qtcolor = dialog.getColor();
    color = qtcolor.rgb();
}

