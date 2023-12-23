using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Frolenko_Lab6
{
	public interface IFileService<T> where T : class
	{
		IEnumerable<T> ReadFile(string fileName);
		void SaveData(IEnumerable<T> data, string fileName);
	}
}
