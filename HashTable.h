#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int M = 100000; //180001

struct list {
    string data;
    string key;
    list* prev;
    list* next;
    list* next_list;
    list() {}
    list(string _key, string _data, list* _a) {
        data = _data;
        key = _key;
        next_list = _a;
        next = prev = nullptr;
    }
};

int h(string& x) {
    vector<int> simple_nums = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
    int result = 0;
    for (int i = 0; i < x.size(); i++)
        result = (result + ((char)x[i]) * simple_nums[i]) % M;
    return result;
}

struct HashTable {
    vector<list*> table;
    list* prev;

    HashTable() {
        table.resize(M);
        prev = nullptr;
    }

    list* insert(string key, string data) {
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

    list* exists(string key) {
        int k = h(key);
        if (table[k] == nullptr)
            return nullptr;
        list* p = table[k];
        while (p != nullptr) {
            if (p->key == key)
                return p;
            p = p->next_list;
        }
        return nullptr;
    }

    list* del(string key) {
        int k = h(key);
        list* p = table[k];
        list* prev_list = nullptr;
        if (p->key == key) {
            list* ans = table[k];
            table[k] = p->next_list;
            return ans;
        }
        while (p != nullptr) {
            if (p->key == key) {
                list* ans = p;
                prev_list->next_list = p->next_list;
                return ans;
            }
            prev_list = p;
            p = p->next_list;
        }
        return nullptr;
    }

    void print() {
        for (int i = 0; i < M; i++) {
            list* p = table[i];
            if (p != nullptr) {
                cout << i << "\t";
                while (p != nullptr) {
                    cout << p->key << " - " << p->data << " ";
                    p = p->next_list;
                }
                cout << endl;
            }
        }
    }
};