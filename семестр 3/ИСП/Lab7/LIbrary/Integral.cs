using System;
using System.Diagnostics;

namespace Library
{
	public class IntegralCalculator
	{
		private static SemaphoreSlim semaphore;
		private static int numThreads;

		public event EventHandler<double> CalculationCompleted;
		public event EventHandler<int> CalculationProgressChanged;

		public double ElapsedTime { get; private set; }
		static int threadCounter = 0;
		static readonly object counterLock = new object();
		public IntegralCalculator(int maxThreads)
		{
			semaphore = new SemaphoreSlim(maxThreads);
			numThreads = maxThreads;
		}

		public void CalculateIntegral()
		{
			int threadId;

			lock (counterLock)
			{
				threadId = threadCounter++;
			}

			string formattedThreadId = threadId.ToString("D4");
			semaphore.Wait();

			Stopwatch stopwatch = Stopwatch.StartNew();

			double a = 0;
			double b = 1;
			double step = 0.00000001;
			double sum = 0;
			int totalSteps = (int)((b - a) / step);

			int progressUpdateInterval = totalSteps / 100;
			if (progressUpdateInterval == 0)
				progressUpdateInterval = 1;

			int currentStep = 0;

			for (int i = 0; i < totalSteps; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					int result = j * j;
				}

				double x = a + i * step;
				double y = Math.Sin(x);
				sum += y * step;

				currentStep++;

				if (currentStep % progressUpdateInterval == 0 || currentStep == totalSteps)
				{
					int progress = (int)Math.Round((double)currentStep * 100 / totalSteps);
					OnCalculationProgressChanged(progress);
				}
			}

			stopwatch.Stop();

			ElapsedTime = stopwatch.Elapsed.TotalMilliseconds;
			OnCalculationCompleted(ElapsedTime, sum);

			semaphore.Release();
		}

		protected virtual void OnCalculationCompleted(double elapsedTime, double result)
		{
			CalculationCompleted?.Invoke(this, result);
		}

		protected virtual void OnCalculationProgressChanged(int progress)
		{
			CalculationProgressChanged?.Invoke(this, progress);
		}
	}
}