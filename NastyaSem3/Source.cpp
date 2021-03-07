#define _CRT_SECURE_NO_WARNINGS


#include <vector>
#include <string>
#include <iostream>
#include <iomanip>


using namespace std;

class Forum
{
private:

public:
	string Fname;
	vector<string> participants;
	string chairman;
	string secretary;
	double UserAmount;

	Forum(string fname, double useramount)
	{
		Fname = fname;
		UserAmount = useramount;
		vector<string> participants;
		chairman = "";
		secretary = "";
	}

protected:

};

vector<Forum> Setup(vector<Forum> Flist);
vector<Forum> add_forum(vector<Forum> Flist);
vector<Forum> delete_forum(vector<Forum> Flist);
vector<Forum> add_person(vector<Forum> Flist);
vector<Forum> delete_person(vector<Forum> Flist);
void print(vector <Forum> Flist);
void menu();

int main()
{
	vector<Forum>Flist;
	Flist = Setup(Flist);
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
			Flist = add_forum(Flist);
			break;
		case 2:
			Flist = delete_forum(Flist);
			break;
		case 3:
			Flist = add_person(Flist);
			break;
		case 4:
			Flist = delete_person(Flist);
			break;
		case 5:
			print(Flist);
			break;
		case 9:
			flag = false;
			break;
		default:
			print(Flist);
			break;
		}
		system("pause");
		system("cls");
	}
}

vector<Forum> Setup(vector<Forum>Flist)
{
	vector<string> part;
	Forum buff = Forum("2ch.hk", 2000);
	buff.participants.push_back("Oleg Ivolga");
	buff.participants.push_back("Kirill Alyamovsky");
	buff.chairman = "Nariman Namazov";
	buff.secretary = "Abu";
	Flist.push_back(buff);

	return Flist;
}

vector<Forum> add_forum(vector<Forum> Flist)
{
	string name;
	double amount;

	cout << "Enter title for this forum" << endl;
	cin.ignore();
	getline(cin, name);

	for (unsigned int i = 0; i < Flist.size(); i++)
	{
		if (name == Flist[i].Fname)
		{
			cout << "This forum already exists" << endl;
			return Flist;
		}
	}

	cout << "Enter maximum amount of people for this forum" << endl;
	cin >> amount;
	Flist.push_back(Forum(name, amount));

	return Flist;
}

vector<Forum> delete_forum(vector<Forum> Flist)
{
	string name;

	cout << "Enter forum title" << endl;
	cin.ignore();
	getline(cin, name);

	for (unsigned int i = 0; i < Flist.size(); i++)
	{
		if (Flist[i].Fname == name)
		{
			Flist.erase(Flist.begin() + i);
			break;
		}
	}

	return Flist;
}

vector<Forum> add_person(vector<Forum> Flist)
{
	string fname, user, buff;
	unsigned int opt, id = -1;

	cout << "Enter forum title" << endl;
	cin.ignore();
	getline(cin, fname);

	for (unsigned int q = 0; q < Flist.size(); q++)
	{
		if (fname == Flist[q].Fname)
		{
			id = q;
			break;
		}
	}

	if (id == -1)
	{
		cout << "There's no such forum" << endl;
		return Flist;
	}

	if (Flist[id].UserAmount <= Flist[id].participants.size())
	{
		cout << "Forum is filled, kick somebody out first" << endl;
		return Flist;
	}

	cout << "Enter 1 for adding chairman, 2 for secretary and 3 for simple participant" << endl;
	cin >> opt;

	cout << "Enter person's name" << endl;
	cin.ignore();
	getline(cin, user);

	switch (opt)
	{
	case 1:
		if (Flist[id].chairman != "")
		{
			buff = Flist[id].chairman;
			Flist[id].participants.push_back(buff);
		}
		Flist[id].chairman = user;

		break;
	case 2:
		if (Flist[id].secretary != "")
		{
			buff = Flist[id].secretary;
			Flist[id].participants.push_back(buff);
		}
		Flist[id].secretary = user;

		break;
	case 3:
		Flist[id].participants.push_back(user);
		break;
	default:
		Flist[id].participants.push_back(user);
		break;
	}

	return Flist;
}

vector<Forum> delete_person(vector<Forum> Flist)
{
	unsigned int opt, id = -1;
	string name, fname;


	cout << "Do you want to delete person from everywhere(1) or only current forum(2) ?" << endl;
	cin >> opt;

	if (opt == 1)
	{
		cout << "Enter person's name" << endl;
		cin.ignore();
		getline(cin, name);

		for (unsigned int i = 0; i < Flist.size(); i++)
		{
			if (name == Flist[i].chairman)
			{
				Flist[i].chairman = "";
			}

			if (name == Flist[i].secretary)
			{
				Flist[i].secretary = "";
			}

			for (unsigned int j = 0; j < Flist[i].participants.size(); j++)
			{
				if (name == Flist[i].participants[j])
				{
					Flist[i].participants[j] = "";
				}
			}
		}
	}


	if (opt == 2)
	{
		cout << "Enter forum title" << endl;
		cin.ignore();
		getline(cin, fname);

		for (unsigned int i = 0; i < Flist.size(); i++)
		{
			if (fname == Flist[i].Fname)
			{
				id = i;
				break;
			}
		}

		if (id == -1)
		{
			cout << "There's no such forum" << endl;
			return Flist;
		}

		cout << "Enter person's Name_Sirname" << endl;
		getline(cin, name);

		if (name == Flist[id].chairman)
		{
			Flist[id].chairman = "";
		}

		if (name == Flist[id].secretary)
		{
			Flist[id].secretary = "";
		}

		for (unsigned int j = 0; j < Flist[id].participants.size(); j++)
		{
			if (name == Flist[id].participants[j])
			{
				Flist[id].participants[j] = "";
			}
		}
	}
	
	return Flist;
}

void menu()
{
	cout << "1)Add new forum" << endl;
	cout << "2)Delete forum" << endl;
	cout << "3)Add new person" << endl;
	cout << "4)Delete person" << endl;
	cout << "5)Print all info" << endl;
	cout << "9)Exit" << endl;
}

void print(vector <Forum> Flist)
{
	cout << "----------------------------------------------------------" << endl;
	for (unsigned int i = 0; i < Flist.size(); i++)
	{
		cout << Flist[i].Fname << ":" << endl << endl;
		cout << "Chairman: " << Flist[i].chairman << endl << endl;
		cout << "Secretary: " << Flist[i].secretary << endl << endl;
		cout << "Participants[" << Flist[i].participants.size() << "/" << Flist[i].UserAmount  << "]" << ":" << endl << endl;

		for (unsigned int j = 0; j < Flist[i].participants.size(); j++)
		{
			cout << Flist[i].participants[j] << endl;
		}
		cout << "----------------------------------------------------------" << endl;
	}
}