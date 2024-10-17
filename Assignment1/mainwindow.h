#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack>
using namespace std;


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

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void bresenham(int,int,int,QRgb);

    void drawCircle(int,int,int,int,QRgb);

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    stack<int> undoLine;
    stack<int> undoCircle;
};
#endif // MAINWINDOW_H
