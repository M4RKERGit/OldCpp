#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <Windows.h>

using namespace std;

struct dateTime
{
    unsigned int day, month, year, second, minute, hour;
};

struct Data
{
    dateTime DateTime;
    char name[30];
    unsigned int number;
};

void menu();

void show(vector<Data> List);

void exiT(vector <Data> List, bool flag);

vector <Data> add(vector <Data>& List);

vector <Data> remove(vector <Data>& List);

vector <unsigned int> search(vector <Data>& List);

vector <Data> replace(vector <Data>& List);

int main()
{
    setlocale(LC_ALL, "RUS");

    vector<Data> List;
    bool flag = true;
    unsigned int option;

    Data MyData;

    FILE* BIN;
    if ((BIN = fopen("C://Users/M4RKER/source/repos/Sem5Sanya/BIN.dat", "rb")) == NULL)
    {
        cout << "\n\n\tОшибка. Файл не найден." << endl;
    }
    else
    { 
        BIN = fopen("C://Users/M4RKER/source/repos/Sem5Sanya/BIN.dat", "rb");
        while (feof(BIN) == 0)
        {
            fread(&MyData.DateTime.year, sizeof(int), 1, BIN);
            fread(&MyData.DateTime.month, sizeof(int), 1, BIN);
            fread(&MyData.DateTime.day, sizeof(int), 1, BIN);
            fread(&MyData.DateTime.hour, sizeof(int), 1, BIN);
            fread(&MyData.DateTime.minute, sizeof(int), 1, BIN);
            fread(&MyData.DateTime.second, sizeof(int), 1, BIN);

            for (int i = 0; i < 30; i++)
            {
                fread(&MyData.name[i], 1, 1, BIN);
            }

            fread(&MyData.number, sizeof(int), 1, BIN);

            List.push_back(MyData);
        }
        List.erase(List.begin() + List.size() - 2);
        fclose(BIN);
    }

    while (flag)
    {
        menu();
        cin >> option;
        system("cls");


        switch (option)
        {
        case 1:
            add(List);
            break;
        case 2:
            replace(List);
            break;
        case 3:
            remove(List);
            break;
        case 4:
            search(List);
            break;
        case 5:
            cout << List.size();
            show(List);
            break;
        case 6:
            exiT(List, flag);
            break;
        default:
            show(List);
            break;
        }
        system("pause");
        system("cls");
    }

    system("Pause");
    return 0;
}

void menu()
{
    cout << "\n\t1) Добавить данные" << endl;
    cout << "\t2) Изменить данные" << endl;
    cout << "\t3) Удалить данные" << endl;
    cout << "\t4) Поиск" << endl;
    cout << "\t5) Показать данные" << endl;
    cout << "\t6) Сохранить и выйти\n\n\t";
}

void show(vector <Data> List)
{
    cout << "\n\t_____________________________________________________________________________" << endl;
    cout << "\t______Дата______|_____Время_____|__________Имя__________|_Численный параметр_";

    for (unsigned int i = 0; i < List.size(); i++)
    {
        cout << "\n\t " << List[i].DateTime.day << "." << List[i].DateTime.month << "." << List[i].DateTime.year << "\t| "
            << List[i].DateTime.hour << ":" << List[i].DateTime.minute << ":" << List[i].DateTime.second << "\t| "
            << List[i].name << "\t\t| " << List[i].number;
    }

    cout << "\n\t________________|_______________|_______________________|____________________\n\n";
}

void exiT(vector <Data> List, bool flag)
{
    FILE* BIN1;
    BIN1 = fopen("C://Users/M4RKER/source/repos/Sem5Sanya/BIN.dat", "wb");
    for (unsigned int i = 0; i < List.size(); i++)
    {
        fwrite(&List[i].DateTime.year, sizeof(int), 1, BIN1);
        fwrite(&List[i].DateTime.month, sizeof(int), 1, BIN1);
        fwrite(&List[i].DateTime.day, sizeof(int), 1, BIN1);
        fwrite(&List[i].DateTime.hour, sizeof(int), 1, BIN1);
        fwrite(&List[i].DateTime.minute, sizeof(int), 1, BIN1);
        fwrite(&List[i].DateTime.second, sizeof(int), 1, BIN1);
        for (int j = 0; j < 30; j++)
        {
            fwrite(&List[i].name[j], 1, 1, BIN1);
        }
        fwrite(&List[i].number, sizeof(int), 1, BIN1);
    }
    fclose(BIN1);

    flag = false;

    exit(0);
}

