// admindialog.h
#pragma once
#include <QDialog>
#include "banklogic.h"

class AdminDialog : public QDialog {
    Q_OBJECT
public:
    explicit AdminDialog(BankManagement* bank, QWidget* parent = nullptr);
private slots:
    void onAddAccount();
    void onDeleteAccount();
    void onSearchAccount();
    void onDeposit();
    void onWithdraw();
    void onShowAll();
    void onBack();
private:
    BankManagement* bank;
};