#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float price;
} Product;

// Function to print a product (Imperative Approach)
void printProduct(Product p) {
    printf("Product Name: %s, Price: %.2f\n", p.name, p.price);
}

// Function to create a product (Functional Approach)
Product createProduct(const char* name, float price) {
    Product p;
    strncpy(p.name, name, 49);
    p.name[49] = '\0'; // Ensures null termination
    p.price = price;
    return p;
}

// Test function
void runTests() {
    Product p1 = createProduct("Apple", 0.60);
    Product p2 = createProduct("Banana", 0.50);
    
    printf("Testing Products:\n");
    printProduct(p1);
    printProduct(p2);
    
    // Additional test cases can be added here
}

int main() {
    runTests();
    return 0;
}