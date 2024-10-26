// toDoList.cpp
// Author: Taha Zeeshan

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

// Function prototypes
void greetingPrompt();  // Displays a greeting message with the current date
void menu();            // Displays the main menu options for user interaction
void validChoice(char& choice); // Validates user input for menu choices

// Class definition for the To-Do list
class list {
private:
    int size; // Represents the ID number of the task
    string todo; // The actual task description
public:
    // Function prototypes
    void entertask(string x);  // Set the task description
    string gettask();          // Retrieve the task description
    void entersize(int x);     // Set the task ID
    int getsize();             // Retrieve the task ID
    void fivetest();           // Run a series of tests on the list class

    // Constructors and operator overloads
    list (const list &x);      // Copy constructor
    list(string x, int y);     // Parameterized constructor
    list& operator=(const list &x); // Assignment operator overload
    
    // Friend functions for input/output
    friend ostream &operator << (ostream &result, list entry); // Output operator overload
    friend istream &operator >> (istream &input, list &entry); // Input operator overload

    // Default constructor
    list() {
        size = 0; // Initialize size to 0
        todo = "blank"; // Initialize task to "blank"
    };
};

// Overload output operator to define how to display task details
ostream &operator << (ostream& result, list entry) {
    // Format for displaying task with ID and static date
    result << "id:" << entry.getsize() << " - " << entry.gettask() << " date: 04/03/2022" << endl;
    return result;
}

// Overload input operator to define how to read task details
istream &operator >> (istream &input, list &entry) {
    // Temporary variables for input
    int size = 1; // Default size
    string todo; // Variable to hold the task description
    
    input >> todo; // Read task description from input
    entry.entertask(todo); // Store the task in the list
    entry.entersize(size); // Set a default size for the task
    return input;
}

// Parameterized constructor to initialize task and ID
list::list(string x, int y) {
    todo = x; // Set the task description
    size = y; // Set the task ID
}

// Overload assignment operator for copying task details
list& list::operator=(const list &x) {
    // Copy data from another list object
    this->size = x.size;
    this->todo = x.todo;
    return *this;
}

// Copy constructor implementation to create a new list object from an existing one
list::list(const list &x) {
    todo = x.todo; // Copy task description
    size = x.size; // Copy task ID
}

// Store the task description in the class
void list::entertask(string x) {
    todo = x; // Assign task description
}

// Retrieve the task description
string list::gettask() {
    return todo; // Return task description
}

// Store the task ID
void list::entersize(int x) {
    size = x; // Assign task ID
}

// Retrieve the task ID
int list::getsize() {
    return size; // Return task ID
}

// Run a series of predefined tests to validate the list functionality
void list::fivetest() {
    // Create five test tasks with IDs
    list task1("eat", 1);
    list task2("sleep", 2);
    list task3("make bed", 3);
    list task4("do hw", 4);
    list task5("take out trash", 5);
    
    cout << "Five tests:\n"; // Indicate the start of tests
    
    // Test each task and output the result
    if ((task1.gettask() == "eat") && (task1.getsize() == 1)) {
        cout << "task 1 passed" << endl;
    } else {
        cout << "task 1 failed" << endl;
    }

    if ((task2.gettask() == "sleep") && (task2.getsize() == 2)) {
        cout << "task 2 passed" << endl;
    } else {
        cout << "task 2 failed" << endl;
    }

    if ((task3.gettask() == "make bed") && (task3.getsize() == 3)) {
        cout << "task 3 passed" << endl;
    } else {
        cout << "task 3 failed" << endl;
    }

    if ((task4.gettask() == "do hw") && (task4.getsize() == 4)) {
        cout << "task 4 passed" << endl;
    } else {
        cout << "task 4 failed" << endl;
    }

    if ((task5.gettask() == "take out trash") && (task5.getsize() == 5)) {
        cout << "task 5 passed" << endl;
    } else {
        cout << "task 5 failed" << endl;
    }
}

int main() {
    char choice = '.'; // User's menu choice
    bool go = true;    // Control variable for the main loop
    int count = 0;     // Number of tasks in the list
    string tsk;        // Temporary variable to hold task input

    // Display program greeting
    greetingPrompt();

    list taskk; // Create a list object for testing

    // Run predefined tests on the list
    taskk.fivetest();
    
    cout << "Overload insertion: enter a task\n";
    cin >> taskk; // Use overloaded input operator to enter a task

    cout << "Overload extraction:\n";
    cout << taskk << endl; // Use overloaded output operator to display the task

    // Initialize dynamic array for tasks
    list *task = new list[count]; // Create dynamic array for tasks
    list *arr = NULL; // Temporary array for resizing tasks

    menu(); // Display the main menu
    
    // Main loop to manage tasks
    while (go) {
        // Validate user input for menu choices
        validChoice(choice);

        // Handle '+' symbol to add a task
        if (choice == '+') {
            count++; // Increase task count
            getline(cin, tsk); // Get the task description
            
            // Allocate new array for updated task count
            arr = new list[count];

            // Copy existing tasks to the temporary array
            for (int i = 0; i < count - 1; i++) {
                arr[i] = task[i];
            }

            // Set the new task in the array
            arr[count - 1].entertask(tsk);
            arr[count - 1].entersize(count);
            delete[] task; // Clear the old array
            task = arr; // Assign the new array to task
            arr = NULL; // Clear temporary array pointer

        // Handle '-' symbol to remove a task
        } else if (choice == '-') {
            int remove = 0; // Task ID to remove
            bool invalidResponse = true; // Flag for valid input

            // Only allow valid task IDs
            while (invalidResponse) {
                cin >> remove;

                // Handle input failure
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                }
                // Check if the input ID is valid
                else if (remove > 0 && remove <= count) {
                    invalidResponse = false;
                }
                
                if (invalidResponse) {
                    cout << "\nInvalid, please enter a valid ID: ";
                }
            }

            arr = new list[count]; // Allocate new array for tasks
            // Copy existing tasks to the temporary array
            for (int i = 0; i < count - 1; i++) {
                arr[i] = task[i];
            }
            
            // Remove the specified task by shifting elements
            for (int i = remove - 1; i < count - 1; i++) {
                arr[i] = task[i + 1];
            }

            count--; // Decrease the task count
            delete[] task; // Clear the old array
            task = arr; // Assign the new array to task
            arr = nullptr; // Clear temporary array pointer
            
        // Handle '?' symbol to display all tasks
        } else if (choice == '?') {
            for (int i = 0; i < count; i++) {
                cout << task[i] << endl; // Display each task
            }
        }
        // Handle '%' symbol to quit the program
        else if (choice == '%') {
            go = false; // Exit the main loop
        }
    }
  
    // Save tasks to a file upon exit
    ofstream myfile("todo.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < count; i++) {
            myfile << task[i] << " "; // Write each task to the file
        }
        myfile.close(); // Close the file
    }

    delete[] task; // Free the allocated memory for tasks
    return 0; // End of program
}

// Function to display a greeting message with the current date
void greetingPrompt() {
    cout << "Welcome to the ToDo List Program!" << endl;
    cout << "Current Date: " << __DATE__ << endl; // Displays compilation date
}

// Function to display the main menu options
void menu() {
    cout << "Menu:" << endl;
    cout << "+ - Add a task" << endl;
    cout << "- - Remove a task" << endl;
    cout << "? - View all tasks" << endl;
    cout << "% - Exit program" << endl;
}

// Function to validate user input for menu choices
void validChoice(char& choice) {
    cout << "Enter your choice: ";
    cin >> choice;
    choice = tolower(choice); // Convert choice to lowercase for consistency
}
