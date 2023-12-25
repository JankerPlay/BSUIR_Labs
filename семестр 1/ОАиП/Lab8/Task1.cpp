#include <iostream>
#include <string>
using namespace std;
#define ll long long
struct kvit
{
	string name;
	string surname;
	ll sum;
};
kvit* kvits = 0;
ll Amount = 0;
kvit* AddStruct(kvit* Obj, const int amount);
void setData(kvit* Obj, const int amount);
void showData(const kvit* Obj, const int amount);
void create();
void search(kvit* Obj, const int amount);
void remove(kvit* Obj, int amount);
void sort(kvit* Obj, int amount);
int main()
{
	ll a = 1;
	do
	{
		setlocale(LC_ALL, "");
		printf("Выберите функцию\n");
		printf("0. Выход из программы\n");
		printf("1. Добавить элемент структуры\n");
		printf("2. Вывести структуру\n");
		printf("3. Найти элемент\n");
		printf("4. Удалить или перезаписать элемент\n");
		printf("5. Отсортировать (обменом по убыванию)\n");
		a = 0;
		scanf_s("%lld", &a);
		if (a == 1)
			create();
		else if (a == 2)
			showData(kvits, Amount);
		else if (a == 3)
			search(kvits, Amount);
		else if (a == 4)
			remove(kvits, Amount);
		else if (a == 5)
			sort(kvits, Amount);
	} while (a != 0);
	return 0;
}
void sort(kvit* Obj, int amount)
{
	for (int i = 1; i < amount; ++i)
	{
		for (int r = 0; r < amount - i; r++)
		{
			if (Obj[r].sum < Obj[r + 1].sum)
			{
				string temp1 = Obj[r].name;
				string temp2 = Obj[r].surname;
				int temp = Obj[r].sum;
				Obj[r].name = Obj[r + 1].name;
				Obj[r].surname = Obj[r + 1].surname;
				Obj[r].sum = Obj[r + 1].sum;
				Obj[r + 1].sum = temp;
				Obj[r + 1].name = temp1;
				Obj[r + 1].surname = temp2;
			}
		}
	}
}
void remove(kvit* Obj, int amount)
{
	ll a;
	printf("Введите номер строки которую хотите удалить или перезаписать ");
	scanf_s("%lld", &a);
	printf("Перезаписать(1) или удалить(2) ");
	ll b;
	scanf_s("%lld", &b);
	a--;
	if (b == 1)
	{
		printf("Название изделия: ");
		cin.ignore();
		getline(cin, Obj[a].surname);
		printf("Дата приема: ");
		getline(cin, Obj[a].name);
		printf("Готовность(0,1): ");
		scanf_s("%lld", &a);
	}
	else if (b == 2)
	{
		for (ll i = a; i < Amount - 1; i++)
		{
			Obj[i].surname = Obj[i + 1].surname;
			Obj[i].name = Obj[i + 1].name;
			Obj[i].sum = Obj[i + 1].sum;
		}
		Amount--;
	}
}
void search(kvit* Obj, const int amount)
{
	system("cls");
	printf("Введите ключевое слово: ");
	string key;
	bool x = 0;
	cin.ignore();
	getline(cin, key);
	ll key2 = key[0] - 48;
	for (ll i = 0; i < amount; i++)
	{
		if (key == Obj[i].name or key == Obj[i].surname or Obj[i].sum == key2)
		{
			printf("%d", i + 1);
			printf("\t");
			printf("%s", Obj[i].surname.c_str());
			printf("\t");
			printf("%s", Obj[i].name.c_str());
			printf("\t");
			printf("%lld", Obj[i].sum);
			printf("\n");
			x = 1;
		}
	}
	if (!x)
		printf("Элемент не найден\n");
}
void create()
{
	ll YesOrNot = 0;
	do
	{
		kvits = AddStruct(kvits, Amount);
		setData(kvits, Amount);
		Amount++;
		printf("Продолжить ввод данных (1 - да, 0 - нет): ");
		scanf_s("%lld", &YesOrNot);
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
void setData(kvit* Obj, const int amount)
{
	system("cls");
	printf("Название изделия: ");
	cin.ignore();
	getline(cin, Obj[amount].surname);
	printf("Дата приема: ");
	getline(cin, Obj[amount].name);
	printf("Готовность(0,1): ");
	scanf_s("%lld", &Obj[amount].sum);
}
void showData(const kvit* Obj, const int amount)
{
	system("cls");
	printf("№\t  Название\t Дата\t Состояние\t\n");
	printf("========================================\n");
	for (int i = 0; i < amount; i++)
	{
		printf("%d", i + 1);
		printf("\t");
		printf("%s", Obj[i].surname.c_str());
		printf("\t");
		printf("%s", Obj[i].name.c_str());
		printf("\t");
		printf("%lld", Obj[i].sum);
		printf("\n");
	}
}