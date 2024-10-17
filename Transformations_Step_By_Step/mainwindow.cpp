#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPolygonF>
#include <QPointF>
#include <cmath>

// Triangle vertices: (75, 25), (50, 75), (100, 75)
// Rhombus vertices: (50, 10), (90, 50), (50, 90), (10, 50)

/*
 * Step 1: Create an image of 500 x 500 and fill it with black colour
 * Step 2: Map that image to a pixmap
 * Step 3: Caste that image to the lable on which we are going to show our output
 * Step 4: Create a QPainter object and pass the address of the pixmmap
 * Step 5: Create a QPen object and set the colour of the pen to white
 * Step 6: Assign that Pen to the QPainter object
 * Step 7: Using the QPainter object, draw the axes at (250,0,250,500) and (0,250,500,250)
 * Step 8: Cast that pixmap onto the label
 *
 * Note: Now our shifted origin is 250,250 and not 0,0
 *
 */


QImage image(500,500,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image.fill(Qt::black);
    pixmap = QPixmap::fromImage(image);

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);
    painter.drawLine(250,0,250,500);
    painter.drawLine(0,250,500,250);

    ui->label->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
* Step 1: Declare triangle vertex points in mainwindow.h (int tx1,tx2,ty1,ty2,tx3,ty3;)
* Step 2: Assign them values from plain text edits
* Step 3: Translate the coordinates with respect to the shifted origin: 250,250
* Step 4: Create a QPainter object and pass the address of the QPixmap and assign a pen to it which is white in colour
* Step 5: Create a QPolygonF object "triangle"
* Step 6: Assign that QPolygonF object the coordinate values using QPointF
* Step 7: Make the painter draw that polygon
* Step 8: Update the pixmap on the label
*
*/

void MainWindow::on_pushButton_clicked()
{
    //Note: tx1 stands for triangle coordinate 1

    tx1 = ui->TX1->toPlainText().toInt();
    ty1 = ui->TY1->toPlainText().toInt();
    tx2 = ui->TX2->toPlainText().toInt();
    ty2 = ui->TY2->toPlainText().toInt();
    tx3 = ui->TX3->toPlainText().toInt();
    ty3 = ui->TY3->toPlainText().toInt();

    tx1 += 250;
    ty1 = 250 - ty1;
    tx2 += 250;
    ty2 = 250 - ty2;
    tx3 += 250;
    ty3 = 250 - ty3;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);


    QPolygonF triangle;
    triangle << QPointF(tx1,ty1) << QPointF(tx2,ty2)<< QPointF(tx3,ty3);

    painter.drawPolygon(triangle);

    ui->label->setPixmap(pixmap);
}

/*
* Step 1: Declare rhombus vertex points in mainwindow.h (int rx1,rx2,ry1,ry2,rx3,ry3,rx4,ry4;)
* Step 2: Assign them values from plain text edits
* Step 3: Translate the coordinates with respect to the shifted origin: 250,250
* Step 4: Create a QPainter object and pass the address of the QPixmap and assign a pen to it which is white in colour
* Step 5: Create a QPolygonF object "rhombus"
* Step 6: Assign that QPolygonF object the coordinate values using QPointF
* Step 7: Make the painter draw that polygon
* Step 8: Update the pixmap on the label
*
*/

void MainWindow::on_pushButton_2_clicked()
{
    //Note: rx1 stands for rhombus x coordinate 1

    rx1 = ui->RX1->toPlainText().toInt();
    ry1 = ui->RY1->toPlainText().toInt();
    rx2 = ui->RX2->toPlainText().toInt();
    ry2 = ui->RY2->toPlainText().toInt();
    rx3 = ui->RX3->toPlainText().toInt();
    ry3 = ui->RY3->toPlainText().toInt();
    rx4 = ui->RX4->toPlainText().toInt();
    ry4 = ui->RY4->toPlainText().toInt();

    rx1 += 250;
    ry1 = 250 - ry1;
    rx2 += 250;
    ry2 = 250 - ry2;
    rx3 += 250;
    ry3 = 250 - ry3;
    rx4 += 250;
    ry4 = 250 - ry4;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);

    QPolygonF rhombus;
    rhombus << QPointF(rx1,ry1)<< QPointF(rx2,ry2)<< QPointF(rx3,ry3)<< QPointF(rx4,ry4);

    painter.drawPolygon(rhombus);

    ui->label->setPixmap(pixmap);


}

