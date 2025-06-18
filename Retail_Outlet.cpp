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
        ~Product() {}
        virtual void display() 
        {
            cout << "Item: " << name << endl << "Price:RM " << price << endl;
        }
        friend void discount(Product& x);
};

void discount(Product& x)
{
    double discount;
    cout<<"Enter discount(%) : ";
    cin>>discount;
    x.price=x.price*(discount/100);
}

class FoodItem :public Product 
{
    private:
        string expiryDate;
    public:
        FoodItem():Product(),expiryDate(""){}
        FoodItem(string n,double p,string e):Product(n,p),expiryDate(e){}
        ~FoodItem(){}
        void display() override 
        {
            Product::display();
            cout<<"Expiry Date : "<<expiryDate<<endl;
        }
};

class BeverageItem :public Product 
{
    private:
        string isAlcohol;
    public:
        BeverageItem():Product(),isAlcohol("Y/N"){}
        BeverageItem(string n,double p,string a):Product(n,p),isAlcohol(a){}
        ~BeverageItem(){}
        void display() override
        {
            Product::display();
            cout<<"Does it contain alcohol? : "<<isAlcohol<<endl;
        }

};


void display_menu();
void add(Product **products,int &count);
void edit(Product *products,int count);
void deleteProduct(Product *products, int &count);
void displayProduct(Product *products, int count);


int main()
{
    int choice;
    int count=0;
    Product *products=nullptr;

    do
    {
        display_menu();
        cin>>choice;

    }while (choice!=5);
}

void display_menu()
{
    cout<<"\n=========Reatil Outlet Menu========="<<endl;
    cout<<"\n1. Add Product";
    cout<<"\n2. Edit Product discount";
    cout<<"\n3. Display Product";
    cout<<"\n4. Delete Product";
    cout<<"\n5. Exit";
}

void add(Product **products,int &count)
{
    int type;
    string name;
    double price;
    cout<<"\nPlease choose the type of item that you want to add\n";
    cout<<"1.Food Item\n";
    cout<<"2.Beverage Item\n";
    cin>>type;
    cin.ignore();
    cout<<"Enter Item name : ";
    getline(cin,name);
    cout<<"Enter Item Price : RM";
    cin>>price;

    Product *newProduct=nullptr;
    if(type==1)
    {
        string expiry_date;
        cout<<"Enter Item expiry date : ";
        getline(cin,expiry_date);
        newProduct=new FoodItem(name,price,expiry_date);
        cin.ignore();
    }
    else if(type==2)
    {
        string alcohol;
        cout<<"Is it contain alcohol? : ";
        getline(cin,alcohol);
        newProduct=new BeverageItem(name,price,alcohol);
    }

    Product **temporary=new Product*[count+1];
    for(int i=0;i<count;i++)
    {
        temporary[i]=products[i];
        temporary[count]=newProduct;
        delete[] products;
        products= temporary;
        count++;
    }
}

void edit(Product *products,int count)
{
    int item;
    displayProduct(products,count);
    cout<<"Select item to edit : ";
    cin>>item;
    
}

void displayProduct(Product *products, int count)
{
    if(count==0)
    {
        cout<<"\nDoesn't have any products";
        return;
    }
    for(int i=0;i<count;i++)
    {
        cout<<i<<endl;
        products[i].display();
    }
}