vector <Data> add(vector <Data>& List)
{
    time_t rawtime;
    rawtime = time(NULL);
    tm* tk;

    time(&rawtime);
    tk = localtime(&rawtime);

    Data MyData;
    char listName[30];
    unsigned int n;

    cout << "\n\n\tВведите имя:\n\n\t";

    cin >> listName;

    for (int i = 0; i < 30; i++)
    {
        MyData.name[i] = listName[i];
    }

    cout << "\n\n\tВведите числовой параметр:\n\n\t";
    cin >> n;

    MyData.number = n;

    MyData.DateTime.year = 1900 + tk->tm_year;
    MyData.DateTime.month = 1 + tk->tm_mon;
    MyData.DateTime.day = tk->tm_mday;
    MyData.DateTime.hour = tk->tm_hour;
    MyData.DateTime.minute = tk->tm_min;
    MyData.DateTime.second = tk->tm_sec;

    List.push_back(MyData);

    return List;

    system("cls");
}

vector <Data> remove(vector <Data>& List)
{
    vector <unsigned int> dnum;
    dnum = search(List);
    unsigned int buff;

    for (unsigned int j = dnum.size(); j >= 1; j--)
    {
        buff = dnum[j-1];
        List.erase(List.begin() + buff);
    }
    return List;
}

vector <unsigned int> search(vector <Data>& List)
{
    char stag[30];
    unsigned int i;
    unsigned int choice;
    bool found = false, flag = false;
    vector <unsigned int> Fnumbers;

    cout << "1 for Name Search, 2 for Date Search, 3 for Number Search" << endl;
    cin >> choice;

    /*while (!flag)
    {
        if ((choice > 3) || (choice < 1))
        {
            cout << "1 for Name Search, 2 for Date Search, 3 for Number Search" << endl;
            cin >> choice;
        }
        else
        if ((1 < choice) & (choice < 3))
        {
            flag = true;
        }
    }*/

    //system("cls");

    if (choice == 1)
    {
        cout << "Dear pidoras, enter search tag" << endl;
        cin >> stag;

        for (i = 0; i < List.size(); i++)
        {
            if (strcmp(List[i].name, stag) == 0)
            {
                cout << i << "      " << List[i].name << "      " << List[i].DateTime.day << "/" << List[i].DateTime.month << "/" << List[i].DateTime.year;
                cout << "      " << List[i].DateTime.hour << ":" << List[i].DateTime.minute << ":" << List[i].DateTime.second << endl;
                found = true;
                Fnumbers.push_back(i);
            }
        }
    }
    
    if (choice == 2)
    {
        unsigned int year, month, day;

        cout << "Enter year" << endl;
        cin >> year;
        cout << "Enter month" << endl;
        cin >> month;
        cout << "Enter day" << endl;
        cin >> day;

        for (i = 0; i < List.size(); i++)
        {
            if ((List[i].DateTime.year == year) & (List[i].DateTime.month == month) & (List[i].DateTime.day == day))
            {
                cout << i << "      " << List[i].name << "      " << List[i].DateTime.day << "/" << List[i].DateTime.month << "/" << List[i].DateTime.year;
                cout << "      " << List[i].DateTime.hour << ":" << List[i].DateTime.minute << ":" << List[i].DateTime.second << endl;
                found = true;
                Fnumbers.push_back(i);
            }
        }
    }
    
    if (choice == 3)
    {
        unsigned int numb;

        cout << "Enter number" << endl;
        cin >> numb;

        for (i = 0; i < List.size(); i++)
        {
            if (List[i].number == numb)
            {
                cout << i << "      " << List[i].name << "      " << List[i].DateTime.day << "/" << List[i].DateTime.month << "/" << List[i].DateTime.year;
                cout << "      " << List[i].DateTime.hour << ":" << List[i].DateTime.minute << ":" << List[i].DateTime.second << endl;
                found = true;
                Fnumbers.push_back(i);
            }
        }
    }

    if (found == false)
    {
        cout << "Incorrect number" << endl;
        return Fnumbers;
    }
    else
        return Fnumbers;
}

vector <Data> replace(vector <Data>& List)
{
    unsigned int buff;
    vector <unsigned int> rnum = search(List);
    if (rnum.size() > 1)
    {
        cout << "Choose order number for replacing" << endl;
        cin >> buff;
        rnum.clear();
        rnum.push_back(buff);
    }

    time_t rawtime;
    rawtime = time(NULL);
    tm* tk;

    time(&rawtime);
    tk = localtime(&rawtime);

    Data forrepl;
    char listName[30];
    unsigned int n;

    cout << "\n\n\tВведите имя:\n\n\t";

    cin >> listName;

    for (int i = 0; i < 30; i++)
    {
        forrepl.name[i] = listName[i];
    }

    cout << "\n\n\tВведите числовой параметр:\n\n\t";
    cin >> n;

    forrepl.number = n;

    forrepl.DateTime.year = 1900 + tk->tm_year;
    forrepl.DateTime.month = 1 + tk->tm_mon;
    forrepl.DateTime.day = tk->tm_mday;
    forrepl.DateTime.hour = tk->tm_hour;
    forrepl.DateTime.minute = tk->tm_min;
    forrepl.DateTime.second = tk->tm_sec;

    List[rnum[0]] = forrepl;
    return List;
}