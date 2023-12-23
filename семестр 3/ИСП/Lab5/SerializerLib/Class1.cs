using System.Collections.Generic;
using System.IO;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Serialization;
using Lab5_Domain;
using Newtonsoft.Json;

namespace SerializerLib
{
	public class Serializer : ISerializer
	{
		public IEnumerable<Restaurant> DeSerializeByLINQ(string fileName)
		{
			XDocument doc = XDocument.Load(fileName);
			var restaurants = doc.Root.Elements("Restaurant")
				.Select(r => new Restaurant
				{
					Name = (string)r.Element("Name"),
					Kitchens = r.Element("Kitchens").Elements("Kitchen")
						.Select(k => new Kitchen
						{
							Name = (string)k.Element("Name"),
							Dishes = k.Element("Dishes").Elements("Dish")
								.Select(d => new Dish
								{
									Name = (string)d.Element("Name"),
									Ingredients = d.Element("Ingredients").Elements("Ingredient")
										.Select(i => new Ingredient
										{
											Name = (string)i.Element("Name"),
											Quantity = (int)i.Element("Quantity")
										})
										.ToList()
								})
								.ToList()
						})
						.ToList()
				})
				.ToList();

			return restaurants;
		}

		public IEnumerable<Restaurant> DeSerializeXML(string fileName)
		{
			XmlSerializer serializer = new XmlSerializer(typeof(List<Restaurant>));
			using (StreamReader reader = new StreamReader(fileName))
			{
				List<Restaurant> restaurants = (List<Restaurant>)serializer.Deserialize(reader);
				return restaurants;
			}
		}

		public IEnumerable<Restaurant> DeSerializeJSON(string fileName)
		{
			string json = File.ReadAllText(fileName);
			List<Restaurant> restaurants = JsonConvert.DeserializeObject<List<Restaurant>>(json);
			return restaurants;
		}

		public void SerializeByLINQ(IEnumerable<Restaurant> restaurants, string fileName)
		{
			XDocument doc = new XDocument(
				new XElement("Restaurants",
					restaurants.Select(r =>
						new XElement("Restaurant",
							new XElement("Name", r.Name),
							new XElement("Kitchens",
								r.Kitchens.Select(k =>
									new XElement("Kitchen",
										new XElement("Name", k.Name),
										new XElement("Dishes",
											k.Dishes.Select(d =>
												new XElement("Dish",
													new XElement("Name", d.Name),
													new XElement("Ingredients",
														d.Ingredients.Select(i =>
															new XElement("Ingredient",
																new XElement("Name", i.Name),
																new XElement("Quantity", i.Quantity)
															)
														)
													)
												)
											)
										)
									)
								)
							)
						)
					)
				)
			);

			doc.Save(fileName);
		}

		public void SerializeXML(IEnumerable<Restaurant> restaurants, string fileName)
		{
			XmlSerializer serializer = new XmlSerializer(typeof(List<Restaurant>));
			using (StreamWriter writer = new StreamWriter(fileName))
			{
				serializer.Serialize(writer, restaurants);
			}
		}

		public void SerializeJSON(IEnumerable<Restaurant> restaurants, string fileName)
		{
			string json = JsonConvert.SerializeObject(restaurants, Newtonsoft.Json.Formatting.Indented);
			File.WriteAllText(fileName, json);
		}
	}
}