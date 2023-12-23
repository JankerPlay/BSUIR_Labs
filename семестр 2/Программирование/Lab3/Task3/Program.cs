using Microsoft.VisualBasic;
using Task3;

Console.WriteLine("1. Определить день недели по дате ");
Console.WriteLine("2. Определить разницу между датами ");
int a;
while (!int.TryParse(Console.ReadLine(), out a) || a < 1 || a > 2)
{
	Console.WriteLine("Ошибка ввода! Введите 1 или 2");
}
DateServise date = new DateServise();
switch (a)
{
	case 1:
		DateTime dte;
		string str = "30.02.2023";
		Console.WriteLine("Введите дату в формате (dd.mm.yyyy)");
		while (!DateTime.TryParse(str, out dte))
		{
			str = Console.ReadLine();
			if (!DateTime.TryParse(str, out dte))
			{
				Console.WriteLine("Ошибка ввода! Некорректная дата");
			}
		}
		Console.WriteLine(date.GetDay(str));
		break;
	case 2:
		int day = 0, month = 0, year = 0;
		DateTime dt;
		string s = "30.02.2023";
		while (!DateTime.TryParse(s, out dt))
		{
			Console.WriteLine("Введите день");
		while (!int.TryParse(Console.ReadLine(), out day) || day < 1 || day > 31)
		{
			Console.WriteLine("Ошибка ввода! Введите корректный день");
		}
		Console.WriteLine("Введите месяц");
		while (!int.TryParse(Console.ReadLine(), out month) || month < 1 || month > 12)
		{
			Console.WriteLine("Ошибка ввода! Введите корректный месяц");
		}
		Console.WriteLine("Введите год");
		while (!int.TryParse(Console.ReadLine(), out year) || year < 1 || year > 9999)
		{
			Console.WriteLine("Ошибка ввода! Введите корректный год");
		}
			s = day + "." + month + "." + year;
			if (!DateTime.TryParse(s, out dt))
			{
				Console.WriteLine("Ошибка ввода! Некорректная дата");
			}
		}
		Console.WriteLine("Количество дней: ");
		Console.Write(date.GetDaysSpan(day, month, year));
		break;
}
