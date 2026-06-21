#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_x_but_clicked();


    void on_pushButton_2_clicked();

    void on_x_but_2_clicked();

private:
    Ui::MainWindow *ui;
    SecondWindow *sWindow;
    QPoint m_dragPosition;

};


#endif // MAINWINDOW_H
