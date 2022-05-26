#pragma once
#include "TreeMap.h"

class Counter : public TreeMap<char, int*>
{
public:
    struct Sorted
    {
        char* keys;
        int** values;
        size_t size;
    };

private:
    Sorted* sorted = nullptr;

    // swap two element of the array
    template<class T>
    void swap(T* arr, int a, int b) {
        T t = arr[a];
        arr[a] = arr[b];
        arr[b] = t;
    }

    // partition for quicksort
    int partition(int high, int low) {
        int smaller = low - 1; // index of smaller element
        for (int i = low; i <= high - 1; i++) {
            if (*sorted->values[i] <= *sorted->values[high]) { // current element is smaller or equal to pivot
                smaller++;
                swap(sorted->values, i, smaller);
                swap(sorted->keys, i, smaller);
            }
        }
        smaller++;
        swap(sorted->values, smaller, high);
        swap(sorted->keys, smaller, high);
        return smaller;
    }

    // quicksort
    void quickSort(int high, int low = 0) {
        if (low < high) {
            int prt_index = partition(high, low);
            quickSort(high, prt_index + 1); // separately sort right part
            quickSort(prt_index - 1, low); // separately sort left part
        }
    }

public:
    Sorted* getSorted() {
        sorted = new Sorted;
        sorted->keys = getKeys();
        sorted->values = getValues();
        sorted->size = get_size();
        quickSort(get_size() - 1);
        return sorted;
    }
};
