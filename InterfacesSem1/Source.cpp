#include <iostream>
#include <time.h>
#include <string.h>
#include <vector>

#define CRT_SECURE_NO_WARNINGS

using namespace std;

string generate();
string add(string useful, unsigned int packnum);
bool detection(string packet, unsigned int packnum);
string assembly(vector<string> base);
bool packcheck(string packet);

bool dataTest(string packet)
{
    int data1 = (int)packet[4] - (int)'0';
    int data2 = (int)packet[5] - (int)'0';
    int data3 = (int)packet[6] - (int)'0';

    int sec1 = (int)packet[0] - (int)'0';
    int sec2 = (int)packet[1] - (int)'0';

    bool test1 = ((data1 == data2) and (data1 == data3) and (data2 == data3)) == (sec1 == 0);
    bool test2 = (data1 + data2 + data3 >= 2 and sec2 == 1) or (data1 + data2 + data3 < 2 and sec2 == 0);

    //cout << sec1 << ' ' << sec2 << " - " << data1 << ' ' << data2 << ' ' << data3 << ' ' << endl;
    //cout << test1 << ' ' << test2 <<endl;

    if (test1 == test2 == 1)
    {
        cout << "данные в порядке!" << endl;
        return true;
    }
    else cout << endl << "пакет поврежден!" << endl;
    return false;

}

int main()
{
    setlocale(LC_ALL, "Russian");
    unsigned int packnum = 0;
    string stringout;
    vector<string> packrecord;
    vector<string> result;
    srand(time(NULL));
    for (unsigned int i = 0; i < 3; i++)                        //используем для автоматической генерации правильных пакетов
    {
        string prom = generate();
        stringout = add(prom, packnum);
        packrecord.push_back(stringout);
        packnum++;                                             //если попросит показать неправильные - ломаем эту строчку, либо комментим её
    }
    for (unsigned int i = 0; i < packrecord.size(); i++)       //проверяем пакеты на наличие косяков
    {
        if (detection(packrecord[i], i) and dataTest(packrecord[i]))
        {
            result.push_back(packrecord[i]);
        }
        else
        {
            cout << "Обнаружены помехи, передача прервана" << endl;
            system("pause");
            return 0;
        }
    }

    stringout = assembly(result);                               //assembly собирает все полезные биты из пакетов и записывает их в stringout

    cout << "-----------------------------------" << endl << endl << endl << "Успешная передача, результат: " << stringout << endl << endl << endl << endl;

    cout << "Вы хотите задать пакет вручную? Y/N" << endl;
    char yn;
    yn = getchar();
    if ((yn != 'y') & (yn != 'Y'))                                             //ну тут просто согласие пользователя на продолжение
    {
        cout << endl << "Завершение процесса..." << endl;
        return 0;
    }

    vector<string> usermess;
    vector<string> acceptedmess;
    string userpack;
    string userres;
    bool flag = 0;
    cout << "Введите ваш пакет(8 цифр)" << endl;

    while (!flag)                                             //3 пакета - по проверке на каждый, должно быть 8 символов и только 0 или 1, иначе вводи заново
    {

        cin >> userpack;

        if (packcheck(userpack) and dataTest(userpack))
        {
            usermess.push_back(userpack);
            flag = true;
            continue;
        }
        else
        {
            cout << endl << "ну это же... это же неправильный пакет, ну вы чего" << endl;
            cout << endl << "ну все, теперь заново пакет вводить надо, даа" << endl;
        }

    }

    flag = 0;
    cout << endl << "Введите ваш второй пакет(8 цифр)" << endl;

    while (!flag)
    {

        cin >> userpack;

        if (packcheck(userpack) and dataTest(userpack))
        {
            usermess.push_back(userpack);
            flag = true;
            continue;
        }
        else
        {
            cout << endl << "ну это же... это же неправильный пакет, ну вы чего" << endl;
            cout << endl << "ну все, теперь заново пакет вводить надо, даа" << endl;
        }
    }

    flag = 0;
    cout << endl << "Введите ваш третий пакет(8 цифр)" << endl;

    while (!flag)
    {

        cin >> userpack;

        if (packcheck(userpack) and dataTest(userpack))
        {
            usermess.push_back(userpack);
            flag = true;
            continue;
        }
        else
        {
            cout << endl << "ну это же... это же неправильный пакет, ну вы чего" << endl;
            cout << endl << "ну все, теперь заново пакет вводить надо, даа" << endl;
        }
    }


    for (unsigned int i = 0; i < 3; i++)
    {
        if (detection(usermess[i], i))
        {
            acceptedmess.push_back(usermess[i]);
        }
        else
        {
            cout << endl << "Обнаружены помехи, передача прервана" << endl;
            system("pause");
            return 0;
        }
    }

    stringout = assembly(acceptedmess);                        //опять же, просто собираем полезные биты

    cout << "-----------------------------------" << endl << endl << endl << "Успешная передача, результат: " << stringout << endl << endl << endl << endl;


    system("pause");
    return 0;
}

