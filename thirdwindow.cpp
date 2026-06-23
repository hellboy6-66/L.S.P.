#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include <QMouseEvent>
#include <QPoint>
#include <QWindow>

ThirdWindow::ThirdWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThirdWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint); //отключение кнопки свернуть
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    QWidget *emptyWidget = new QWidget(this);
    emptyWidget->setGeometry(0, 0, 800, 40);
    emptyWidget->setStyleSheet("background-color: #383838;");
    emptyWidget->installEventFilter(this);

    ui->but_x->raise();
    ui->but_minimize->raise();
}

ThirdWindow::~ThirdWindow()
{
    delete ui;
}

void ThirdWindow::on_but_x_clicked()
{
    this->close();
}



void ThirdWindow::on_but_minimize_clicked()
{
    this->showMinimized();
}
bool ThirdWindow::eventFilter(QObject *watched, QEvent *event) // логика перетаскивания
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
    return QWidget::eventFilter(watched, event);
}
