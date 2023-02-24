#include "LinkedList.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    int i;
    cin >> i;
    cout << i << '\n';

    int arr[5] = {1, 2, 3, 4, 5};

    LinkedList<int>* List = new LinkedList<int>(arr, 5);
    int s = List->GetLength();
    cout << s << '\n';
 
    //menu();
}