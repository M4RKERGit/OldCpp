#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <stdlib.h>




using namespace std;

struct Perem
{
	int Value;
	string Name;
	int Pointer;
	string PSwitch;
	int Cell;
};

vector<Perem> variable(vector<Perem> avto);
vector<Perem> set(vector<Perem> avto);
vector<Perem> variablePtr(vector<Perem> avto);
vector<Perem> setAddr(vector<Perem> avto);
vector<Perem> setValue(vector<Perem> avto);
vector<Perem> new_(vector<Perem> dynamic);
int new_cont(vector<Perem> dynamic);
vector<Perem> del_avto(vector<Perem> avto);
vector<Perem> del_dynamic(vector<Perem> dynamic);
void print(vector<Perem> avto, vector<Perem> dynamic);
void menu();


void main()
{
	vector<Perem> avto(10, { 0, "NaN", -1, "OFF", 0 });
	vector<Perem> dynamic(10, { 0, "NaN", -1, "OFF", 0 });
	int option, delChoice;
	bool flag = true;
	int Adr6;
	char NaM[10];
	char PSW[10];

	FILE* fp;
	char path[] = "text.txt";

	int count_p = 0;
	int razmer = 0;
	int i = 0;

	if ((fp = fopen(path, "r")) != NULL)
	{
		string razmer_text;

		ifstream file("text.txt", ios::in | ios::ate);
		if (file) {

			ifstream::streampos filesize = file.tellg();
			razmer_text.reserve(filesize);
			file.seekg(0);
			razmer = filesize;
			file.close();
		}

		fscanf(fp, "%d", &count_p);

		for (i = 0; i < count_p; i++)
		{
			fscanf(fp, "%s %d %d %s %d \n", NaM, &avto[i].Value, &avto[i].Pointer, PSW, &avto[i].Cell);
			avto[i].Name = NaM;
			avto[i].PSwitch = PSW;
		}
	}

	while (flag == true)
	{
		menu();
		cin >> option;
		system("cls");
		switch (option)
		{
		case 1:
			avto = variable(avto);
			print(avto, dynamic);
			break;
		case 2:
			avto = set(avto);
			print(avto, dynamic);
			break;
		case 3:
			avto = variablePtr(avto);
			print(avto, dynamic);
			break;
		case 4:
			avto = setAddr(avto);
			print(avto, dynamic);
			break;
		case 5:
			avto = setValue(avto);
			print(avto, dynamic);
			break;
		case 6:
			dynamic = new_(dynamic);
			Adr6 = new_cont(dynamic);
			dynamic.pop_back();
			print(avto, dynamic);
			cout << endl << "Adress of flagged cell:" << endl << Adr6 << endl;
			break;
		case 7:
			cout << "Enter 0 for Automatic Memory or 1 for Dynamic Memory" << endl;
			cin >> delChoice;
			switch (delChoice)
			{
			case 0:
				avto = del_avto(avto);
				break;

			case 1:
				dynamic = del_dynamic(dynamic);
				break;
			}
			print(avto, dynamic);
			break;
		case 8:
			print(avto, dynamic);
			break;
		case 9:
			flag = false;
			break;
		default:
			print(avto, dynamic);
			break;
		}
		system("pause");
		system("cls");
	}
	
	
	fp = fopen(path, "w+");

	fprintf(fp, "%d", avto.size());
	fprintf(fp, "\n");

	for (i = 0; i < avto.size(); i++)
	{
		fprintf(fp, "%s %d %d %s %d \n", avto[i].Name.c_str(), avto[i].Value, avto[i].Pointer,
			avto[i].PSwitch.c_str(), avto[i].Cell);
	}
	
}

vector<Perem> variable(vector<Perem> avto)
{
	string VaR;

	cout << "Enter new variables's name:" << endl;
	cin >> VaR;

	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == VaR)
		{
			cout << "Variable with this name was already created" << endl;
			return avto;
		}
	}

	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == "NaN" && avto[i].Cell == 0)
		{
			avto[i].Cell = 1;
			avto[i].Name = VaR;
			avto[i].PSwitch = "VAR";
			break;
		}
	}

	return avto;

}

vector<Perem> set(vector<Perem> avto)
{
	string VaR;
	int Value;
	bool count = false;

	cout << "Enter variable's name:" << endl;
	cin >> VaR;
	cout << "Enter variable's value:" << endl;
	cin >> Value;

	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == VaR)
		{
			count = true;
		}
	}

	if (count == false)
	{
		cout << "Variable with this name wasn't found";
		return avto;
	}


	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == VaR)
		{
			avto[i].Value = Value;
		}
	}
	return avto;
}

vector<Perem> variablePtr(vector<Perem> avto)
{
	string VaR;
	cout << "Enter new pointer's name:" << endl;
	cin >> VaR;

	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == "NaN" && avto[i].Cell == 0)
		{
			avto[i].Cell = 1;
			avto[i].PSwitch = "POINTER";
			avto[i].Name = VaR;
			break;
		}
	}
	return avto;
}

