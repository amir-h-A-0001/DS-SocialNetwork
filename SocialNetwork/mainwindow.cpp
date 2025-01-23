#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFramesShadow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFramesShadow() {
    QGraphicsDropShadowEffect *coverShadow = new QGraphicsDropShadowEffect(ui->userInformationF);
    coverShadow->setBlurRadius(40.0);
    coverShadow->setColor(palette().color(QPalette::Shadow));
    coverShadow->setOffset(0.0);
    ui->userInformationF->setGraphicsEffect(coverShadow);

}