/*
* Step 1: Delare varibles to store the translated coordinates in function or header file (Here I have declared in function)
* Step 2: Read tx and ty from the ui plain text edit
* Step 3: Use Formula: xnew = xold + tx and ynew = yold + ty
* But in QT, the Y coordinate starts from top instead of bottom, we do ynew = yold - ty
* Step 4: Create a QPainter object and pass the address of the pixmap. Assign it a pen which is white in colour
* Step 5: Create a QPolygonF object "triange"
* Step 6: Assign the translated coordinates to the triangle object
* Step 7: Make the painter draw that polygon
* Step 8: Update the pixmap on the label.
*
*/


void MainWindow::on_pushButton_3_clicked()
{
    //Note: ttx1 stands for translated triangle x coordinate 1
    int ttx1,tty1,ttx2,tty2,ttx3,tty3;
    int tx,ty;

    tx = ui->TX->toPlainText().toInt();
    ty = ui->TY->toPlainText().toInt();

    ttx1 = tx1 + tx;
    tty1 = ty1 - ty;
    ttx2 = tx2 + tx;
    tty2 = ty2 - ty;
    ttx3 = tx3 + tx;
    tty3 = ty3 - ty;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);

    QPolygonF triangle;
    triangle << QPointF(ttx1,tty1) << QPointF(ttx2,tty2) << QPointF(ttx3,tty3);

    painter.drawPolygon(triangle);

    ui->label->setPixmap(pixmap);
}

/*
* Step 1: Delare varibles to store the translated coordinates in function or header file (Here I have declared in function)
* Step 2: Read tx and ty from the ui plain text edit
* Step 3: Use Formula: xnew = xold + tx and ynew = yold + ty
* But in QT, the Y coordinate starts from top instead of bottom, we do ynew = yold - ty
* Step 4: Create a QPainter object and pass the address of the pixmap. Assign it a pen which is white in colour
* Step 5: Create a QPolygonF object "rhombus"
* Step 6: Assign the translated coordinates to the rhombus object
* Step 7: Make the painter draw that polygon
* Step 8: Update the pixmap on the label.
*
*/


void MainWindow::on_pushButton_4_clicked()
{
    //Note: trx1 stands for translated rhombus coordinate 1
    int trx1,try1,trx2,try2,trx3,try3,trx4,try4;
    int tx,ty;

    tx = ui->TX->toPlainText().toInt();
    ty = ui->TY->toPlainText().toInt();

    trx1 = rx1 + tx;
    try1 = ry1 - ty;
    trx2 = rx2 + tx;
    try2 = ry2 - ty;
    trx3 = rx3 + tx;
    try3 = ry3 - ty;
    trx4 = rx4 + tx;
    try4 = ry4 - ty;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);

    QPolygonF rhombus;
    rhombus << QPointF(trx1,try1) << QPointF(trx2,try2) << QPointF(trx3,try3) << QPointF(trx4,try4);

    painter.drawPolygon(rhombus);

    ui->label->setPixmap(pixmap);


}

/*
* Step 1: Delare varibles to store the scaled coordinates in function or header file (Here I have declared in function)
* Step 2: Read sx and sy from the ui plain text edit
* Step 3: Read the x1, y1, x2, y2, x3, y3 coordinates as well
* This is so because the formula is x*sx and y*sy But we have added 250,250 to both x and y initially.
* So if we multiply the values stored in tx1,ty1,.. , sx and sy will be multiplied to 250 and 250 as well, which we don't want
* Step 4: Use formula: xnew = xold*sx and ynew= ynew*sy
* Step 5: Shift these coordinates with respected to shifted origin at 250,250
* Step 6: Create a QPainter object and pass the address of pixmap and assign a white colour pen to it
* Step 7: Create a QPolygonF object "triangle" and assign the scaled coordinates to it
* Step 8: Make the painter draw the Polygon
* Step 9: Update the pixmapn on label
*/

