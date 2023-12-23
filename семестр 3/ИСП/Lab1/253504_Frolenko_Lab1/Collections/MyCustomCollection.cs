using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using _253504_Frolenko_Lab1.Interfaces;
namespace _253504_Frolenko_Lab1.Collections
{
	public class MyCustomCollection<T> : ICustomCollection<T>
	{
		private class Node
		{
			public T Data { get; set; }
			public Node Next { get; set; }
		}
		private Node head;
		private Node current;
		private int count;
		
		public T this[int index]
		{
			get
			{
				if(index < 0 || index >= count)
					throw new IndexOutOfRangeException();
				Node node = FindNode(index);
				return node.Data;
			}
			set
			{
				if (index < 0 || index >= count)
					throw new IndexOutOfRangeException();

				Node node = FindNode(index);
				node.Data = value;
			}
		}
		public void Reset()
		{
			current = head;
		}
		public void Next()
		{
			if(current != null)
			{
				current = current.Next;
			}
		}
		public T Current()
		{
			if(current == null)
			{
				throw new InvalidOperationException("Cursor is not set to a valid element");
			}
			return current.Data;
		}
		public int Count
		{
			get { return count; }
		}
		public void Add(T item)
		{
			Node newNode = new Node { Data = item, Next = null };
			if(head == null)
			{
				head = newNode;	
				current = newNode;
			}
			else
			{
				Node lastNode = FindNode(count - 1);
				lastNode.Next = newNode;
			}
			count++;
		}
		public void Remove(T item)
		{
			Node previousNode = null;
			Node currentNode = head;
			while(currentNode != null)
			{
				if(currentNode.Data.Equals(item))
				{
					if(previousNode != null)
					{
						previousNode.Next = currentNode.Next;
						if(current == currentNode)
						{
							current = previousNode;
						}
					}
					else
					{
						head = currentNode.Next;
						if(current == currentNode)
						{
							current = head;
						}
					}
					count--;
					return;
				}
				previousNode = currentNode; 
				currentNode = currentNode.Next;
			}
		}
		public T RemoveCurrent()
		{
			if (current == null)
			{
				throw new InvalidOperationException("Cursor is not set to a valid element");
			}
			T data = current.Data;
			Remove(data);
			return data;
		}
		private Node FindNode(int index)
		{
			Node node = head;
			for(int i = 0; i < index; i++)
			{
				node = node.Next;
			}
			return node;
		}
		public bool Any(Func<T, bool> predicate)
		{
			Node currentNode = head;
			while (currentNode != null)
			{
				if (predicate(currentNode.Data))
				{
					return true;
				}
				currentNode = currentNode.Next;
			}
			return false;
		}
		public IEnumerator<T> GetEnumerator()
		{
			Node currentNode = head;
			while (currentNode != null)
			{
				yield return currentNode.Data;
				currentNode = currentNode.Next;
			}
		}

		IEnumerator IEnumerable.GetEnumerator()
		{
			return GetEnumerator();
		}
	}
}