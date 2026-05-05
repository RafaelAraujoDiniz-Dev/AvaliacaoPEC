#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    float price;
} Product;

Product inventory[MAX_PRODUCTS];
int productCount = 0;

void addProduct();
void listProducts();
void searchProduct();
void deleteProduct();
void calculateTotalValue();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addProduct(); break;
            case 2: listProducts(); break;
            case 3: searchProduct(); break;
            case 4: deleteProduct(); break;
            case 5: calculateTotalValue(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid option, try again.\n");
        }
    } while (choice != 6);
    return 0;
}

void displayMenu() {
    printf("\n1. Add Product\n");
    printf("2. List Products\n");
    printf("3. Search Product\n");
    printf("4. Delete Product\n");
    printf("5. Calculate Total Inventory Value\n");
    printf("6. Exit\n");
}

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory full! Cannot add more products.\n");
        return;
    }
    Product p;
    printf("Enter product ID: ");
    scanf("%d", &p.id);
    printf("Enter product name: ");
    scanf("%s", p.name);
    printf("Enter product price: ");
    scanf("%f", &p.price);
    inventory[productCount++] = p;
    printf("Product added successfully!\n");
}

void listProducts() {
    printf("\nProducts in inventory:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", inventory[i].id, inventory[i].name, inventory[i].price);
    }
}

void searchProduct() {
    int id;
    printf("Enter product ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            printf("Found product: ID: %d, Name: %s, Price: %.2f\n", inventory[i].id, inventory[i].name, inventory[i].price);
            return;
        }
    }
    printf("Product not found.\n");
}

void deleteProduct() {
    int id;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            for (int j = i; j < productCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            productCount--;
            printf("Product deleted successfully!\n");
            return;
        }
    }
    printf("Product not found.\n");
}

void calculateTotalValue() {
    float total = 0.0;
    for (int i = 0; i < productCount; i++) {
        total += inventory[i].price;
    }
    printf("Total inventory value: %.2f\n", total);
}