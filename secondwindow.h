#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QLabel>

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
    void readJsonFile(const QString &filePath);
};

#endif // SECONDWINDOW_H
