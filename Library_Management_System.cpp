#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Function to read valid integer input
int readInt(string message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input! Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Book class
class Book {
private:
    string title, author, isbn;
    bool available;
    int borrowDays;

public:
    // Constructor
    Book(string t, string a, string i) {
        title = t;
        author = a;
        isbn = i;
        available = true;
        borrowDays = 0;
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    bool isAvailable() { return available; }

    void issueBook(int days) {
        available = false;
        borrowDays = days;
    }

    int returnBook(int daysKept) {
        int fine = 0;

        if (daysKept > borrowDays) {
            fine = (daysKept - borrowDays) * 5;
        }

        available = true;
        borrowDays = 0;
        return fine;
    }

    void display(int id) {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nISBN: " << isbn;
        cout << "\nStatus: "
             << (available ? "Available" : "Issued");
        cout << "\n--------------------------\n";
    }
};

// Library class
class Library {
private:
    vector<Book> books;

public:
    // Add a new book
    void addBook() {
        string title, author, isbn;

        cout << "\nEnter book title: ";
        getline(cin, title);

        cout << "Enter author name: ";
        getline(cin, author);

        cout << "Enter ISBN: ";
        getline(cin, isbn);

        if (title.empty() || author.empty() || isbn.empty()) {
            cout << "Book details cannot be empty!\n";
            return;
        }

        for (const Book &b : books) {
            if (b.getISBN() == isbn) {
                cout << "This ISBN already exists!\n";
                return;
            }
        }

        books.push_back(Book(title, author, isbn));
        cout << "Book added successfully!\n";
    }

    // Display all books
    void displayBooks() {
        if (books.empty()) {
            cout << "\nNo books in the library.\n";
            return;
        }

        cout << "\n===== BOOK LIST =====\n";

        for (int i = 0; i < (int)books.size(); i++) {
            books[i].display(i + 1);
        }
    }

    // Search by title, author or ISBN
    void searchBook() {
        string query;
        bool found = false;

        cout << "\nEnter title, author or ISBN: ";
        getline(cin, query);

        for (int i = 0; i < (int)books.size(); i++) {
            if (books[i].getTitle() == query ||
                books[i].getAuthor() == query ||
                books[i].getISBN() == query) {
                books[i].display(i + 1);
                found = true;
            }
        }

        if (!found) {
            cout << "Book not found!\n";
        }
    }

    // Issue a book
    void checkoutBook() {
        if (books.empty()) {
            cout << "\nNo books available in the records.\n";
            return;
        }

        displayBooks();

        int id = readInt("Enter Book ID to issue: ");

        if (id < 1 || id > (int)books.size()) {
            cout << "Invalid Book ID!\n";
            return;
        }

        if (!books[id - 1].isAvailable()) {
            cout << "This book is already issued!\n";
            return;
        }

        int days = readInt("Enter borrowing period in days: ");

        if (days <= 0) {
            cout << "Borrowing period must be positive!\n";
            return;
        }

        books[id - 1].issueBook(days);
        cout << "Book issued successfully!\n";
    }

    // Return a book and calculate fine
    void returnBook() {
        if (books.empty()) {
            cout << "\nNo books in the library records.\n";
            return;
        }

        displayBooks();

        int id = readInt("Enter Book ID to return: ");

        if (id < 1 || id > (int)books.size()) {
            cout << "Invalid Book ID!\n";
            return;
        }

        if (books[id - 1].isAvailable()) {
            cout << "This book has not been issued!\n";
            return;
        }

        int days = readInt("Enter total days the book was kept: ");

        if (days < 0) {
            cout << "Days cannot be negative!\n";
            return;
        }

        int fine = books[id - 1].returnBook(days);

        cout << "Book returned successfully!\n";
        cout << "Fine amount: Rs. " << fine << "\n";
    }
};

// Main function
int main() {
    Library library;
    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                library.addBook();
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                library.searchBook();
                break;

            case 4:
                library.checkoutBook();
                break;

            case 5:
                library.returnBook();
                break;

            case 6:
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
