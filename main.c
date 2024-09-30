#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 100
#define MEMBER_FILE "members.txt"

typedef struct {
    char name[50];
    int member_id;
    int is_member;
    int birth_month; // เพิ่มฟิลด์เดือนเกิด
} Member;

typedef struct {
    char name[50];
    float price;
} OrderItem;

OrderItem ordered_items[MAX_ITEMS];
int item_count = 0;
Member current_member;

void register_member();
void load_member(int member_id);
int login_member();
float menu();
float select_item(const char* category, const char* items[], const float prices[], int count);
float pizza();
float customize_pizza();
float appetizers();
float drinks();
void print_receipt(float total_price);
void clear_input_buffer();
float discount_member(float total_price);

int main() {
    float total_price = 0.0;
    float discount = 0.0;
    int continue_shopping = 1;

    printf("Do you have an existing membership? (1 for Yes, 0 for No): ");
    int member_choice;
    while (scanf("%d", &member_choice) != 1 || (member_choice != 0 && member_choice != 1)) {
        printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
        clear_input_buffer();
    }

    if (member_choice == 1) {
        int login_success = login_member();
        if (!login_success) {
            printf("No matching member found.\n");
            printf("Do you want to register as a new member? (1 for Yes, 0 for No): ");
            int register_choice;
            while (scanf("%d", &register_choice) != 1 || (register_choice != 0 && register_choice != 1)) {
                printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
                clear_input_buffer();
            }
            if (register_choice == 1) {
                register_member();
            }
        }
    } else {
        printf("Do you want to register as a new member? (1 for Yes, 0 for No): ");
        int register_choice;
        while (scanf("%d", &register_choice) != 1 || (register_choice != 0 && register_choice != 1)) {
            printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
            clear_input_buffer();
        }
        if (register_choice == 1) {
            register_member();
        }
    }

    while (continue_shopping) {
        float item_price = menu();
        total_price += item_price;
        printf("Your current total price is: %.2f\n", total_price);
        printf("Do you want to choose another item? (1 for Yes, 0 for No): ");
        while (scanf("%d", &continue_shopping) != 1 || (continue_shopping != 0 && continue_shopping != 1)) {
            printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
            clear_input_buffer();
        }
    }

    discount = discount_member(total_price);
    total_price -= discount;

    print_receipt(total_price);
    printf("Thank you for your order!\n");
    return 0;
}

// เพิ่มการลงทะเบียนสมาชิกพร้อมเดือนเกิด
void register_member() {
    printf("\n--- Member Registration ---\n");
    printf("Enter your name: ");
    clear_input_buffer();
    fgets(current_member.name, sizeof(current_member.name), stdin);
    current_member.name[strcspn(current_member.name, "\n")] = 0;

    printf("Enter your member ID (number): ");
    while (scanf("%d", &current_member.member_id) != 1) {
        printf("Invalid input. Please enter a valid member ID (number): ");
        clear_input_buffer();
    }

    printf("Enter your birth month (1-12): ");
    while (scanf("%d", &current_member.birth_month) != 1 || current_member.birth_month < 1 || current_member.birth_month > 12) {
        printf("Invalid input. Please enter a valid birth month (1-12): ");
        clear_input_buffer();
    }

    current_member.is_member = 1;

    FILE *file = fopen(MEMBER_FILE, "a");
    if (file == NULL) {
        perror("Error opening file to save member information");
        return;
    }
    fprintf(file, "%s\n%d\n%d\n", current_member.name, current_member.member_id, current_member.birth_month);
    fclose(file);

    printf("Registration successful! Welcome, %s!\n\n", current_member.name);
}

// ปรับปรุงการโหลดข้อมูลสมาชิกให้โหลดเดือนเกิด
void load_member(int member_id) {
    FILE *file = fopen(MEMBER_FILE, "r");
    if (file == NULL) {
        current_member.is_member = 0;
        return;
    }

    char name[50];
    int id, birth_month;

    while (fgets(name, sizeof(name), file) != NULL) {
        name[strcspn(name, "\n")] = 0;
        if (fscanf(file, "%d\n%d\n", &id, &birth_month) == 2) {
            if (id == member_id) {
                strcpy(current_member.name, name);
                current_member.member_id = id;
                current_member.birth_month = birth_month;
                current_member.is_member = 1;
                fclose(file);
                return;
            }
        }
    }

    current_member.is_member = 0;
    fclose(file);
}

int login_member() {
    printf("Enter your member ID to log in: ");
    int member_id;
    while (scanf("%d", &member_id) != 1) {
        printf("Invalid input. Please enter a valid member ID (number): ");
        clear_input_buffer();
    }

    load_member(member_id);

    if (current_member.is_member) {
        printf("Login successful! Welcome back, %s!\n\n", current_member.name);
        return 1;
    } else {
        return 0;
    }
}

// ฟังก์ชันส่วนลดสมาชิก (ปรับปรุงให้ใช้เดือนเกิดได้)
float discount_member(float total_price) {
    float discount = 0.0;

    if (current_member.is_member) {
        printf("As a member, you get a 10%% discount!\n");
        discount += total_price * 0.10;
    }

    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int currentMonth = localTime->tm_mon + 1;

    if (current_member.birth_month == currentMonth && total_price >= 10) {
        printf("Happy Birthday Month!\nYou get an additional 15%% discount!\n");
        discount += total_price * 0.15;
    }

    return discount;
}

