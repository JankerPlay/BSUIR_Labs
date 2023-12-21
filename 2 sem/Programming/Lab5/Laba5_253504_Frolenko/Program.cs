public class Product
{
	public string Name { get; set; }
	public float Price { get; set; }
	public int Quantity { get; set; }
}
public class Order
{
	public string CustomerLastName { get; set; }
	public List<Product> Products { get; set; }
	public float TotalPrice => Products.Sum(p => p.Price * p.Quantity);
}
public class Shop
{
	private List<Product> products = new List<Product>();
	private List<Order> orders = new List<Order>();
	public void AddProduct(Product product)
	{
		products.Add(product);
	}
	public void RegisterOrder(Order order)
	{
		orders.Add(order);
	}
	public List<Order> GetOrdersByCustomerLastName(string lastName)
	{
		return orders.Where(o => o.CustomerLastName == lastName).ToList();
	}
	public float GetTotalPriceByCustomerLastName(string lastName)
	{
		return orders.Where(o => o.CustomerLastName == lastName).Sum(o => o.TotalPrice);
	}
}
class Program
{
	static void Main(string[] args)
	{
		var shop = new Shop();
		var phone = new Product { Name = "iPhone", Price = 1423, Quantity = 112 };
		var book = new Product { Name = "The bible", Price = 23452, Quantity = 320 };
		var shirt = new Product { Name = "Off-while", Price = 5234, Quantity = 23 };
		shop.AddProduct(phone);
		shop.AddProduct(book);
		shop.AddProduct(shirt);
		var order = new Order { CustomerLastName = "Pupkin", Products = new List<Product> { phone, book } };
		shop.RegisterOrder(order);
		var ordersByPupkin = shop.GetOrdersByCustomerLastName("Pupkin");
		Console.WriteLine("Orders by Pupkin:");
		foreach (var o in ordersByPupkin)
		{
			Console.WriteLine($"Purchases: {string.Join(", ", o.Products.Select(p => p.Name))}");
		}
		var totalPriceByPupkin = shop.GetTotalPriceByCustomerLastName("Pupkin");
		Console.WriteLine($"Total price for Pupkin: {totalPriceByPupkin}");
	}
}