#pragma once
#include <random>
#include <time.h>
#include "Student.h"

template <class T>
T generate() 
{
	return T();
}

template<>
int generate() 
{
	return rand() % 10000 - 5000;
}

template<>
double generate() 
{
	return (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 100 - 50;
}

template<>
Student generate() 
{
	Student example;
	std::vector<std::string> names = { "Alexey", "Yan", "Artem", "Andrey", "Ivan", "Nikita", "Michail", "Alexandr", "Pavel" };
	example.SetName(names[rand() % 9]);
	example.SetAge(17 + rand() % 5);
	example.SetGroup(100 + rand() % 899);
	example.SetCourse(1 + rand() % 4);

	return example;
}

template<>
std::string generate() 
{
	std::string res;
	int sz = rand() % 10;
	if (sz == 0)
	{
		return std::string("");
	}
	res.reserve(sz);
	for (int i = 0; i < sz; ++i) 
	{
		res.push_back(static_cast<char>(65 + rand() % 59));
	}

	return res;
}
