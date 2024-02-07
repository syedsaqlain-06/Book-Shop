#pragma once

#include<list>
#include"book.h"


    void load_data(fstream &file,list<book> &l)           //Function to copy data from file to list:
    {       
            book b;
            file.read((char*)&b, sizeof(b));
            while (!file.eof())
            {      
                l.push_back(b);
                file.read((char*)&b, sizeof(b));
            }
    }

    void add_book(fstream &file, const int& n,list<book> &l)      //Function to add new books:
    {
        book b;
        for (int i = 0; i < n; i++)
        {
            b.input();
            file.write((const char*)&b, sizeof(b));
            l.push_back(b);
        }
    }

    list<book>::iterator show_book( const int& id,list<book> &l)   //Function to display one book record:
    {
        list<book>::iterator it;
        it = l.begin();    
        while (it != l.end())
        {
            if (it->id == id)
            {
                return it;                   
            }
            ++it;
        }
        it._Ptr = nullptr;
        return it;

    }

    void show_all(list<book>& l)                          //Function to display all records:
    {
        list<book>::iterator it;
        it = l.begin();
        while (it != l.end())
        {                                     
            it->display();
            ++it;
        }
    }

    list<book>::iterator change_price(fstream& file, const int& id, const int& new_price, list<book>& l)  //Function to change price of any book:
    {
        book b;
        list<book>::iterator it;
        it = l.begin();
        file.seekg(0, ios::beg);

        while (it != l.end() && !file.eof())
        {
            file.read((char*)&b, sizeof(b));
            if (it->id == id)
            {
                it->price = new_price;                  //To change price in list:

                file.seekp(sizeof(b) * -1, ios::cur);             // To change price in file: 
                file.write((const char*)&*it, sizeof(*it));

                return it;
            }
            ++it;
        } 
        
        it._Ptr = nullptr;    
        return it;
    }

    list<book>::iterator delete_book(fstream& file, const int& id, list<book>& l)        //Function to delete one record:
    {
        book b;
        list<book>::iterator it;
        bool flag = false;
        it = l.begin();
        while (it != l.end())
        {
            if (it->id == id)                   //
            {                                   //
                l.erase(it);                    //  Deleting record from list:
                flag = true;                    //
                break;                          //
            }
            ++it;
        }
        if (flag == false)
        {
            it._Ptr = nullptr;
            return it;
        }

        ofstream file2;

        file2.open("temp.bin", ios::out | ios::binary);
        if (file2.is_open())
        {
            file.read((char*)&b, sizeof(b));
            while (!file.eof())
            {                                                        //
                if (id != b.id)                                      //
                {                                                    //
                    file2.write((const char*)&b, sizeof(b));         //
                                                                     // Deleting record from file:
                }                                                    //
                file.read((char*)&b, sizeof(b));                     //
                                                                     //
            }
            file2.close();
            file.close();
            remove("shoprecord.bin");
            rename("temp.bin", "shoprecord.bin");
        }
        return it;
    }
   
    void delete_all(list<book>& l)                 // Function to delete all records:
    {
        ofstream file;

        l.clear();
        remove("shoprecord.bin");
        file.open("shoprecord.bin", ios::out | ios::binary);
        file.close();
    }

    void total_sales(const int& val, list<book>& l)           //Function to calculate total sales amount:
    {

        list<book>::reverse_iterator r_it;
        r_it = l.rbegin();
        r_it->sum_sales = r_it->sum_sales + val;

    }

    int show_total_sales(list<book>& l)                    //Function to display total sales amount:
    {
        if (l.empty())
        {
            return 0;
        }
        list<book>::reverse_iterator r_it;
        r_it = l.rbegin();
        return r_it->sum_sales;
    }

    list<book>::iterator sell(fstream& file, const int &id,const int &val, list<book>& l)   //Function for sell:
    {
        book b;
        list<book>::iterator it;
        it = l.begin();
        file.seekg(0, ios::beg);
        while (it != l.end() && !file.eof())
        {
            file.read((char*)&b, sizeof(b));
                                                           
            if (it->id == id)                              
            {                                              //
                if (it->stock > 0)                         // Maintaining the the quantity of books available to sell .             
                {                                          // reducing stock from list when sold:
                    if (it->stock - val >= 0)              //
                    {
                        it->stock = it->stock - val;
                        total_sales(it->price*val,l);        //Passing sales amount to total sales function:
                    }
                    else
                    {
                        throw("Not that much stock available to sell !. check the stock availability :");
                    }
                   
                }
                else
                {
                    throw("No more stock available! ");
                }

                file.seekp(sizeof(b) * -1, ios::cur);     
                file.write((const char*)&*it, sizeof(*it));         //  reducing stock from file when sold:
                                             

                file.seekp(sizeof(b) * -1, ios::end);                      //Updating total sales amount in file:
                file.write((const char*)&l.back(), sizeof(l.back()));

                return it;
            }
            ++it;

        } 
            it._Ptr = nullptr;
            return it;
    }

    list<book>::iterator purchased(fstream& file, const int &id, const int &val, list<book>& l)  //Function for purchased:
    {
        book b;
        list<book>::iterator it;
        it = l.begin();
        file.seekg(0, ios::beg);
        while(it!=l.end() && !file.eof())
        {
            file.read((char*)&b, sizeof(b));
                                                            
            if (it->id == id)                             
            {                                              
                it->stock = it->stock + val;                  // Adding stock in list when purchased:

                file.seekp(sizeof(b) * -1, ios::cur);             //Adding stock in file when purchased:                                                        //
                file.write((const char*)&*it, sizeof(*it));

                return it;
            }
            ++it;
        }
        
        
        it._Ptr = nullptr;
        return it;

    }
  

    list<book>::iterator update(fstream& file, int& id, list<book>& l)   //Function to update any record:
    {
        book b;
        list<book>::iterator it;
        it = l.begin();
        file.seekg(0, ios::beg);

        while (it != l.end() && !file.eof())
        {
            file.read((char*)&b, sizeof(b));
            if (it->id == id)
            {

                b.input();
                for (int i = 0; i < 20; i++)
                {
                   it->name[i] = b.name[i];                      //
                }                                                // Updating in list:
                it->id = b.id;                                   //
                it->price = b.price;
                it->stock = b.stock;

                file.seekp(sizeof(b) * -1, ios::cur);
                file.write((const char*)&b, sizeof(b));          //Updating in file:
                
                return it;
            }
            ++it;
         }

        it._Ptr = nullptr;
        return it;
    }


