#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void DDA(int,int,int,int,QRgb);

    void on_pushButton_2_clicked();
    void cohenSuderland(int,int,int,int);
    int codeCompute(int x,int y);

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    const int TOP=8, BOTTOM=4,RIGHT=2,LEFT=1,INSIDE=0;
    int xMin,xMax,yMin,yMax;
    QPixmap pixmap;
    QRgb color = qRgb(255,255,255);
    QColor qtcolor = Qt::white;
};
#endif // MAINWINDOW_H
