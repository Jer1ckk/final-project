#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Account {
    int ID;
    string name, email, password;

    Account* next;
};

struct Student {
    int ID;
    string name, email, password;

    Student* next;
};

class AdminSystem {
    Account* head;
    Account* tail;
    string adminfile = "adminAccount.csv";
    string studentfile = "studentAccount.csv";

public:
    AdminSystem() {
        int size = 0;
        head = tail = NULL;
    }

    bool login(string email, string password) {
        Account*current = head;
        while(current != NULL) {
            if(current->email == email && current->password == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool isEmpty() {
        if ( head == NULL ) {
            return true;
        }
        return false;
    }
    void addAccount(int accID, string accName, string accEmail, string accPassword) {
        Account* information = new Account{accID, accName, accEmail, accPassword};
        if(isEmpty()) {
            head = tail = information;
        }
        else {
            tail->next = information;
            tail = information;
        }
    }
    void saveToFile(int choice) {
        fstream file;
        string fileName;
        if(choice == 1) {
            fileName = adminfile;
        }
        else if(choice == 2) {
            fileName = studentfile;
        }
        file.open(fileName, ios::app);
        Account* current = head;
        while (current != NULL) {
            file << current->ID << "," << current->name << "," << current->email << "," << current->password << endl;
            current = current->next;
        }
        file.close();
    }

    void loadFromFile(int choice) {
        fstream file;
        string fileName;
        if(choice == 1) {
            fileName = adminfile;
        }
        else if(choice == 2) {
            fileName = studentfile;
        }
        file.open(fileName, ios::in);
        if(!file.is_open()) return;
            string line;
            while (getline(file, line)) {
                string tempID, name, email, password;
                stringstream ss(line);

                getline(ss, tempID, ',');
                int ID = stoi(tempID);
                getline(ss, name, ',');
                getline(ss, email, ',');
                getline(ss, password, ',');

                addAccount(ID, name, email, password);
            }
        file.close();
    }

    void display_acc() {
        if (isEmpty()) {
            cout << "No accounts to display." << endl;
            return;
        }

        Account* current = head;
        while (current != NULL) {
            cout << "ID: " << current->ID << ", Name: " << current->name << ", Email: " << current->email << ", Password: " << current->password << endl;
            current = current->next;
        }
    }
};

void newStudent() {
    AdminSystem *data = new AdminSystem();
    int ID;
    string email, password, name;

    cout << "Enter the ID for new student: ";
    cin >> ID;
    cout << "Enter the name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter the new Email: ";
    cin >> email;
    cout << "Enter the new password: ";
    cin >> password;

    data->addAccount(ID, name, email, password);
    data->saveToFile(2);
    cout << "Student account created successfully!" << endl;
}

void newAdmin() {
    AdminSystem *data = new AdminSystem();
    int ID;
    string email, password, name;

    cout << "Enter the ID for new admin: ";
    cin >> ID;
    cout << "Enter the name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter the new Email: ";
    cin >> email;
    cout << "Enter the new password: ";
    cin >> password;

    data->addAccount(ID, name, email, password);
    data->saveToFile(1);
    cout << "Admin account created successfully!" << endl;
}


int main() {
    AdminSystem Account;
    int userType;
    // Account.display_acc();

    do {
        cout << "=== Attendance System ===" <<endl;
        cout << "1. Admin" <<endl;
        cout << "2. Student" <<endl;
        cout << "3. Exit the program" <<endl;
        cout << "Enter your choice: ";
        cin >> userType;

        Account.loadFromFile(userType);

        switch (userType) {
        case 1: {
            string adminEmail, adminPassword;
            cout << "Enter admin email: ";
            cin >> adminEmail;
            cout << "Enter admin password: ";
            cin >> adminPassword;
            if(Account.login(adminEmail, adminPassword)) {
                int adminChoice;
                do {
                    cout << "\n=== Admin System ===" <<endl;
                    cout << "1) Add new student" <<endl;
                    cout << "2) Add new admin" <<endl;
                    cout << "3) View student list" <<endl;
                    cout << "4) Edit student attendance" <<endl;
                    cout << "5) View attendance" <<endl;
                    cout << "6) Logout" <<endl;
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    switch(adminChoice) {
                        case 1: {
                            newStudent();
                            break;
                        }
                        case 2: {
                            newAdmin();
                            break;
                        }
                        case 3: {

                            break;
                        }
                        case 4: {
                            break;
                        }
                        case 5: {
                            break;
                        }
                        case 6: {
                            break;
                        }
                    }
                } while (adminChoice != 6);

            }
            else {
                cout << "Invalid email or password!" <<endl;
            }
            break;
        }
        case 2: {

        }
            break;
        }
    } while (userType != 3);

    return 0;

}
