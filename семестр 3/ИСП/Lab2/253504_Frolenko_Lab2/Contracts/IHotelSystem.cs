using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Frolenko_Lab2.Contracts
{
	public interface IHotelSystem
	{
		void GetRoomInformation();
		void RegisterClient(string clientname);
		public void BookRoom(string clientname, int roomnumber);
		void GetAvailableRooms();
		decimal CalculateStayCost(string clientname);
		int GetMostPopularRoom();
	}
}