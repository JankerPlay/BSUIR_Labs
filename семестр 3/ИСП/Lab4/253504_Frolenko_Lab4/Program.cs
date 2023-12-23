using _253504_Frolenko_Lab4;
using System;
using System.IO;

public class Program
{
	public static void Main(string[] args)
	{
		string foldername = "Frolenko_Lab4";
		if (Directory.Exists(foldername))
		{
			Directory.Delete(foldername, true);
		}

		Directory.CreateDirectory(foldername);

		Random random = new Random();
		string[] extensions = { ".txt", ".rtf", ".dat", ".inf" };

		int filesToCreate = 10;

		for (int i = 0; i < filesToCreate; i++)
		{
			string path = Path.Combine(foldername, Path.GetRandomFileName());
			string extension = extensions[random.Next(extensions.Length)];
			path += extension;

			File.WriteAllText(path, string.Empty);
		}

		string[] files = Directory.GetFiles(foldername);

		foreach (string filePath in files)
		{
			string path = Path.GetFileName(filePath);
			string extension = Path.GetExtension(path);

			Console.WriteLine($"Файл: {path} имеет расширение {extension}");
		}
		List<ArtItem> artItems = new List<ArtItem>();
		artItems.Add(new ArtItem("Мона Лиза", 1503, true));
		artItems.Add(new ArtItem("Звездная ночь", 1889, true));
		artItems.Add(new ArtItem("Тайная вечеря", 1495, false));
		artItems.Add(new ArtItem("Гильотина", 1937, true));
		artItems.Add(new ArtItem("Сотворение Адама", 1511, false));
		artItems.Add(new ArtItem("Девятый вал", 1850, true));
		FileService<ArtItem> fileService = new FileService<ArtItem>();
		string fileName = Path.Combine(foldername, "artItems.bin");
		fileService.SaveData(artItems, fileName);
		string newFileName = Path.Combine(foldername, "renamedArtItems.bin");
		File.Move(fileName, newFileName);
		IEnumerable<ArtItem> readArtItems = fileService.ReadFile(newFileName);
		Console.WriteLine();
		foreach (ArtItem artItem in readArtItems)
		{
			Console.WriteLine($"Название: {artItem.Name}, Год создания: {artItem.YearCreated}, Оригинал: {artItem.IsOriginal}");
		}
		List<ArtItem> arrItems = new List<ArtItem>();
		FileService<ArtItem> fileservice = new FileService<ArtItem>();
		string filename2 = Path.Combine(foldername, "renamedArtItems.bin");
		IEnumerable<ArtItem> readItems = fileservice.ReadFile(filename2);
		arrItems.AddRange(readItems);
		MyCustomComparer<ArtItem> comparer = new MyCustomComparer<ArtItem>();
		IEnumerable<ArtItem> sortedArr = arrItems.OrderBy(item => item.Name);
		Console.WriteLine();
		Console.WriteLine("Чтение из второй коллекции отсортированной по имени:");
		foreach (ArtItem artItem in sortedArr)
		{
			Console.WriteLine($"Название: {artItem.Name}, Год создания: {artItem.YearCreated}, Оригинал: {artItem.IsOriginal}");
		}
		IEnumerable<ArtItem> sortedArr2 = arrItems.OrderBy(item => item.YearCreated);
		Console.WriteLine();
		Console.WriteLine("Чтение из второй коллекции отсортированной по году:");
		foreach (ArtItem artItem in sortedArr2)
		{
			Console.WriteLine($"Название: {artItem.Name}, Год создания: {artItem.YearCreated}, Оригинал: {artItem.IsOriginal}");
		}


	}
}