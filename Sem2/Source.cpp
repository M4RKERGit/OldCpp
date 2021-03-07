#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;



class Pos
{
	private:

	public:
		
		int hour, minute;
		bool busy;

		Pos(unsigned int i, unsigned int j)
		{
			hour = i;
			minute = j * 15;
			busy = false;
		}

	protected:

};


class Quest
{
	private:


	public:
		int QShour, QSminute, QEhour, QEminute;
		string Qname;
		char nj, nb;

		Quest(int i, int j, int a, int b, string Name)
		{
			QShour = i;
			QEhour = a;
			
			QSminute = j;
			QEminute = b;

			Qname = Name;
		}

		Quest(const Quest& object)
		{
			QShour = object.QShour;
			QEhour = object.QEhour;

			QSminute = object.QSminute;
			QEminute = object.QEminute;

			Qname = object.Qname;
		}
		
		~Quest()
		{

		}


	protected:

};


vector<Pos> Setup(vector<Pos> plan);
vector<Quest> add_quest(vector<Quest> Qlist);
vector<Pos> Update(vector<Pos> plan, vector<Quest> Qlist);
vector<Quest> Delete(vector<Quest> Qlist);
void menu();
void print(vector<Pos> list, vector<Quest> Qlist);


int main()
{
	int option;
	bool flag = true;

	vector<Quest> Qlist;
	vector<Pos> plan;
	plan = Setup(plan);

	while (flag)
	{
		menu();
		cin >> option;
		system("cls");
		switch (option)
		{
		case 1:
			Qlist = add_quest(Qlist);
			plan = Update(plan, Qlist);
			break;
		case 2:
			Qlist = Delete(Qlist);
			plan = Update(plan, Qlist);
			break;
		case 3:
			print(plan, Qlist);
			break;
		case 9:
			flag = false;
			break;
		default:
			print(plan, Qlist);
			break;
		}
		system("pause");
		system("cls");
	}
}

vector<Pos> Setup(vector<Pos> plan)
{
	for (unsigned int i = 7; i < 23; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			plan.push_back(Pos(i, j));
		}
	}
	return plan;
}

vector<Quest> add_quest(vector<Quest> Qlist)
{
	int sh, sm, eh, em;
	string Qname;

	cout << "Enter start hour" << endl;
	cin >> sh;

	if (sh > 23 || sh < 7)
	{
		cout << "Incorrect input, execution is not allowed" << endl;
		return Qlist;
	}

	cout << "Enter start minute" << endl;
	cin >> sm;

	if (sm > 60 || sm < 0)
	{
		cout << "Incorrect input, execution is not allowed" << endl;
		return Qlist;
	}

	cout << "Enter end hour" << endl;
	cin >> eh;

	if (eh > 23 || eh < 7)
	{
		cout << "Incorrect input, execution is not allowed" << endl;
		return Qlist;
	}

	cout << "Enter end minute" << endl;
	cin >> em;

	if (em > 60 || em < 0)
	{
		cout << "Incorrect input, execution is not allowed" << endl;
		return Qlist;
	}

	cout << "Enter quest's name" << endl;
	cin >> Qname;

	if (Qname.length() > 30 || Qname.length() < 1)
	{
		cout << "Incorrect input, execution is not allowed" << endl;
		return Qlist;
	}

	Qlist.push_back(Quest(sh, sm, eh, em, Qname));

	vector<Pos> empty;

	print(empty, Qlist);

	return Qlist;
}

vector<Pos> Update(vector<Pos> plan, vector<Quest> Qlist)
{
	int Ssum, Esum, QSsum, QEsum;
	for (unsigned int i = 0; i < plan.size(); i++)
	{
		plan[i].busy = false;
	}
	for (unsigned int i = 0; i < plan.size(); i++)
	{
		for (unsigned int j = 0; j < Qlist.size(); j++)
		{
			Ssum = plan[i].hour * 60 + plan[i].minute;
			Esum = Ssum + 15;
			QSsum = Qlist[j].QShour * 60 + Qlist[j].QSminute;
			QEsum = Qlist[j].QEhour * 60 + Qlist[j].QEminute;
			if (Ssum >= QSsum && Esum <= QEsum)
			{
				plan[i].busy = true;
			}
			if (QSsum > Ssum && QEsum < Esum)
			{
				plan[i].busy = true;
			}
			if (QEsum - Ssum < 15 && QEsum - Ssum > 0)
			{
				plan[i].busy = true;
			}
		}
	}
	return plan;
}

vector<Quest> Delete(vector<Quest> Qlist)
{
	int num;
	cout << "Enter a number of quest you want to delete" << endl;
	cin >> num;

	if (Qlist.size() == 0)
	{
		cout << "Nothing to delete" << endl;
		return Qlist;
	}

	Qlist.erase(Qlist.begin() + num - 1);
	return Qlist;
}

void menu()
{
	cout << "1)Add new quest" << endl;
	cout << "2)Delete quest" << endl;
	cout << "3)Print all quests and timelines" << endl;
}

void print(vector<Pos> list, vector<Quest> Qlist)
{
	string SHour = "", EHour = "", SMin = "", EMin = "", buff = "", buff2 = "", Tbuff = "", BS = "";

	for (unsigned int i = 0; i < list.size(); i++)
	{		
		SMin = "";
		EMin = "";
		buff = "";
		buff2 = "";
		Tbuff = "";
		Tbuff = to_string(list[i].hour);
		if (list[i].hour < 10)
		{
			buff = "0" + Tbuff;
		}

		else buff = Tbuff;
			
		Tbuff = to_string(list[i].minute);
		if (list[i].minute < 10)
		{
			buff2 = "0" + to_string(list[i].minute);
		}

		else buff2 = Tbuff;

		if (list[i].busy == true)
		{
			BS = "BUSY";
		}
		else BS = "FREE";

		cout << buff << ":" << setw(12) << left << buff2 << setw(12) << left << BS << endl << endl;
	}


	cout << endl << endl << endl << endl << endl << "List of your quests for today:" << endl;
	SHour = "", EHour = "", SMin = "", EMin = "", buff = "", buff2 = "", Tbuff = "";

	for (unsigned int i = 0; i < Qlist.size(); i++)
	{
			
		Tbuff = to_string(Qlist[i].QShour);
		if (Qlist[i].QShour < 10)
		{
			SHour = "0" + Tbuff;
		}

		else SHour = Tbuff;
			
		Tbuff = to_string(Qlist[i].QEhour);
		if (Qlist[i].QEhour < 10)
		{
			EHour = "0" + Tbuff;
		}

		else EHour = Tbuff;

		Tbuff = to_string(Qlist[i].QSminute);
		if (Qlist[i].QSminute < 10)
		{
			SMin = "0" + Tbuff;
		}

		else SMin = Tbuff;

		Tbuff = to_string(Qlist[i].QEminute);
		if (Qlist[i].QEminute < 10)
		{
			EMin = "0" + Tbuff;
		}

		else EMin = Tbuff;


		cout << SHour << ":" << SMin << "-" << EHour << ":" << EMin  << "    " << Qlist[i].Qname << endl;
	}

}