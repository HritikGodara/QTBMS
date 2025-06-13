#include "mainwindow.h"
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>
#include "admindialog.h"
#include "clientdialog.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    auto *adminBtn = new QPushButton("Admin Login", this);
    auto *clientBtn = new QPushButton("Client Login", this);
    auto *exitBtn = new QPushButton("Exit", this);

    layout->addWidget(adminBtn);
    layout->addWidget(clientBtn);
    layout->addWidget(exitBtn);

    setCentralWidget(central);

    connect(adminBtn, &QPushButton::clicked, this, &MainWindow::adminLogin);
    connect(clientBtn, &QPushButton::clicked, this, &MainWindow::clientLogin);
    connect(exitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}

void MainWindow::adminLogin() {
    bool ok;
    QString user = QInputDialog::getText(this, "Admin Login", "Username:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString pass = QInputDialog::getText(this, "Admin Login", "Password:", QLineEdit::Password, "", &ok);
    if (!ok) return;
    if (user == "admin" && pass == "admin123") {
        AdminDialog dlg(&bank, this);
        dlg.exec();
    } else {
        QMessageBox::warning(this, "Error", "Invalid admin credentials!");
    }
}

void MainWindow::clientLogin() {
    bool ok;
    int accNum = QInputDialog::getInt(this, "Client Login", "Enter Account Number:", 1001, 1001, 9999, 1, &ok);
    if (!ok) return;
    BankAccount* acc = bank.findAccount(accNum);
    if (acc) {
        ClientDialog dlg(&bank, accNum, this);
        dlg.exec();
    } else {
        QMessageBox::warning(this, "Error", "Account not found!");
    }
}