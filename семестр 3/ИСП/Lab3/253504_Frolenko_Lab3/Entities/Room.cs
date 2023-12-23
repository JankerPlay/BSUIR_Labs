using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Generic;
using _253504_Frolenko_Lab3.Contracts;
using Generic.Math;

namespace _253504_Frolenko_Lab3.Entities
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
		public List<int> BookedRooms { get; set; }
		public Client(string name)
		{
			Name = name;
			BookedRooms = new List<int>();
		}
	}

	public class HotelSystem : IHotelSystem
	{
		public event Action RoomListChanged;
		public event Action ClientListChanged;
		public event Action<string, int> RoomBooked;
		private Dictionary<int, Room> rooms;
		private List<Client> clients;

		public HotelSystem()
		{
			rooms = new Dictionary<int, Room>();
			clients = new List<Client>();
		}

		public void GetRoomInformation()
		{
			Console.WriteLine("Rooms Information:");
			foreach (var room in rooms.Values)
			{
				Console.WriteLine($"Room Number: {room.Number}, Price: {room.Price}");
			}
		}

		public void RegisterClient(string clientName)
		{
			if (clients.Any(client => client.Name == clientName))
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
			var client = clients.FirstOrDefault(client => client.Name == clientName);
			if (client == null)
			{
				Console.WriteLine($"Client {clientName} is not registered.");
				return;
			}

			var room = rooms.GetValueOrDefault(roomNumber);
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
			var bookedRooms = clients.SelectMany(client => client.BookedRooms).Distinct();
			var availableRooms = rooms.Values.Where(room => !bookedRooms.Contains(room.Number)).ToList();

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
			var client = clients.FirstOrDefault(client => client.Name == clientName);
			if (client == null)
			{
				Console.WriteLine($"Client {clientName} is not registered.");
				return 0;
			}

			decimal totalCost = 0;
			foreach (var roomNumber in client.BookedRooms)
			{
				if (rooms.TryGetValue(roomNumber, out var room))
				{
					totalCost = GenericMath.Add(totalCost, room.Price);
				}
			}

			Console.WriteLine($"Total stay cost for client {clientName}: {totalCost}");
			return totalCost;
		}

		public void AddRoom(int number, decimal price)
		{
			if (rooms.ContainsKey(number))
			{
				Console.WriteLine($"Room {number} already exists.");
				return;
			}

			var room = new Room(number, price);
			rooms.Add(number, room);
			Console.WriteLine($"Room {number} with price {price} has been added.");
			RoomListChanged?.Invoke();
		}
		public List<int> GetRoomsSortedByPrice()
		{
			var sortedRooms = rooms.Values.OrderBy(room => room.Price).Select(room => room.Number).ToList();
			return sortedRooms;
		}
		public decimal GetTotalStayCost()
		{
			decimal totalCost = clients.SelectMany(client => client.BookedRooms)
									   .Sum(roomNumber => rooms.GetValueOrDefault(roomNumber)?.Price ?? 0);
			return totalCost;
		}
		public string GetClientWithMaxPayment()
		{
			var clientWithMaxPayment = clients.OrderByDescending(client => client.BookedRooms.Sum(roomNumber => rooms.GetValueOrDefault(roomNumber)?.Price ?? 0))
											 .FirstOrDefault();

			return clientWithMaxPayment?.Name;
		}
		public int GetNumberOfClientsWithPaymentGreaterThan(decimal amount)
		{
			int count = clients.Aggregate(0, (total, client) =>
										total + (client.BookedRooms.Sum(roomNumber => rooms.GetValueOrDefault(roomNumber)?.Price ?? 0) > amount ? 1 : 0));
			return count;
		}
		public Dictionary<decimal, int> GetRoomCountByPriceCategory()
		{
			var roomCountByPriceCategory = rooms.Values.GroupBy(room => room.Price)
													   .ToDictionary(group => group.Key, group => group.Count());
			return roomCountByPriceCategory;
		}
		public int GetMostPopularRoom()
		{
			var roomCounts = clients
			   .SelectMany(client => client.BookedRooms)
			   .GroupBy(roomNumber => roomNumber)
			   .OrderByDescending(group => group.Count())
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