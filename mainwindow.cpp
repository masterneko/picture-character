#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QtGui>
#include <QString>
#include <QLabel>

#include <QDebug>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background:transparent;");
    ui->label->setStyleSheet("background-color: black;");
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAcceptDrops(true);
    //setWindowOpacity(qreal(90)/100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_label_linkActivated(const QString &link)
{
}

void MainWindow::on_label_linkHovered(const QString &link)
{
    if(ui->label->underMouse()){
        ui->label->setAcceptDrops(true);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}
void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;
        ui->label->setText( "" );
        int w = ui->label->width();
        int h = ui->label->height();
        setWindowOpacity(qreal(100)/100);
        ui->label->setStyleSheet("background-color: transparent;");
        QFileInfo fileInformatation(fileName);
        if(fileInformatation.suffix() == "gif"){
            QPixmap pic(fileName);
            pic = pic.scaled(w,h,Qt::KeepAspectRatio);
            ui->label->setMask(pic.mask());
            QMovie *movie = new QMovie(fileName);
            ui->label->setMovie(movie);
            movie->start();
        }else{
        QPixmap pic(fileName);
        ui->label->setPixmap(pic.scaled(w,h,Qt::KeepAspectRatio));
        }
    }
}