void MainWindow::on_pushButton_5_clicked()
{
    //Note: stx1 stands for scaled triangle x coordinate 1
    int stx1,sty1,stx2,sty2,stx3,sty3;
    int sx,sy;

    sx = ui->SX->toPlainText().toInt();
    sy = ui->SY->toPlainText().toInt();
    stx1 = ui->TX1->toPlainText().toInt();
    sty1 = ui->TY1->toPlainText().toInt();
    stx2 = ui->TX2->toPlainText().toInt();
    sty2 = ui->TY2->toPlainText().toInt();
    stx3 = ui->TX3->toPlainText().toInt();
    sty3 = ui->TY3->toPlainText().toInt();


    stx1 = stx1*sx;
    sty1 = sty1*sy;
    stx2 = stx2*sx;
    sty2 = sty2*sy;
    stx3 = stx3*sx;
    sty3 = sty3*sy;

    stx1 += 250;
    sty1 = 250 - sty1;
    stx2 += 250;
    sty2 = 250 - sty2;
    stx3 += 250;
    sty3 = 250 - sty3;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);

    QPolygonF triangle;
    triangle << QPointF(stx1,sty1) << QPointF(stx2,sty2) << QPointF(stx3,sty3);

    painter.drawPolygon(triangle);

    ui->label->setPixmap(pixmap);
}

/*
* Step 1: Delare varibles to store the scaled coordinates in function or header file (Here I have declared in function)
* Step 2: Read sx and sy from the ui plain text edit
* Step 3: Read the x1, y1, x2, y2, x3, y3, x4, y4 coordinates as well
* This is so because the formula is x*sx and y*sy But we have added 250,250 to both x and y initially.
* So if we multiply the values stored in rx1,ry1,.. , sx and sy will be multiplied to 250 and 250 as well, which we don't want
* Step 4: Use formula: xnew = xold*sx and ynew= ynew*sy
* Step 5: Shift these coordinates with respected to shifted origin at 250,250
* Step 6: Create a QPainter object and pass the address of pixmap and assign a white colour pen to it
* Step 7: Create a QPolygonF object "rhombus" and assign the scaled coordinates to it
* Step 8: Make the painter draw the Polygon
* Step 9: Update the pixmapn on label
*/

void MainWindow::on_pushButton_6_clicked()
{
    //Note: srx1 stands for scaled rhombus x coordinate 1
    int srx1,sry1,srx2,sry2,srx3,sry3,srx4,sry4;
    int sx,sy;

    sx = ui->SX->toPlainText().toInt();
    sy = ui->SY->toPlainText().toInt();
    srx1 = ui->RX1->toPlainText().toInt();
    sry1 = ui->RY1->toPlainText().toInt();
    srx2 = ui->RX2->toPlainText().toInt();
    sry2 = ui->RY2->toPlainText().toInt();
    srx3 = ui->RX3->toPlainText().toInt();
    sry3 = ui->RY3->toPlainText().toInt();
    srx4 = ui->RX4->toPlainText().toInt();
    sry4 = ui->RY4->toPlainText().toInt();


    srx1 = srx1*sx;
    sry1 = sry1*sy;
    srx2 = srx2*sx;
    sry2 = sry2*sy;
    srx3 = srx3*sx;
    sry3 = sry3*sy;
    srx4 = srx4*sx;
    sry4 = sry4*sy;

    srx1 += 250;
    sry1 = 250 - sry1;
    srx2 += 250;
    sry2 = 250 - sry2;
    srx3 += 250;
    sry3 = 250 - sry3;
    srx4 += 250;
    sry4 = 250 - sry4;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);

    QPolygonF rhombus;
    rhombus << QPointF(srx1,sry1) << QPointF(srx2,sry2) << QPointF(srx3,sry3) << QPointF(srx4,sry4);

    painter.drawPolygon(rhombus);

    ui->label->setPixmap(pixmap);
}


