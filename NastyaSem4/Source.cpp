#define _CRT_SECURE_NO_WARNINGS


#include <vector>
#include <string>
#include <iostream>
#include <iomanip>


using namespace std;

class AND
{
private:

public:
    bool in1, in2, out;
    string name;

    AND(string Name)
    {
        name = Name;
        in1 = 0;
        in2 = 0;
        out = 0;
    }

    AND Refresh(AND object)
    {
        object.out = in1 & in2;
        return object;
    }

protected:

};

class OR
{
private:

public:
    bool in1, in2, out;
    string name;

    OR(string Name)
    {
        name = Name;
        in1 = 0;
        in2 = 0;
        out = 0;
    }

    OR Refresh(OR object)
    {
        object.out = in1 | in2;
        return object;
    }

protected:

};

class NOT
{
private:

public:
    string name;
    bool in, out;

    NOT(string Name)
    {
        name = Name;
        in = 0;
        out = 0;
    }

    NOT Refresh(NOT object)
    {
        object.out = !in;
        return object;
    }

protected:

};

vector<AND> add_AND(vector<AND> Alist);
vector<OR> add_OR(vector<OR> Olist);
vector<NOT> add_NOT(vector<NOT> Nlist);
int connect(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist);
void delete_part(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist);
void Refresh(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist);
void new_scheme(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist);
void Setup(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist);
void print(vector<AND> Alist, vector<OR> Olist, vector<NOT> Nlist);
void menu();

int main()
{
    vector<AND> Alist;
    vector<OR> Olist;
    vector<NOT> Nlist;
    Setup(Alist, Olist, Nlist);
    Refresh(Alist, Olist, Nlist);
    bool flag = true;
    unsigned int option, opt;

    while (flag)
    {
        menu();
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            cout << "1 for AND, 2 for OR, 3 for NOT" << endl;
            cin >> opt;
            switch (opt)
            {
            case 1:
                Alist = add_AND(Alist);
                break;
            case 2:
                Olist = add_OR(Olist);
                break;
            case 3:
                Nlist = add_NOT(Nlist);
                break;
            }
            Refresh(Alist, Olist, Nlist);
            break;
        case 2:
            delete_part(Alist, Olist, Nlist);
            break;
        case 3:
            connect(Alist, Olist, Nlist);
            Refresh(Alist, Olist, Nlist);
            break;
        case 4:
            new_scheme(Alist, Olist, Nlist);
            break;
        case 5:
            print(Alist, Olist, Nlist);
            break;
        case 9:
            flag = false;
            break;
        default:
            print(Alist, Olist, Nlist);
            break;
        }
        system("pause");
        system("cls");
    }
}

vector<AND> add_AND(vector<AND> Alist)
{
    string name;

    cout << "Enter codename for this part" << endl;
    cin.ignore();
    getline(cin, name);

    Alist.push_back(AND(name));

    return Alist;
}

vector<OR> add_OR(vector<OR> Olist)
{
    string name;

    cout << "Enter codename for this part" << endl;
    cin.ignore();
    getline(cin, name);

    Olist.push_back(OR(name));

    return Olist;
}

vector<NOT> add_NOT(vector<NOT> Nlist)
{
    string name;

    cout << "Enter codename for this part" << endl;
    cin.ignore();
    getline(cin, name);

    Nlist.push_back(NOT(name));

    return Nlist;
}

void delete_part(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist)
{
    string cname;

    cout << "Enter codename" << endl;
    cin.ignore();
    getline(cin, cname);

    for (unsigned int i = 0; i < Alist.size(); i++)
    {
        if (cname == Alist[i].name)
        {
            Alist.erase(Alist.begin() + i);
            break;
        }
    }

    for (unsigned int i = 0; i < Olist.size(); i++)
    {
        if (cname == Olist[i].name)
        {
            Olist.erase(Olist.begin() + i);
            break;
        }
    }

    for (unsigned int i = 0; i < Nlist.size(); i++)
    {
        if (cname == Nlist[i].name)
        {
            Nlist.erase(Nlist.begin() + i);
            break;
        }
    }
}

