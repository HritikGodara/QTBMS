// clientdialog.h
#pragma once
#include <QDialog>
#include "banklogic.h"

class ClientDialog : public QDialog {
    Q_OBJECT
public:
    ClientDialog(BankManagement* bank, int accountNum, QWidget* parent = nullptr);
private slots:
    void onViewAccount();
private:
    BankManagement* bank;
    int accountNum;
};