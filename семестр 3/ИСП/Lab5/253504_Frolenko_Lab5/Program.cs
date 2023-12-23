using Lab5_Domain;
using SerializerLib;
class Program
{
	static void Main(string[] args)
	{
		List<Restaurant> restaurants = new List<Restaurant>
		{
			new Restaurant
			{
				Name = "Restaurant1",
				Kitchens = new List<Kitchen>
				{
					new Kitchen
					{
						Name = "Kitchen1",
						Dishes = new List<Dish>
						{
							new Dish
							{
								Name = "Dish1",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient1", Quantity = 1 },
									new Ingredient { Name = "Ingredient2", Quantity = 2 },
								}
							},
							new Dish
							{
								Name = "Dish2",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient3", Quantity = 3 },
									new Ingredient { Name = "Ingredient4", Quantity = 4 },
								}
							}
						}
					},
					new Kitchen
					{
						Name = "Kitchen2",
						Dishes = new List<Dish>
						{
							new Dish
							{
								Name = "Dish3",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient5", Quantity = 5 },
									new Ingredient { Name = "Ingredient6", Quantity = 6 },
								}
							},
							new Dish
							{
								Name = "Dish4",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient7", Quantity = 7 },
									new Ingredient { Name = "Ingredient8", Quantity = 8 },
								}
							}
						}
					},
					new Kitchen
					{
						Name = "Kitchen3",
						Dishes = new List<Dish>
						{
							new Dish
							{
								Name = "Dish5",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient9", Quantity = 9 },
									new Ingredient { Name = "Ingredient10", Quantity = 10 },
								}
							},
							new Dish
							{
								Name = "Dish6",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient11", Quantity = 11 },
									new Ingredient { Name = "Ingredient12", Quantity = 12 },
								}
							}
						}
					}
				}
			},
			new Restaurant
			{
				Name = "Restaurant2",
				Kitchens = new List<Kitchen>
				{
					new Kitchen
					{
						Name = "Kitchen4",
						Dishes = new List<Dish>
						{
							new Dish
							{
								Name = "Dish7",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient13", Quantity = 13 },
									new Ingredient { Name = "Ingredient14", Quantity = 14 },
								}
							},
							new Dish
							{
								Name = "Dish8",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient15", Quantity = 15 },
									new Ingredient { Name = "Ingredient16", Quantity = 16 },
								}
							}
						}
					},
					new Kitchen
					{
						Name = "Kitchen5",
						Dishes = new List<Dish>
						{
							new Dish
							{
								Name = "Dish9",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient17", Quantity = 17 },
									new Ingredient { Name = "Ingredient18", Quantity = 18 },
								}
							},
							new Dish
							{
								Name = "Dish10",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient19", Quantity = 19 },
									new Ingredient { Name = "Ingredient20", Quantity = 20 },
								}
							}
						}
					},
					new Kitchen
					{
						Name = "Kitchen6",
						Dishes = new List<Dish>
						{
							new Dish
							{
								Name = "Dish11",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient21", Quantity = 21 },
									new Ingredient { Name = "Ingredient22", Quantity = 22 },
								}
							},
							new Dish
							{
								Name = "Dish12",
								Ingredients = new List<Ingredient>
								{
									new Ingredient { Name = "Ingredient23", Quantity = 23 },
									new Ingredient { Name = "Ingredient24", Quantity = 24 },
								}
							}
						}
					}
				}
			}
		};
		Serializer serializer = new Serializer();
		serializer.SerializeXML(restaurants, "restaurants.xml");
		serializer.SerializeJSON(restaurants, "restaurants.json");
		serializer.SerializeByLINQ(restaurants, "restaurants_linq.xml");
		List<Restaurant> xmlRestaurants = serializer.DeSerializeXML("restaurants.xml").ToList();
		List<Restaurant> jsonRestaurants = serializer.DeSerializeJSON("restaurants.json").ToList();
		List<Restaurant> linqXmlRestaurants = serializer.DeSerializeByLINQ("restaurants_linq.xml").ToList();
		Console.WriteLine("File:");
		foreach (var restaurant in xmlRestaurants)
		{
			Console.WriteLine("Restaurant Name: " + restaurant.Name);
			foreach (var kitchen in restaurant.Kitchens)
			{
				Console.WriteLine("Kitchen Name: " + kitchen.Name);
				foreach (var dish in kitchen.Dishes)
				{
					Console.WriteLine("Dish Name: " + dish.Name);
					foreach (var ingredient in dish.Ingredients)
					{
						Console.WriteLine("Ingredient Name: " + ingredient.Name + ingredient.Quantity);
					}
				}
			}
		}
		Console.WriteLine("File:");
		foreach (var restaurant in xmlRestaurants)
		{
			Console.WriteLine("Restaurant Name: " + restaurant.Name);
			foreach (var kitchen in restaurant.Kitchens)
			{
				Console.WriteLine("Kitchen Name: " + kitchen.Name);
				foreach (var dish in kitchen.Dishes)
				{
					Console.WriteLine("Dish Name: " + dish.Name);
					foreach (var ingredient in dish.Ingredients)
					{
						Console.WriteLine("Ingredient Name: " + ingredient.Name + " " + ingredient.Quantity);
					}
				}
			}
		}

	}
}