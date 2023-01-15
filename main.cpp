#include "HashTable.h"
#include <iostream>

using namespace std;

int main()
{
    //string s = "Alexey Ryzhov 514";
    //std::cout << h(s) << "\n";

    int arr[5] = { 1, 2, 3, 7, 10 };
    LinkedList<int>* list = new LinkedList<int>(arr, 5);
    list->Print_line();
    list->Delete(2);
    list->Print_line();

    HashTable<string, int>* Table = new HashTable<string, int>();
    for (int i = 0; i < 3; i++)
    {
        string key;
        int value;
        cin >> key >> value;
        Table->Insert(key, value);
    }
    Table->Print();
}