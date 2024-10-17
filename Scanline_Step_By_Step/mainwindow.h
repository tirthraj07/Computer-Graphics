#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

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

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void drawLine(int,int,int,int);

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    std::vector<int> x;     //To store x coordinates of given polygon
    std::vector<int> y;     //To store y coordinates of given polygon
    std::vector<float> slope; //To store slopes of two consecutive points
};
#endif // MAINWINDOW_H
