#include <iostream>
#include<string>
using namespace std;

class Product 
{
    protected:
        string name;
        double price;
    public:
        Product():name("unknown"),price(0.0){}
        Product (string n,double p):name(n),price(p){}
        virtual void display() 
        {
            cout << "Item: " << name << endl << "Price: RM " << price << endl;
        }
        friend void discount(Product& x);
        friend void editName(Product& x);
        friend void editPrice(Product& x);
};

void discount(Product& x)
{
    double discount;
    cout<<"Enter discount(%) : ";
    cin>>discount;
    x.price=x.price*(discount/100);
}

void editName(Product& x)
{
    string newName;
    cin.ignore();
    cout<<"Enter new name : ";
    cin>>newName;
    newName=x.name;
}

void editPrice(Product& x)
{
    double newPrice;
    cout<<"Enter new price";
    cin>>newPrice;
    newPrice=x.price;
}

class FoodItem :public Product 
{
    private:
        string expiryDate;
    public:
        FoodItem():Product(),expiryDate("N/A"){}
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


void add(Product**& products,int &count);
void edit(Product** products,int count);
void deleteProduct(Product**& products, int &count);
void displayProduct(Product** products, int count);


int main()
{
    int choice;
    int count=0;
    Product **products=nullptr;

    do
    {
        cout<<"\n=========Reatil Outlet Menu========="<<endl;
        cout<<"\n1. Add Product";
        cout<<"\n2. Edit Product discount";
        cout<<"\n3. Display Product";
        cout<<"\n4. Delete Product";
        cout<<"\n5. Exit\n";
        cout<<"Enter choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                add(products,count);
                break;
            case 2:
                edit(products,count);
                break;
            case 3:
                displayProduct(products,count);
                break;
            case 4:
                deleteProduct(products,count);
        }

    }while (choice!=5);


    for(int i=0;i<count;i++)
    {
        delete products[i];
        
    }
    delete[] products;
    cout<<"\n\n\n";
    system("pause");
    return 0;
}

void add(Product**& products,int &count)
{
    int type;
    string name;
    double price;
    cout<<"\nPlease choose the type of item that you want to add\n";
    cout<<"1.Food Item\n";
    cout<<"2.Beverage Item\n";
    cout<<"Type : ";
    cin>>type;
    cin.ignore();
    cout<<"Enter Item name : ";
    getline(cin,name);
    cout<<"Enter Item Price : RM ";
    cin>>price;

    Product* newProduct=nullptr;
    if(type==1)
    {
        string expiry_date;
        cin.ignore();
        cout<<"Enter Item expiry date : ";
        getline(cin,expiry_date);
        newProduct=new FoodItem(name,price,expiry_date);
    }
    else if(type==2)
    {
        string alcohol;
        cin.ignore();
        cout<<"Is it contain alcohol? : ";
        getline(cin,alcohol);
        newProduct=new BeverageItem(name,price,alcohol);
    }

    Product **temporary=new Product*[count+1];
    for(int i=0;i<count;++i)
    {
        temporary[i]=products[i];
        
    }
        temporary[count]=newProduct;
        delete[] products;
        products= temporary;
        count++;
}

void edit(Product** products,int count)
{
    int item;
    int y1,y2,y3;
    if(count==0)
    {
        cout<<"\nDoesn't have any products";
        return;
    }
    else
    {
        displayProduct(products,count);
        cout<<"Select item to edit : ";
        cin>>item;
        if(item>0 && item<=count)
        {
            cin.ignore();
            cout<<"Edit name ?[Y/N] ";
            cin>>y1;
            if(y1=='Y'||y1=='y')
            {
                editName(*products[item]);
            }
            else if(y1=='N'||y1=='n')
            {
                return;
            }
            cin.ignore();
            cout<<"Edit price ?[Y/N] ";
            cin>>y2;
            if(y2=='Y'||y2=='y')
            {
                editPrice(*products[item]);
            }
            else if(y2=='N'||y2=='n')
            {
                return;
            }
            cin.ignore();
            cout<<"Want to apply discount ?[Y/N] ";
            cin>>y3;
            if(y3=='Y'||y3=='y')
            {
                discount(*products[item]);
            }
            else if(y3=='N'||y3=='n')
            {
                return;
            }
        }
        else
        {
            cout<<"Invalid item."<<endl;
        }
    }

    
}

void displayProduct(Product** products, int count)
{
    if(count==0)
    {
        cout<<"\nDoesn't have any products";
        return;
    }
    for(int i=0;i<count;i++)
    {
        cout<<"\n"<<i+1<<"."<<endl;
        products[i]->display();
    }
}

void deleteProduct(Product**& products, int &count)
{
    int item;
    if(count==0)
    {
        cout<<"\nDoesn't have any products";
        return;
    }
    else
    {
        displayProduct(products,count);
        cout<<"Enter item to delete : ";
        cin>>item;
        if(item>0 && item<=count)
        {
            delete products[item-1];
            for(int i=item;i<=count-1;++i)
            {
                products[i]=products[i+1];
                
            }
            count--;
            Product** temporary=new Product*[count];
            for(int i=0;i<count;i++)
            {
                temporary[i]=products[i];
                
            }
            delete[] products;
            products=temporary;
            cout<<"Item deleted"<<endl;
        }
        else
        {
            cout<<"Invalid Item"<<endl;
        }
    }
}
