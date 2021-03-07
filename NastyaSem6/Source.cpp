#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

void menu();

map <vector<string>, unsigned int> add(map <vector<string>, unsigned int> mp)
{
	vector<string> info;
	unsigned int number;
	pair<vector<string>, unsigned int> pip;

	cout << "Enter name for this module" << endl;
	cin >> info[0];

	cout << "Enter specification for this module" << endl;
	cin >> info[1];

	cout << "Enter order number for this module" << endl;
	cin >> number;

	pip = make_pair(info, number);
	mp.insert(pip);
	return mp;
}

void print(map <vector<string>, unsigned int> mp)
{
	map <vector<string>, unsigned int> :: iterator it = mp.begin();

	cout << "Sorted: " << endl;
	for (unsigned int i = 0; it != mp.end(); advance(it, 1), i++)
	{
		cout << i << ") Specification" << setw(8) << it->first[1] << setw(8) << "Name" << setw(8) << it->first[0] << " | " << setw(8) << "Number" << setw(5) << it->second << endl;
	}
}

map <vector<string>, unsigned int> setup(map <vector<string>, unsigned int> mp)
{
	vector<string> m1, m2, m3;

	m1.push_back("First");
	m1.push_back("Zhopa");
	m2.push_back("Second");
	m2.push_back("Fishka");
	m3.push_back("Third");
	m3.push_back("Gay");

	mp.insert(pair <vector<string>, unsigned int>(m1, 10));
	mp.insert(pair <vector<string>, unsigned int>(m2, 18));
	mp.insert(pair <vector<string>, unsigned int>(m3, 6));

	return mp;
}

int main()
{
	map <vector<string>, unsigned int> mp;

	mp = setup(mp);

	bool flag = true;
	int option;

	while (flag)
	{
		menu();
		cin >> option;
		system("cls");
		switch (option)
		{
		case 1:
			mp = add(mp);
			break;
		case 2:
			cout << "There should be remove function, but i'm lazy" << endl;
			break;
		case 3:
			print(mp);
			break;
		case 9:
			flag = false;
			break;
		default:
			print(mp);
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}

void menu()
{
	cout << "1)Add new module" << endl;
	cout << "2)Remove module" << endl;
	cout << "3)Print all device info" << endl;
	cout << "9)Exit" << endl;
}