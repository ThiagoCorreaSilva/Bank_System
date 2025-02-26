#include "PERSON.hpp"

void PERSON::error_message()
{
    std::cout << "\n\033[31mSALDO INSUFICIENTE!\033[0m\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

bool PERSON::verifyAmount(int &value_1, int &value_2)
{
    if (value_1 - value_2 < 0)
    {
        error_message();
        return false;
    }
    else return true;
}

void PERSON::setName(std::string value) {name = value;}

void PERSON::addMoney(int value)
{
    money += value;

    system("cls");
    std::cout << "Adicionado para " << name << " " << value << " reais\n";
    std::cout << "Dinheiro atual de " << name << " " << money << " reais";

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void PERSON::removeMoney(int value)
{
    bool canContinue = verifyAmount(money, value);
    if (!canContinue) return;

    money -= value;

    system("cls");
    std::cout << "Removido de " << name << " " << value << " reais\n";
    std::cout << "Dinheiro atual de " << name << " " << money << " reais\n";

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void PERSON::depositMoney(int value)
{
    bool canContinue = verifyAmount(money, value);
    if (!canContinue) return;

    money -= value;
    moneyOnDeposit += value;

    system("cls");
    std::cout << "Depositado: " << value << " reais\n";
    std::cout << "Dinheiro atual: " << money << " reais\n";
    std::cout << "Deposito atual: " << moneyOnDeposit << " reais\n";

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void PERSON::withdrawMoney(int value)
{
    bool canContinue = verifyAmount(moneyOnDeposit, value);
    if (!canContinue) return;

    moneyOnDeposit -= value;
    money += value;

    system("cls");
    std::cout << "Tirado do deposito: " << value << " reais\n";
    std::cout << "Dinheiro atual: " << money << " reais\n";
    std::cout << "Deposito atual: " << moneyOnDeposit << " reais\n";
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void PERSON::showMoney()
{
    system("cls");
    std::cout << "Dinheiro na conta______: " << money << '\n';
    std::cout << "Dinheiro depositado____: " << moneyOnDeposit << '\n';

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void PERSON::addContact(PERSON contact)
{
    contactList.push_front(contact);
}

void PERSON::removeAllContacts()
{
    for (int i = 0; i < contactList.size(); i++)
    {
        contactList.pop_front();
    }
}

PERSON PERSON::findContact(std::string contactName)
{
    PERSON person;

    for (PERSON contact : contactList)
    {
        if (contact.getName() == contactName)
        {
            std::cout << "\033[32mContato achado!\033[0m\n";
            person = contact;
            return person;
        }
    }

    return person;
}

void PERSON::getContactList()
{
    if (contactList.size() == 0)
    {
        std::cout << "\033[31mLista de contato vazia!\033[0m\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        return;
    }

    for (PERSON contact : contactList)
    {
        std::cout << "------------------------------------\n";
        std::cout << "Nome_________: " << contact.getName() << '\n';
        std::cout << "------------------------------------\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void PERSON::showOptions()
{
    std::cout << "Adicionar dinheiro_________________: DIGITE 1\n"; 
    std::cout << "Remover dinheiro___________________: DIGITE 2\n";
    std::cout << "Depositar dinheiro_________________: DIGITE 3\n";
    std::cout << "Tirar dinheiro do deposito_________: DIGITE 4\n";
    std::cout << "Tranferir dinheiro para contato____: DIGITE 5\n";
    std::cout << "Ver lista de contato_______________: DIGITE 6\n";
    std::cout << "Criar nova conta___________________: DIGITE 7\n";
    std::cout << "Verificar saldo____________________: DIGITE 8\n";
    std::cout << "Mudar de usuario___________________: DIGITE 9\n";
    std::cout << "Sair do programa___________________: DIGITE 10\n\n";
}

int PERSON::getMoney() {return money;}

std::string PERSON::getName() {return name;}