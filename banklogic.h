// banklogic.h
#pragma once
#include <string>
#include <vector>

class BankAccount {
private:
    std::string name;
    int accountNum;
    double balance;
    std::string accountType;
public:
    BankAccount(std::string n, int ac, double bal, std::string type);
    std::string getName();
    int getAccountNum();
    double getBalance();
    std::string getAccountType();
    void deposit(double amount);
    bool withdraw(double amount);
};

struct Node {
    BankAccount* account;
    Node* next;
    Node(BankAccount* acc);
};

class BankManagement {
private:
    Node* head;
    static int nextAccountNum;
public:
    BankManagement();
    int AddAccount(const std::string& name, double balance, const std::string& type);
    bool deleteAccount(int accountNum);
    BankAccount* findAccount(int accountNum);
    std::vector<BankAccount*> getAllAccounts();
};