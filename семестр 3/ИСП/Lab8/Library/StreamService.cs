using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Library;
using Newtonsoft.Json;
public class StreamService<T> where T : Artwork
{
	private SemaphoreSlim writeSemaphore = new SemaphoreSlim(1);
	//private SemaphoreSlim copySemaphore = new SemaphoreSlim(0);
	public event Action<int, string> StreamOperationEvent;
	private ManualResetEvent writeCompletedEvent = new ManualResetEvent(false);

	private void OnStreamOperation(int threadId, string message)
	{
		StreamOperationEvent?.Invoke(threadId, message);
	}

	public async Task WriteToStream(Stream stream, IEnumerable<T> data, IProgress<string> progress)
	{
		int totalCount = data.Count();
		int currentCount = 0;
		int delayPerItem = (int)Math.Max(3000 / totalCount, 5);
		int newProgressPercentage = -1;

		foreach (var item in data)
		{
			Thread.Sleep(delayPerItem);
			currentCount++;

			int progressPercentage = currentCount * 100 / totalCount;
			if (progressPercentage > newProgressPercentage)
			{
				newProgressPercentage = progressPercentage;
				progress?.Report($"Прогресс: {progressPercentage}% Поток: {Thread.CurrentThread.ManagedThreadId}");
			}
			string itemString = $"{item.Id},{item.Title},";
			int threadId = Thread.CurrentThread.ManagedThreadId;
			OnStreamOperation(threadId, "Выполняется запись в поток");
			byte[] itemBytes = Encoding.UTF8.GetBytes(itemString);

			writeSemaphore.Wait();
			try
			{
				stream.Write(itemBytes, 0, itemBytes.Length);
			}
			finally
			{
				writeSemaphore.Release();
			}

			OnStreamOperation(threadId, "Запись в поток завершена");

			if (currentCount == totalCount)
			{
				writeCompletedEvent.Set();
			}
		}
	}

	public async Task CopyFromStream(Stream stream, string filename, IProgress<string> progress)
	{
		int threadId = Thread.CurrentThread.ManagedThreadId;
		OnStreamOperation(threadId, "Выполняется копирование из потока");

		writeCompletedEvent.WaitOne();

		using (FileStream fileStream = new FileStream(filename, FileMode.Create))
		{
			Thread.Sleep(10);
			int bufferSize = 4096;
			byte[] buffer = new byte[bufferSize];
			int bytesRead;
			long totalBytesRead = 0;
			long totalBytes = stream.Length;

			while ((bytesRead = stream.Read(buffer, 0, bufferSize)) > 0)
			{
				fileStream.Write(buffer, 0, bytesRead);
				totalBytesRead += bytesRead;

				int progressPercentage = (int)(totalBytesRead * 100 / totalBytes);
				Thread.Sleep(10);
				progress?.Report($"Прогресс: {progressPercentage}% Поток: {Thread.CurrentThread.ManagedThreadId}");
			}
		}
		OnStreamOperation(threadId, "Копирование из потока завершено");
	}

	public async Task<int> GetStatisticsAsync(string fileName, Func<T, bool> filter)
	{
		int count = 0;

		using (StreamReader reader = new StreamReader(fileName))
		{
			string line;
			while ((line = await reader.ReadLineAsync()) != null)
			{
				string[] values = line.Split(',');

				for (int i = 0; i < values.Length - 1; i += 2)
				{
					T item = Activator.CreateInstance<T>();
					int id;
					if (int.TryParse(values[i].Trim(), out id))
					{
						item.Id = id;
						item.Title = values[i + 1].Trim();

						if (filter(item))
						{
							count++;
						}
					}
				}
			}
		}

		return count;
	}
}