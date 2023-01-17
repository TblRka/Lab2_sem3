#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Histogram.h"
#include "Windows.h"

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
		std::cout << "Choose option:\n 1. Fill random\n 2. Add\n 3. Remove\n 4. Show\n 5. Elements\n 7. Back\n> ";
		std::cin >> var;
		switch (var) 
		{
		case 1:
		{
			Sleep(10);
			system("cls");

			size_t count = 0;
			std::cout << "Enter number of elements: ";
			std::cin >> count;
			DynamicArray<Pair<int, int>> xseries;
			xseries.Reserve(count);
			get_xseries<int>(xseries);
			hist.fill_rand(count, xseries); 

			Sleep(10);
			system("cls");
		}
		break;

		case 2:
		{
			Sleep(10);
			system("cls");

			std::cout << "Enter name, age, group and course:\n";
			std::string _name;
			int _age;
			int _group;
			int _course;
			std::cin >> _name >> _age >> _group >> _course;
			Student st(_name, _age, _group, _course);
			hist.insert(st); 

			Sleep(10);
			system("cls");
		}
		break;

		case 3:
		{
			Sleep(10);
			system("cls");

			int a = 0;
			std::cout << "Enter value: ";
			std::cin >> a;
			hist.remove(a); 

			Sleep(10);
			system("cls");
		}
		break;

		case 4:
		{
			Sleep(10);
			system("cls");

			hist.show_file();
			system("start Hist1.exe");
		}
		break;

		case 5:
			Sleep(10);
			system("cls");

			std::cout << hist;
			break;

		case 6:
			Sleep(10);
			system("cls");

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
			Sleep(10);
			system("cls");

			menu_type<Age>();
			break;
		case 2:
			Sleep(10);
			system("cls");

			menu_type<Group>();
			break;
		case 3:
			Sleep(10);
			system("cls");

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

			Sleep(10);
			system("cls");

			menu_hist();
			break;
		case 2:
			var = 0;
			break;
		default:
			std::cout << "Wrong option... Try again\n";
		}
		Sleep(10);
		system("cls");
	}
}
