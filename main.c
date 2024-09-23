#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 100  // Maximum number of items that can be ordered

// Structure to store ordered items
typedef struct {
    char name[50];
    float price;
} OrderItem;

// Global array to store the ordered items
OrderItem ordered_items[MAX_ITEMS];
int item_count = 0;

// Function declarations
float menu();
float select_item(const char* category, const char* items[], const float prices[], int count);
float pizza();
float pizza_choose();
float appetizers();
float drinks();
void print_receipt(float total_price);  // New function to print the receipt
void clear_input_buffer();  // Function to clear the input buffer

int main() {
    float total_price = 0.0;
    int continue_shopping = 1;
    printf("test");

    while (continue_shopping) {
        float item_price = menu();
        total_price += item_price;
        printf("Your current total price is: %.2f\n", total_price);
        printf("Do you want to choose another item? (1 for Yes, 0 for No): ");

        // Input validation for continue_shopping
        while (scanf("%d", &continue_shopping) != 1 || (continue_shopping != 0 && continue_shopping != 1)) {
            printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
            clear_input_buffer();  // Clear buffer if input is invalid
        }
    }

    // Print the receipt when shopping is done
    print_receipt(total_price);

    printf("Thank you for your order!\n");
    return 0;
}

float menu() {
    printf("Option list\n");
    printf("1. Pizza\n");
    printf("2. Customize Pizza\n");
    printf("3. Appetizers\n");
    printf("4. Drinks\n");
    printf("Choose an option: ");

    int choose_menu;

    // Input validation for menu selection
    while (scanf("%d", &choose_menu) != 1 || choose_menu < 1 || choose_menu > 4) {
        printf("Invalid input. Please enter a number between 1 and 4: ");
        clear_input_buffer();  // Clear buffer if input is invalid
    }

    switch (choose_menu) {
        case 1: return pizza();
        case 2: return pizza_choose();
        case 3: return appetizers();
        case 4: return drinks();
        default: return 0.0;  // Shouldn't be reached due to validation
    }
}

float select_item(const char* category, const char* items[], const float prices[], int count) {
    printf("You chose %s.\n", category);
    printf("---%s list---\n", category);

    for (int i = 0; i < count; i++) {
        printf("%d. %s : $%.2f\n", i + 1, items[i], prices[i]);
    }

    printf("Choose an option: ");
    int choice;

    // Input validation for item selection
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Please enter a number between 1 and %d: ", count);
        clear_input_buffer();  // Clear buffer if input is invalid
    }

    printf("You chose %s.\n", items[choice - 1]);

    // Store the selected item in the global order array
    strcpy(ordered_items[item_count].name, items[choice - 1]);
    ordered_items[item_count].price = prices[choice - 1];
    item_count++;

    return prices[choice - 1];
}

float pizza() {
    const char* pizza_items[] = {
        "Margherita", "Pepperoni", "Vegetarian", "Hawaiian", "BBQ Chicken"
    };
    const float pizza_prices[] = {
        8.50, 9.00, 8.75, 9.25, 10.00
    };
    return select_item("Pizza", pizza_items, pizza_prices, 5);
}

float pizza_choose() {
    printf("You chose to customize your pizza. Price will vary.\n");

    // Store customized pizza in order
    strcpy(ordered_items[item_count].name, "Customized Pizza");
    ordered_items[item_count].price = 12.00;
    item_count++;

    return 12.00;
}

float appetizers() {
    const char* appetizer_items[] = {
        "Garlic Knots", "Mozzarella Sticks", "Bruschetta",
        "Stuffed Jalapenos", "Fried Calamari", "Chicken Wings",
        "Onion Rings", "Fried Ravioli"
    };
    const float appetizer_prices[] = {
        3.00, 5.00, 4.75, 9.25, 2.50, 7.00, 2.75, 2.00
    };
    return select_item("Appetizers", appetizer_items, appetizer_prices, 8);
}

float drinks() {
    const char* drink_items[] = {
        "Soda", "Water", "Juice"
    };
    const float drink_prices[] = {
        1.50, 1.00, 2.50
    };
    return select_item("Drinks", drink_items, drink_prices, 3);
}

// New function to print the receipt
void print_receipt(float total_price) {
    // Get current time and date
    time_t t;
    time(&t);
    struct tm *timeinfo = localtime(&t);

    // Format the date as day/month/year
    char date_str[11];
    strftime(date_str, sizeof(date_str), "%d/%m/%Y", timeinfo);

    printf("\n--- Receipt ---\n");
    printf("Restaurant: Pizza Place\n");
    printf("Date: %s\n", date_str);  // Print formatted date
    printf("Items Ordered:\n");

    // Print ordered items
    for (int i = 0; i < item_count; i++) {
        printf("%d. %s - $%.2f\n", i + 1, ordered_items[i].name, ordered_items[i].price);
    }

    printf("Total Price: $%.2f\n", total_price);
    printf("--------------------\n\n");
}

// Function to clear the input buffer
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