vector<Perem> setAddr(vector<Perem> avto)
{
	string VaR;
	string PoI;
	unsigned int NOR;
	bool count = false;

	cout << "Enter variable's name:" << endl;
	cin >> VaR;

	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == VaR)
		{
			count = true;
		}
	}

	if (count == false)
	{
		cout << "Variable with this name wasn't found";
		return avto;
	}

	count = false;


	cout << "Enter pointer's name:" << endl;
	cin >> PoI;



	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == PoI)
		{
			count = true;
		}
	}

	if (count == false)
	{
		cout << "Pointer with this name wasn't found";
		return avto;
	}




	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == VaR)
		{
			NOR = i;
			break;
		}
	}

	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == PoI)
		{
			avto[i].Pointer = NOR;
			break;
		}
	}


	return avto;
}

vector<Perem> setValue(vector<Perem> avto)
{
	string PoI;
	bool count;

	cout << "Enter pointer's name:" << endl;
	cin >> PoI;


	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == PoI)
		{
			count = true;
		}
	}

	if (count == false)
	{
		cout << "Variable with this name wasn't found";
		return avto;
	}


	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == PoI)
		{
			cout << "Enter value:" << endl;
			cin >> avto[avto[i].Pointer].Value;
			break;
		}
	}

	return avto;
}

vector<Perem> new_(vector<Perem> dynamic)
{
	for (unsigned int i = 0; i < dynamic.size(); i++)
	{
		if (dynamic[i].Cell == 0)
		{
			dynamic[i].Cell = 1;
			dynamic.resize(dynamic.size() + 1);
			dynamic[10].Pointer = i;
			break;
		}
	}
	return dynamic;
}

int new_cont(vector<Perem> dynamic)
{
	int Addr = dynamic[10].Pointer;
	return Addr;
}

vector<Perem> del_avto(vector<Perem> avto)
{
	string PoI, VaR;
	bool count;

	cout << "Enter pointer's name:" << endl;
	cin >> PoI;


	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == PoI)
		{
			count = true;
		}
	}

	if (count == false)
	{
		cout << "Pointer with this name wasn't found";
		return avto;
	}


	for (unsigned int i = 0; i < avto.size(); i++)
	{
		if (avto[i].Name == PoI)
		{
			if (avto[i].Pointer == -1)
			{
				cout << "Pointer does not point";
				return avto;
			}
			else
				avto[avto[i].Pointer] = { 0, "NaN", -1, "OFF", 0 };
			break;


		}
	}
	return avto;
}

vector<Perem> del_dynamic(vector<Perem> dynamic)
{
	string PoI;
	bool count;

	cout << "Enter pointer's name:" << endl;
	cin >> PoI;

	for (unsigned int i = 0; i < dynamic.size(); i++)
	{
		if (dynamic[i].Name == PoI)
		{
			count = true;
		}
	}

	if (count == false)
	{
		cout << "Pointer with this name wasn't found";
		return dynamic;
	}


	for (unsigned int i = 0; i < dynamic.size(); i++)
	{
		if (dynamic[i].Name == PoI)
		{
			if (dynamic[i].Pointer == -1)
			{
				cout << "Pointer does not point";
				return dynamic;
			}
			dynamic[dynamic[i].Pointer] = { 0, "", -1, "OFF", 0 };
			break;
		}
	}
	return dynamic;
}

void print(vector<Perem> avto, vector<Perem> dynamic)
{
	cout << avto[0].Name << endl;
	for (unsigned int i = 0; i < avto.size(); i++)
	{
		cout << endl << setw(12) << left << avto[i].Name << setw(12) << left << avto[i].Value << setw(12) << left << avto[i].Pointer << setw(12) << left << avto[i].PSwitch << setw(12) << left << avto[i].Cell;
	}
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	for (unsigned int i = 0; i < dynamic.size(); i++)
	{
		cout << endl << setw(12) << left << dynamic[i].Name << setw(12) << left << dynamic[i].Value << setw(12) << left << dynamic[i].Pointer << setw(12) << left << dynamic[i].PSwitch << setw(12) << left << dynamic[i].Cell;

	}
	cout << endl;
}

void menu()
{
	cout << endl << "Menu" << endl << "1)Look for a free space and add a null variable" << endl;
	cout << "2)Look for variable's name and set its value" << endl;
	cout << "3)Look for a free space and add a null pointer" << endl;
	cout << "4)Set pointer on variable" << endl;
	cout << "5)Set value by pointer's adress" << endl;
	cout << "6)Set a flag in free dynamic memory" << endl;
	cout << "7)Delete adressed auto or dynamic cell" << endl;
	cout << "8)Print both memory cards" << endl;
	cout << "9)Exit program with saving" << endl;
}