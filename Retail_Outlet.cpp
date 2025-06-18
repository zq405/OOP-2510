#include <iostream>
#include<string>
using namespace std;

class Product 
{
    protected:
        string name;
        double price;
    public:
        Product():name(""),price(0.0){}
        Product (string n,double p):name(n),price(p){}

        Product(const Product& other): name(other.name),price(other.price){}
        ~Product() {}
        virtual void display() 
        {
            cout << "Item: " << name << endl << "Price:RM " << price << endl;
        }
        friend double calTotal(const Product& item);
};

class FoodItem :public Product 
{
    private:
        string cuisine;
    public:
        FoodItem():cuisine(""){}
        FoodItem(string n,double p,string c):Product(n,p),cuisine(c){}
        FoodItem(const FoodItem& other): Product(other),cuisine(other.cuisine){}
        ~FoodItem(){}
        void display()const 
        {
            cout << "Food Item : " << name << endl << "Price :RM" << price << endl << "Cuisine: " << cuisine << endl;
        }
};

class BeverageItem :public Product 
{
    private:
        bool isAlcoholic;
    public:
        BeverageItem():isAlcoholic(""){}
        BeverageItem(string n,double p,bool a):Product(n,p),isAlcoholic(a){}
        BeverageItem(const BeverageItem& other): Product(other),isAlcoholic(other.isAlcoholic){}
        ~BeverageItem(){}
        void display() override
        {
            cout<<"Beverage Item : "<<name<<endl;
            cout<<"Price : RM "<<price<<endl;
            cout<<
        }

};
