#include <iostream>
#include <fstream>
#include <string>
#include <limits> 

using namespace std;


void registerUser();
bool loginUser();
bool isUsernameTaken(string username);

const string DB_FILE = "users.txt";


void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    int choice;

    while (true) {
        cout << "\n--- User Management System ---" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";

        
        if (!(cin >> choice)) {
            cout << "[ERROR] Please enter a valid number (1-3)." << endl;
            cin.clear();
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    cout << "\n[SUCCESS] Welcome back! Access granted." << endl;
                } else {
                    cout << "\n[ERROR] Invalid username or password." << endl;
                }
                break;
            case 3:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

bool isUsernameTaken(string username) {
    ifstream file(DB_FILE);
    if (!file) return false;

    string u, p;
    while (file >> u >> p) {
        if (u == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void registerUser() {
    string username, password;
    cout << "\n--- Registration ---" << endl;
    cout << "Enter new username (no spaces): ";
    cin >> username;

    if (isUsernameTaken(username)) {
        cout << "[ERROR] Username already exists. Try a different one." << endl;
        return;
    }

    cout << "Enter new password (no spaces): ";
    cin >> password;

    ofstream file(DB_FILE, ios::app); 
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
        cout << "[SUCCESS] Registration complete!" << endl;
    } else {
        cout << "[ERROR] Could not open database file." << endl;
    }
}

bool loginUser() {
    string username, password, u, p;
    cout << "\n--- Login ---" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file(DB_FILE);
    if (!file.is_open()) {
        cout << "[ERROR] No database found. Please register first." << endl;
        return false;
    }

    while (file >> u >> p) {
        if (u == username && p == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}