void MainWindow::on_pushButton_7_clicked()
{
    float rtx1, rty1, rtx2, rty2, rtx3, rty3;
    float tx1, ty1, tx2, ty2, tx3, ty3;
    float deg;

    deg = ui->DEG->toPlainText().toInt();
    tx1 = ui->TX1->toPlainText().toInt();
    ty1 = ui->TY1->toPlainText().toInt();
    tx2 = ui->TX2->toPlainText().toInt();
    ty2 = ui->TY2->toPlainText().toInt();
    tx3 = ui->TX3->toPlainText().toInt();
    ty3 = ui->TY3->toPlainText().toInt();

    float radian = qDegreesToRadians(deg);

    rtx1 = tx1*cos(radian) - ty1*sin(radian);
    rty1 = tx1*sin(radian) + ty1*cos(radian);
    rtx2 = tx2*cos(radian) - ty2*sin(radian);
    rty2 = tx2*sin(radian) + ty2*cos(radian);
    rtx3 = tx3*cos(radian) - ty3*sin(radian);
    rty3 = tx3*sin(radian) + ty3*cos(radian);

    rtx1 += 250;
    rty1 = 250 - rty1;
    rtx2 += 250;
    rty2 = 250 - rty2;
    rtx3 += 250;
    rty3 = 250 - rty3;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);

    QPolygonF triangle;
    triangle << QPointF(rtx1,rty1) << QPointF(rtx2,rty2) << QPointF(rtx3,rty3);

    painter.drawPolygon(triangle);

    ui->label->setPixmap(pixmap);

}


void MainWindow::on_pushButton_8_clicked()
{
    float rrx1, rry1, rrx2, rry2, rrx3, rry3, rrx4, rry4;
    float rx1, ry1, rx2, ry2, rx3, ry3, rx4, ry4;
    float deg;

    deg = ui->DEG->toPlainText().toInt();
    rx1 = ui->RX1->toPlainText().toInt();
    ry1 = ui->RY1->toPlainText().toInt();
    rx2 = ui->RX2->toPlainText().toInt();
    ry2 = ui->RY2->toPlainText().toInt();
    rx3 = ui->RX3->toPlainText().toInt();
    ry3 = ui->RY3->toPlainText().toInt();
    rx4 = ui->RX4->toPlainText().toInt();
    ry4 = ui->RY4->toPlainText().toInt();

    float radian = qDegreesToRadians(deg);

    rrx1 = rx1*cos(radian) - ry1*sin(radian);
    rry1 = rx1*sin(radian) + ry1*cos(radian);
    rrx2 = rx2*cos(radian) - ry2*sin(radian);
    rry2 = rx2*sin(radian) + ry2*cos(radian);
    rrx3 = rx3*cos(radian) - ry3*sin(radian);
    rry3 = rx3*sin(radian) + ry3*cos(radian);
    rrx4 = rx4*cos(radian) - ry4*sin(radian);
    rry4 = rx4*sin(radian) + ry4*cos(radian);

    rrx1 += 250;
    rry1 = 250 - rry1;
    rrx2 += 250;
    rry2 = 250 - rry2;
    rrx3 += 250;
    rry3 = 250 - rry3;
    rrx4 += 250;
    rry4 = 250 - rry4;

    QPainter painter(&pixmap);
    QPen pen(Qt::white);
    painter.setPen(pen);

    QPolygonF rhombus;
    rhombus << QPointF(rrx1,rry1) << QPointF(rrx2,rry2) << QPointF(rrx3,rry3) << QPointF(rrx4,rry4);

    painter.drawPolygon(rhombus);

    ui->label->setPixmap(pixmap);
}

