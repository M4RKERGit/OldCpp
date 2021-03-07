#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Post
{
private:

public:
	vector<string> text;
	string date;
	char photo;

	Post(vector<string> txt, string dt, char ph)
	{
		text = txt;
		date = dt;
		photo = ph;
	}


protected:

};

class User
{
private:

public:
	int ID;
	string fn, sn, birth;
	vector<Post>wall;
	vector<string>friends;
	vector<char>photos;

	User(int i, string FN, string SN, string BD)
	{
		ID = i;
		fn = FN;
		sn = SN;
		birth = BD;
	}


protected:

};

vector<User>Setup(vector<User>Ulist);
vector<User>add_user(vector<User>Ulist);
vector<User>add_friend(vector<User>Ulist);
vector<User>add_post(vector<User>Ulist);
void define_picture(char sym);
void print_all(vector<User>Ulist);
void print_user(vector<User>Ulist);
void print_news(vector<User>Ulist);
void menu();


int main()
{
	vector<User>Ulist;
	Ulist = Setup(Ulist);
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
			Ulist = add_user(Ulist);
			break;
		case 2:
			Ulist = add_friend(Ulist);
			break;
		case 3:
			print_all(Ulist);
			break;
		case 4:
			print_user(Ulist);
			break;
		case 5:
			Ulist = add_post(Ulist);
			break;
		case 6:
			print_news(Ulist);
			break;
		case 9:
			flag = false;
			break;
		default:
			print_all(Ulist);
			break;
		}
		system("pause");
		system("cls");
	}
}

vector<User>Setup(vector<User>Ulist)
{
	Ulist.push_back(User(1, "Oleg", "Ivolga", "29/03/2001"));
	Ulist.push_back(User(2, "Alexey", "Podvoysky", "04/09/2000"));
	Ulist.push_back(User(3, "Nariman", "Namazov", "18/07/2000"));
	Ulist[0].friends.push_back("2 Alexey Podvoysky 04/09/2000");
	Ulist[1].friends.push_back("1 Oleg Ivolga 29/03/2001");
	Ulist[0].friends.push_back("3 Nariman Namazov 18/07/2000");
	Ulist[2].friends.push_back("1 Oleg Ivolga 29/03/2001");

	return Ulist;
}

vector<User>add_user(vector<User>Ulist)
{
	string FN, SN, BD;
	int aidi;
	cout << "Enter new user's first name" << endl;
	cin >> FN;
	cout << "Enter new user's first name" << endl;
	cin >> SN;
	cout << "Enter new user's birth date in this format: DD/MM/YYYY" << endl;
	cin >> BD;

	aidi = Ulist.size() + 1;

	Ulist.push_back(User(aidi, FN, SN, BD));

	return Ulist;
}

vector<User>add_friend(vector<User>Ulist)
{
	int Uid, Fid;
	string Add = "";
	string Add2 = "";


	cout << "Enter user's ID" << endl;
	cin >> Uid;

	cout << "Enter friend's ID" << endl;
	cin >> Fid;

	Fid -= 1;
	Uid -= 1;

	Add += Fid;
	Add += " ";
	Add += Ulist[Fid].fn;
	Add += " ";
	Add += Ulist[Fid].sn;

	Add += Uid;
	Add += " ";
	Add2 += Ulist[Uid].fn;
	Add2 += " ";
	Add2 += Ulist[Uid].sn;

	Ulist[Uid].friends.push_back(Add);
	Ulist[Fid].friends.push_back(Add2);

	return Ulist;
}

vector<User>add_post(vector<User>Ulist)
{
	unsigned id;
	string date;
	vector<string> TXT;
	char photo;
	string txtbuff;

	cout << "Enter user's ID:" << endl;
	cin >> id;
	id -= 1;

	cout << "Enter text for a post(5 lines maximum):" << endl;

	for (unsigned int i = 0; i < 6; i++)
	{
		getline(cin, txtbuff);
		TXT.push_back(txtbuff);
	}

	for (unsigned int i = 0; i < TXT.size(); i++)
	{
		if (TXT[i].empty())
		{
			TXT.erase(TXT.begin() + i);
			i--;
		}
	}
	
	cout << "Post limit reached" << endl;


	cout << "Enter post date:" << endl;

	cin >> date;

	cout << "Choose picture:" << endl;

	cin >> photo;

	Post Np = Post(TXT, date, photo);

	Ulist[id].wall.push_back(Np);

	return Ulist;
}

void print_news(vector<User>Ulist)
{
	int id;
	string buff;
	int idbuff;

	cout << "Enter user's ID" << endl;
	cin >> id;
	id -= 1;
	cout << "NEWS:" << endl << endl;

	for (unsigned int i = 0; i < Ulist[id].friends.size(); i++)
	{
		buff = Ulist[id].friends[i][0];
		idbuff = stoi(buff);
		idbuff -= 1;
		if (Ulist[idbuff].wall.size() > 0)
		{
			cout << Ulist[idbuff].fn << " " << Ulist[idbuff].sn << endl << endl << endl;

			for (unsigned int j = 0; j < Ulist[idbuff].wall.size(); j++)
			{
				cout << Ulist[idbuff].wall[j].date << endl << endl;
				for (unsigned int q = 0; q < Ulist[idbuff].wall[j].text.size(); q++)
				{
					cout << Ulist[idbuff].wall[j].text[q] << endl;
				}
				cout << endl;
				define_picture(Ulist[idbuff].wall[j].photo);
				cout << endl << endl << "--------------------------------------------------------------" << endl << endl;
			}
		}

	}
}

