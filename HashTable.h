#pragma once

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Pair.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable 
{
private:
	template <typename Key, typename Value>
	struct Chain 
	{
	private:
		friend HashTable;
		LinkedList<Pair<Key, Value>>* list;
		size_t _size;
	public:
		Chain() 
		{
			list = nullptr;
			_size = 0;
		}
		~Chain() 
		{
			if (list) delete list;
		}
		size_t size() 
		{
			return _size;
		}
		void push_back(const Pair<Key, Value>& el) 
		{
			if (!list) 
			{
				list = new LinkedList<Pair<Key, Value>>;
			}
			list->Append(el);
			_size++;
		}
		bool find(Key key) 
		{
			if (!list)
			{
				return false;
			}
			for (int i = 0; i < _size; ++i) 
			{
				if (key == list->GetIndex(i).first)
				{
					return true;
				}
			}
			return false;
		}
	};
	size_t arr_size = 0;
	size_t size = 0;
	double max_load_factor = 0.75;
	DynamicArray<Chain<Key, Value>*>* table = nullptr;
	Hash hasher;

public:
	HashTable(); //+
	HashTable(const HashTable<Key, Value, Hash>& other);
	~HashTable(); //+

	size_t GetCapacity(); //+
	size_t GetSize(); //+
	bool Empty(); //+
	double GetMaxLoadFactor();//+
	double GetLoadFactor();//+
	void SetMaxLoadFactor(double new_factor); // +

	Value& At(const Key& key); //+

	size_t Erase(const Key& key);//+

	void Insert(const Key key, const Value value);//+
	bool Find(const Key& key); //+

	void Print(); //+
	void Rehash(size_t new_size);//+
	void Reserve(size_t count);//+

	HashTable<Key, Value, Hash>& operator=(const HashTable<Key, Value, Hash>& another);
	Value& operator[](const Key& key);
private:
	size_t get_hash(const Key& key, size_t arr_size);
};

template <typename Key, typename Value, typename Hash>
size_t HashTable<Key, Value, Hash>::get_hash(const Key& key, size_t arr_size) 
{
	return hasher(key) % arr_size;
}

template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::HashTable() 
{
	arr_size = 10;
	table = new DynamicArray<Chain<Key, Value>*>;
	table->Resize(arr_size);
	for (int i = 0; i < arr_size; ++i) 
	{
		table->Get(i) = nullptr;
	}
}


template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::HashTable(const HashTable<Key, Value, Hash>& another) 
{
	if (table)
	{
		delete table;
	}
	arr_size = another.arr_size;
	max_load_factor = another.max_load_factor;
	size = another.size;
	hasher = another.hasher;

	table = new DynamicArray<Chain<Key, Value>*>;
	table->Resize(arr_size);

	for (int i = 0; i < arr_size; ++i) 
	{
		table->Get(i) = nullptr;
	}
	for (int i = 0; i < arr_size; ++i) 
	{
		if (another.table->Get(i)) 
		{
			table->Get(i) = new Chain<Key, Value>;
			if (another.table->Get(i)->list) 
			{
				size_t sz = another.table->Get(i)->size();
				for (int j = 0; j < sz; ++j) 
				{
					table->Get(i)->push_back(another.table->Get(i)->list->GetIndex(j));
				}
			}
		}
	}
}

template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::~HashTable() 
{
	if (table) 
	{
		delete table;
	}
}

template <typename Key, typename Value, typename Hash>
size_t HashTable<Key, Value, Hash>::GetCapacity() 
{
	return arr_size;
}

template <typename Key, typename Value, typename Hash>
size_t HashTable<Key, Value, Hash>::GetSize() 
{
	return size;
}

