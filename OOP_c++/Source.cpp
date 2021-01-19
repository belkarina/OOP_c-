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

	static Shop input(Shop ourshop) {
		int quantityProd;
		Item prod[MAX];
		do {
			cout << "How many products do you have in your shop?" << endl;
			rewind(stdin);
			cin >> quantityProd;
			if (cin.fail())
				cin.clear();
		} while (quantityProd <= 0 || quantityProd > MAX);
		ourshop.quantityProd = quantityProd;

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
					ourshop.prod[j] = ourshop.prod[i];
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
	_getch();
	system("cls");
	cout << "Price of 1st item = " << ourshop.returnPrice(0) << endl;
	cout << "Price of 1st item = " << ourshop++.returnPrice(0) << endl;
	cout << "Price of 1st item = " << ourshop.returnPrice(0) << endl;
	cout << "Price of 1st item = " << (++ourshop).returnPrice(0) << endl;

	cout << "Program is over. Press any key to exit.";

	/*cout << "Now it is a static object:" << endl;
	Item staticItem = Item();

	cout << "Item created, Init used." << endl;
	staticItem.output(staticItem, 0);

	cout << "Now we need enter values of item:" << endl;
	staticItem = Item::input(0);
	staticItem.output(staticItem, 0);

	cout << "If we are add 2 equal items, we will get:" << endl;
	cout << "Sum price = " << Item::add(&staticItem, &staticItem) << endl << endl;
	staticItem.output(staticItem, 0);

	cout << "Sale! 50%!" << endl;
	staticItem.sale(&staticItem, 1);
	staticItem.output(staticItem, 0);

	cout << "Sale is over!" << endl;
	staticItem.markup(&staticItem, 1);
	staticItem.output(staticItem, 0);
	
	cout << "Press any key to continue";
	_getch();

	system("cls");

	cout << "Now it is a dynamic object:" << endl;
	Item* dynamicItem = new Item("Something", "Somewhere", 100);
	dynamicItem->output(dynamicItem[0], 0);
	delete dynamicItem;

	cout << "Press any key to continue" << endl;
	_getch();

	cout << "Now it is a dynamic array of objects:" << endl;
	int num;
	do {
		cout << "How many objects do you want to input?" << endl;
		rewind(stdin);
		cin >> num;
		if (cin.fail())
			cin.clear();
	} while (num <= 0);
	cout << endl;

	Item* badItem = (Item*)calloc(num, sizeof(Item));
	for (int i = 0; i < num; i++)
		badItem[i] = Item::input(i);
 
	cout << "Now we are showing your last object:" << endl;
	badItem[num - 1].output(badItem[num-1], num - 1);

	free(badItem);

	Item* dynamicItem1 = new Item[5];
	delete[] dynamicItem1;

	Item* badItem2 = (Item*)malloc(10 * sizeof(Item));
	badItem2 = (Item*)realloc(badItem2, 20 * sizeof(Item));
	free(badItem2);*/
	_getch();
	return 0;
}