string generate()
{
    string res(3, '\0');                                     //тут генерируются ТОЛЬКО полезные биты, 3 символа
    for (unsigned int i = 0; i < 3; i++)
    {
        int buff = rand() % 100;                            //по моему любимому принципу 0-49 и 50-100 :)
        if (buff > 49)
        {
            res[i] = '1';
        }
        else res[i] = '0';
    }
    return res;
}

string add(string useful, unsigned int packnum)
{
    string res(8, '\0');                                    //тута мы добавляем 2 бита защиты и 3 бита на номер пакета
    int count = 0;
    if (useful == "000" | useful == "111")                  //отсекаем первую цифру защиты для 000 и 111
    {
        res[0] = '0';
    }
    else res[0] = '1';

    for (unsigned int i = 0; i < 3; i++)                    //считаем кол-во единиц
    {
        if (useful[i] == '1')
        {
            count++;
        }
    }

    if (count >= 2)                                         //делаем вывод, какая из цифр доминирует
    {
        res[1] = '1';
    }
    else res[1] = '0';

    res[4] = useful[0];
    res[5] = useful[1];
    res[6] = useful[2];

    switch (packnum)                                        //и отсюда же добавляем номер пакета, ориентируясь на то, что пришло в функцию
    {
    case 0:
        res[2] = '0';
        res[3] = '0';
        res[7] = '0';
        break;
    case 1:
        res[2] = '0';
        res[3] = '0';
        res[7] = '1';
        break;
    case 2:
        res[2] = '0';
        res[3] = '1';
        res[7] = '0';
        break;
        /*case 3:
            res[2] = '0';
            res[3] = '1';
            res[7] = '1';
            break;*/
    }


    cout << res << endl << "-------------------------------" << endl;
    return res;
}

bool detection(string packet, unsigned int packnum)
{
    int buff = (static_cast<int>(packet[7]) - 48) + ((static_cast<int>(packet[3]) - 48)) * 2 + ((static_cast<int>(packet[2]) - 48) * 4);
    //cout << buff << endl;               //вот такой вот перевод в 10чную систему, минус 48, ибо переводит изначально в АСКИ

    if (buff == packnum)                //ну и сверяемся с нормальным номером пакета, который ожидается
    {
        cout << "Номер пакета совпадает" << endl;
        return true;
    }
    else cout << endl << "Номер пакета (" << buff << ") не совпадает, пакет отвергнут" << endl;
    return false;



}



string assembly(vector<string> base)
{
    string rec_data(9, '\0');          //ну тут просто перегоняем символы полезных битов из полученных пакетов в одну строку
    rec_data[0] = base[0][4];
    rec_data[1] = base[0][5];
    rec_data[2] = base[0][6];
    rec_data[3] = base[1][4];
    rec_data[4] = base[1][5];
    rec_data[5] = base[1][6];
    rec_data[6] = base[2][4];
    rec_data[7] = base[2][5];
    rec_data[8] = base[2][6];
    return rec_data;
}

bool packcheck(string packet)
{
    if (packet.length() != 8)                  //проверка на длину задаваемого пакета
    {
        cout << "Пакет задан неверно, символов должно быть 8" << endl << endl;
        return false;
    }

    for (unsigned int i = 0; i < 8; i++)                        //и на употребляемые символы
    {
        if ((packet[i] != '0') & (packet[i] != '1'))
        {
            cout << "Пакет задан неверно, содержатся не только 0 и 1" << endl << endl;
            return false;
        }
    }
    return true;
}