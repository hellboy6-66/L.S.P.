#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_x_but_clicked()
{
    this->close();
}

