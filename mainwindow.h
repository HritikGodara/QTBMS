#pragma once
#include <QMainWindow>
#include "banklogic.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void adminLogin();
    void clientLogin();
private:
    BankManagement bank;
};