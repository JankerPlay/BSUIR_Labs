using _253504_Frolenko_Lab3.Entities;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;

namespace YourNamespace
{
	class Program
	{
		static void Main(string[] args)
		{
			HotelSystem hotelSystem = new HotelSystem();
			Journal journal = new Journal(hotelSystem);
			hotelSystem.RegisterClient("John");
			hotelSystem.RegisterClient("Alice");
			hotelSystem.RegisterClient("Alex");
			hotelSystem.AddRoom(324, 10530);
			hotelSystem.AddRoom(435, 15450);
			hotelSystem.AddRoom(234, 20000);
			hotelSystem.AddRoom(235, 20000);
			hotelSystem.AddRoom(123, 43523);
			hotelSystem.RoomBooked += (clientName, roomNumber) =>
			{
				Console.WriteLine($"Room {roomNumber} has been booked by client {clientName}.");
			};
			hotelSystem.BookRoom("John", 324);
			hotelSystem.BookRoom("Alice", 435);
			hotelSystem.BookRoom("Alex", 324);
			hotelSystem.BookRoom("John", 234);
			hotelSystem.GetAvailableRooms();
			decimal johnCost = hotelSystem.CalculateStayCost("John");
			decimal aliceCost = hotelSystem.CalculateStayCost("Alice");
			decimal alexCost = hotelSystem.CalculateStayCost("Alex");
			int mostPopularRoom = hotelSystem.GetMostPopularRoom();
			hotelSystem.GetRoomInformation();
			journal.PrintEvents();
			List<int> sortedRooms = hotelSystem.GetRoomsSortedByPrice();
			Console.WriteLine("Sorted Rooms:");
			foreach (int roomNumber in sortedRooms)
			{
				Console.WriteLine($"Room Number: {roomNumber}");
			}
			decimal totalStayCost = hotelSystem.GetTotalStayCost();
			Console.WriteLine($"Total stay cost for all clients: {totalStayCost}");
			string clientWithMaxPayment = hotelSystem.GetClientWithMaxPayment();
			Console.WriteLine($"Client with the maximum payment: {clientWithMaxPayment}");
			decimal amount = 20000;
			int numberOfClientsWithPaymentGreaterThanAmount = hotelSystem.GetNumberOfClientsWithPaymentGreaterThan(amount);
			Console.WriteLine($"Number of clients with payment greater than {amount}: {numberOfClientsWithPaymentGreaterThanAmount}");
			Dictionary<decimal, int> roomCountByPriceCategory = hotelSystem.GetRoomCountByPriceCategory();
			Console.WriteLine("Room count by price category:");
			foreach (var kvp in roomCountByPriceCategory)
			{
				Console.WriteLine($"Price: {kvp.Key}, Room Count: {kvp.Value}");
			}
		}
	}
}