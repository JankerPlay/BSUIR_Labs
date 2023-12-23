using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Generic;
using _253504_Frolenko_Lab2.Contracts;
using _253504_Frolenko_Lab2.Interfaces;
using _253504_Frolenko_Lab2.Collections;
using Generic.Math;

namespace _253504_Frolenko_Lab2.Entities
{
	public class Room
	{
		public int Number { get; set; }
		public decimal Price { get; set; }
		public Room(int number, decimal price)
		{
			Number = number;
			Price = price;
		}
	}
	public class Client
	{
		public string Name { get; set; }
		public MyCustomCollection<int> BookedRooms { get; set; }
		public Client(string name)
		{
			Name = name;
			BookedRooms = new MyCustomCollection<int>();
		}
	}
	public class HotelSystem : IHotelSystem
	{
		public event Action RoomListChanged;
		public event Action ClientListChanged;
		public event Action<string, int> RoomBooked;
		private MyCustomCollection<Room> rooms;
		private MyCustomCollection<Client> clients;
		public HotelSystem()
		{
			rooms = new MyCustomCollection<Room>();
			clients = new MyCustomCollection<Client>();
		}
		public void GetRoomInformation()
		{
			Console.WriteLine("Rooms Information:");
			foreach (var room in rooms)
			{
				Console.WriteLine($"Room Number: {room.Number}, Price: {room.Price}");
			}
		}
		public void RegisterClient(string clientName)
		{
			if (clients.Any(c => c.Name == clientName))
			{
				Console.WriteLine($"Client {clientName} is already registered.");
			}
			else
			{
				var client = new Client(clientName);
				clients.Add(client);
				Console.WriteLine($"Client {clientName} has been registered.");
				ClientListChanged?.Invoke();
			}
		}
		public void BookRoom(string clientName, int roomNumber)
		{
			var client = clients.FirstOrDefault(c => c.Name == clientName);
			if (client == null)
			{
				Console.WriteLine($"Client {clientName} is not registered.");
				return;
			}
			var room = rooms.FirstOrDefault(r => r.Number == roomNumber);
			if (room == null)
			{
				Console.WriteLine($"Room {roomNumber} does not exist.");
				return;
			}

			if (client.BookedRooms.Contains(roomNumber))
			{
				Console.WriteLine($"Room {roomNumber} is already booked by client {clientName}.");
			}
			else
			{
				client.BookedRooms.Add(roomNumber);
				RoomBooked?.Invoke(clientName, roomNumber);
			}
		}
		public void GetAvailableRooms()
		{
			var bookedRooms = clients.SelectMany(c => c.BookedRooms).Distinct();
			var availableRooms = rooms.Where(r => !bookedRooms.Contains(r.Number)).ToList();

			if (availableRooms.Count > 0)
			{
				Console.WriteLine("Available Rooms:");
				foreach (var room in availableRooms)
				{
					Console.WriteLine($"Room Number: {room.Number}, Price: {room.Price}");
				}
			}
			else
			{
				Console.WriteLine("No available rooms at the moment.");
			}
		}
		public decimal CalculateStayCost(string clientName)
		{
			var client = clients.FirstOrDefault(c => c.Name == clientName);
			if (client == null)
			{
				Console.WriteLine($"Client {clientName} is not registered.");
				return 0;
			}

			decimal totalCost = GenericMath.Add(0, 0);
			foreach (var roomNumber in client.BookedRooms)
			{
				var room = rooms.FirstOrDefault(r => r.Number == roomNumber);
				if (room != null)
				{
					totalCost = GenericMath.Add(totalCost, room.Price);
				}
			}

			Console.WriteLine($"Total stay cost for client {clientName}: {totalCost}");
			return totalCost;
		}

		public void AddRoom(int number, decimal price)
		{
			var room = new Room(number, price);
			rooms.Add(room);
			Console.WriteLine($"Room {number} with price {price} has been added.");
			RoomListChanged?.Invoke();
		}

		public int GetMostPopularRoom()
		{
			var roomCounts = clients
				.SelectMany(c => c.BookedRooms)
				.GroupBy(r => r)
				.OrderByDescending(g => g.Count())
				.ToList();

			if (roomCounts.Count > 0)
			{
				var mostPopularRoom = roomCounts.First().Key;
				Console.WriteLine($"The most popular room: {mostPopularRoom}");
				return mostPopularRoom;
			}
			else
			{
				Console.WriteLine("No rooms have been booked yet.");
				return 0;
			}
		}
	}
}
