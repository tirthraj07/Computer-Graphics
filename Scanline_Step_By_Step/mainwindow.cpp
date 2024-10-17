#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QImage>
#include<QPixmap>
#include<vector>
#include<QPainter>
#include<QPen>
#include<QPointF>
#include<QPolygonF>

// Make an image of 500 x 500 with format RGB 888

QImage image(500,500,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //fill the image with black colour

    image.fill(Qt::black);

    //Define a QPixmap object called pixmap in mainwindow.h for later use
    //Cast the image onto the pixmap
    pixmap = QPixmap::fromImage(image);

    //Now cast the pixmap onto the label
    ui->label->setPixmap(pixmap);

    //Thus you have a black output screen :)
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Now create an array/vector to store points x and y of polygon
// Define that array in mainwindow.h
// Note: x[i], y[i] refer to one point

// When 'Enter point' button is clicked, the points are stored in the array
void MainWindow::on_pushButton_clicked()
{
    //Take the x and y points from user and store in our array/vector
    int xPoint = ui->x->toPlainText().toInt();
    int yPoint = ui->y->toPlainText().toInt();
    x.push_back(xPoint);
    y.push_back(yPoint);

    // Just plot the point on image so that the user can see what polygon is being drawn
    // To do that, create a QPainter object called painter and pass the address of the pixmap you want to edit
    QPainter painter(&pixmap);
    // Give the painter a white pen to draw.
    QPen pen(Qt::white);
    painter.setPen(pen);
    // Make the painter draw that point
    painter.drawPoint(QPoint(xPoint,yPoint));
    // Update the pixmap
    ui->label->setPixmap(pixmap);
}


// When 'Draw Polygon' button is pressed
void MainWindow::on_pushButton_2_clicked()
{
    // After storing the coordinates of points in our vector, don't forget to append the first point in the array again to complete the polygon
    // Check if the user has already done it for us. If yes, then no need to append :)
    // So check if the last element in x == first element in x and last element in y == first element in y

    if(x[x.size()-1]!=x[0]||y[y.size()-1]!=y[0]){
        x.push_back(x[0]);
        y.push_back(y[0]);
    }

    // To draw a polygon, we simply create a QPolygon object (Don't forget to include QPolygonF library (F stands for floating point, i.e if decimal exists)
    QPolygonF poly;

    // Now just enter the points in this polygon object. QT will automatically create polygon for you :)
    // Just pass the x and y coordinates in QPointF
    for(int i=0; i<x.size()-1;i++){
        poly<< QPointF(x[i],y[i]);
    }

    // Now polygon is created, but you need to draw that polygon.
    // For that create a QPainter object and pass the address of pixmap you want the painter to draw on :)
    QPainter painter(&pixmap);


    // Give the painter a white pen to draw :)
    QPen pen(Qt::white);
    painter.setPen(pen);

    // Make the painter paint that Polygon on the pixmap
    painter.drawPolygon(poly);

    // Update the pixmap
    ui->label->setPixmap(pixmap);

}


// By this far, we have drawn a polygon
// We also have an array of x and y coordinates of that polygon.
// Now we have to implement the SCAN LINE Algorithm

// Draws a line
void MainWindow::drawLine(int x1, int y1, int x2, int y2)
{
    // Create a QPainter object painter
    QPainter painter(&pixmap);
    // Create a coloured pen
    QPen pen(Qt::yellow);
    painter.setPen(pen);
    // Make painter draw line
    painter.drawLine(x1,y1,x2,y2);
    
}


// If 'fill polygon button' is clicked
void MainWindow::on_pushButton_3_clicked()
{
    // Step 1: Calculate the slopes of two consecutive points in our vector/array and store it in another vector called slope
    // Declare that slope array/vector in mainwindow.h file for later use.
    // Make that vector of 'float' data type as dy/dx can be decimal
    // This slope[i] is the slope of line between points (x[i],y[i]) and (x[i+1],y[i+1])

    // Calculate dy and dx for all the points
    float dy, dx;
    for(int i=0; i<=x.size()-2;i++){     // Iterate till the second last element
        dy = y[i+1] - y[i];
        dx = x[i+1] - x[i];

        // Beware of edge cases like division by 0
        if(dy==0.0f){
            slope.push_back(1.0);
        }
        else if(dx==0.0f){
            slope.push_back(0.0);
        }
        else{
            slope.push_back(dx/dy); // INVERSE OF SLOPE!!!!!! DON"T MAKE THIS MISTAKEEEE!! I SPENT 1 HOUR DEBUGGING THIS!
        }
    }

    // Now we have slope array :)

    // Step 2: In scan fill algorithm, our scanline goes from ymin to ymax
    // Here our ymin = 0 and ymax = 500
    // Note: In QT Creator moving from ymin = 0 to ymax = 500, means going from TOP to BOTTOM and not the other way!

    // Now create a vector/array called xIntersection. You will need this later.
    // This vector will keep track of all the intersections of polygon in that perticular scan line
    // Say scanline is at y = k, and it intersects the polygon at x1,x2. Then append that x1,x2 on to the Array so that we can draw a line later :)

    std::vector<int> xIntersections;

    //Initiate a loop that iterates through each pixel row on the screen, from y=0 to y=499.
    for(int scanline=0; scanline<500; scanline++){


        // Clear the xIntersections vector before each scanline

        xIntersections.clear();

        // Iterate through each edge of the polygon.
        // Check if the current scanline intersects with any edges
        // i.e, just check if the current y lies between y[i] and y[i+1]
        // Note: y[i] >= scanline >= y[i+1] OR y[i] <= scanline <= y[i+1]
        // If yes then find the xIntersection point
        // We Know: m = (y2 - y1)/(x2 - x1)
        // Thus: x2 = x1 + (1/m)*(y2 - y1) HERE WE NEED INVERSE OF SLOPE!
        // Here y2 = scanline and we need to find x when y = scanline.
        // Therefore: x[i] + slope[i]*(scanline - y[i]) OUR SLOPE[i] STORES INVERSE OF SLOPE SO WE JUST MULTIPLY

        for(int i=0; i<=y.size()-2; i++){

            // Check if y[i] >= scanline >= y[i+1]

            if(y[i] > scanline && scanline >=y[i+1]){
                int xScanline = int(x[i] + slope[i] * (scanline - y[i]));
                xIntersections.push_back(xScanline);
            }

            // Also check if y[i] <= scanline <= y[i+1]. So the same. The formula won't change :)

            else if(y[i]<=scanline && scanline < y[i+1]){
                int xScanline = int(x[i] + slope[i] * (scanline - y[i]));
                xIntersections.push_back(xScanline);
            }

        }



        // Now we have the XInterSection Array for the particular Scan Line

        // Step 3: Sorting the Intersections
        // Sort the x-coordinates of the intersections in descending order
        sort(xIntersections.begin(),xIntersections.end());
        reverse(xIntersections.begin(),xIntersections.end());

        // Now draw a line between xIntersections[i],scanline and xIntersections[i+1],scanline

        if(xIntersections.size()>1){
            for(int i=0; i<xIntersections.size()-1; i=i+2){
                if(i==xIntersections.size()-1) break;
                // Call a function drawLine that draws a line :)

                drawLine(xIntersections[i],scanline,xIntersections[i+1],scanline);

            }
        }



    }

    ui->label->setPixmap(pixmap);

}