// ฟังก์ชันเมนู
float menu() {
    printf("\n--- Menu ---\n");
    printf("1. Pizza\n");
    printf("2. Customize Pizza\n");
    printf("3. Appetizers\n");
    printf("4. Drinks\n");
    printf("Choose an option: ");

    int choose_menu;

    while (scanf("%d", &choose_menu) != 1 || choose_menu < 1 || choose_menu > 4) {
        printf("Invalid input. Please enter a number between 1 and 4: ");
        clear_input_buffer();
    }

    switch (choose_menu) {
        case 1: return pizza();
        case 2: return customize_pizza();
        case 3: return appetizers();
        case 4: return drinks();
        default: return 0.0;
    }
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

float customize_pizza() {
    printf("\nYou chose to customize your pizza.\n");


    printf("1. Small ($10.00)\n");
    printf("2. Medium ($12.00)\n");
    printf("3. Large ($14.00)\n");
    printf("Choose a size:\n");
    int size_choice;
    while (scanf("%d", &size_choice) != 1 || size_choice < 1 || size_choice > 3) {
        printf("Invalid input. Please enter 1, 2, or 3: ");
        clear_input_buffer();
    }

    float base_price = 0.0;
    char size_name[20];

    switch (size_choice) {
        case 1:
            base_price = 10.00;
            strcpy(size_name, "Small");
            break;
        case 2:
            base_price = 12.00;
            strcpy(size_name, "Medium");
            break;
        case 3:
            base_price = 14.00;
            strcpy(size_name, "Large");
            break;
    }

    printf("Choose toppings (each $1.00):\n");
    printf("1. Pepperoni\n");
    printf("2. Mushrooms\n");
    printf("3. Onions\n");
    printf("4. Sausage\n");
    printf("5. Bacon\n");
    printf("6. Extra cheese\n");
    printf("7. Olives\n");
    printf("8. Green peppers\n");
    printf("[9 for Finish]\n");

    int topping_choice;
    int topping_count = 0;
    char toppings[100] = "";

    while (1) {
        printf("Select a topping or finish: ");
        while (scanf("%d", &topping_choice) != 1 || topping_choice < 1 || topping_choice > 9) {
            printf("Invalid input. Please select a topping from 1-9: ");
            clear_input_buffer();
        }
        if (topping_choice == 9) break;

        switch (topping_choice) {
            case 1: strcat(toppings, "Pepperoni, "); topping_count++; break;
            case 2: strcat(toppings, "Mushrooms, "); topping_count++; break;
            case 3: strcat(toppings, "Onions, "); topping_count++; break;
            case 4: strcat(toppings, "Sausage, "); topping_count++; break;
            case 5: strcat(toppings, "Bacon, "); topping_count++; break;
            case 6: strcat(toppings, "Extra cheese, "); topping_count++; break;
            case 7: strcat(toppings, "Olives, "); topping_count++; break;
            case 8: strcat(toppings, "Green peppers, "); topping_count++; break;
        }
    }

    if (topping_count > 0) {
        toppings[strlen(toppings) - 2] = '\0';
    }

    float total_price = base_price + (topping_count * 1.00);
    snprintf(ordered_items[item_count].name, sizeof(ordered_items[item_count].name), "Customized Pizza (%s) with %s", size_name, topping_count > 0 ? toppings : "no toppings");
    ordered_items[item_count].price = total_price;
    item_count++;

    printf("You customized a %s pizza with the following toppings: %s\n", size_name, topping_count > 0 ? toppings : "No toppings");
    printf("Total price for your customized pizza: %.2f\n", total_price);
    return total_price;
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

float select_item(const char* category, const char* items[], const float prices[], int count) {
    printf("\n--- %s List ---\n", category);

    for (int i = 0; i < count; i++) {
        printf("%d. %s : $%.2f\n", i + 1, items[i], prices[i]);
    }

    printf("Choose an option: ");
    int choice;

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Please enter a number between 1 and %d: ", count);
        clear_input_buffer();
    }

    printf("You chose %s.\n", items[choice - 1]);

    strcpy(ordered_items[item_count].name, items[choice - 1]);
    ordered_items[item_count].price = prices[choice - 1];
    item_count++;

    return prices[choice - 1];
}

// ฟังก์ชันพิมพ์ใบเสร็จ
void print_receipt(float total_price) {
    time_t t;
    time(&t);
    struct tm *timeinfo = localtime(&t);

    char date_str[11];
    strftime(date_str, sizeof(date_str), "%d/%m/%Y", timeinfo);

    printf("\n--- Receipt ---\n");
    printf("Restaurant: Pizza Place\n");
    printf("Date: %s\n", date_str);
    if (current_member.is_member) {
        printf("Member: %s (ID: %d)\n", current_member.name, current_member.member_id);
    }
    printf("Items Ordered:\n");

    for (int i = 0; i < item_count; i++) {
        printf("%d. %s - $%.2f\n", i + 1, ordered_items[i].name, ordered_items[i].price);
    }

    printf("Total Price: $%.2f\n", total_price);
    printf("--------------------\n\n");
}

// ฟังก์ชันล้างบัฟเฟอร์
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
