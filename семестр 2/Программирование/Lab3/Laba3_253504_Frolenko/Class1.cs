using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3_253504_Frolenko
{
	internal class number
	{
		public int value;
		public void vvod()
		{
			while (!int.TryParse(Console.ReadLine(), out value) || value < 100 || value > 999) 
			{
				Console.WriteLine("Ошибка ввода! Введите трехзначное число");
			}
		}
		public void change()
		{
			int a = value / 100, b = (value % 100 / 10), c = value % 10;
			value = c * 100 + b * 10 + a;
		}
		public void print()
		{
			Console.WriteLine($"Перевернутое число {value}");
		}
	}
}
