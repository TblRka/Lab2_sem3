#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Histogram.h"
#include "Student.h"

template <class X>
void get_xseries(DynamicArray<Pair<X, X>>& xseries) 
{
	Pair<X, X> pair;
	std::cout << "Enter pair of partition:\n";
	std::cin >> pair.first >> pair.second;
	while (pair.first != X() && pair.second != X()) 
	{
		xseries.Append(pair);
		std::cout << "Enter pair of partition: (enter 0 0 to exit)\n";
		std::cin >> pair.first >> pair.second;
	}
}

template <class T>
void menu_type() 
{
	int var = 1;
	Histogram<Student, int, T> hist;
	while (var) 
	{
		std::cout << "Choose option:\n 1. Fill random\n 2. Add\n 3. Remove\n 4. Show\n 5. Show with elements\n 6. Describe\n 7. Back\n> ";
		std::cin >> var;
		switch (var) 
		{
		case 1:
		{
			size_t count = 0;
			std::cout << "Enter quantity: ";
			std::cin >> count;
			DynamicArray<Pair<int, int>> xseries;
			xseries.Reserve(count);
			get_xseries<int>(xseries);
			hist.fill_rand(count, xseries); 
		}
		break;

		case 2:
		{
			std::cout << "Enter name, age, group, course:\n";
			std::string _name;
			int _age;
			int _group;
			int _course;
			std::cin >> _name >> _age >> _group >> _course;
			Student st(_name, _age, _group, _course);
			hist.insert(st); 
		}
		break;

		case 3:
		{
			int a = 0;
			std::cout << "Enter value: ";
			std::cin >> a;
			hist.remove(a); 
		}
		break;

		case 4:
		{
			hist.show_file();
		}

			//system("start Plot_text.exe");;
		break;

		case 5:
			std::cout << hist;
			break;

		case 6:
			hist.describe();
			break;

		case 7:
			var = 0;
			break;

		default:
			std::cout << "Wrong option... Try again\n";
			break;
		}
	}
}

void menu_hist() 
{
	int var = 1;
	while (var) 
	{
		std::cout << "Chose category to work with:\n 1. Age\n 2. Group\n 3. Course\n 4. Quit\n> ";
		std::cin >> var;
		switch (var) 
		{
		case 1:
			menu_type<Age>();
			break;
		case 2:
			menu_type<Group>();
			break;
		case 3:
			menu_type<Course>();
			break;
		case 4:
			var = 0;
			break;
		default:
			std::cout << "Wrong input... Try again\n";
		}
	}
}

void menu() {
	int var = 1;
	while (var) 
	{
		std::cout << "Choose the class:\n1. Histogram\n2. Quit\n> ";
		std::cin >> var;
		switch (var) 
		{
		case 1:
			menu_hist();
			break;
		case 2:
			var = 0;
			break;
		default:
			std::cout << "Wrong option... Try again\n";
		}
	}
}
