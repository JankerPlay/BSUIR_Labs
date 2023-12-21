using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2.Services
{
	internal class equation
	{
		public double value;
		public double x;
		public double z;
		public void vvod()
		{
			Console.WriteLine("Введите x ");
			while (!double.TryParse(Console.ReadLine(), out x))
			{
				Console.WriteLine("Ошибка ввода! Введите число");
			}
			Console.WriteLine("Введите z ");
			while (!double.TryParse(Console.ReadLine(), out z))
			{
				Console.WriteLine("Ошибка ввода! Введите число");
			}
		}
		public void result()
		{
			if (z >= 0)
			{
				x = 2 * z + 1;
			}
			else if (z < 0)
			{
				x = Math.Log(z * z - z);
			}
			value = Math.Pow(Math.Sin(x), 2) + Math.Pow(Math.Cos(Math.Pow(x, 3)), 5) + Math.Log(Math.Pow(x, 2 / 5));
		}
		public void print()
		{
			Console.WriteLine("Метод нахождения x: ");
			if (z >= 0)
				Console.WriteLine("x=2z+1");
			else
				Console.WriteLine("x=ln(z^2-z)");
			Console.WriteLine($"Итог: {value}");
		}
	}
}
