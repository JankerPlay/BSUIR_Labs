namespace Lab5_Domain
{
	public class Restaurant
	{
		public string Name { get; set; }
		public List<Kitchen> Kitchens { get; set; }

		public Restaurant()
		{
			Kitchens = new List<Kitchen>();
		}
	}
	public class Kitchen
	{
		public string Name { get; set; }
		public List<Dish> Dishes { get; set; }

		public Kitchen()
		{
			Dishes = new List<Dish>();
		}
	}
	public class Dish
	{
		public string Name { get; set; }
		public List<Ingredient> Ingredients { get; set; }

		public Dish()
		{
			Ingredients = new List<Ingredient>();
		}
	}
	 public class Ingredient
    {
        public string Name { get; set; }
        public int Quantity { get; set; }
    }
}