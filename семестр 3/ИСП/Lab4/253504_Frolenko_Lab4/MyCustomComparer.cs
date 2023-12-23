using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Frolenko_Lab4
{
	public class MyCustomComparer<T> : IComparer<T>
	{
		public int Compare(T x, T y)
		{
			string nameX = GetName(x);
			string nameY = GetName(y);

			return string.Compare(nameX, nameY, StringComparison.OrdinalIgnoreCase);
		}

		private string GetName(T item)
		{
			Type type = typeof(T);
			var nameProperty = type.GetProperty("Name");
			if (nameProperty != null && nameProperty.PropertyType == typeof(string))
			{
				string name = (string)nameProperty.GetValue(item);
				return name;
			}

			throw new InvalidOperationException($"Тип {type.FullName} не содержит свойства Name или свойство Name не является строковым.");
		}
	}
}
