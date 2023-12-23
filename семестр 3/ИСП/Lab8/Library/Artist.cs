using Newtonsoft.Json;

namespace Library
{
	public class Artwork
	{
		public int Id { get; set; }
		public string Title { get; set; }
		public static int ArtistArtworkCount { get; set; }
		public Artwork()
		{

		}
		public Artwork(int id, string title)
		{
			Id = id;
			Title = title;
			ArtistArtworkCount = 2;
		}
	}
}