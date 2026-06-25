#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include <QMouseEvent>
#include <QPoint>
#include <QWindow>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCloseEvent>
#include <QApplication>

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

    QRegularExpression rx("[a-zA-Zа-яА-ЯёЁ]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_name->setValidator(validator);
    ui->lineEdit_name->setMaxLength(15);

    QRegularExpression ri("[1-9][0-9]{0,5}");
    QRegularExpressionValidator *intvalidator = new QRegularExpressionValidator(ri, this);
    ui->lineEdit_age->setValidator(intvalidator);
    ui->lineEdit_age->setMaxLength(2);

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
void saveJson(QString input_name, QString input_age, QString input_sex) { //регистрация - сохранение инфы в json
    QJsonObject user_inf;
    user_inf["name"] = input_name;
    user_inf["age"] = input_age;
    user_inf["sex"] = input_sex;
    user_inf["level"] = "1";
    user_inf["rank"] = "soldier";
    user_inf["xp"] = "0";

    QJsonObject userObj;
    userObj["user"] = user_inf;
    QJsonDocument doc(userObj);
    QFile file("config.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();

    }
}
void ThirdWindow::on_regist_but_clicked(){
    QString nameInput = ui->lineEdit_name->text();
    QString ageInput = ui->lineEdit_age->text();
    if (nameInput == "" or ageInput == ""){
        QMessageBox::warning(this,
                             "Ошибка ввода",
                             "Пожалуйста, введите имя и возраст.");
        return;
    }
    QString selectedSex;
    if (ui->radio_male->isChecked()){
        selectedSex = "мужской";
    } else if (ui->radio_female->isChecked()){
        selectedSex = "женский";
    } else {
        QMessageBox::warning(this,
                             "Ошибка выбора",
                             "Пожалуйста, выберите хотя бы один вариант.");
        return;
    }
    saveJson(nameInput, ageInput, selectedSex);
    this->hide();
    emit backToMain();
}
void ThirdWindow::closeEvent(QCloseEvent *event) {
    QApplication::quit();
    event->accept();
}
