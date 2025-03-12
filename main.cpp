#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>

using namespace std;

// Book class
class Book
{
private:
    string title;
    string author;
    string ISBN;
    bool available;
public:
    // Book attribute constructor
    Book(string t, string a, string i) : title(t), author(a), ISBN(i), available(true) {}

    // Function to check out a book
    void checkOut() { available = false; }

    // Function to check in a book
    void checkIn() { available = true; }

    // Getters for book details
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }

    // Function to display book information
    void display() const
    {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: "
        	 << ISBN << ", Available: " << (available ? "Yes" : "No") << endl;
    }
};

// User base class
class User
{
protected:
    static int idCounter; // Static counter to assign the user IDs
    int userID;
    string name;

public:
    // User attribute constructor
    User(string n) : name(n) { userID = ++idCounter; }

    // Virtual destructor to prevent memory leaks in derived classes
    virtual ~User() {}

    // Virtual function so derived classes implement display()
    virtual void display() const = 0;

    // Getter for user ID
    int getUserID() const { return userID; }
};

// Initialize the user ID counter
int User::idCounter = 0;

// User derived classes
class Student : public User
{
public:
    Student(string n) : User(n) {}

    // Display function override
    void display() const override
    {
        cout << "[Student] Name: " << name << ", UserID: " << userID << endl;
    }
};

class Faculty : public User
{
public:
    Faculty(string n) : User(n) {}

    // Display function override
    void display() const override
    {
        cout << "[Faculty] Name: " << name << ", UserID: " << userID << endl;
    }
};


// Factory Pattern (creating users dynamically)
class UserFactory
{
public:
    static User* createUser(int type, string name)
    {
        if (type == 1)
        	return new Student(name);
        else if (type == 2)
        	return new Faculty(name);
        else throw invalid_argument("Invalid user type!");
    }
};

// Library Class (Singleton Pattern; one instance of the class exists)
class Library
{
private:
    vector<Book*> books;  // Stores all books
    vector<User*> users;  // Stores all users

    // Constructor
    Library() {}

public:
    // Get a single instance of the Library class
    static Library& getInstance()
    {
        static Library instance;
        return instance;
    }

    // Destructor to clean up any allocated memory
    ~Library()
    {
        for (size_t i = 0; i < books.size(); i++)
        {
            delete books[i];
        }
        for (size_t i = 0; i < users.size(); i++)
        {
            delete users[i];
        }
    }

    // Function to add a new book
    void addBook(string title, string author, string ISBN)
    {
        books.push_back(new Book(title, author, ISBN));
        cout << "Book added successfully!" << endl;
    }

    // Function to list all books
    void listAllBooks()
    {
        // Check if any books exist
    	if (books.empty())
        {
            cout << "No books available!" << endl;
            return;
        }
        for (size_t i = 0; i < books.size(); i++)
        {
            books[i]->display();
        }
    }

    // Function to add a new user
    void addUser(int type, string name)
    {
        User* newUser = UserFactory::createUser(type, name);
        users.push_back(newUser);
        cout << "User added successfully! UserID: " << newUser->getUserID() << endl;
    }

    // Function to list all users
    void listAllUsers()
    {
    	// Check if any users exist
        if (users.empty())
        {
            cout << "No users available!" << endl;
            return;
        }
        for (size_t i = 0; i < users.size(); i++)
        {
            users[i]->display();
        }
    }

    // Function to check out a book
    void checkOutBook()
    {
        string title, author, ISBN;
        cout << "Enter Title: ";
        cin.ignore(); getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, ISBN);

        for (size_t i = 0; i < books.size(); i++)
        {
        	// Validate all book attributes match the system
            if (books[i]->getTitle() == title && books[i]->getAuthor() == author)
            {
            	// Check if the book is already checked out
                if (books[i]->isAvailable())
                {
                    books[i]->checkOut();
                    cout << "Book checked out successfully!" << endl;
                }
                else
                {
                    cout << "Book is already checked out!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Function to check in a book
    void checkInBook()
    {
        string title, author, ISBN;
        cout << "Enter Title: ";
        cin.ignore(); getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, ISBN);

        for (size_t i = 0; i < books.size(); i++)
        {
        	// Validate all book attributes match the system
            if (books[i]->getTitle() == title && books[i]->getAuthor() == author)
            {
                // Check if the book is already available
            	if (!books[i]->isAvailable())
                {
                    books[i]->checkIn();
                    cout << "Book checked in successfully!" << endl;
                }
                else
                {
                    cout << "Book is already available!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
};

int main()
{
    Library& lib = Library::getInstance();
    int choice;

    // Do-while loop to display the menu
    do
    {
        cout << "\nLibrary Management System";
        cout << "\n1. Manage Books";
        cout << "\n2. Manage Users";
        cout << "\n3. Manage Transactions";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        // Validate input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, try again." << endl;
            continue;
        }

        // Switch statement so program behaves accordingly to input
        switch (choice)
        {
			case 1:
			{
				int bookChoice;
				do
				{
					cout << "\n1. Add Book";
					cout << "\n2. List Books";
					cout << "\n3. Back";
					cout << "\nEnter your choice: ";
					cin >> bookChoice;

					if (bookChoice == 1)
					{
						string title, author, ISBN;
						cout << "Enter Title: ";
						cin.ignore(); getline(cin, title);
						cout << "Enter Author: ";
						getline(cin, author);
						cout << "Enter ISBN: ";
						getline(cin, ISBN);

						lib.addBook(title, author, ISBN);
					}
					else if (bookChoice == 2)
					{
						lib.listAllBooks();
					}
				} while (bookChoice != 3);
				break;
			}
			case 2:
			{
				int userChoice;
				do
				{
					cout << "\n1. Add User";
					cout << "\n2. List Users";
					cout << "\n3. Back";
					cout << "\nEnter your choice: ";
					cin >> userChoice;

					if (userChoice == 1)
					{
						int type;
						string name;
						cout << "Enter 1 for Student, 2 for Faculty: ";
						cin >> type;
						cin.ignore();
						cout << "Enter Name: ";
						getline(cin, name);

						lib.addUser(type, name);
					}
					else if (userChoice == 2)
					{
						lib.listAllUsers();
					}
				} while (userChoice != 3);
				break;
			}
			case 3:
			{
				int transactionChoice;
				do
				{
					cout << "\n1. Check Out Book";
					cout << "\n2. Check In Book";
					cout << "\n3. Back";
					cout << "\nEnter your choice: ";
					cin >> transactionChoice;

					if (transactionChoice == 1)
					{
						lib.checkOutBook();
					} else if (transactionChoice == 2)
					{
						lib.checkInBook();
					}
				} while (transactionChoice != 3);
				break;
			}
			case 4:
				cout << "Exiting program..." << endl;
				break;
			default:
				cout << "Invalid option. Try again!" << endl;
		}
	} while (choice != 4);

    return 0;
}