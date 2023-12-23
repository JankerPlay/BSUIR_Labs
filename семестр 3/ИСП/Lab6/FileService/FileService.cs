using System.Collections.Generic;
using System.IO;
using _253504_Frolenko_Lab6;
using Newtonsoft.Json;

namespace FileService
{
	public class FileService<T> : IFileService<T> where T : class
	{
		public IEnumerable<T> ReadFile(string fileName)
		{
			string json = File.ReadAllText(fileName);
			IEnumerable<T> data = JsonConvert.DeserializeObject<IEnumerable<T>>(json);
			return data;
		}
		public void SaveData(IEnumerable<T> data, string fileName)
		{
			string json = JsonConvert.SerializeObject(data);
			File.WriteAllText(fileName, json);
		}
	}
}