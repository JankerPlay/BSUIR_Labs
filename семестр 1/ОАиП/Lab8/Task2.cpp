#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define ll long long
struct kvit
{
	string name;
	string surname;
	string thirdname;
	string adres;
	string date;
};
kvit* kvits = 0;
ll Amount = 0;
kvit* AddStruct(kvit* Obj, const int amount);
void setData(kvit* Obj, const int amount);
void showData(const kvit* Obj, const int amount);
void create();
void proverka(kvit* Obj, const int amount);
void zapis(const kvit* Obj, const int amount);
void remove(kvit* Obj, int amount);
void prosmotr();
int main()
{
	ofstream os("result.txt");
	setlocale(LC_ALL, "");
	ll a = 1;
	do
	{
		if (Amount > 1)
			proverka(kvits, Amount);
		cout << "�������� �������";
		cout << endl;
		cout << "0. ����� �� ���������";
		cout << endl;
		cout << "1. �������� ������� ���������";
		cout << endl;
		cout << "2. ������� ���������";
		cout << endl;
		cout << "3. �������� ��������� � ����";
		cout << endl;
		cout << "4. ������� ��������� �� �����";
		cout << endl;
		cout << "5. ������������ ������� ���������";
		cout << endl;
		a = 0;
		cin >> a;
		if (a == 1)
			create();
		else if (a == 2)
			showData(kvits, Amount);
		else if (a == 3)
			zapis(kvits, Amount);
		else if (a == 4)
			prosmotr();
		else if (a == 5)
			remove(kvits, Amount);
	} while (a != 0);
}
void remove(kvit* Obj, int amount)
{
	system("cls");
	ll a;
	cout << "������� ����� ������ ������� ������ ������������ ";
	cin >> a;
	a--;
	cout << "������� ��� ";
	cin >> Obj[a].name;
	cout << "������� ������� ";
	cin >> Obj[a].surname;
	cout << "������� �������� ";
	cin >> Obj[a].thirdname;
	cout << "������� ����� ";
	cin >> Obj[a].adres;
	cout << "������� ���� ";
	cin >> Obj[a].date;
}
void prosmotr()
{
	system("cls");
	string getcontent;
	ifstream se("result.txt");
	if (se.is_open())
		while (getline(se, getcontent))
			cout << getcontent << endl;
	se.close();
}
void setData(kvit* Obj, const int amount)
{
	system("cls");
	cout << "������� ��� ";
	cin >> Obj[amount].name;
	cout << "������� ������� ";
	cin >> Obj[amount].surname;
	cout << "������� �������� ";
	cin >> Obj[amount].thirdname;
	cout << "������� ����� ";
	cin >> Obj[amount].adres;
	cout << "������� ���� ";
	cin >> Obj[amount].date;
}
void create()
{
	ll YesOrNot = 0;
	do
	{
		kvits = AddStruct(kvits, Amount);
		setData(kvits, Amount);
		Amount++;
		cout << "���������� ���� ������ (1 - ��, 0 - ���): ";
		cin >> YesOrNot;
	} while (YesOrNot != 0);
}
kvit* AddStruct(kvit* Obj, const int amount)
{
	if (amount == 0)
		Obj = new kvit[amount + 1];
	else
	{
		kvit* tempObj = new kvit[amount + 1];
		for (int i = 0; i < amount; i++)
			tempObj[i] = Obj[i];
		Obj = tempObj;
	}
	return Obj;
}
void proverka(kvit* Obj, int amount)
{
	for (ll i = 0; i < amount; i++)
	{
		for (ll j = 0; j < amount; j++)
		{
			if (i != j and Obj[i].name == Obj[j].name and Obj[i].surname == Obj[j].surname and Obj[i].thirdname == Obj[j].thirdname and Obj[i].adres == Obj[j].adres)
			{
				for (ll q = i; q < Amount - 1; q++)
				{
					Obj[q].name = Obj[q + 1].name;
					Obj[q].surname = Obj[q + 1].surname;
					Obj[q].thirdname = Obj[q + 1].thirdname;
					Obj[q].adres = Obj[q + 1].adres;
					Obj[q].date = Obj[q + 1].date;
				}
				Amount--;
				amount--;
				i = 0; j = 0;
			}
		}
	}
}
void showData(const kvit* Obj, const int amount)
{
	system("cls");
	cout << "�  " << "���\t" << "������� " << "�������� " << "����� " << "���� " << endl;
	cout << "========================================" << endl;
	for (int i = 0; i < amount; i++)
		cout << i + 1 << "  " << Obj[i].name << '\t' << Obj[i].surname << '\t' << Obj[i].thirdname << '\t' << Obj[i].adres << '\t' << Obj[i].date << '\t' << endl;
}
void zapis(const kvit* Obj, const int amount)
{
	ofstream os("result.txt");
	os << "�  " << "���\t" << "������� " << "�������� " << "����� " << "���� " << endl;
	os << "========================================" << endl;
	for (int i = 0; i < amount; i++)
		os << i + 1 << "  " << Obj[i].name << '\t' << Obj[i].surname << '\t' << Obj[i].thirdname << '\t' << Obj[i].adres << '\t' << Obj[i].date << '\t' << endl;
	os.close();
}