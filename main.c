#include <stdio.h>
#include <stdlib.h>

float menu();
float pizza();
float pizza_choose();
float appetizers();
float drinks();
int membership();

int choose_menu, choose_pizza, choose_appetizers;

int main() {
    float total_price = 0.0;
    int continue_shopping = 1;

    printf("Welcome to Pizza Shop \n");
    while (continue_shopping) {
        float item_price = menu();
        total_price += item_price;
        printf("Your current total price is: %.2f\n", total_price);
        printf("Do you want to choose another item? (1 for Yes, 0 for No): ");
        scanf("%d", &continue_shopping);
    }

    printf("\n--Your final total price is: %.2f--\n", total_price);
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
    scanf("%d", &choose_menu);

    if (choose_menu == 1) return pizza();
    else if (choose_menu == 2) return pizza_choose();
    else if (choose_menu == 3) return appetizers();
    else if (choose_menu == 4) return drinks();
    else {
        printf("Invalid choice\n");
        return 0.0;
    }
}

float pizza() {
    printf("You chose pizza.\n\n");
    printf("---Pizza list---\n");
    printf("1. Margherita : $8.50\n");
    printf("2. Pepperoni : $9.00\n");
    printf("3. Vegetarian : $8.75\n");
    printf("4. Hawaiian : $9.25\n");
    printf("5. BBQ Chicken : $10.00\n");
    printf("Choose an option: ");
    scanf("%d", &choose_pizza);

    if (choose_pizza == 1) {
        printf("You chose Margherita Pizza.\n");
        return 8.50;
    }
    else if (choose_pizza == 2) {
        printf("You chose Pepperoni Pizza.\n");
        return 9.00;
    }
    else if (choose_pizza == 3) {
        printf("You chose Vegetarian Pizza.\n");
        return 8.75;
    }
    else if (choose_pizza == 4) {
        printf("You chose Hawaiian Pizza.\n");
        return 9.25;
    }
    else if (choose_pizza == 5) {
        printf("You chose BBQ Chicken Pizza.\n");
        return 10.00;
    }
    else {
        printf("Invalid choice\n");
        return pizza();
    }
}

float pizza_choose() {
    printf("You chose to customize your pizza. Price will vary.\n");
    return 12.00;
}

float appetizers() {
    printf("You chose appetizers.\n");
    printf("---Appetizers list---\n");
    printf("1. Garlic Knots : $3.00\n");
    printf("2. Mozzarella Sticks : $5.00\n");
    printf("3. Bruschetta : $4.75\n");
    printf("4. Stuffed Jalapenos : $9.25\n");
    printf("5. Fried Calamari : $2.50\n");
    printf("6. Chicken Wings : $7.00\n");
    printf("7. Onion Rings : $2.75\n");
    printf("8. Fried Ravioli : $2.00\n");
    printf("Choose an option: ");
    scanf("%d", &choose_appetizers);

    if (choose_appetizers == 1) {
        printf("You chose Garlic Knots.\n");
        return 3.00;
    }
    else if (choose_appetizers == 2) {
        printf("You chose Mozzarella Sticks.\n");
        return 5.00;
    }
    else if (choose_appetizers == 3) {
        printf("You chose Bruschetta.\n");
        return 4.75;
    }
    else if (choose_appetizers == 4) {
        printf("You chose Stuffed Jalapenos.\n");
        return 9.25;
    }
    else if (choose_appetizers == 5) {
        printf("You chose Fried Calamari.\n");
        return 2.50;
    }
    else if (choose_appetizers == 6) {
        printf("You chose Chicken Wings.\n");
        return 7.00;
    }
    else if (choose_appetizers == 7) {
        printf("You chose Onion Rings.\n");
        return 2.75;
    }
    else if (choose_appetizers == 8) {
        printf("You chose Fried Ravioli.\n");
        return 2.00;
    }
    else {
        printf("Invalid choice\n");
        return appetizers();
    }
}

float drinks() {
    printf("You chose drinks.\n");
    printf("---Drinks list---\n");
    printf("1. Soda : $1.50\n");
    printf("2. Water : $1.00\n");
    printf("3. Juice : $2.50\n");
    printf("Choose an option: ");
    int choose_drink;
    scanf("%d", &choose_drink);

    if (choose_drink == 1) {
        printf("You chose Soda.\n");
        return 1.50;
    }
    else if (choose_drink == 2) {
        printf("You chose Water.\n");
        return 1.00;
    }
    else if (choose_drink == 3) {
        printf("You chose Juice.\n");
        return 2.50;
    }
    else {
        printf("Invalid choice\n");
        return drinks();
    }
}
