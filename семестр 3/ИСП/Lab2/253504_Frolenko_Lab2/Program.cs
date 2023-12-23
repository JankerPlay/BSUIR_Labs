using _253504_Frolenko_Lab2.Collections;
using _253504_Frolenko_Lab2.Entities;
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
			hotelSystem.AddRoom(234, 20310);
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
			try
			{
				MyCustomCollection<int> collection = new MyCustomCollection<int>();
				collection.Add(10);
				collection.Add(20);
				collection.Add(30);
				int invalidIndex = 10;
				int value = collection[invalidIndex];
			}
			catch (IndexOutOfRangeException ex)
			{
				Console.WriteLine("IndexOutOfRangeException caught: " + ex.Message);
			}
			catch (ItemNotFoundException ex)
			{
				Console.WriteLine("ItemNotFoundException caught: " + ex.Message);
			}
			catch (Exception ex)
			{
				Console.WriteLine("Exception caught: " + ex.Message);
			}
		}
	}
}