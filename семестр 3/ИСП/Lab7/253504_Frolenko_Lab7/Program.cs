using Library;
using System;
using System.Threading;
using System.Threading.Tasks;
public class Program
{
	static void Main(string[] args)
	{
		int numThreads = 5;
		int maxThreads = 2;
		IntegralCalculator calculator = new IntegralCalculator(maxThreads);
		calculator.CalculationCompleted += CalculationCompletedHandler;
		calculator.CalculationProgressChanged += CalculationProgressChangedHandler;

		Thread[] threads = new Thread[numThreads];

		for (int i = 0; i < numThreads; i++)
		{
			threads[i] = new Thread(calculator.CalculateIntegral);
			threads[i].Start();
		}

		for (int i = 0; i < numThreads; i++)
		{
			threads[i].Join();
		}

		Console.ReadLine();
	}

	static void CalculationCompletedHandler(object sender, double result)
	{
		double elapsedTime = ((IntegralCalculator)sender).ElapsedTime;
		int threadId = Thread.CurrentThread.ManagedThreadId;
		string formattedThreadId = threadId.ToString("D4");
		  
		Console.WriteLine($"Поток {formattedThreadId}: Завершен с результатом: {result}");
		Console.WriteLine($"Время выполнения: {elapsedTime} мс");
	}

	static void CalculationProgressChangedHandler(object sender, int progress)
	{
		int threadId = Thread.CurrentThread.ManagedThreadId;
		string progressBar = GenerateProgressBar(progress);
		string formattedThreadId = threadId.ToString("D4");

		Console.WriteLine($"Поток {formattedThreadId}: {progressBar} {progress}%");
	}

	static string GenerateProgressBar(int progress)
	{
		const int totalLength = 20;
		int completedLength = (int)Math.Round((double)progress / 100 * totalLength);
		int remainingLength = totalLength - completedLength;

		string progressBar = "[" + new string('=', completedLength) + ">" + new string(' ', remainingLength) + "]";
		return progressBar;
	}
}