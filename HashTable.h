#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template <class T, class K> 
struct list {
    T data;
    K key;
    list* prev;
    list* next;
    list* next_list;
    list() {}
    list(K _key, T _data, list* _a) {
        data = _data;
        key = _key;
        next_list = _a;
        next = prev = nullptr;
    }
};

template <class K>
int h(K& x) {
    vector<int> simple_nums = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
    int result = 0;
    for (int i = 0; i < x.size(); i++)
        result = (result + ((char)x[i]) * simple_nums[i]) % M;
    return result;
}

template <class T, class K>
class HashTable {
    vector<list*> table;
    list* prev;

    HashTable() {
        table.resize(M);
        prev = nullptr;
    }

     void insert(K key, T data) {
        int k = h(key);
        if (table[k] == nullptr) {
            table[k] = new list(key, data, nullptr);
            table[k]->prev = prev;
            if (prev != nullptr)
                prev->next = table[k];
            prev = table[k];
            return table[k];
        }
        list* p = table[k];
        while (p != nullptr) {
            if (p->key == key) {
                p->data = data;
                return p;
            }
            if (p->next_list == nullptr) {
                p->next_list = new list(key, data, nullptr);
                p->next_list->prev = prev;
                if (prev != nullptr)
                    prev->next = p->next_list;
                prev = p->next_list;
                return p->next_list;
            }
            p = p->next_list;
        }
        return nullptr;
    }