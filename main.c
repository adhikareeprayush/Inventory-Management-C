#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int itemID;
    char itemName[50];
    int quantity;
    float price;
} InventoryItem;

void addItem();
void displayItems();
void searchItem();
void updateItem();
void deleteItem();

FILE *fp;

int main()
{
    int choice;

    while (1)
    {
        printf("\nInventory Management System\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Search Item\n");
        printf("4. Update Item\n");
        printf("5. Delete Item\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addItem();
            break;
        case 2:
            displayItems();
            break;
        case 3:
            searchItem();
            break;
        case 4:
            updateItem();
            break;
        case 5:
            deleteItem();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void addItem()
{
    InventoryItem item;
    fp = fopen("inventory.dat", "ab"); // Append to binary file

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID: ");
    scanf("%d", &item.itemID);
    printf("Enter Item Name: ");
    scanf("%s", item.itemName);
    printf("Enter Quantity: ");
    scanf("%d", &item.quantity);
    printf("Enter Price: ");
    scanf("%f", &item.price);

    fwrite(&item, sizeof(InventoryItem), 1, fp);
    fclose(fp);
    printf("Item added successfully!\n");
}

void displayItems()
{
    InventoryItem item;
    fp = fopen("inventory.dat", "rb"); // Read binary file

    if (fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\n%-10s %-20s %-10s %-10s\n", "ItemID", "ItemName", "Quantity", "Price");
    while (fread(&item, sizeof(InventoryItem), 1, fp))
    {
        printf("%-10d %-20s %-10d %-10.2f\n", item.itemID, item.itemName, item.quantity, item.price);
    }
    fclose(fp);
}

void searchItem()
{
    int id, found = 0;
    InventoryItem item;

    fp = fopen("inventory.dat", "rb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID to search: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(InventoryItem), 1, fp))
    {
        if (item.itemID == id)
        {
            printf("Item Found:\n");
            printf("ID: %d, Name: %s, Quantity: %d, Price: %.2f\n",
                   item.itemID, item.itemName, item.quantity, item.price);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Item with ID %d not found!\n", id);
    }
    fclose(fp);
}

void updateItem()
{
    int id, found = 0;
    InventoryItem item;

    FILE *tempFile = fopen("temp.dat", "wb");
    fp = fopen("inventory.dat", "rb");

    if (fp == NULL || tempFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID to update: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(InventoryItem), 1, fp))
    {
        if (item.itemID == id)
        {
            printf("Enter new Quantity: ");
            scanf("%d", &item.quantity);
            printf("Enter new Price: ");
            scanf("%f", &item.price);
            found = 1;
        }
        fwrite(&item, sizeof(InventoryItem), 1, tempFile);
    }

    fclose(fp);
    fclose(tempFile);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
        printf("Item updated successfully!\n");
    else
        printf("Item with ID %d not found!\n", id);
}

void deleteItem()
{
    int id, found = 0;
    InventoryItem item;

    FILE *tempFile = fopen("temp.dat", "wb");
    fp = fopen("inventory.dat", "rb");

    if (fp == NULL || tempFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID to delete: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(InventoryItem), 1, fp))
    {
        if (item.itemID == id)
        {
            found = 1;
            continue;
        }
        fwrite(&item, sizeof(InventoryItem), 1, tempFile);
    }

    fclose(fp);
    fclose(tempFile);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
        printf("Item deleted successfully!\n");
    else
        printf("Item with ID %d not found!\n", id);
}
