#include "stdio.h"
#include <iostream>
#include "conio.h"
#include <windows.h>
#include <malloc.h>

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
		country = newCountry;
		name = newName;
		price = newPrice;
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
		country = newCountry;
	}
	void setName(string newName) {
		name = newName;
	}
	void setPrice(double newPrice) {
		price = newPrice;
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
	void output(int i) {
		cout << i + 1 << " product:" << endl;
		cout << "Country: " << country << endl;
		cout << "Product: " << name << endl;
		cout << "Price = " <<  price << endl << endl;
	}

	// Add 
	static int add(Item* item, Item* secondItem) {
		int sum;
		sum = item->getPrice() + secondItem->getPrice();
		return sum;
	}

	// Add sale
	static void sale(Item* item, int num) {
		for (int i = 0; i < num; i++)
			(*item).setPrice((*item).getPrice() * 0.5);
	}

	// Add markup
	void markup(Item* item, int num) {
		for (int i = 0; i < num; i++)
			(*item).setPrice((*item).getPrice() * 2);
	}
};


int main() {
	
	cout << "Now it is a static object:" << endl;
	Item staticItem = Item();

	cout << "Item created, Init used." << endl;
	staticItem.output(0);

	cout << "Now we need enter values of item:" << endl;
	staticItem = Item::input(0);
	staticItem.output(0);

	cout << "If we are add 2 equal items, we will get:" << endl;
	cout << "Sum price = " << Item::add(&staticItem, &staticItem) << endl << endl;
	staticItem.output(0);

	cout << "Sale! 50%!" << endl;
	staticItem.sale(&staticItem, 1);
	staticItem.output(0);

	cout << "Sale is over!" << endl;
	staticItem.markup(&staticItem, 1);
	staticItem.output(0);
	
	cout << "Press any key to continue";
	_getch();

	system("cls");

	cout << "Now it is a dynamic object:" << endl;
	Item* dynamicItem = new Item("Something", "Somewhere", 100);
	dynamicItem->output(0);
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
	badItem[num - 1].output(num - 1);

	free(badItem);

	Item* dynamicItem1 = new Item[5];
	delete[] dynamicItem1;

	Item* badItem2 = (Item*)malloc(10 * sizeof(Item));
	badItem2 = (Item*)realloc(badItem2, 20 * sizeof(Item));
	free(badItem2);
	cout << "Program is over. Press any key to exit.";
	_getch();
	return 0;
}