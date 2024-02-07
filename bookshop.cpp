// bookshop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<list>
#include"bookshop.h"

using namespace std;

int main()
{
    list<book> l;
    list<book>::iterator it;
    fstream file;

    int num;
    int book_id;
    char chose;
   
    file.open("shoprecord.bin", ios::in | ios::binary);
    if (file.is_open())
    {
        load_data(file,l);
        file.close();
    }
    else
    {
        file.open("shoprecord.bin", ios::out | ios::binary);
        if (file.is_open())
        {
            cout << "File created  " << endl;
            file.close();
        }
        else
        {
            cout << "File creating failed !" << endl;
        }
        

    }

    do {

        cout << "Enter 1 to add new books: " << endl;
        cout << "Enter 2 to display books: " << endl;
        cout << "Enter 3 for purchased   : " << endl;
        cout << "Enter 4 to change price of any book: " << endl;
        cout << "Enter 5 to sell book: " << endl;
        cout << "Enter 6 to delete book: " << endl;
        cout << "Enter 7 for total sales : " << endl;
        cout << "Enter 8 to update any book:" << endl;

        cin >> num;


        switch (num)
        {
        case 1:
            int n;
            file.open("shoprecord.bin", ios::app | ios::binary);
            if (file.is_open())
            {
                cout << "Enter how many book records you want to enter: " << endl;
                cin >> n;
                add_book(file, n,l);
                file.close();

            }
            else
            {
                cout << "File not found!" << endl;
            }

            break;
        case 2:

            if (l.empty())
            {
                cout << "No record found to display! " << endl;
            }
            else
            {
                cout << "Enter 1 to to display one record: " << endl;
                cout << "Enter 2 to to display all record: " << endl;
                cin >> num;

                switch (num)
                {
                case 1:
                    cout << "Enter book ID: " << endl;
                    cin >> book_id;
                    it = show_book(book_id,l);
                    if (it._Ptr != nullptr)
                    {
                        it->display();
                    }
                    else
                    {
                        cout << "Book with ID \"" << book_id << "\" not found! " << endl;
                    }
                    break;

                case 2:

                    show_all(l);

                    break;
                }
            }

            break;

        case 3:

            file.open("shoprecord.bin", ios::in | ios::out | ios::ate | ios::binary);
            if (file.is_open())
            {
                int quantity;
                cout << "Enter purchased book ID: " << endl;
                cin >> book_id;
                cout << "Enter number of books purchased: " << endl;
                cin >> quantity;

                it = purchased(file, book_id, quantity,l);
                if (it._Ptr == nullptr)
                {
                    cout << "Book with ID \"" << book_id << "\" not found! " << endl;
                }
                else
                {
                    cout << "Stock updated successfully : " << endl;
                }
            }
            else
            {
                cout << "File not found! ";
            }
            break;

        case 4:

            int new_price;
            file.open("shoprecord.bin", ios::in | ios::out | ios::ate | ios::binary);
            if (file.is_open())
            {
                cout << "Enter book ID : " << endl;
                cin >> book_id;
                cout << "Enter book price [new price] :" << endl;
                cin >> new_price;
                it = change_price(file, book_id, new_price,l);
                if (it._Ptr == nullptr)
                {
                    cout << "Book with ID \"" << book_id << "\" not found! " << endl;
                }
                else
                {
                    cout << "Price updated successfully :" << endl;
                }
            }
            file.close();
            break;

        case 5:

            file.open("shoprecord.bin", ios::in | ios::out | ios::ate | ios::binary);
            if (file.is_open())
            {
                int sold;
                cout << "Enter sold book ID : " << endl;
                cin >> book_id;
                cout << "Enter number of books sold: " << endl;
                cin >> sold;
                try
                {
                    it = sell(file, book_id, sold,l);

                    if (it._Ptr == nullptr)
                    {
                        cout << "Book with ID \"" << book_id << "\" not found! " << endl;
                    }
                }
                catch (const char* msg)
                {
                    cout << msg << endl;
                }
                file.close();
            }
            else
            {
                cout << "File not found! " << endl;
            }

            break;

        case 6:
            if (l.empty())
            {
                cout << "No record found to delete :" << endl;
            }
            else
            {

                cout << "Enter 1 to delete one record :" << endl;
                cout << "Enter 2 to delete all record :" << endl;
                cin >> num;

                switch (num)
                {
                case 1:
                    file.open("shoprecord.bin", ios::in | ios::binary);
                    if (file.is_open())
                    {
                        cout << "Enter book ID to delete its record: " << endl;
                        cin >> book_id;
                        it = delete_book(file, book_id,l);
                        if (it._Ptr == nullptr)
                        {
                            cout << "Book with ID \"" << book_id << "\" not found! " << endl;
                        }
                        else
                        {
                            cout << "Book record deleted successfully :" << endl;
                        }
                    }
                    file.close();

                    break;

                case 2:

                    char confirm;
                    cout << "Enter \"c\" to confirm  delete all records or any other key to cancel : " << endl;
                    cin >> confirm;
                    if (confirm == 'c' || confirm == 'C')
                    {
                        delete_all(l);
                        cout << "All book records deleted successfully: " << endl;
                    }
                    break;
                }

                break;
            }
            break;

        case 7:

            cout << "----------------------" << endl;
             cout << "Total sales= Rs " << show_total_sales(l) << endl;
            cout << "----------------------" << endl;
             break;

        case 8:

            file.open("shoprecord.bin", ios::in | ios::out | ios::ate | ios::binary);
            if (file.is_open())
            {
                cout << "Enter book ID:" << endl;
                cin >> book_id;

                it = update(file, book_id,l);
                if (it._Ptr == nullptr)
                {
                    cout << "Book with ID \"" << book_id << "\" not found: " << endl;
                }
                else
                {
                    cout << "Record updated successfully: " << endl;
                }


                file.close();
            }
            else
            {
                cout << "File not found! " << endl;
            }
            break;

        }   
        
        cout << "Enter \"Y\" for main menu or any other key to terminate :" << endl;
        cin >> chose;

    } while (chose == 'Y' || chose == 'y');
     

    return 0;
}


