#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pure function to apply a function to each element of an array
int* map(int* arr, int length, int (*func)(int), int* new_length) {
    int* new_array = (int*)malloc(length * sizeof(int));
    *new_length = length;
    for (int i = 0; i < length; i++) {
        new_array[i] = func(arr[i]);
    }
    return new_array;
}

// Example transformation function
int square(int x) {
    return x * x;
}

// Pure function to filter elements based on a predicate
int* filter(int* arr, int length, int (*predicate)(int), int* new_length) {
    int* new_array = (int*)malloc(length * sizeof(int));
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (predicate(arr[i])) {
            new_array[count++] = arr[i];
        }
    }
    *new_length = count;
    return new_array;
}

// Example predicate function
int is_even(int x) {
    return x % 2 == 0;
}

// Pure function to reduce elements to a single value
int reduce(int* arr, int length, int (*func)(int, int), int initial) {
    int result = initial;
    for (int i = 0; i < length; i++) {
        result = func(result, arr[i]);
    }
    return result;
}

// Example reduction function
int sum(int a, int b) {
    return a + b;
}

int main() {
    // Sample array
    int arr[] = {1, 2, 3, 4, 5};
    int length = 5;

    // Map example
    int* squared = NULL;
    int new_length = 0;
    squared = map(arr, length, square, &new_length);

    // Filter example
    int* evens = NULL;
    evens = filter(arr, length, is_even, &new_length);

    // Reduce example
    int total = reduce(arr, length, sum, 0);

    // Print results
    printf("Squared: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", squared[i]);
    }
    printf("\n");

    printf("Evens: ");
    for (int i = 0; i < new_length; i++) {
        printf("%d ", evens[i]);
    }
    printf("\n");

    printf("Sum: %d\n", total);

    // Free allocated memory
    free(squared);
    free(evens);

    return 0;
}