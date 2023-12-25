#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    (*ui).setupUi(this);
//    myImage1.load("C:\\Users\\Vlastelin\\Documents\\KPSVP\\Screenshot_95.png");
//    loadImg();
    m_split = 256*m_diff;
    ui->label->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    QSize screenSize = ui->centralWidget->size();
    //QSize screenSize = QDesktopWidget().availableGeometry(this).size();
    ui->label->resize(screenSize.width(), screenSize.height());
    ui->spinBox->move(screenSize.width()-ui->spinBox->width(),0);

}

QImage * MainWindow::greyScale(QImage *origin){
    QImage * newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

    QColor oldColor;

    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(origin->pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average,average,average));
        }
    }

    return newImage;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(m_imgH) {
        QPoint pos = event->pos();
        QSize winSz = ui->centralWidget->size();

        int PCX = (double)pos.x()/winSz.width()*m_imgW;
        int PCY = (double)pos.y()/winSz.height()*m_imgH;
        QColor realColor = QColor(myImage2->pixel(PCX,PCY));
        curPixIntence = (realColor.red()+realColor.green()+realColor.blue())/3;

        std::map<int, std::map<int, bool>> checked;
        std::map<int, std::map<int, bool>> check;

        for(int dy=-1;dy<=1;dy++) for(int dx=-1;dx<=1;dx++) {
            check[PCY+dy][PCX+dx]=1;
            checked[PCY+dy][PCX+dx]=1;
        }
        //    clock_t start= clock();
        myImage2=greyScale(&myImage1);

        while((int)check.size()!=0) {
            for (auto const &i : check) {
                if ((int)check[i.first].size() == 0) {
                    check.erase(i.first);
                    continue;
                }
                for(auto const &j:i.second) {

                    if(checkDepth(j.first,i.first)) {
                        myImage2->setPixel(j.first,i.first,qRgb(255,0,0));
                        for(int dy=-1;dy<=1;dy++) for(int dx=-1;dx<=1;dx++) {
                            if(!checked[i.first+dy][j.first+dx] && i.first+dy>=0 && i.first+dy<m_imgH && j.first+dx>=0 && j.first+dx<m_imgW) {
                                checked[i.first+dy][j.first+dx] = 1;
                                check[i.first+dy][j.first+dx] = 1;
                                //std::cout<<i.first+dy<<" "<<j.first+dx<<std::endl;
                            }
                        }
                    }
                    check[i.first].erase(j.first);
                }

            }
        }

        ui->label->setPixmap(QPixmap::fromImage(*myImage2));
    }
}

int MainWindow::checkDepth(int x,int y) {
    QColor adjColor = QColor(myImage2->pixel(x,y));
    int average = (adjColor.red()+adjColor.green()+adjColor.blue())/3;
    if(average<curPixIntence+m_split && average>curPixIntence-m_split) return 1;
    else {return 0;}
}
void MainWindow::loadImg() {
    myImage2=greyScale(&myImage1);
    m_imgH = myImage2->height();
    m_imgW = myImage2->width();
    ui->label->setPixmap(QPixmap::fromImage(*myImage2));
    ui->label->resize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    m_split = 255*((double)arg1/100);
    //std::cout<<m_split<<""<<(double)arg1/100;
}

void MainWindow::on_pushButton_pressed()
{
    QString a = QFileDialog::getOpenFileName(this,tr("Open File"), "", "PNG (*.PNG; *.PNS)");
    myImage1.load(a);
    loadImg();
    //std::cout<<a.toStdString();
}
