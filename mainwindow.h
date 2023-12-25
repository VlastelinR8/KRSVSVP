#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QDesktopWidget>

#include <QImage>
#include <QImageReader>
#include <QSize>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QLabel>
#include <QResizeEvent>

#include <iostream>
#include <map>
#include <typeinfo>
#include <time.h>

#include <QString>

#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event) final;
    void mousePressEvent(QMouseEvent* event);
    void loadImg();
    int checkDepth(int x, int y);
    QImage *greyScale(QImage *origin);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_pressed();

private:
    QImage *myImage2;
    QImage myImage1;
    int m_imgW, m_imgH=0;
    int curPixIntence;
    float m_diff = 0.2;
    int m_split;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
