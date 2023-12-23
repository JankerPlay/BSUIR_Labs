	using System;
	using System.Collections.Generic;
	using System.IO;
	using System.Reflection;

namespace _253504_Frolenko_Lab6
{
	public class Program
	{
		public static void Main(string[] args)
		{
			List<Employee> employees = new List<Employee>();
			employees.Add(new Employee(1, true, "John Doe"));
			employees.Add(new Employee(2, true, "Jane Smith"));
			employees.Add(new Employee(3, false, "Mark Johnson"));
			employees.Add(new Employee(4, true, "Emily Davis"));
			employees.Add(new Employee(5, false, "Michael Wilson"));
			employees.Add(new Employee(6, true, "Sarah Brown"));

			foreach (var employee in employees)
			{
				employee.DisplayInfo();
				Console.WriteLine();
			}
			string dllPath = @"C:\Users\kira1\OneDrive\Рабочий стол\C#\253504_Frolenko_Lab6\FileService\obj\Debug\net6.0\FileService.dll";
			var assembly = Assembly.LoadFrom(dllPath);
			Type fileServiceType2 = assembly.GetType("FileService.FileService`1");
			Type fileServiceGenericType2 = fileServiceType2.MakeGenericType(typeof(Employee));
			object fileServiceInstance2 = Activator.CreateInstance(fileServiceGenericType2);
			MethodInfo saveDataMethod = fileServiceGenericType2.GetMethod("SaveData");
			saveDataMethod.Invoke(fileServiceInstance2, new object[] { employees, "employees.json" });
			Type fileServiceType = assembly.GetType("FileService.FileService`1");
			Type fileServiceGenericType = fileServiceType.MakeGenericType(typeof(Employee));
			object fileServiceInstance = Activator.CreateInstance(fileServiceGenericType);
			MethodInfo loadDataMethod = fileServiceGenericType.GetMethod("ReadFile");
			string filePath = @"C:\Users\kira1\OneDrive\Рабочий стол\C#\253504_Frolenko_Lab6\253504_Frolenko_Lab6\bin\Debug\net6.0\employees.json";
			object loadedData = loadDataMethod.Invoke(fileServiceInstance, new object[] { filePath });
			Console.WriteLine();
			Console.WriteLine("Информация из файла: ");
			if (loadedData is IEnumerable<Employee> loadedEmployees)
			{
				foreach (var employee in loadedEmployees)
				{
					employee.DisplayInfo();
					Console.WriteLine();
				}
			}
			else
			{
				Console.WriteLine("Ошибка при загрузке данных из файла.");
			}
		}
	}
}