#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPoint>
#include <QWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sWindow = new SecondWindow();
    tWindow = new ThirdWindow();
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint); //отключение кнопки свернуть
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    QWidget *emptyWidget = new QWidget(ui->centralwidget);
    emptyWidget->setGeometry(0, 0, 800, 40);
    emptyWidget->setStyleSheet("background-color: #383838;");
    emptyWidget->installEventFilter(this);

    ui->x_but->raise();
    ui->minimize_but->raise();
}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::on_x_but_clicked()
{
    this->close();
}
bool MainWindow::eventFilter(QObject *watched, QEvent *event) // логика перетаскивания
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            m_dragPosition = mouseEvent->globalPosition().toPoint() - this->frameGeometry().topLeft();
            return true;
        }
    }
    else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (this->windowHandle()) {
            this->windowHandle()->startSystemMove();
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}
void MainWindow::on_pushButton_2_clicked()
{
    sWindow->show();
    sWindow->activateWindow();
    this->hide();
}
void MainWindow::on_choice_but1_clicked()
{
    connect(tWindow, &ThirdWindow::backToMain, this, &MainWindow::show);
    tWindow->show();
    tWindow->activateWindow();
    this->hide();
}
void MainWindow::on_minimize_but_clicked()
{
    this->showMinimized();
}

