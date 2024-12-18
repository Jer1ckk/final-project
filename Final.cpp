#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


struct Account {
    string name;
    int acc_id;
    int permission;
    string password;

    Account *next ;
};

struct Quiz {
    int question_id;
    string question ;
    string ans1;
    string ans2;
    string ans3;
    string correct_ans;

    Quiz *next;

};

class login {
    int size;
    Account* head;
    Account* tail;

public:
    login() {
        size = 0;
        head = tail = NULL;
    }

    bool is_empty() {
        if ( head == NULL ) {
            return true;
        }
        return false;
    }

    void user() {
        cout<<size<<endl;
    }

    void create_acc(int acc_id, string name, string password ,int permission ) {
        Account *create = new Account;
        create->acc_id = acc_id;
        create->name = name;
        create->password = password;
        create->permission = permission;
        create->next = NULL;

        if (is_empty()) {
            head = tail = create;
        } 
        else {
            tail->next = create;
            tail = create;
        }
        size++;
    }

    void delete_acc(int id) {
        if (is_empty()) {
            cout << "There are no accounts to delete." << endl;
            return;
        }

        Account *temp = head;
        Account *prev = NULL;

        while (temp != NULL && temp->acc_id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Account with ID " << id << " not found." << endl;
            return;
        }

        if (temp == head) {
            head = head->next;
            if (head == NULL) { 
                tail = NULL;
            }
        }
        else {
            prev->next = temp->next;
            if (temp == tail) {
                tail = prev;
            }
        }

        delete temp; 
        size--;
        cout << "Account with ID " << id << " deleted successfully." << endl;
    }

    void display_acc() {
        if (is_empty()) {
            cout << "No accounts to display." << endl;
            return;
        }

        Account *temp = head;
        while (temp != NULL) {
            cout << "ID: " << temp->acc_id << ", Name: " << temp->name << ", Permission: " << temp->permission << endl;
            temp = temp->next;
        }
    }

    int login_permission(string name, string password) {
        if (is_empty()) {
            cout << "No accounts in the system. Please create an account first." << endl;
            return -1;
        }

        Account *temp = head;

        while (temp != NULL) {
            if (temp->name == name && temp->password == password) {
                cout << "Login successful! Welcome, " << temp->name << "!" << endl;
                cout << "Account ID: " << temp->acc_id << ", Permission Level: " << temp->permission << endl;
                return temp->permission;
            }
            temp = temp->next;
        }
    cout << "Invalid name or password. Please try again." << endl;
    return 0;
    }

    void save_to_file( string file_name ) {
        fstream file;
        file.open(file_name, ios::out);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << file_name << " for saving data." << endl;
            return;
        }

        Account* temp = head;
        while (temp != NULL) {
            file << temp->name << "," << temp->password << "," << temp->acc_id << "," << temp->permission << endl;
            temp = temp->next;
        }

        file.close();
        cout << "Account data has been saved to " << file_name << "." << endl;
    }

    void read_from_file(string file_name) {
        fstream f;
        f.open(file_name , ios::in) ;
        if (!f.is_open()) {
            cout << "Error: Unable to open file " << file_name << " for saving data." << endl;
            return;
        }
        string line;
        while (getline(f, line)) {
            stringstream ss(line);
            string name, password, temp_id, temp_permission;

            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, temp_id, ',');
            getline(ss, temp_permission);

            int id = stoi(temp_id);
            int permission = stoi(temp_permission);

            create_acc(id, name, password, permission);
        }
        f.close();

    }
};


int main() {
    login system;

    system.read_from_file("Data.txt") ;

    system.display_acc();

    string login_email;
    string pass_login;
    int permission_level;

    do {
        cout << "Enter Your Email: ";
        cin >> login_email;
        cout << "Enter Your Password: ";
        cin >> pass_login;

        permission_level = system.login_permission(login_email, pass_login);

        if (permission_level == -1) {
            cout << "No accounts in the system. Exiting..." << endl;
            return 0;
        } else if (permission_level == 0) {
            cout << "Invalid credentials. Please try again." << endl;
        }
    } while (permission_level != 3 && permission_level != 2 && permission_level != 1);

    cout << "You have logged in with permission level " << permission_level << ". Access granted." << endl;

    system.save_to_file("test.txt");

    return 0;
}


