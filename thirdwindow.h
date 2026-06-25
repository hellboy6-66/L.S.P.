#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QWidget>

namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = nullptr);
    ~ThirdWindow();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::ThirdWindow *ui;
    QPoint m_dragPosition;
signals:
    void backToMain();
private slots:
    void on_but_x_clicked();
    void on_but_minimize_clicked();
    void on_regist_but_clicked();
};

#endif // THIRDWINDOW_H
