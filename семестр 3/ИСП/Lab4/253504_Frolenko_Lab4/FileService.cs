using System;
using System.Collections.Generic;
using System.IO;

namespace _253504_Frolenko_Lab4
{
	public class FileService<T> : IFileService<T>
	{
		public IEnumerable<T> ReadFile(string fileName)
		{
			using (BinaryReader reader = new BinaryReader(File.OpenRead(fileName)))
			{
				while (reader.BaseStream.Position < reader.BaseStream.Length)
				{
					yield return ReadObject(reader);
				}
			}
		}

		public void SaveData(IEnumerable<T> data, string fileName)
		{
			if (File.Exists(fileName))
			{
				File.Delete(fileName);
			}

			using (BinaryWriter writer = new BinaryWriter(File.OpenWrite(fileName)))
			{
				foreach (T item in data)
				{
					WriteObject(writer, item);
				}
			}
		}

		private T ReadObject(BinaryReader reader)
		{
			try
			{
				string name = reader.ReadString();
				int yearCreated = reader.ReadInt32();
				bool isOriginal = reader.ReadBoolean();

				return (T)(object)new ArtItem(name, yearCreated, isOriginal);
			}
			catch (Exception ex)
			{
				Console.WriteLine("Ошибка при чтении данных: " + ex.Message);
				return default(T);
			}
		}

		private void WriteObject(BinaryWriter writer, T item)
		{
			try
			{
				writer.Write(((ArtItem)(object)item).Name);
				writer.Write(((ArtItem)(object)item).YearCreated);
				writer.Write(((ArtItem)(object)item).IsOriginal);
			}
			catch (Exception ex)
			{
				Console.WriteLine("Ошибка при записи данных: " + ex.Message);
			}
		}
	}
}