int connect(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist)
{
    unsigned int id1, id2, inopt;
    bool found = false;
    string fname, sname;
    char ftype, stype;

    cout << "FIRST ELEMENT:" << endl << endl;

    cout << "Enter element's codename:" << endl;
    cin >> fname;

    for (unsigned int i = 0; i < Alist.size(); i++)
    {
        if (fname == Alist[i].name)
        {
            found = true;
            ftype = 'a';
            id1 = i;
            break;
        }
    }

    for (unsigned int i = 0; i < Olist.size(); i++)
    {
        if (fname == Olist[i].name)
        {
            found = true;
            ftype = 'o';
            id1 = i;
            break;
        }
    }

    for (unsigned int i = 0; i < Nlist.size(); i++)
    {
        if (fname == Nlist[i].name)
        {
            found = true;
            ftype = 'n';
            id1 = i;
            break;
        }
    }

    if (found == false)
    {
        cout << "There's no such element" << endl;
        return 0;
    }

    cout << "SECOND ELEMENT:" << endl << endl;

    cout << "Enter element's codename:" << endl;
    cin >> sname;

    for (unsigned int i = 0; i < Alist.size(); i++)
    {
        if (sname == Alist[i].name)
        {
            found = true;
            stype = 'a';
            id2 = i;
            break;
        }
    }

    for (unsigned int i = 0; i < Olist.size(); i++)
    {
        if (sname == Olist[i].name)
        {
            found = true;
            stype = 'o';
            id2 = i;
            break;
        }
    }

    for (unsigned int i = 0; i < Nlist.size(); i++)
    {
        if (sname == Nlist[i].name)
        {
            found = true;
            stype = 'n';
            id2 = i;
            break;
        }
    }

    if (found == false)
    {
        cout << "There's no such element" << endl;
        return 0;
    }




    if (ftype == 'a')
    {
        if (stype == 'a')
        {
            cout << "First or second in?" << endl;
            cin >> inopt;
            if (inopt == 1)
            {
                Alist[id2].in1 = Alist[id1].out;
            }
            else Alist[id2].in2 = Alist[id1].out;
        }

        if (stype == 'o')
        {
            cout << "First or second in?" << endl;
            cin >> inopt;
            if (inopt == 1)
            {
                Olist[id2].in1 = Alist[id1].out;
            }
            else Olist[id2].in2 = Alist[id1].out;
        }

        if (stype == 'n')
        {
            Nlist[id2].in = Alist[id1].out;
        }


    }


    if (ftype == 'o')
    {
        if (stype == 'a')
        {
            cout << "First or second in?" << endl;
            cin >> inopt;
            if (inopt == 1)
            {
                Alist[id2].in1 = Olist[id1].out;
            }
            else Alist[id2].in2 = Olist[id1].out;
        }

        if (stype == 'o')
        {
            cout << "First or second in?" << endl;
            cin >> inopt;
            if (inopt == 1)
            {
                Olist[id2].in1 = Olist[id1].out;
            }
            else Olist[id2].in2 = Olist[id1].out;
        }

        if (stype == 'n')
        {
            Nlist[id2].in = Olist[id1].out;
        }


    }


    if (ftype == 'n')
    {
        if (stype == 'a')
        {
            cout << "First or second in?" << endl;
            cin >> inopt;
            if (inopt == 1)
            {
                Alist[id2].in1 = Nlist[id1].out;
            }
            else Alist[id2].in2 = Nlist[id1].out;
        }

        if (stype == 'o')
        {
            cout << "First or second in?" << endl;
            cin >> inopt;
            if (inopt == 1)
            {
                Olist[id2].in1 = Nlist[id1].out;
            }
            else Olist[id2].in2 = Nlist[id1].out;
        }

        if (stype == 'n')
        {
            Nlist[id2].in = Nlist[id1].out;
        }


    }
    return 0;
}

void Refresh(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist)
{
    for (unsigned int i = 0; i < Alist.size(); i++)
    {
        Alist[i] = Alist[i].Refresh(Alist[i]);
    }

    for (unsigned int i = 0; i < Olist.size(); i++)
    {
        Olist[i] = Olist[i].Refresh(Olist[i]);
    }

    for (unsigned int i = 0; i < Nlist.size(); i++)
    {
        Nlist[i] = Nlist[i].Refresh(Nlist[i]);
    }
}

void new_scheme(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist)
{
    Alist.clear();
    Olist.clear();
    Nlist.clear();
}

void menu()
{
    cout << "1)Add new part" << endl;
    cout << "2)Delete chosen part" << endl;
    cout << "3)Connect smth to smth" << endl;
    cout << "4)Create new scheme" << endl;
    cout << "5)Print scheme" << endl;
}

void Setup(vector<AND>& Alist, vector<OR>& Olist, vector<NOT>& Nlist)
{
    AND and1("and1");
    OR or1("or1");
    NOT not1("not1");
    Alist.push_back(and1);
    Olist.push_back(or1);
    Nlist.push_back(not1);
}

void print(vector<AND> Alist, vector<OR> Olist, vector<NOT> Nlist)  
{
    cout << "AND ELEMENTS:" << endl << endl;

    for (unsigned int i = 0; i < Alist.size(); i++)
    {
        cout << Alist[i].name << endl;
        cout << "In1:" << Alist[i].in1 << endl;
        cout << "In2:" << Alist[i].in2 << endl;
        cout << "Out:" << Alist[i].out << endl;
        cout << "-------------------------------------------";
    }

    cout << endl << endl << "OR ELEMENTS:" << endl << endl;

    for (unsigned int i = 0; i < Olist.size(); i++)
    {
        cout << Olist[i].name << endl;
        cout << "In1:" << Olist[i].in1 << endl;
        cout << "In2:" << Olist[i].in2 << endl;
        cout << "Out:" << Olist[i].out << endl;
        cout << "-------------------------------------------";
    }

    cout << endl << endl << "NOT ELEMENTS:" << endl << endl;

    for (unsigned int i = 0; i < Nlist.size(); i++)
    {
        cout << Nlist[i].name << endl;
        cout << "In:" << Nlist[i].in << endl;
        cout << "Out:" << Nlist[i].out << endl;
        cout << "-------------------------------------------";
    }
    cout << endl;
}