void define_picture(char sym)
{
	string Flower[29] = {
	"                 $$$",
	"             $$$$  $$$$",
	"           $$$$$  $$$$$$",
	"          $$$$$  $$$$$$$$",
	"          $$$$$  $$$$$$$  $$$$",
	"      $$   $$$$$  $$$$  $$$$$$$$",
	"    $$$$$$    $$$  $$   $$$$$$$$$",
	"   $$$$$$$            $$$$    $$$$",
	"  $$$$$$$$$$     §§   $$  $$$$  $$$",
	" $$$$$$$$$$$$$  §§§§    $$$$$$$$  $$",
	"$$  $$$$$$$$    §§§§  $$$$$$$$$$$$$$",
	"$$$$  $$$$  $$   §§     $$$$$$$$$$$",
	"   $$$$$    $$$$            $$$$$$$$",
	" $$$$$$$$$   $$  $$$    $$$$$$",
	"    $$$$$$$$  $$$$  $$$$$   $$",
	"      $$$$  $$$$$$$  $$$$$",
	"           $$$$$$$$  $$$$$",
	"            $$$$$$  $$$$$",
	"   §§        $$$$  $$$$",
	"  §§ §§         $$$         §",
	"  §§§ §§§       §§§        § §",
	"   §§§ §§§      §§§      §§§ §§",
	"   §§§§ §§§     §§§     §§§ §§§",
	"    §§§§ §§§    §§§    §§§§ §§",
	"     §§§§§ §§§§ §§§ §§§§§ §§§",
	"      §§§§§§ §§§§§§§§§§§ §§§",
	"       §§§§§§§ §§§§§§§§ §§§",
	"         §§§§§§ §§§§§ §§§§",
	"            §§§§§§§ §§§§§"
	};

	string Motocycle[22] = {
	"                      oooo",
	"                    oo      ||                   ooo",
	"                              |||                ||    oo",
	"                                |||              ||",
	"                                  |||            ||",
	"                                       ooooooooooo",
	"                                oooooooooooOOOoo",
	"                          ooooooooooooo   OOO oo",
	"                      ooooooooooooooooooooooooo",
	"     ooooooooo    oooooooooooooo oo            oo",
	"   oooooooooooooooooooooooooo   oo            ooo",
	"  ooooooooooooooooooooooooooooo oo   oooooooooo",
	" oo        oooooooooooooooooooooooooooooooooooooooo",
	"oo        oooooooooooooooooooooo    oooo       ooooooooo",
	"ooooooooooooooooooooooooooooo   oooo             ooooooooo",
	" oo        ooooooooooooooooooooo   oo oo          ooooooooo",
	"  oo       oooooooooooooooooooooooooo oo           ooooooooo",
	"    ooooooooooooooooooooooooooooooo              ==ooooooooo",
	"       ooooo        ooooooooooooooo  oooo         ooooooooo",
	"                                    ooooo       ooooooooo",
	"                                        oooooooooooooooo",
	"                                          oooooooooooo"
	};
	
	switch (sym)
	{
	case '*':
		for (unsigned int i = 0; i < 29; i++)
			cout << Flower[i] << endl;
		break;
	case '$':
		for (unsigned int i = 0; i < 22; i++)
			cout << Motocycle[i] << endl;
		break;
	default:
		cout << "No picture" << endl;
		break;
	}
}

void print_all(vector<User>Ulist)
{
	for (unsigned i = 0; i < Ulist.size(); i++)
	{
		cout << Ulist[i].ID << " " << setw(12) << left << Ulist[i].fn << setw(12) << left << Ulist[i].sn << setw(12) << left << Ulist[i].birth << endl;
	}
}

void print_user(vector<User>Ulist)
{
	unsigned int id;
	
	cout << "Enter user's ID" << endl;
	cin >> id;
	id -= 1;

	cout << setw(8) << left << Ulist[id].fn << setw(8) << left << Ulist[id].sn << endl << setw(8) << left << Ulist[id].birth << endl;

	cout << "FRIENDS:" << endl;

	for (unsigned int i = 0; i < Ulist[id].friends.size(); i++)
	{
		cout << Ulist[id].friends[i] << endl;
	}

	cout << "WALL:" << endl << endl;

	for (unsigned int i = 0; i < Ulist[id].wall.size(); i++)
	{
		cout << Ulist[id].wall[i].date << endl << endl;
		for (unsigned int q = 0; q < Ulist[id].wall[i].text.size(); q++)
		{
			cout << Ulist[id].wall[i].text[q] << endl;
		}
		cout << endl;
		define_picture(Ulist[id].wall[i].photo);
		cout << endl << endl << "--------------------------------------------------------------" << endl << endl;
	}
}

void menu()
{
	cout << "1)Add new user" << endl;
	cout << "2)Add friend to user" << endl;
	cout << "3)Print all info shortly" << endl;
	cout << "4)Print all about chosen user" << endl;
	cout << "5)Create a post" << endl;
	cout << "6)Print user's news" << endl;
	cout << "9)Exit" << endl;
}