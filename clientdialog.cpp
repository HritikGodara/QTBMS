// clientdialog.cpp
#include "clientdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>

ClientDialog::ClientDialog(BankManagement* bank, int accountNum, QWidget* parent)
    : QDialog(parent), bank(bank), accountNum(accountNum) {
    setWindowTitle("Client Panel");
    auto* layout = new QVBoxLayout(this);

    auto* viewBtn = new QPushButton("View Account", this);
    auto* backBtn = new QPushButton("Back to Login", this);
    auto* exitBtn = new QPushButton("Exit", this);

    layout->addWidget(viewBtn);
    layout->addWidget(backBtn);
    layout->addWidget(exitBtn);

    connect(viewBtn, &QPushButton::clicked, this, &ClientDialog::onViewAccount);
    connect(backBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(exitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}

void ClientDialog::onViewAccount() {
    BankAccount* acc = bank->findAccount(accountNum);
    if (acc) {
        QString info = QString("Name: %1\nAccount Number: %2\nType: %3\nBalance: %4")
            .arg(QString::fromStdString(acc->getName()))
            .arg(acc->getAccountNum())
            .arg(QString::fromStdString(acc->getAccountType()))
            .arg(acc->getBalance());
        QMessageBox::information(this, "Account Info", info);
    } else {
        QMessageBox::warning(this, "Error", "Account not found.");
    }
}
// Implement each slot to show dialogs and interact with banklogic