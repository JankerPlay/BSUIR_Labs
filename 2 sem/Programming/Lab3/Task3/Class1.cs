using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;

namespace Task3
{
	internal class DateServise
	{
		public string asd;
		public DayOfWeek GetDay(string date)
		{
			int day = (date[0] - 48) * 10 + date[1] - 48;
			int month = (date[3] - 48) * 10 + date[4] - 48;
			int year = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10 + date[9] - 48;
			DateTime qdate = new DateTime(year, month, day);
			return qdate.DayOfWeek;
		}
		public double GetDaysSpan(int day, int month, int year)
		{
			DateTime now = new DateTime();
			now = DateTime.Now;
			DateTime qdate = new DateTime(year, month, day);
			TimeSpan ts = now.Subtract(qdate);
			int diff = (int)ts.TotalDays;
			return diff;
		}
	}
}
