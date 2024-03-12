#include <iostream>
#include <fstream>
using namespace std;

class temp
{
    string itemID, itemName;             // Data members to store product details
    int itemQuantity, itemPrice;         // Data members to store product quantity and price
    fstream file, file1;                 // File streams for reading and writing data
    int totalAmount, quantity, itemRate; // Variables to calculate total purchase amount
    string search;                       // Variable to store user input for product search
    char _choice;                        // Variable to store user choice

public:
    void addProduct(string username, string password); // Function to add a new product
    void viewProduct(void);                            // Function to view all products
    void buyProduct(void);                             // Function to buy a product
} obj;

// Function to authenticate store executive
bool authenticate(string username, string password)
{
    return (username == "executive" && password == "password");
}

// Main function
int main()
{
    char choice;

    cout << "Are you a store executive? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (authenticate(username, password))
        {
            cout << "Login successful!" << endl;
            cout << "Press A to add product" << endl;
            cin >> choice;
            if (choice == 'A' || choice == 'a')
            {
                obj.addProduct(username, password); // Call addProduct function
            }
        }
        else
        {
            cout << "Invalid username or password. Access denied." << endl;
        }
    }
    else
    {
        cout << "press 1 --> Start Shopping" << endl;
        cout << "press 0 --> Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            obj.viewProduct(); // Call viewProduct function
            obj.buyProduct();  // Call buyProduct function
            break;
        case '0':
            return 0;
        default:
            cout << "Invalid Selection...!";
            break;
        }
    }

    return 0;
}

// Function to add a new product
void temp ::addProduct(string username, string password)
{
    if (!authenticate(username, password))
    {
        cout << "Unauthorized access! Only store executives are allowed to add products." << endl;
        return;
    }

    cout << "Enter Product ID :: ";
    cin >> itemID;
    cout << "Enter Product Name :: ";
    cin >> itemName;
    cout << "Enter Product Quantity :: ";
    cin >> itemQuantity;
    cout << "Enter Product Price :: ";
    cin >> itemPrice;

    fstream file("data.txt", ios::in | ios::out);

    bool productExists = false;

    while (file >> search >> itemName >> quantity >> itemPrice)
    {
        if (search == itemID)
        {
            itemQuantity += quantity;
            file.seekp(file.tellg());
            file << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
            productExists = true;
            break;
        }
    }

    file.close();

    if (!productExists)
    {
        ofstream outFile("data.txt", ios::app);
        outFile << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
        outFile.close();
    }
}

// Function to view all products
void temp ::viewProduct()
{
    file.open("data.txt", ios::in);
    while (file >> itemID >> itemName >> itemQuantity >> itemPrice)
    {
        cout << "--------------------------" << endl;
        cout << "Product Id\t\tProduct Name\t\tQuantity\t\tProduct Price" << endl;
        cout << itemID << "\t\t\t" << itemName << "\t\t\t" << itemQuantity << "\t\t\t" << itemPrice << endl;
        cout << "--------------------------" << endl;
    }
    file.close();
}

// Function to buy a product
void temp ::buyProduct()
{
    _choice = 'y';

    while (_choice == 'y' || _choice == 'Y')
    {
        totalAmount = 0;

        file.open("data.txt", ios::in);
        file1.open("temp.txt", ios::out | ios::app);
        cout << "Enter Product ID :: ";
        cin >> search;
        cout << "Enter Quantity :: ";
        cin >> quantity;

        bool found = false;

        while (file >> itemID >> itemName >> itemQuantity >> itemPrice)
        {
            if (itemID == search)
            {
                found = true;

                if (quantity <= itemQuantity)
                {
                    itemQuantity -= quantity;
                    file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;

                    itemRate = quantity * itemPrice;
                    totalAmount += itemRate;

                    cout << "Purchase successful!" << endl;
                }
                else
                {
                    cout << "Insufficient quantity available!" << endl;
                }
            }
            else
            {
                file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
            }
        }

        file.close();
        file1.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");

        if (!found)
        {
            cout << "Product not found in inventory!" << endl;
        }
        else
        {
            cout << "------Payment Bill------" << endl;
            cout << "Total Purchase Amount :: " << totalAmount << endl;
            cout << "------------------------" << endl;
        }

        cout << "Available Quantity: " << itemQuantity << endl;

        cout << "\n Continue Shopping ? (Y / N) ";
        cin >> _choice;

        if (_choice != 'y' && _choice != 'Y')
        {
            break;
        }
    }
}
