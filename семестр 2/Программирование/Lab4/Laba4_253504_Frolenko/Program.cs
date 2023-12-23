public class TVShop                 // класс-контейнер
{
	private static TVShop instance;
	private string shopName;
	private float tvPrice;
	private int totalSales;
	private TVShop()
	{
		shopName = "NAME";
		tvPrice = 10;
		totalSales = 1;
	}
	public static TVShop Instance
	{
		get
		{
			if (instance == null)
				instance = new TVShop();
			return instance;
		}
	}
	public string ShopName
	{
		get 
		{
			return shopName; 
		}
		set 
		{
			shopName = value; 
		}
	}
	public float TVPrice
	{
		get
		{
			return tvPrice;
		}
		set
		{
			tvPrice = value; 
		}
	}
	public int TotalSales
	{
		get
		{
			return totalSales;
		}
		set
		{
			totalSales = value; 
		}
	}
	public void AddSale(int price)
	{
		totalSales += price;
	}
	public void RemoveSale(int price)
	{
		totalSales -= price;
	}
	public float CalculateRevenue()
	{
		return totalSales * tvPrice;
	}
}
public class Television        // контейнеризируемый класс
{
	private string model;
	private float price;
	public Television(string model, float price)
	{
		this.model = model;
		this.price = price;
	}
	public string Model
	{
		get 
		{
			return model;
		}
	}
	public float Price
	{
		get 
		{
			return price; 
		}
		set
		{ 
			price = value;
		}
	}
}