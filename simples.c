#include <stdio.h>

// Imperative paradigm function to calculate the sum of two integers
int sum(int a, int b) {
    return a + b;
}

// Functional paradigm function using a function pointer
int functional_sum(int (*func)(int, int), int a, int b) {
    return func(a, b);
}

int main() {
    int a = 5;
    int b = 10;

    // Imperative approach
    int result_imperative = sum(a, b);
    printf("Imperative Sum: %d\n", result_imperative);

    // Functional approach
    int result_functional = functional_sum(sum, a, b);
    printf("Functional Sum: %d\n", result_functional);

    return 0;
}