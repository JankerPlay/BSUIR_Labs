using _253504_Frolenko_Lab3.Entities;

public class Journal
{
	private List<string> roomChanges;
	private List<string> clientChanges;

	public Journal(HotelSystem hotelSystem)
	{
		roomChanges = new List<string>();
		clientChanges = new List<string>();

		hotelSystem.RoomListChanged += HandleRoomListChanged;
		hotelSystem.ClientListChanged += HandleClientListChanged;
		hotelSystem.RoomBooked += HandleRoomBooked;
	}

	public void PrintEvents()
	{
		Console.WriteLine("List of Registered Events:");

		Console.WriteLine("Room Changes:");
		foreach (var change in roomChanges)
		{
			Console.WriteLine(change);
		}

		Console.WriteLine("Client Changes:");
		foreach (var change in clientChanges)
		{
			Console.WriteLine(change);
		}

		Console.WriteLine();
	}

	private void HandleRoomListChanged()
	{
		roomChanges.Add("Room list changed.");
	}

	private void HandleClientListChanged()
	{
		clientChanges.Add("Client list changed.");
	}

	private void HandleRoomBooked(string clientName, int roomNumber)
	{
		roomChanges.Add("Room booked.");
	}
}