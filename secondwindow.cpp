#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QCloseEvent>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>

SecondWindow::SecondWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    //bool login = false;
}

SecondWindow::~SecondWindow()
{
    delete ui;
}
void SecondWindow::closeEvent(QCloseEvent *event) {
    QApplication::quit();
    event->accept();
}
void readJsonFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл!";
        return;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);

    if (document.isObject()) {
        QJsonObject rootObject = document.object();

        // 1. Достаем вложенный объект "user"
        QJsonObject object = rootObject["user"].toObject();

        QString name = object["name"].toString();
        int age = object["age"].toString().toInt();
        QString level = object["level"].toString();
        QString  rank = object["rank"].toString();
        QString sex = object["sex"].toString();
        int xp = object["xp"].toInt();
        qDebug() << "Имя:" << name;
        qDebug() << "Возраст:" << age;

    }
}
void SecondWindow::on_pushButton_clicked()
{

    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Выберите файл",
                                                    "",
                                                    "All Files (*.*)");
    if (!filePath.isEmpty()) {
        readJsonFile(filePath);
        qDebug() << "Выбранный путь:" << filePath;
    } else {
         return;
    }

}

