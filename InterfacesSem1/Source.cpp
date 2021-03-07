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
        cout << "������ � �������!" << endl;
        return true;
    }
    else cout << endl << "����� ���������!" << endl;
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
    for (unsigned int i = 0; i < 3; i++)                        //���������� ��� �������������� ��������� ���������� �������
    {
        string prom = generate();
        stringout = add(prom, packnum);
        packrecord.push_back(stringout);
        packnum++;                                             //���� �������� �������� ������������ - ������ ��� �������, ���� ��������� �
    }
    for (unsigned int i = 0; i < packrecord.size(); i++)       //��������� ������ �� ������� �������
    {
        if (detection(packrecord[i], i) and dataTest(packrecord[i]))
        {
            result.push_back(packrecord[i]);
        }
        else
        {
            cout << "���������� ������, �������� ��������" << endl;
            system("pause");
            return 0;
        }
    }

    stringout = assembly(result);                               //assembly �������� ��� �������� ���� �� ������� � ���������� �� � stringout

    cout << "-----------------------------------" << endl << endl << endl << "�������� ��������, ���������: " << stringout << endl << endl << endl << endl;

    cout << "�� ������ ������ ����� �������? Y/N" << endl;
    char yn;
    yn = getchar();
    if ((yn != 'y') & (yn != 'Y'))                                             //�� ��� ������ �������� ������������ �� �����������
    {
        cout << endl << "���������� ��������..." << endl;
        return 0;
    }

    vector<string> usermess;
    vector<string> acceptedmess;
    string userpack;
    string userres;
    bool flag = 0;
    cout << "������� ��� �����(8 ����)" << endl;

    while (!flag)                                             //3 ������ - �� �������� �� ������, ������ ���� 8 �������� � ������ 0 ��� 1, ����� ����� ������
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
            cout << endl << "�� ��� ��... ��� �� ������������ �����, �� �� ����" << endl;
            cout << endl << "�� ���, ������ ������ ����� ������� ����, ���" << endl;
        }

    }

    flag = 0;
    cout << endl << "������� ��� ������ �����(8 ����)" << endl;

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
            cout << endl << "�� ��� ��... ��� �� ������������ �����, �� �� ����" << endl;
            cout << endl << "�� ���, ������ ������ ����� ������� ����, ���" << endl;
        }
    }

    flag = 0;
    cout << endl << "������� ��� ������ �����(8 ����)" << endl;

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
            cout << endl << "�� ��� ��... ��� �� ������������ �����, �� �� ����" << endl;
            cout << endl << "�� ���, ������ ������ ����� ������� ����, ���" << endl;
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
            cout << endl << "���������� ������, �������� ��������" << endl;
            system("pause");
            return 0;
        }
    }

    stringout = assembly(acceptedmess);                        //����� ��, ������ �������� �������� ����

    cout << "-----------------------------------" << endl << endl << endl << "�������� ��������, ���������: " << stringout << endl << endl << endl << endl;


    system("pause");
    return 0;
}

string generate()
{
    string res(3, '\0');                                     //��� ������������ ������ �������� ����, 3 �������
    for (unsigned int i = 0; i < 3; i++)
    {
        int buff = rand() % 100;                            //�� ����� �������� �������� 0-49 � 50-100 :)
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
    string res(8, '\0');                                    //���� �� ��������� 2 ���� ������ � 3 ���� �� ����� ������
    int count = 0;
    if (useful == "000" | useful == "111")                  //�������� ������ ����� ������ ��� 000 � 111
    {
        res[0] = '0';
    }
    else res[0] = '1';

    for (unsigned int i = 0; i < 3; i++)                    //������� ���-�� ������
    {
        if (useful[i] == '1')
        {
            count++;
        }
    }

    if (count >= 2)                                         //������ �����, ����� �� ���� ����������
    {
        res[1] = '1';
    }
    else res[1] = '0';

    res[4] = useful[0];
    res[5] = useful[1];
    res[6] = useful[2];

    switch (packnum)                                        //� ������ �� ��������� ����� ������, ������������ �� ��, ��� ������ � �������
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
    //cout << buff << endl;               //��� ����� ��� ������� � 10���� �������, ����� 48, ��� ��������� ���������� � ����

    if (buff == packnum)                //�� � ��������� � ���������� ������� ������, ������� ���������
    {
        cout << "����� ������ ���������" << endl;
        return true;
    }
    else cout << endl << "����� ������ (" << buff << ") �� ���������, ����� ���������" << endl;
    return false;



}



string assembly(vector<string> base)
{
    string rec_data(9, '\0');          //�� ��� ������ ���������� ������� �������� ����� �� ���������� ������� � ���� ������
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
    if (packet.length() != 8)                  //�������� �� ����� ����������� ������
    {
        cout << "����� ����� �������, �������� ������ ���� 8" << endl << endl;
        return false;
    }

    for (unsigned int i = 0; i < 8; i++)                        //� �� ������������� �������
    {
        if ((packet[i] != '0') & (packet[i] != '1'))
        {
            cout << "����� ����� �������, ���������� �� ������ 0 � 1" << endl << endl;
            return false;
        }
    }
    return true;
}