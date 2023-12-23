using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Frolenko_Lab4
{
	public class ArtItem
	{
		public string Name { get; set; }
		public int YearCreated { get; set; }
		public bool IsOriginal { get; set; }

		public ArtItem(string name, int yearCreated, bool isOriginal)
		{
			Name = name;
			YearCreated = yearCreated;
			IsOriginal = isOriginal;
		}
	}
}