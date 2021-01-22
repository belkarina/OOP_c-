#include "stdio.h"
#include <iostream>
#include "conio.h"
#include <windows.h>
#include <malloc.h>
#define MAX 20

using namespace std;

// Create class
class Item {

private:
	string country;
	string name;
	double price;
public:
	// Init
	Item() {
		country = "";
		name = "";
		price = 0;
	}
	// Correct(?) init
	Item(string newCountry, string newName, double newPrice) {
		this->country = newCountry;
		this->name = newName;
		this->price = newPrice;
	}
	// Copy constructor, shallow copy
	Item(const Item& oldItem) {
		this->country = oldItem.country;
		this->name = oldItem.name;
		this->price = oldItem.price;
	}

	string getCountry() {
		return(country);
	}
	string getName() {
		return(name);
	}
	double getPrice() {
		return(price);
	}
	void setCountry(string newCountry){
		this->country = newCountry;
	}
	void setName(string newName) {
		this->name = newName;
	}
	void setPrice(double newPrice) {
		this->price = newPrice;
	}

	// Read 
	static Item input(int i) {
		string newCountry;
		string newName;
		double newPrice;
		do {
			cout << "Input country of " << i + 1 << " product: ";
			rewind(stdin);
			cin >> newCountry;
		} while (newCountry[0] == '\0' || newCountry[0] == ' ');

		do {
			cout << "Input name of " << i + 1 << " product: ";
			rewind(stdin);
			cin >> newName;
		} while (newName[0] == '\0' || newName[0] == ' ');

		do {
			cout << "Input price of " << i + 1 << " product: ";
			rewind(stdin);
			cin >> newPrice;
			if (cin.fail())
				cin.clear();
		} while (newPrice <= 0);
		cout << endl;
		Item newItem = Item(newCountry, newName, newPrice);
		return(newItem);
	}

	// Display
	void output(Item prod, int i) {
		cout << i + 1 << " product:" << endl;
		cout << "Country: " << prod.country << endl;
		cout << "Product: " << prod.name << endl;
		cout << "Price = " << prod.price << endl << endl;
	}

	// Add 
	static int add(Item item, Item secondItem) {
		int sum;	
		sum = item.price + secondItem.price;
		return sum;
	}

	// Add sale, return by link
	static Item* sale(Item* item, int num) {
		for (int i = 0; i < num; i++)
			item[i].setPrice(item[i].getPrice() * 0.5);
		return item;
	}

	// Add markup
	Item markup(Item* item, int num) {
		for (int i = 0; i < num; i++)
			(*item).setPrice((*item).getPrice() * 2);
		return (*item);
	}
};


class Shop {
	friend class Item;
	friend Shop changeItem(Shop&, Item);
	friend Shop operator ++(Shop& i);
	friend Shop operator++(Shop& i, int);
private:
	Item prod[MAX];
	int quantityProd;
	static string nameShop;					// name of shop network
public: 
	// Init
	Shop() {
		nameShop = "Welcome to our shop network!\n";
		quantityProd = 0;
	}
	// Correct(?) init
	Shop(int newQuantityProd) {
		this->quantityProd = newQuantityProd;
	}

	// return by address
	int getQuantityProd() {
		return(quantityProd);
	}

	void setProd(Item item, int i) {
		if (i < quantityProd && i >= 0)
			this->prod[i] = item;
	}

	static Shop input(Shop ourshop) {
		int quantityProd;
		Item prod[MAX];
		/*do {
			cout << "How many products do you have in your shop?" << endl;
			rewind(stdin);
			cin >> quantityProd;
			if (cin.fail())
				cin.clear();
		} while (quantityProd <= 0 || quantityProd > MAX);*/
		
			try {
				cout << "How many products do you have in your shop?" << endl;
				rewind(stdin);
				cin >> quantityProd;
				if (cin.fail())
					cin.clear();
				if (quantityProd <= 0 || quantityProd > MAX) {
					cin.clear();
					throw 1;
				}
			}
			catch (int quantityProd)
			{
				cerr << "Sorry, some problems with input. Press any key to exit." << endl;
				_getch();
				exit(0);
			}
		
		ourshop = Shop(quantityProd);

		for (int i = 0; i < quantityProd; i++) {
			ourshop.prod[i] = Item::input(i);
			cout << "If you want to have the same products - enter their quantity without the one just entered." << endl;
			cout <<	"If you don't want to - enter anything and click enter." << endl;
			rewind(stdin);
			int num;
			cin >> num;
			if (cin.fail())
				cin.clear();
			if (num > 0 && num < (quantityProd - i)) {
				for (int j = i + 1; j <= (i + num); j++) {
					ourshop.prod[j] = Item(ourshop.prod[i]);
					//ourshop.prod[j] = ourshop.prod[i];
				}
				i = i + num;
			}	
		}
		return (ourshop);
	}