template <typename Key, typename Value, typename Hash>
bool HashTable<Key, Value, Hash>::Empty() 
{
	if (size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::Insert(const Key key, const Value value) {
	if (!table) 
	{
		arr_size = 10;
		table = new DynamicArray<Chain<Key, Value>*>;
		table->Resize(arr_size);
		for (int i = 0; i < arr_size; ++i) 
		{
			table->Get(i) = nullptr;
		}
	}
	size_t index = get_hash(key, arr_size);
	if (!table->Get(index)) 
	{
		table->Get(index) = new Chain<Key, Value>;
	}
	if (table->Get(index)->find(key))
	{
		return;
	}

	table->Get(index)->push_back(Pair<Key, Value>{key, value});
	size++;

	if (GetLoadFactor() > max_load_factor) 
	{
		Rehash(2 * arr_size);
	}
}

template <typename Key, typename Value, typename Hash>
bool HashTable<Key, Value, Hash>::Find(const Key& key) 
{
	if (!table)
	{
		return false;
	}
	size_t index = get_hash(key);
	if (table->Get(index)) 
	{
		if (table->Get(index)->find(key))
		{
			return true;
		}
	}
	return false;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::SetMaxLoadFactor(double new_factor) 
{
	if (new_factor > 1)
	{
		throw std::exception("Index out of range");
	}
	max_load_factor = new_factor;
}

template <typename Key, typename Value, typename Hash>
double HashTable<Key, Value, Hash>::GetMaxLoadFactor() 
{
	return max_load_factor;
}

template <typename Key, typename Value, typename Hash>
double HashTable<Key, Value, Hash>::GetLoadFactor() 
{
	return static_cast<double>(size) / arr_size;
}

template <typename Key, typename Value, typename Hash> 
Value& HashTable<Key, Value, Hash>::At(const Key& key) 
{
	if (!table) 
	{
		arr_size = 10;
		table = new DynamicArray<Chain<Key, Value>*>;
		table->Resize(arr_size);
		for (int i = 0; i < arr_size; ++i) 
		{
			table->Get(i) = nullptr;
		}
	}
	size_t index = get_hash(key, arr_size);
	if (!table->Get(index)) //если бакета нет, создаем его
	{
		table->Get(index) = new Chain<Key, Value>;
	}
	Chain<Key, Value>* chain = table->Get(index);
	if (chain->find(key)) //проверяем наличие этого ключа в бакете, если есть, заменяем
	{
		int i = 0;
		while (key != chain->list->GetIndex(i).first) 
		{
			i++;
		}
		return chain->list->GetIndex(i).second;
	}
	else //если нет элемента в бакете
	{ 
		if (!chain->list) //проверяем, есть ли список в бакете, если нет, создаем 
		{
			chain->list = new LinkedList<Pair<Key, Value>>;
		}
		chain->push_back(Pair<Key, Value>{ Key(), Value() });
		size++;
		if (GetLoadFactor() > max_load_factor) 
		{
			Rehash(2 * arr_size);
		}
		return chain->list->GetIndex(chain->size() - 1).second;
	}
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::Print() 
{
	if (!table) 
	{
		std::cout << "{}";
		return;
	}
	std::cout << "{ ";
	for (int i = 0; i < arr_size; ++i) 
	{
		Chain<Key, Value>* chain = table->Get(i);
		if (chain) 
		{
			if (chain->list) 
			{
				int sz = chain->size();
				for (int j = 0; j < sz; ++j) 
				{
					std::cout << chain->list->GetIndex(j) << i << " ";
				}
			}
		}
	}
	std::cout << "}\n";
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::Rehash(size_t new_size) {
	if (!table) 
	{
		arr_size = new_size;
		table = new DynamicArray<Chain<Key, Value>*>;
		table->Resize(arr_size);
		for (int i = 0; i < arr_size; ++i) 
		{
			table->Get(i) = nullptr;
		}
		return;
	}
	if (static_cast<double>(size) / new_size > max_load_factor)
	{
		return;
	}

	DynamicArray<Chain<Key, Value>*>* new_table = new DynamicArray<Chain<Key, Value>*>;
	new_table->Resize(new_size);
	for (int i = 0; i < new_size; ++i) 
	{
		new_table->Get(i) = nullptr;
	}
	for (int i = 0; i < arr_size; ++i)
	{
		if (table->Get(i)) 
		{
			if (table->Get(i)->list) 
			{
				size_t sz = table->Get(i)->size();
				for (int j = 0; j < sz; ++j) 
				{
					Pair<Key, Value>& tmp_pair = table->Get(i)->list->GetIndex(j);
					size_t index = get_hash(tmp_pair.first, new_size);
					if (!new_table->Get(i))
					{
						new_table->Get(i) = new Chain<Key, Value>;
					}
					new_table->Get(i)->push_back(Pair<Key, Value>{tmp_pair.first, tmp_pair.second});
				}
			}
		}
	}
	for (int i = 0; i < arr_size; ++i) 
	{
		if (!table->Get(i))
		{
			delete table->Get(i);
		}
	}
	delete table;
	table = new_table;
	arr_size = new_size;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::Reserve(size_t count) {
	if (count < size)
	{
		return;
	}
	size_t new_size = static_cast<size_t>(std::ceil(count / max_load_factor));
	Rehash(new_size + 2);
}

template <typename Key, typename Value, typename Hash>
size_t HashTable<Key, Value, Hash>::Erase(const Key& key) {
	if (!table)
	{
		return 0;
	}
	size_t index = get_hash(key, arr_size);
	if (table->Get(index)) 
	{
		if (table->Get(index)->find(key)) 
		{
			int i = 0;
			while (key != table->Get(index)->list->GetIndex(i).first) 
			{
				i++;
			}
			table->Get(i)->list->Delete(i);
			table->Get(i)->_size--;
			size--;
			return 1;
		}
	}
	return 0;
}

template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>& HashTable<Key, Value, Hash>::operator=(const HashTable<Key, Value, Hash>& another) {
	if (table)
	{
		delete table;
	}
	arr_size = another.arr_size;
	max_load_factor = another.max_load_factor;
	size = another.size;
	hasher = another.hasher;
	table = new DynamicArray<Chain<Key, Value>*>;
	table->Resize(arr_size);
	for (int i = 0; i < arr_size; ++i) 
	{
		table->Get(i) = nullptr;
	}
	for (int i = 0; i < arr_size; ++i) 
	{
		if (another.table->Get(i)) 
		{
			table->Get(i) = new Chain<Key, Value>;
			if (another.table->Get(i)->list) 
			{
				size_t sz = another.table->Get(i)->size();
				for (int j = 0; j < sz; ++j) 
				{
					table->Get(i)->push_back(another.table->Get(i)->list->GetIndex(j));
				}
			}
		}
	}
	return *this;
}


template <typename Key, typename Value, typename Hash>
Value& HashTable<Key, Value, Hash>::operator[](const Key& key) 
{
	if (!table) 
	{
		arr_size = 10;
		table = new DynamicArray<Chain<Key, Value>*>;
		table->Resize(arr_size);
		for (int i = 0; i < arr_size; ++i) 
		{
			table->Get(i) = nullptr;
		}
	}
	size_t index = get_hash(key, arr_size);
	if (!table->Get(index)) //если бакета нет, создаем его
	{
		table->Get(index) = new Chain<Key, Value>;
	}
	Chain<Key, Value>* chain = table->Get(index);
	if (chain->find(key)) //проверяем наличие этого ключа в бакете, если есть, заменяем
	{
		int i = 0;
		while (key != chain->list->GetIndex(i).first) 
		{
			i++;
		}
		return chain->list->GetIndex(i).second;
	}
	else //если нет элемента в бакете
	{
		chain->push_back(Pair<Key, Value>{ key, Value() });
		size++;
		if (GetLoadFactor() > max_load_factor) 
		{
			Rehash(2 * arr_size);
		}
		return chain->list->GetIndex(chain->size() - 1).second;
	}
}