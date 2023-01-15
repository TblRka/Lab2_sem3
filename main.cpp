#include "LinkedList.h"

int main()
{
    //string s = "Alexey Ryzhov 514";
    //std::cout << h(s) << "\n";

    int arr[5] = { 1, 2, 3, 7, 10 };
    LinkedList<int>* list = new LinkedList<int>(arr, 5);
    list->Print_line();
    list->Delete(2);
    list->Print_line();
}