	static Shop output(Shop ourshop, int flag) {
		cout << nameShop;
		for (int i = 0; i < ourshop.getQuantityProd(); i++) {
			ourshop.prod->output(ourshop.prod[i], i);
		}
		
		if (flag) {
			cout << "If you want to change first item - press enter, if you don't - press any key." << endl;
			rewind(stdin);
			if (_getch() == 13) {
				Item item = Item::input(0);
				ourshop = changeItem(ourshop, item);
			}
			for (int i = 0; i < ourshop.getQuantityProd(); i++) {
				ourshop.prod->output(ourshop.prod[i], i);
			}
			_getch();
		}
		return(ourshop);
	}

	int operator +(Shop ourshop) {
		return (Item::add(ourshop.prod[0], ourshop.prod[0]));
	}

	static int add(Item* item, Item* secondItem) {
		int sum;
		sum = item->getPrice() + secondItem->getPrice();
		return sum;
	}

	Shop sale(Shop ourshop) {
		cout << "Sale! 50!" << endl;
		Item::sale(ourshop.prod, quantityProd);
		output(ourshop, 0);
		return ourshop;
	}
	
	double returnPrice(int i) {
		return(this->prod[i].getPrice());
	}

	~Shop() {
	}

};
string Shop::nameShop;
static Shop changeItem(Shop& shop, Item changeProd) {
	shop.prod[0] = changeProd;
	return(shop);
};

Shop operator ++(Shop& ourshop) {
	ourshop.prod[0].setPrice(ourshop.prod[0].getPrice() + 1);
	return ourshop;
};

Shop operator ++(Shop& ourshop, int) {
	Shop oldValue(ourshop);
	ourshop.prod[0].setPrice(ourshop.prod[0].getPrice() + 1);
	return oldValue;
};




int main() {
	Shop ourshop = Shop();
	ourshop = Shop::input(ourshop);
	ourshop = ourshop.output(ourshop, 1);
	int sum = ourshop + ourshop;
	cout << "Sum price = " << sum << endl << endl;
	ourshop = ourshop.sale(ourshop);
	cout << "Press any key to continue";

	_getch();
	//system("cls");
	//cout << "Price of 1st item = " << ourshop.returnPrice(0) << endl;
	//cout << "Price of 1st item = " << ourshop++.returnPrice(0) << endl;
	//cout << "Price of 1st item = " << ourshop.returnPrice(0) << endl;
	//cout << "Price of 1st item = " << (++ourshop).returnPrice(0) << endl;

	system("cls");

	cout << "Now it is a dynamic object:" << endl;
	Shop* dynamicShop = new Shop();
	int amount = 2;
	dynamicShop = new Shop(amount);
	dynamicShop[0] = Shop::input(dynamicShop[0]);
	dynamicShop[0] = Shop::output(dynamicShop[0], 0);
	Item* dynamicItem = new Item("dynamic", "item", 18);
	dynamicShop[0].setProd(dynamicItem[0], 0);
	dynamicShop[0] = Shop::output(dynamicShop[0], 0);
	cout << "Press any key to continue";
	_getch();
	system("cls");

	// Array with constructor with one param 
	Shop arrShop[2] = { amount, ++amount };
	for (int i = 0; i < 2; i++) {
		arrShop[i] = Shop::output(arrShop[i], 0);
	}


	//dynamicShop = dynamicShop.output(dynamicShop, 1);
	//dynamicItem->output(dynamicItem[0], 0);
	//delete dynamicItem;

	cout << "Program is over. Press any key to exit.";

	_getch();
	return 0;
}