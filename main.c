#include <stdio.h>

void displayMenu() {
    printf("Product Registration System\n");
    printf("1. Imperative Implementation\n");
    printf("2. Functional Implementation\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    displayMenu();
    scanf("%d", &choice);
    // Additional logic can be added here based on user choice.
    return 0;
}