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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

SecondWindow::SecondWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this); //дизайн верхней панели
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QWidget *topBar = new QWidget();
    topBar->setFixedHeight(50);
    topBar->setStyleSheet("background-color: #383838;");

    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(10, 0, 10, 0);

    QWidget *spacerWidget = new QWidget();
    topLayout->addWidget(spacerWidget, 1);

    label_name = new QLabel("Имя");
    topLayout->addWidget(label_name);

    QWidget *xp_bar = new QWidget();
    xp_bar->setFixedSize(200, 10);
    xp_bar->setStyleSheet("background-color: darkgray;");
    topLayout->addWidget(xp_bar);

    QWidget *xp_sum = new QWidget(xp_bar);
    xp_sum->setFixedSize(100, 10);
    xp_sum->setStyleSheet("background-color: green;");
    xp_sum->move(0, 0);

    mainLayout->addWidget(topBar);

    mainLayout->addStretch(1);

    //дизайн остального
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch(1);

    QPushButton *button_select = new QPushButton("Выбрать", this);
    connect(button_select, &QPushButton::clicked, this, &SecondWindow::onButtonSelectClicked);
    hLayout->addWidget(button_select);

    hLayout->addStretch(1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(hLayout);
    mainLayout->addStretch(1);

    mainLayout->addLayout(hLayout);
    mainLayout->addStretch(1);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}
void SecondWindow::closeEvent(QCloseEvent *event) {
    QApplication::quit();
    event->accept();
}
void SecondWindow::readJsonFile(const QString &filePath) {
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
        label_name->setText(name);
        qDebug() << "Возраст:" << age;

    }
}
void SecondWindow::onButtonSelectClicked() {
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


