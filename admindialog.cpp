// admindialog.cpp
#include "admindialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

AdminDialog::AdminDialog(BankManagement* bank, QWidget* parent)
    : QDialog(parent), bank(bank) {
    setWindowTitle("Admin Panel");
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* addBtn = new QPushButton("Add Account", this);
    QPushButton* delBtn = new QPushButton("Delete Account", this);
    QPushButton* searchBtn = new QPushButton("Search Account", this);
    QPushButton* depBtn = new QPushButton("Deposit", this);
    QPushButton* withBtn = new QPushButton("Withdraw", this);
    QPushButton* showAllBtn = new QPushButton("Show All Accounts", this);
    QPushButton* backBtn = new QPushButton("Back", this);

    layout->addWidget(addBtn);
    layout->addWidget(delBtn);
    layout->addWidget(searchBtn);
    layout->addWidget(depBtn);
    layout->addWidget(withBtn);
    layout->addWidget(showAllBtn);
    layout->addWidget(backBtn);

    connect(addBtn, &QPushButton::clicked, this, &AdminDialog::onAddAccount);
    connect(delBtn, &QPushButton::clicked, this, &AdminDialog::onDeleteAccount);
    connect(searchBtn, &QPushButton::clicked, this, &AdminDialog::onSearchAccount);
    connect(depBtn, &QPushButton::clicked, this, &AdminDialog::onDeposit);
    connect(withBtn, &QPushButton::clicked, this, &AdminDialog::onWithdraw);
    connect(showAllBtn, &QPushButton::clicked, this, &AdminDialog::onShowAll);
    connect(backBtn, &QPushButton::clicked, this, &AdminDialog::onBack);
}

void AdminDialog::onAddAccount() {
    bool ok;
    QString name = QInputDialog::getText(this, "Add Account", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QStringList types = {"saving", "current"};
    QString type = QInputDialog::getItem(this, "Add Account", "Account Type:", types, 0, false, &ok);
    if (!ok) return;

    double balance = QInputDialog::getDouble(this, "Add Account", "Initial Balance:", 0, 0, 1e9, 2, &ok);
    if (!ok) return;

    int accNum = bank->AddAccount(name.toStdString(), balance, type.toStdString());
    QMessageBox::information(this, "Success", "Account created. Number: " + QString::number(accNum));
}

void AdminDialog::onDeleteAccount() {
    bool ok;
    int accNum = QInputDialog::getInt(this, "Delete Account", "Account Number:", 1001, 1001, 9999, 1, &ok);
    if (!ok) return;

    if (bank->deleteAccount(accNum)) {
        QMessageBox::information(this, "Success", "Account deleted.");
    } else {
        QMessageBox::warning(this, "Error", "Account not found.");
    }
}

void AdminDialog::onSearchAccount() {
    bool ok;
    int accNum = QInputDialog::getInt(this, "Search Account", "Account Number:", 1001, 1001, 9999, 1, &ok);
    if (!ok) return;

    BankAccount* acc = bank->findAccount(accNum);
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

void AdminDialog::onDeposit() {
    bool ok;
    int accNum = QInputDialog::getInt(this, "Deposit", "Account Number:", 1001, 1001, 9999, 1, &ok);
    if (!ok) return;
    double amount = QInputDialog::getDouble(this, "Deposit", "Amount:", 0, 0, 1e9, 2, &ok);
    if (!ok) return;

    BankAccount* acc = bank->findAccount(accNum);
    if (acc) {
        acc->deposit(amount);
        QMessageBox::information(this, "Success", "Deposited successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Account not found.");
    }
}

void AdminDialog::onWithdraw() {
    bool ok;
    int accNum = QInputDialog::getInt(this, "Withdraw", "Account Number:", 1001, 1001, 9999, 1, &ok);
    if (!ok) return;
    double amount = QInputDialog::getDouble(this, "Withdraw", "Amount:", 0, 0, 1e9, 2, &ok);
    if (!ok) return;

    BankAccount* acc = bank->findAccount(accNum);
    if (acc) {
        if (acc->withdraw(amount)) {
            QMessageBox::information(this, "Success", "Withdrawn successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Insufficient balance.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Account not found.");
    }
}

void AdminDialog::onShowAll() {
    QString all;
    auto accounts = bank->getAllAccounts();
    for (auto acc : accounts) {
        all += QString("Name: %1 | Account Number: %2 | Type: %3 | Balance: %4\n")
            .arg(QString::fromStdString(acc->getName()))
            .arg(acc->getAccountNum())
            .arg(QString::fromStdString(acc->getAccountType()))
            .arg(acc->getBalance());
    }
    if (all.isEmpty()) all = "No accounts found.";
    QMessageBox::information(this, "All Accounts", all);
}

void AdminDialog::onBack() {
    this->close();
}