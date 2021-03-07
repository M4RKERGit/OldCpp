#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Substance
{
private:

public:
	string name;
	float amount;

	Substance(string Name, float Amount)
	{
		name = Name;
		amount = Amount;
	}

protected:

};

class Tube
{
private:

public:
	string name;
	vector<Substance> substances;
	float volume;

	Tube(string Name, float Volume)
	{
		name = Name;
		volume = Volume;
	}


protected:

};

class Retort
{
private:

public:
	string name;
	vector<Substance> substances;
	float volume;

	Retort(string Name, float Volume)
	{
		name = Name;
		volume = Volume;
	}


protected:

};

class Pallet
{
private:

public:
	vector<Substance> substances;

	Pallet()
	{

	}


protected:

};

vector<Tube> add_to_tube(vector<Tube> Tlist, Pallet* pallet);
vector<Retort> add_to_retort(vector<Retort> Rlist, Pallet* pallet);
Pallet add_to_pallet(Pallet pallet);
vector<Tube> add_tube(vector<Tube> Tlist);
vector<Retort> add_retort(vector<Retort> Tlist);
vector<Tube> clear_tube(vector<Tube> Tlist, Pallet* pallet);
vector<Retort> clear_retort(vector<Retort> Tlist, Pallet* pallet);
Pallet clear_pallet(Pallet pallet);
Pallet overflow(Pallet pallet, Substance substance);
void print(vector<Tube> Tlist, vector<Retort> Rlist, Pallet pallet);
void menu();


int main()
{
	vector<Tube> Tlist;
	vector<Retort> Rlist;
	Pallet pallet;
	bool flag = 1;
	int option;
	int opt;

	while (flag)
	{
		menu();
		cin >> option;
		system("cls");
		switch (option)
		{
		case 1:
			cout << "Enter 1 for tubes or 2 for retorts" << endl;
			cin >> opt;

			switch (opt)
			{
			case 1:
				Tlist = add_tube(Tlist);
				break;
			case 2:
				Rlist = add_retort(Rlist);
				break;
			}
			opt = 0;
			break;
		case 2:
			cout << "Enter 1 for tubes, 2 for retorts, 3 for pallet" << endl;
			cin >> opt;

			switch (opt)
			{
			case 1:
				Tlist = add_to_tube(Tlist, &pallet);
				break;
			case 2:
				Rlist = add_to_retort(Rlist, &pallet);
				break;
			case 3:
				pallet = add_to_pallet(pallet);
				break;
			}
			opt = 0;
			break;
		case 3:
			cout << "Enter 1 for tubes, 2 for retorts, 3 for pallet" << endl;
			cin >> opt;

			switch (opt)
			{
			case 1:
				Tlist = clear_tube(Tlist, &pallet);
				break;
			case 2:
				Rlist = clear_retort(Rlist, &pallet);
				break;
			case 3:
				pallet = clear_pallet(pallet);
				break;
			}
			opt = 0;
			break;
		case 4:
			print(Tlist, Rlist, pallet);
			break;
		case 9:
			flag = false;
			break;
		default:
			print(Tlist, Rlist, pallet);
			break;
		}
		system("pause");
		system("cls");
	}
}

vector<Tube> add_to_tube(vector<Tube> Tlist, Pallet* pallet)
	{
		unsigned int i, q;
		string subst;
		float amount = 0;
		float current = 0;
		float razn = 0;
		bool same = false;

		cout << "Enter number of tube" << endl;
		cin >> i;
		i--;

		if (i > Tlist.size())
		{
			cout << "Invalid number" << endl;
			return Tlist;
		}


		cout << "Enter substance" << endl;
		cin >> subst;


		cout << "Enter amount" << endl;
		cin >> amount;

		if (amount <= 0)
		{
			cout << "Incorrect amount" << endl;
			return Tlist;
		}

		for (q = 0; q < Tlist[i].substances.size(); q++)
		{
			if (Tlist[i].substances[q].name == subst)
			{
				same = true;
				break;
			}
		}

		for (unsigned int j = 0; j < Tlist[i].substances.size(); j++)
		{
			current += Tlist[i].substances[j].amount;
		}

		if (Tlist[i].volume < current + amount)
		{
			razn = amount - (Tlist[i].volume - current);
			Substance over = Substance(subst, razn);
			*pallet = overflow(*pallet, over);
			if (same == true)
			{
				Tlist[i].substances[q].amount += (Tlist[i].volume - current);
				return Tlist;
			}
			else Tlist[i].substances.push_back(Substance(subst, Tlist[i].volume - current));
			return Tlist;
		}
		if (same)
		{
			Tlist[i].substances[q].amount += amount;
			return Tlist;
		}
		else Tlist[i].substances.push_back(Substance(subst, amount));
		return Tlist;
	};

