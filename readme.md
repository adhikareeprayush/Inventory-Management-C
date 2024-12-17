# **Inventory Management System in C**

This Inventory Management System allows users to manage a collection of inventory items. The system enables users to **add**, **display**, **search**, **update**, and **delete** inventory records stored in a binary file (`inventory.dat`).

---

## **Features**

- **Add Item**: Add a new item to the inventory.
- **Display Items**: View all inventory items with their details.
- **Search Item**: Search for an item based on its ID.
- **Update Item**: Modify the quantity and price of an existing item.
- **Delete Item**: Remove an item from the inventory.
- **Exit**: Exit the program.

---

## **Program Structure**

The program is divided into several functions:

| **Function**     | **Purpose**                                                         |
| ---------------- | ------------------------------------------------------------------- |
| `addItem()`      | Adds a new item to the inventory file.                              |
| `displayItems()` | Reads and displays all items stored in the file.                    |
| `searchItem()`   | Searches for an item based on its ID and displays its details.      |
| `updateItem()`   | Updates the quantity and price of an existing item based on its ID. |
| `deleteItem()`   | Deletes an item from the inventory file based on its ID.            |

---

## **Data Structure**

The program uses a **structure** named `InventoryItem` to store item details:

```c
typedef struct {
    int itemID;            // Unique ID for each item
    char itemName[50];     // Name of the item
    int quantity;          // Quantity in stock
    float price;           // Price of the item
} InventoryItem;
```

Each record includes:

- `itemID`: A unique integer identifier for the item.
- `itemName`: The name of the inventory item (string).
- `quantity`: The quantity of the item in stock.
- `price`: The price of the item.

The data is stored persistently in a binary file called `inventory.dat`.

---

## **Function Descriptions**

### 1. **`addItem()`**

- Appends a new item to the inventory file.
- Prompts the user for:
  - Item ID
  - Item Name
  - Quantity
  - Price
- Writes the data to the file using `fwrite()` in **binary append mode** (`ab`).

**File Mode Used**: `ab`  
**File Access**: Appends data without overwriting the existing file.

---

### 2. **`displayItems()`**

- Reads all the items from the file and displays them in a formatted table.
- Uses `fread()` to read the binary data.

**File Mode Used**: `rb`  
**File Access**: Reads the file content without modifying it.

---

### 3. **`searchItem()`**

- Searches for an item based on its **ID**.
- Reads through the file and compares each record's `itemID` with the user input.
- If found, it displays the item details; otherwise, it prints an error message.

**File Mode Used**: `rb`  
**File Access**: Reads the file without making changes.

---

### 4. **`updateItem()`**

- Updates the **quantity** and **price** of an existing item based on its ID.
- Logic:
  - Reads all records from the `inventory.dat` file.
  - Updates the matching record and writes the updated records to a **temporary file** (`temp.dat`).
  - Replaces the original file with the temporary file.

**File Modes Used**:

- `rb` (Read from the original file)
- `wb` (Write to a temporary file)

**File Access**:

- Ensures data integrity by working with a temporary file.

---

### 5. **`deleteItem()`**

- Deletes an item from the file based on its ID.
- Logic:
  - Reads all records from `inventory.dat`.
  - Copies all records **except the one to be deleted** into a **temporary file** (`temp.dat`).
  - Replaces the original file with the temporary file.

**File Modes Used**:

- `rb` (Read from the original file)
- `wb` (Write to a temporary file)

---

### 6. **`main()`**

- Displays a menu with options for the user.
- Based on the user's choice, it calls the appropriate function:
  - Add Item
  - Display Items
  - Search Item
  - Update Item
  - Delete Item
  - Exit
- Continuously loops until the user selects "Exit".

---

## **Program Flow**

1. **User Input**:  
   The user selects an operation from the menu (Add, Display, Search, Update, Delete).

2. **File Handling**:  
   The program opens `inventory.dat` using appropriate modes:

   - `ab` for appending new records.
   - `rb` for reading existing records.
   - `wb` for overwriting or creating new files.

3. **Temporary File (for Update/Delete)**:  
   When updating or deleting items, a **temporary file** (`temp.dat`) is used to ensure data integrity:

   - Data is first written to `temp.dat`.
   - The original file is deleted and replaced with `temp.dat`.

4. **Output**:  
   Based on the operation, the program either:

   - Displays the inventory.
   - Searches for an item.
   - Updates or deletes an item.

5. **Exit**:  
   The program exits cleanly when the user chooses option `6`.

---

## **How to Compile and Run**

1. **Save the Code**:  
   Save the program to a file, e.g., `inventory.c`.

2. **Compile the Program**:  
   Use a C compiler (e.g., GCC) to compile the program:

   ```bash
   gcc inventory.c -o inventory
   ```

3. **Run the Program**:  
   Execute the compiled file:

   ```bash
   ./inventory
   ```

4. **Follow the Menu**:
   - Choose an option (1-6).
   - Provide input as prompted.

---

## **File Used**

- **`inventory.dat`**:  
   A binary file that stores all the inventory records persistently.

---

## **Example Run**

```
Inventory Management System
1. Add Item
2. Display Items
3. Search Item
4. Update Item
5. Delete Item
6. Exit
Enter your choice: 1

Enter Item ID: 101
Enter Item Name: Pen
Enter Quantity: 50
Enter Price: 5.5
Item added successfully!
```

---

## **Notes**

- The program uses **binary files** for efficiency and data integrity.
- It ensures no data is lost during updates and deletions by using a temporary file (`temp.dat`).
- Proper error handling ensures the program does not crash if the file is missing or corrupted.

---

## **Possible Enhancements**

- Add input validation for negative quantities and prices.
- Implement sorting functionality (e.g., sort by name or ID).
- Improve file handling for large datasets.

---
