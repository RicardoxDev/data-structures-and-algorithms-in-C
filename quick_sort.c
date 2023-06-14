#include <stdio.h>

void printArray(int arr[], int length) {
    int i;

    printf("%s \n", "[");
    for(i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n%s\n", "]");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int start, int finish) {
    int min = start - 1;
    int pivot = arr[finish];

    int i;
    for(i = start; i < finish - 1; i++) {
        if(arr[i] < pivot) {
          min++;
          swap(&arr[min], &arr[i]);
        }
    }
    swap(&arr[min + 1], &pivot);

    return min;
}

void quickSort(int arr[], int start, int finish) {
    if(start > finish) return;
    int pi = partition(arr, start, finish);

    quickSort(arr, pi + 1, finish);
    quickSort(arr, start, pi - 1);
}

int main() {
    int numbers[] = {5, 3, 7, 6, 8, 4, 9, 6};
    int length = *(&numbers + 1) - numbers;
    
    quickSort(numbers, 0, 7);
    printArray(numbers, length);

    return 1;
}