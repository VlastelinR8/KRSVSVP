#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


//    QImage myImage;
//    myImage.load("C:\\Users\\Vlastelin\\Documents\\KPSVP\\pack.png");

//    QLabel myLabel;
//    myLabel.setPixmap(QPixmap::fromImage(myImage));

//    myLabel.show();

//    QGraphicsScene scene;
//    QGraphicsView view(&scene);
//    QGraphicsPixmapItem item(QPixmap("C:\\Users\\Vlastelin\\Documents\\KPSVP\\pack.png"));
//    item = w.greyScale(item);
//    scene.addItem(&item);
//    view.show();


   w.show();


    return a.exec();
}