vector<Retort> add_to_retort(vector<Retort> Rlist, Pallet* pallet)
{
	unsigned int i, q;
	string subst;
	float amount = 0;
	float current = 0;
	float razn = 0;
	bool same = false;

	cout << "Enter number of retort" << endl;
	cin >> i;
	i--;


	if (i > Rlist.size())
	{
		cout << "Invalid number" << endl;
		return Rlist;
	}


	cout << "Enter substance" << endl;
	cin >> subst;


	cout << "Enter amount" << endl;
	cin >> amount;

	if (amount <= 0)
	{
		cout << "Incorrect amount" << endl;
		return Rlist;
	}

	for (q = 0; q < Rlist[i].substances.size(); q++)
	{
		if (Rlist[i].substances[q].name == subst)
		{
			same = true;
			break;
		}
	}

	for (unsigned int j = 0; j < Rlist[i].substances.size(); j++)
	{
		current += Rlist[i].substances[j].amount;
	}

	if (Rlist[i].volume < current + amount)
	{
		razn = amount - (Rlist[i].volume - current);
		Substance over = Substance(subst, razn);
		*pallet = overflow(*pallet, over);
		if (same == true)
		{
			Rlist[i].substances[q].amount += (Rlist[i].volume - current);
			return Rlist;
		}
		else Rlist[i].substances.push_back(Substance(subst, Rlist[i].volume - current));
		return Rlist;
	}
	if (same == true)
	{
		Rlist[i].substances[q].amount += amount;
		return Rlist;
	}
	else Rlist[i].substances.push_back(Substance(subst, amount));
	return Rlist;
}

Pallet add_to_pallet(Pallet pallet)
{
	string subst;
	float amount;


	cout << "Enter substance" << endl;
	cin >> subst;


	cout << "Enter amount" << endl;
	cin >> amount;

	if (amount <= 0)
	{
		cout << "Incorrect amount" << endl;
		return pallet;
	}

	pallet.substances.push_back(Substance(subst, amount));

	return pallet;
}

vector<Tube> add_tube(vector<Tube> Tlist)
{
	string name;
	float volume;

	cout << "Enter name for this tube" << endl;
	cin >> name;

	cout << "Enter maximum volume" << endl;
	cin >> volume;

	if (volume <= 0)
	{
		cout << "Incorrect volume" << endl;
		return Tlist;
	}

	Tlist.push_back(Tube(name, volume));
	return Tlist;
}

vector<Retort> add_retort(vector<Retort> Rlist)
{
	string name;
	float volume;

	cout << "Enter name for this retort" << endl;
	cin >> name;

	cout << "Enter maximum volume" << endl;
	cin >> volume;

	if (volume <= 0)
	{
		cout << "Incorrect volume" << endl;
		return Rlist;
	}

	Rlist.push_back(Retort(name, volume));
	return Rlist;
}

Pallet overflow(Pallet pallet, Substance substance)
{
	bool same = false;
	unsigned int q;
	for (q = 0; q < pallet.substances.size(); q++)
	{
		if (pallet.substances[q].name == substance.name)
		{
			same = true;
			break;
		}
	}

	if (same == true)
	{
		pallet.substances[q].amount += substance.amount;
	}
	else pallet.substances.push_back(substance);

	return pallet;
}

vector<Tube> clear_tube(vector<Tube> Tlist, Pallet* pallet)
{
	unsigned int i;

	cout << "Enter number of tube" << endl;
	cin >> i;
	i--;

	for (unsigned int j = 0; j < Tlist[i].substances.size(); j++)
	{
		Substance buff = Tlist[i].substances[j];
		*pallet = overflow(*pallet, buff);
	}

	for (unsigned int j = 0; j < Tlist[i].substances.size(); j++)
	{
		Tlist[i].substances.pop_back();
	}

	return Tlist;
}

vector<Retort> clear_retort(vector<Retort> Rlist, Pallet* pallet)
{
	unsigned int i;

	cout << "Enter number of retort" << endl;
	cin >> i;
	i--;

	for (unsigned int j = 0; j < Rlist[i].substances.size(); j++)
	{
		Substance buff = Rlist[i].substances[j];
		*pallet = overflow(*pallet, buff);
	}

	for (unsigned int j = 0; j < Rlist[i].substances.size(); j++)
	{
		Rlist[i].substances.pop_back();
	}

	return Rlist;
}

Pallet clear_pallet(Pallet pallet)
{
	for (unsigned int i = 0; i < pallet.substances.size(); i++)
	{
		pallet.substances.pop_back();
	}
	return pallet;
}

void menu()
{
	cout << "1)Add item" << endl;
	cout << "2)Add fluid" << endl;
	cout << "3)Clear item" << endl;
	cout << "4)Print current state" << endl;
	cout << "9)Exit" << endl;
 }

void print(vector<Tube> Tlist, vector<Retort> Rlist, Pallet pallet)
{
	cout << "Tubes:" << endl;

	for (unsigned i = 0; i < Tlist.size(); i++)
	{
		cout << "--------------------------------------------------------------------" << endl;
		cout << Tlist[i].name << "   " << Tlist[i].volume << endl << "Contains:" << endl;

		for (unsigned int j = 0; j < Tlist[i].substances.size(); j++)
		{
			cout << Tlist[i].substances[j].name << ": " << Tlist[i].substances[j].amount << endl;
		}
	}

	cout << endl << endl << endl << "Retorts:" << endl;

	for (unsigned i = 0; i < Rlist.size(); i++)
	{
		cout << "--------------------------------------------------------------------" << endl;
		cout << Rlist[i].name << "   " << Rlist[i].volume << endl << "Contains:" << endl;

		for (unsigned int j = 0; j < Rlist[i].substances.size(); j++)
		{
			cout << Rlist[i].substances[j].name << ": " << Rlist[i].substances[j].amount << endl;
		}
	}

	cout << endl << endl << endl << "Pallet:" << endl;

	for (unsigned int i = 0; i < pallet.substances.size(); i++)
	{
		cout << "--------------------------------------------------------------------" << endl;
		cout << pallet.substances[i].name << " " << pallet.substances[i].amount << endl;
	}
}