#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QMap>
#include <QGlobalStatic>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void onButtonSelectClicked();
private:
    Ui::SecondWindow *ui;
    QLabel *label_name;
    QWidget *xp_sum;
    void readJsonFile(const QString &filePath);


};

#endif // SECONDWINDOW_H
