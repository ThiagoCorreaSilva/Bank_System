#include "PERSON.hpp"
#include <cctype> //To verify if a letter is a digit

std::list<PERSON> dataBase;
PERSON currentUser;
int answer {0};
int value {0};

void create_user();
void manipulate_money();
void change_account();

int main()
{
    bool repeat {true};

    create_user();

    while (repeat)
    {
        system("cls");
        std::cout << "Bem vindo " << currentUser.getName() << " ao MushcBank!\n";
        std::cout << "O que deseja fazer?\n\n";
    
        currentUser.showOptions();
        std::cin >> answer;

        system("cls");

        //Monyey options
        if (answer >= 1 && answer <= 5) manipulate_money();

        else if (answer == 6) currentUser.getContactList();

        //Want to create a new account
        else if (answer == 7) create_user();

        else if (answer == 8) currentUser.showMoney();

        else if (answer == 9) change_account();

        //Want to leave
        else if (answer == 10) repeat = false;
        else
        {
            //If cin read a letter instead a number
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore();
            }

            system("cls");
            std::cout << "\033[31mCOMANDO INVALIDO!\033[0m\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    system("cls");
    std::cout << "Obrigado por utilizar nosso programa!\n";
    system("pause");

    return 0;
}

void create_user()
{
    std::string name;
    char user_answer;
    PERSON person;

    userRestart:

    system("cls");
    std::cout << "Para criar uma conta, precissamos que voce insira um nome!\n";

    //Ignore if the buffer contains \n
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, name);

    //If the data base isnt empty
    if (!dataBase.empty())
        for (PERSON p: dataBase)
        {
            if (p.getName() == name)
            {
                std::cout << "\033\n[31mNOME JA EXISTENTE NO BANCO DE DADOS\033[0m\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                goto userRestart;
            }
        }

    for (auto letter : name)
    {
        //Verify if the letter is a number or a symbol
        if (isdigit(letter) || ispunct(letter))
        {
            std::cout << "\n\033[31mNOME INVALIDO! COLOQUE APENAS LETRAS!\033[0m\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));

            goto userRestart;
        }
    }

    person.setName(name);

    //Add the person to the front of the dataBase
    dataBase.push_front(person);

    //To change to the account that was created
    if (dataBase.size() > 1)
    {
        //Add all people in dataBase as contact to the new account
        for (PERSON peopleData : dataBase)
        {
            if (peopleData.getName() == person.getName()) continue;
                
            person.addContact(peopleData);
        }

        std::cout << "\nDeseja entrar na conta criada? [y/n]\n";
        std::cin >> user_answer;

        //If the user want to change the account
        if (user_answer == 'y' || user_answer == 'Y') currentUser = person;

        //If the user dont want to change the account
        else currentUser.addContact(person);

    }
    //If this is the first account created
    else currentUser = person;

    system("cls");
    std::cout << "\033[32mUsuario criado com sucesso!\033[0m\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void manipulate_money()
{
    std::cout << "Digite a quantia!\n";
    std::cin >> value;

    switch (answer)
    {
    case 1:
        currentUser.addMoney(value);
        break;

    case 2:
        currentUser.removeMoney(value);
        break;

    case 3:
        currentUser.depositMoney(value);
        break;

    case 4:
        currentUser.withdrawMoney(value);
        break;

    case 5:
        //If the dataBase only have one person, return
        if (dataBase.size() == 1)
        {
            std::cout << "\033[31mNao existe nenhum usuario alem de voce\033[0m\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));

            return;
        }
        if (currentUser.getMoney() - value < 0)
        {
            currentUser.error_message();
            return;
        }

        std::string contactName;

        system("cls");
        std::cout << "Escolha um contato e digite seu nome!\n\n";
        currentUser.getContactList();
        std::cout << '\n';

        //Go to
        tryAgain:

        if (std::cin.peek() == '\n') std::cin.ignore();
        std::getline(std::cin, contactName);

        //Try to get the contact in dataBase
        PERSON contact = currentUser.findContact(contactName);
        if (contact.getName() == "")
        {
            std::cout << "\nContato nao achado!\n";
            goto tryAgain;
        }

        for (PERSON &user : dataBase)
        {
            if (user.getName() == contact.getName())
            {
                system("cls");
                user.addMoney(value);
                currentUser.removeMoney(value);
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
        break;
    }
}

void change_account()
{
    if (dataBase.size() == 1)
    {
        std::cout << "\033[31mNENHUM USUARIO ENCONTRADO!\033[0m\n";

        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::string newUser;

    system("cls");
    for (PERSON user : dataBase)
    {
        if (user.getName() == currentUser.getName()) continue;

        std::cout << "-----------------------------------\n";
        std::cout << user.getName() << '\n';
        std::cout << "-----------------------------------\n";
    }
    
    //Goto
    changeAccountRestart:

    std::cout << "\nDigite o nome do usuario que voce entrar\n";

    //If the cin get the '\n'
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, newUser);

    for (PERSON user : dataBase)
    {
        if (user.getName() == newUser)
        {
            currentUser = user;
            currentUser.removeAllContacts();

            for (PERSON person : dataBase)
            {
                if (person.getName() == currentUser.getName()) continue;
                currentUser.addContact(person);
            }
        }
    }
}