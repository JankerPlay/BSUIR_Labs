int number=1;
while (number != 0)
{
	Console.WriteLine("Введите номер задния(1 или 2) или введите 0 чтобы завершить программу");
	number = Convert.ToInt32(Console.ReadLine());
	Console.Clear();
	switch (number)
	{
		case 0:
			break;
		case 1:
			int a, b, c;
			Console.WriteLine("Введите a");
			a = Convert.ToInt32(Console.ReadLine());
			Console.WriteLine("Введите b");
			b = Convert.ToInt32(Console.ReadLine());
			Console.WriteLine("Введите c");
			c = Convert.ToInt32(Console.ReadLine());
			if (a > b + c || b > a + c || c > b + c)
			{
				Console.WriteLine("Такого треугольника не существует");
			}
			else
			{
				Console.WriteLine("Данный треугольник существует");
			}
			break;
		case 2:
			int x, y, xc = 10, yc = 5;
			Console.WriteLine("Введите x");
			x = Convert.ToInt32(Console.ReadLine());
			Console.WriteLine("Введите y");
			y = Convert.ToInt32(Console.ReadLine());
			if (x > 0 && y > 0 && x < 10 && y < 5)
				Console.WriteLine("Да");
			else if ((y==0 || y==5) && x>=0 && x <=xc 
				  || (x==10 || x==0) && y>=0 && y <=5)
				Console.WriteLine("На границе");
			else
				Console.WriteLine("Нет");
			break;
	}
}