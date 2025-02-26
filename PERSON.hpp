#pragma once

#include <iostream>
#include <string>
#include <list>
#include <chrono> //To manipulate time
#include <thread> //To use this_thread

class PERSON
{
    private:
        int money = 0;
        int moneyOnDeposit = 0;
        std::string name;
        std::list<PERSON> contactList;

    public:
        std::string getName();
        PERSON findContact(std::string contactName);
        bool verifyAmount(int &value_1, int &value_2);
        int getMoney();
        void error_message();
        void showMoney();
        void addMoney(int value);
        void setName(std::string value);
        void depositMoney(int value);
        void withdrawMoney(int value);
        void removeMoney(int value);
        void addContact(PERSON contact);
        void removeAllContacts();
        void getContactList();
        void showOptions();
};