#pragma once

using namespace std;

struct book
{
    char name[20];
    int id;
    int price;
    int stock;

    int sum_sales;

    book()
    {
        name[0] = '\0';
        id = 0;
        price = 0;
        stock = 0;
        sum_sales = 0;
    }

    void input()
    {
        cout << "Enter book name : ";
        cin >> name;
        cout << "Enter book ID   : ";
        cin >> id;
        cout << "Enter book price: ";
        cin >> price;
        cout << "Enter book stock: ";
        cin >> stock;

        cout << "-----------------------" << endl;
    }


    void display()
    {
        cout << "__________________" << endl;
        cout << "Book Name : " << name << endl;
        cout << "Book ID   : " << id << endl;
        cout << "Book price: " << price << endl;
        cout << "Book stock: " << stock << endl;
        cout << "__________________" << endl;

    }


};
