using _253504_Frolenko_Lab1.Collections;
using _253504_Frolenko_Lab1.Entities;
using System;

namespace YourNamespace
{
	class Program
	{
		static void Main(string[] args)
		{
			HotelSystem hotelSystem = new HotelSystem();
			hotelSystem.RegisterClient("John");
			hotelSystem.RegisterClient("Alice");
			hotelSystem.RegisterClient("Alex");
			hotelSystem.AddRoom(324, 10530);
			hotelSystem.AddRoom(435, 15450);
			hotelSystem.AddRoom(234, 20310);
			hotelSystem.AddRoom(123, 43523);
			hotelSystem.BookRoom("John", 324);
			hotelSystem.BookRoom("Alice", 4435);
			hotelSystem.BookRoom("Alex", 324);
			hotelSystem.BookRoom("John", 234);
			hotelSystem.GetAvailableRooms();
			decimal johnCost = hotelSystem.CalculateStayCost("John");
			decimal aliceCost = hotelSystem.CalculateStayCost("Alice");
			decimal alexCost = hotelSystem.CalculateStayCost("Alex");
			int mostPopularRoom = hotelSystem.GetMostPopularRoom();
			hotelSystem.GetRoomInformation();
		}
	}
}