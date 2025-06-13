// main.cpp
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "banklogic.h"
#include "admindialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;

    BankManagement bank;

    QWidget window;
    window.setWindowTitle("Bank Management System");
    QVBoxLayout* layout = new QVBoxLayout(&window);

    QPushButton* adminBtn = new QPushButton("Admin Login", &window);
    QPushButton* exitBtn = new QPushButton("Exit", &window);

    layout->addWidget(adminBtn);
    layout->addWidget(exitBtn);

    QObject::connect(adminBtn, &QPushButton::clicked, [&]() {
        AdminDialog dlg(&bank, &window);
        dlg.exec();
    });
    QObject::connect(exitBtn, &QPushButton::clicked, &app, &QApplication::quit);

    window.show();
    w.show();
    return app.exec();
}