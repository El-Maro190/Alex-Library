#include <iostream>
#include <string>
using namespace std;

void inputList() {
	cout << "Welcome to Alex Library" << endl << "What would you like to do?" << endl <<
		"To add    a book, enter 1" << endl <<
		"To search  by ID, enter 2" << endl <<
		"To update a book, enter 3" << endl <<
		"To remove a book, enter 4" << endl <<
		"To borrow a book, enter 5" << endl <<
		"To return a book, enter 6" << endl <<
		"To view the full list of available books, enter 0" << endl <<
		"To exit the program, enter -1" << endl;
}

void addBook(string id, string title, string author, string books[][3], int& currentSize, int SIZE) {
	if (currentSize >= SIZE)
	{
		cout << "Books List is full, delete a book to free space for adding!" << endl;
		return;
	}

	for (int i = 0; i < currentSize; i++) {
		if (books[i][0] == id) {
			cout << "A book with ID '" << id << "' already exists. Try again!" << endl;
			return;
		}
	}

	if (id.empty() || title.empty() || author.empty()) {
		cout << "Book details cannot be empty. Try again!" << endl;
		return;
	}

	books[currentSize][0] = id;
	books[currentSize][1] = title;
	books[currentSize][2] = author;

	currentSize++;
	cout << "Book added successfully!" << endl;
}

int searchByID(string books[][3], int currentSize, string id, bool isAvailable[]) {
	for (int i = 0; i < currentSize; i++)
	{
		if (books[i][0] == id)
		{
			cout << "Book Found!" << endl;
			cout << "ID: " << books[i][0]
				<< ", Title: " << books[i][1]
				<< ", Author: " << books[i][2]
				<< ", Status: ";
			isAvailable[i] ? cout << "Available\n" : cout << "Not Available\n";
			return i;
		}
	}
	cout << "Book with ID '" << id << "' not found in the book list!" << endl;
	return -1;
}

void updateBook(string previousID, string id, string title, string author, string books[][3], int currentSize, bool isAvailable[]) {
	int index = searchByID(books, currentSize, previousID, isAvailable);

	if (index == -1)
	{
		cout << "Book with ID '" << previousID << "' not found in the book list!" << endl;
		return;
	}

	if (!id.empty() && id != previousID) {
		for (int i = 0; i < currentSize; i++) {
			if (books[i][0] == id) {
				cout << "A book with ID '" << id << "' already exists!" << endl;
				return;
			}
		}
	}

	if (id.empty() && title.empty() && author.empty()) {
		cout << "Please enter the data you want to update" << endl;
		return;
	}

	if (!id.empty())
	{
		books[index][0] = id;
	}
	if (!title.empty())
	{
		books[index][1] = title;
	}
	if (!author.empty())
	{
		books[index][2] = author;
	}

	cout << "Book updated successfully!" << endl;
	cout << "ID: " << books[index][0]
		<< ", Title: " << books[index][1]
		<< ", Author: " << books[index][2]
		<< ", Status: ";
	isAvailable[index] ? cout << "Available\n" : cout << "Not Available\n";
}

void removeBook(string id, string books[][3], int& currentSize, bool isAvailable[]) {
	int index = searchByID(books, currentSize, id, isAvailable);
	if (index == -1)
	{
		cout << "Book with ID '" << id << "' not found in the book list!" << endl;
		return;
	}

	for (int i = index; i < currentSize - 1; i++)
	{
		books[i][0] = books[i + 1][0];
		books[i][1] = books[i + 1][1];
		books[i][2] = books[i + 1][2];
		isAvailable[i] = isAvailable[i + 1];
	}

	books[currentSize][0] = "";
	books[currentSize][1] = "";
	books[currentSize][2] = "";

	currentSize--;
	cout << "Book with ID '" << id << "' removed successfully!" << endl;
}

void borrowBook(string id, string books[][3], int currentSize, bool isAvailable[]) {
	int index = searchByID(books, currentSize, id, isAvailable);
	if (index == -1)
	{
		cout << "Book with ID '" << id << "' not found in the book list!" << endl;
	}
	else if (!isAvailable[index])
	{
		cout << "Book with ID '" << id << "' is not currently available!" << endl;
	}
	else {
		isAvailable[index] = false;
		cout << "Book with ID '" << id << "' has been borrowed successfully!" << endl;

	}
}

void returnBook(string id, string books[][3], int currentSize, bool isAvailable[]) {
	int index = searchByID(books, currentSize, id, isAvailable);
	if (index == -1) {
		cout << "Book with ID '" << id << "' not found in the book list!" << endl;
	}
	else if (isAvailable[index]) {
		cout << "Book with ID '" << id << "' is already available!" << endl;
	}
	else {
		isAvailable[index] = true;
		cout << "Book with ID '" << id << "' has been returned successfully!" << endl;
	}
}

void display(string books[][3], int currentSize, bool isAvailable[]) {
	if (currentSize == 0) {
		cout << "No books available." << endl;
	}
	else {
		cout << "Available books:" << endl;
		for (int i = 0; i < currentSize; i++) {
			cout << "ID: " << books[i][0]
				<< ", Title: " << books[i][1]
				<< ", Author: " << books[i][2]
				<< ", Status: ";
			isAvailable[i] ? cout << "Available\n" : cout << "Not Available\n";
		}
	}
}


int main()
{
	int inpNum, currentSize = 5;
	int const SIZE = 10;
	string books[SIZE][3]{
	{"1", "To Kill a Mockingbird", "Harper Lee"},
	{"2", "1984", "George Orwell"},
	{"3", "The Great Gatsby", "F. Scott Fitzgerald"},
	{"4", "Pride and Prejudice", "Jane Austen"},
	{"5", "Moby-Dick", "Herman Melville"} };
	bool isAvailable[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		isAvailable[i] = true;
	}
	while (true)
	{
		inputList();
		cin >> inpNum;
		cin.ignore();
		if (inpNum == 1)
		{
			string id, title, author;
			cout << "Enter book id: ";
			getline(cin, id);
			cout << "Enter book title: ";
			getline(cin, title);
			cout << "Enter book author: ";
			getline(cin, author);
			addBook(id, title, author, books, currentSize, SIZE);
		}
		else if (inpNum == 2) {
			string id;
			cout << "Enter book id: ";
			getline(cin, id);
			searchByID(books, currentSize, id, isAvailable);
		}
		else if (inpNum == 3) {
			string previousID, id, title, author;
			cout << "Enter current book id: ";
			getline(cin, previousID);
			cout << "Enter updated book id: ";
			getline(cin, id);
			cout << "Enter updated book title: ";
			getline(cin, title);
			cout << "Enter updated book author: ";
			getline(cin, author);
			updateBook(previousID, id, title, author, books, currentSize, isAvailable);
		}
		else if (inpNum == 4) {
			string id;
			cout << "Enter book id: ";
			getline(cin, id);
			removeBook(id, books, currentSize, isAvailable);
		}
		else if (inpNum == 5) {
			string id;
			cout << "Enter book id to borrow: ";
			getline(cin, id);
			borrowBook(id, books, currentSize, isAvailable);
		}
		else if (inpNum == 6) {
			string id;
			cout << "Enter book id to borrow: ";
			getline(cin, id);
			returnBook(id, books, currentSize, isAvailable);
		}
		else if (inpNum == 0) {
			display(books, currentSize, isAvailable);
		}
		else if (inpNum == -1)
		{
			cout << "Leaving the program, Goodbye!" << endl;
			break;
		}
		else {
			cout << "Invalid input, Please try again!" << endl;
		}
		cout << "-------------------------------------\n";
	}
}