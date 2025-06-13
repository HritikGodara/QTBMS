// banklogic.cpp
#include "banklogic.h"
#include <iostream>

BankAccount::BankAccount(std::string n, int ac, double bal, std::string type)
    : name(n), accountNum(ac), balance(bal), accountType(type) {}

std::string BankAccount::getName() { return name; }
int BankAccount::getAccountNum() { return accountNum; }
double BankAccount::getBalance() { return balance; }
std::string BankAccount::getAccountType() { return accountType; }
void BankAccount::deposit(double amount) { balance += amount; }
bool BankAccount::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

Node::Node(BankAccount* acc) : account(acc), next(nullptr) {}

int BankManagement::nextAccountNum = 1001;

BankManagement::BankManagement() : head(nullptr) {}

int BankManagement::AddAccount(const std::string& name, double balance, const std::string& type) {
    int accountNum = nextAccountNum++;
    BankAccount* newAcc = new BankAccount(name, accountNum, balance, type);
    Node* newNode = new Node(newAcc);
    newNode->next = head;
    head = newNode;
    return accountNum;
}

bool BankManagement::deleteAccount(int accountNum) {
    Node* temp = head;
    Node* prev = nullptr;
    while (temp != nullptr) {
        if (temp->account->getAccountNum() == accountNum) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp->account;
            delete temp;
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

BankAccount* BankManagement::findAccount(int accountNum) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->account->getAccountNum() == accountNum) {
            return temp->account;
        }
        temp = temp->next;
    }
    return nullptr;
}

std::vector<BankAccount*> BankManagement::getAllAccounts() {
    std::vector<BankAccount*> accounts;
    Node* temp = head;
    while (temp) {
        accounts.push_back(temp->account);
        temp = temp->next;
    }
    return accounts;
}