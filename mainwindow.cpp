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
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    QWidget *emptyWidget = new QWidget(ui->centralwidget);
    emptyWidget->setGeometry(0, 0, 800, 40);
    emptyWidget->setStyleSheet("background-color: #383838;");
    emptyWidget->installEventFilter(this);

    ui->x_but->raise();


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_x_but_clicked()
{
    this->close();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
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
