#include "stdio.h"
#include "conio.h"
#include <windows.h>

// Create struct
struct grocerystore {
	char country[20];
	char prod[20];
	double price;
};

// Read func
grocerystore input(int i) {
	grocerystore inputshop;
	do {
		rewind(stdin);
		printf("Input country of %d product: ", i + 1);
		gets_s(inputshop.country, 20);
	} while (inputshop.country[0] == '\0' || inputshop.country[0] == ' ');

	do {
		rewind(stdin);
		printf("Input name of %d product: ", i + 1);
		gets_s(inputshop.prod, 20);
	} while (inputshop.prod[0] == '\0' || inputshop.prod[0] == ' ');

	int dop;
	do {
		rewind(stdin);
		printf("Input price of %d product(for ex. 2081.98): ", i + 1);
		dop = scanf_s("%lf", &inputshop.price);
	} while (dop != 1 || inputshop.price < 0);

	printf("\n");
	return inputshop;
}

// Display func
void output(int i, grocerystore outputshop) {
	printf("%d product:\n", i + 1);
	printf("Country: ");
	puts(outputshop.country);
	printf("Product: ");
	puts(outputshop.prod);
	printf("Price = %.2lf\n\n", outputshop.price);
}

// Init func
grocerystore init() {
	grocerystore initshop;
	initshop.country[0] = ' ';
	initshop.prod[0] = ' ';
	initshop.price = 0;
	return initshop;
}

// Add func
void add(grocerystore* addshop, int num) {
	printf("Do you want buy smth?(\'1\' - yes, else - no)\n");
	if (_getch() == '1') {
		printf("OK. How many products do you want? ");
		int n;
		rewind(stdin);
		scanf_s("%d", &n);
		rewind(stdin);
		printf("What product numbers do you want?(if you want more than 1 same things - enter \"1 1 1 1...\") ");
		int prod[20];
		double sum = 0;
		for (int i = 0; i < n; i++) {
			scanf_s("%d", &prod[i]);
			int dop = prod[i] - 1;
			sum += addshop[dop].price;
			if (prod[i] > num || prod[i] < 0) {
				sum -= addshop[dop].price;
				i--;
				printf("Incorrect number of product, please, enter again.\n");
			}
		}
		printf("\nSum price = %.2lf", sum);
	}

}

// Add sale func
void salestruct(struct grocerystore* shop, int num) {
	for (int i = 0; i < num; i++)
		shop[i].price = shop[i].price * 0.5;
}

// Add markup func
void markupstruct(struct grocerystore* shop, int num) {
	for (int i = 0; i < num; i++)
		shop[i].price = shop[i].price * 2;
}

int main() {
	int num, dop;
	printf("How many products do you want to input?(positive number)\n");
	do {
		rewind(stdin);
		dop = scanf_s("%d", &num);
		if (num < 1) printf("Please, input positive number\n");
	} while (num < 1 || dop != 1);

	if (num == 1) {																// non-dinamic struct
		struct grocerystore shop[2];											// create struct in project
		shop[0] = init();
		shop[0] = input(0);

		output(0, shop[0]);

		printf("For add func we need one more struct. Please, input its. \nIf you are tired and don't want - you can press \'1\' right now and go out of the program. Otherwise - press any key.\n\n");
		rewind(stdin);
		if (_getch() == '1') {
			printf("Thank you for honesty! Bye!");
			_getch();
			return 0;
		}
		shop[1] = init();
		shop[1] = input(1);

		output(0, shop[0]);
		output(1, shop[1]);

		add(shop, 2);

		printf("\n\nSale! 50%!\n\n");
		salestruct(shop, 2);

		output(0, shop[0]);
		output(1, shop[1]);

		add(shop, 2);

		printf("\nSale is over.\n");
		markupstruct(shop, num);

		output(0, shop[0]);
		output(1, shop[1]);

		printf("Program is over.");
		_getch();
	}
	else {
		struct grocerystore* shop;												// create dinamic struct in project
		shop = (struct grocerystore*)malloc(num * sizeof(struct grocerystore));

		for (int i = 0; i < num; i++) {
			shop[i] = init();
			shop[i] = input(i);
		}

		for (int i = 0; i < num; i++)
			output(i, shop[i]);

		add(shop, num);
		_getch();

		printf("\n\nSale! 50%!\n\n");
		salestruct(shop, num);

		for (int i = 0; i < num; i++)
			output(i, shop[i]);

		add(shop, num);

		printf("Press any key to continue\n");
		_getch();

		printf("\nSale is over.\n");
		markupstruct(shop, num);

		for (int i = 0; i < num; i++)
			output(i, shop[i]);

		printf("Program is over.");
		_getch();
	}
	return 0;
}