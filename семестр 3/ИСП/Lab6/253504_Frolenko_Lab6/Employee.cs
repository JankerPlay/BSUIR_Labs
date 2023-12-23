using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace _253504_Frolenko_Lab6
{
	public class Employee
	{
		public int EmployeeID { get; set; }
		public bool IsActive { get; set; }
		public string Name { get; set; }
		public Employee(int employeeID, bool isActive, string name)
		{
			EmployeeID = employeeID;
			IsActive = isActive;
			Name = name;
		}
		public void DisplayInfo()
		{
			Console.WriteLine("Employee ID: " + EmployeeID);
			Console.WriteLine("Name: " + Name);
			Console.WriteLine("Active: " + IsActive);
		}
	}
}