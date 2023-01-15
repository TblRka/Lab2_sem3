#pragma once
#include <iostream>

template <class T> class DynamicArray
{
private:
	int size = 0;
	T* arr = nullptr;

public:
	DynamicArray();
	DynamicArray(T* items, int count);
	DynamicArray(int count);
	DynamicArray(const DynamicArray<T>& dynamicArray);
	~DynamicArray();

	T& Get(int index);
	int GetSize();

	void Set(int index, T value);
	void Resize(int newSize);
	void DeleteLast();

	DynamicArray<T>* GetSublist(int startIndex, int endIndex);
	DynamicArray<T>* Concat(DynamicArray<T>* list);

	void Print();
	void Print_line();
	void Print(int index);

	bool operator==(const DynamicArray<T>& a);
	bool operator!=(const DynamicArray<T>& a);

	void Swap(int index1, int index2);
};

template <class T> DynamicArray<T>::DynamicArray() {}
template <class T> DynamicArray<T>::DynamicArray(T* items, int count) : size(count), arr(new T[count])
{


	for (int i = 0; i < size; i++)
	{
		arr[i] = items[i];
	}

	//std::memcpy(arr, items, count * sizeof(T));
}

template <class T> DynamicArray<T>::DynamicArray(int count) : size(count), arr(new T[count]) {}
template <class T> DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) : DynamicArray(dynamicArray.arr, dynamicArray.size) {}
template <class T> DynamicArray<T>:: ~DynamicArray()
{
	delete[] arr;
}

template <class T> T& DynamicArray<T>::Get(int index)
{
	if (index >= size || index < 0)
	{
		throw std::out_of_range("IndexOutOfRange");
	}
	return arr[index];
}
template <class T> int DynamicArray<T>::GetSize()
{
	return size;
}

template <class T> void DynamicArray<T>::Set(int index, T value)
{

	this->Resize(size + 1);
	for (int i = size - 1; i >= index; i--)
	{
		if (i > index)
		{
			arr[i] = arr[i - 1];
		}
		if (i == index)
		{
			arr[i] = value;
		}
	}
}

template <class T> void DynamicArray<T>::Resize(int newSize)
{
	if (newSize < 0)
	{
		throw std::exception("Index is out of range");
	}
	T* copy = new T[size];
	std::memcpy(copy, arr, size * sizeof(T));
	delete[] this->arr;
	arr = new T[newSize + 1];
	std::memcpy(arr, copy, size * sizeof(T));
	delete[] copy;
	size = newSize;

}

template <class T> DynamicArray<T>* DynamicArray<T>::GetSublist(int startIndex, int endIndex)
{

	if (startIndex < 0 || startIndex >= size || endIndex < 0 || endIndex >= size)
	{
		throw std::exception("Index is out of range");
	}
	else
	{
		DynamicArray<T>* sublist = new DynamicArray<T>(arr + startIndex, endIndex - startIndex + 1);
		return sublist;
	}
}

template <class T> DynamicArray<T>* DynamicArray<T>::Concat(DynamicArray<T>* dynamicArray)
{

	DynamicArray<T>* result = new DynamicArray<T>(*this);
	result->Resize(this->size + dynamicArray->size);
	std::memcpy(result->arr + size, dynamicArray->arr, dynamicArray->size * sizeof(T));
	return result;
}

template <class T> void DynamicArray<T>::Print()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << std::endl;
	}
}
template <class T> void DynamicArray<T>::Print_line()
{
	for (int i = 0; i < size - 1; i++)
	{
		std::cout << "[" << arr[i] << "] ";
	}
	std::cout << "[" << arr[size - 1] << "]" << std::endl;
}
template <class T> void DynamicArray<T>::Print(int index)
{
	std::cout << arr[index] << std::endl;
}
template <class T> void DynamicArray<T>::DeleteLast()
{
	Resize(size - 1);
}
template <class T> void DynamicArray<T>::Swap(int index1, int index2)
{
	T k = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = k;
}

template <class T> bool DynamicArray<T>::operator==(const DynamicArray<T>& a)
{
	if (size != a.size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			if (arr[i] != a.arr[i])
			{
				return false;
			}
		}
	}
	return true;
}
template <class T> bool DynamicArray<T>::operator!=(const DynamicArray<T>& a)
{
	return !(*this == a);
}
