#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <chrono>
#include <thread>
#include <limits>

using namespace std;

struct Account {
    string name;
    int acc_id;
    string email;
    int permission;
    string password;

    Account *next ;
};

struct Question{
    int id_question ;
    string question;
    string ans1 , ans2 , ans3 ;
    char correct_ans ;
    Question* left ,* right;
};

struct History {
    int id_student;
    int math_score , physic_score ;
    float  average_score;
    History* left , * right;
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

    int get_size() {
        return size;
    }

    void create_acc(int acc_id, string name, string email, string password, int permission) {
        Account* create = new Account;
        create->acc_id = acc_id;
        create->name = name;
        create->email = email;
        create->password = password;
        create->permission = permission;
        create->next = NULL;

        if (is_empty()) {
            head = tail = create;
        } else {
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

        Account* temp = head;
        while (temp != NULL) {
            cout << "ID: " << temp->acc_id
                << ", Name: " << temp->name
                << ", Email: " << temp->email  // Display email
                << ", Permission: " << temp->permission
                << endl;
            temp = temp->next;
        }
        cout << endl;
    }


    int login_permission(string email, string password) {
        if (is_empty()) {
            cout << "No accounts in the system. Please create an account first." << endl;
            return -1;
        }

        Account *temp = head;

        while (temp != NULL) {
            if (temp->email == email && temp->password == password) {
                cout << "Login successful! Welcome, " << temp->name << "!" << endl;
                //cout << "Account ID: " << temp->acc_id << ", Permission Level: " << temp->permission << endl;
                return temp->permission;
            }
            temp = temp->next;
        }
        cout << "Invalid name or password. Please try again." << endl;
        return 0;
    }

    int login_id(string email, string password) {
        if (is_empty()) {
            cout << "No accounts in the system. Please create an account first." << endl;
            return -1;
        }

        Account *temp = head;

        while (temp != NULL) {
            if (temp->email == email && temp->password == password) {
                return temp->acc_id;
            }
            temp = temp->next;
        }
    }


    void save_to_file() {
        fstream file;
        string file_name = "Data.txt";
        file.open(file_name, ios::out);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << file_name << " for saving data." << endl;
            return;
        }

        Account* temp = head;
        while (temp != NULL) {
            file << temp->name << ","
                << temp->email << ","
                << temp->password << ","
                << temp->acc_id << ","
                << temp->permission << endl;
            temp = temp->next;
        }
        file.close();
        cout<<endl;
    }

    void read_from_file() {
        fstream f;
        string file_name = "Data.txt";
        f.open(file_name, ios::in);
        if (!f.is_open()) {
            cout << "Error: Unable to open file " << file_name << " for reading data." << endl;
            return;
        }

        string line;
        while (getline(f, line)) {
            stringstream ss(line);
            string name, email, password, temp_id, temp_permission;

            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, password, ',');
            getline(ss, temp_id, ',');
            getline(ss, temp_permission);

            int id = stoi(temp_id);
            int permission = stoi(temp_permission);

            create_acc(id, name, email, password, permission);
        }
        f.close();
    }

};

class Quiz {
    Question* root;
    History *history_root;
    int size ;
    int score ;

public:
    Quiz () {
        root = nullptr ;
        history_root = nullptr ;
        size = 0;
        score = 0;
    }

    Question* insert( Question* root , int id , string question , string ans1, string ans2, string ans3, char correct_ans ) {

        if ( root == nullptr ) {

            root = new Question ;
            root->id_question = id ;
            root->question = question ;
            root->ans1 = ans1 ;
            root->ans2 = ans2 ;
            root->ans3 = ans3 ;
            root->correct_ans = correct_ans ;
            root->left = nullptr ;
            root->right = nullptr ;
            size++;
        }
        else if ( root->id_question < id ) {
            root->right = insert( root->right , id , question , ans1, ans2, ans3 , correct_ans );
        }
        else if ( root->id_question > id ) {
            root->left =  insert( root->left , id , question , ans1, ans2, ans3 , correct_ans );
        }
        return root;
    }

    void add(int id , string question , string ans1, string ans2, string ans3, char correct_ans) {
        root = insert (root , id , question , ans1, ans2, ans3 , correct_ans) ;
    }

    void inorder(Question* root) {
        if (root != nullptr ) {
            inorder(root->left);
            cout<<"Question "<<root->id_question<<". "<<root->question<<endl;
            cout<<"a. "<<root->ans1<<"\t b. "<<root->ans2<<"\t c. "<<root->ans3<<"\t correct answer: "<<root->correct_ans<<endl;
            inorder(root->right);
        }
    }

    void inorder_() {
        inorder(root);
        cout<<endl;
    }

    Question* delete_node(Question* root, int id_question) {
        if (root == nullptr) {
            return root;
        }

        if (id_question < root->id_question) {
            root->left = delete_node(root->left, id_question);
        }
        else if (id_question > root->id_question) {
            root->right = delete_node(root->right, id_question);
        }
        else {

            if (root->left == nullptr) {

                Question* temp = root->right;
                delete root;
                size--;
                return temp;
            } else if (root->right == nullptr) {

                Question* temp = root->left;
                delete root;
                size--;
                return temp;
            }

            Question* temp = find_min(root->right) ;
            root->id_question = temp->id_question ;
            root->question = temp->question ;
            root->ans1 = temp->ans1 ;
            root->ans2 = temp->ans2 ;
            root->ans3 = temp->ans3 ;
            root->correct_ans = temp->correct_ans ;
            root->right = delete_node(root->right, temp->id_question);
        }
        return root;
    }

    Question* find_min(Question* root) {
        while ( root->left != nullptr ) {
            root = root->left ;
        }
        return root;
    }

    void remove(int id_question) {
        root = delete_node(root, id_question);
    }

    void delete_tree(Question* root) {
        if (root != nullptr) {
            delete_tree(root->left);
            delete_tree(root->right);
        }
        delete root;
    }

    Question* find_quest(Question* root, int id) {
        while (root != nullptr) {
            if (id == root->id_question) {
                return root;
            }
            else if (id < root->id_question) {
                root = root->left;
            }
            else {
            root = root->right;
            }
        }
        return nullptr;
    }

    Question* find_question(int id) {
        return find_quest(root, id);
    }


    bool search(Question* root , int id) {
        while ( root != nullptr ) {
            if (id == root->id_question) {
                return true;
            }
            else if ( id > root->id_question ) {
                root = root->right ;
            }
            else if ( id < root->id_question ) {
                root = root->left ;
            }
        }
        return false ;
    }

    void search_question(int id) {
        bool result = search (root , id ) ;
        if (!result) {
            cout << "Question id " << id << " does not exists in the tree." << endl;
        }
        else {
            cout << "Question id  " << id << " exists in the tree." << endl;
        }
    }

    void display_question(int id) {
        Question* current = root ;
        while (current != nullptr){
            if (id==current->id_question){
                cout << "Question ID: " << current->id_question << endl;
                cout << current->question << endl;
                cout << "a. " << current->ans1 << "\n";
                cout << "b. " << current->ans2 << "\n";
                cout << "c. " << current->ans3 << "\n";
                cout << "Correct Answer: " << current->correct_ans << endl;
                return;
            }
            else if ( id < current->id_question ) {
                current = current->left ;
            }
            else {
                current = current->right ;
            }
        }
        cout << "Question with ID " << id << " does not exist." << endl ;
    }

    void save_history() {
        fstream file;
        string file_name = "history.txt";

        file.open(file_name, ios::out);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << file_name << " for saving data." << endl;
            return;
        }

        save_history_to_file_preorder(history_root, file);

        file.close();
        cout << "Question data has been saved to " << file_name << "." << endl;
    }

    void save_history_to_file_preorder(History* root, fstream& file) {
        if (root != nullptr) {
            file << root->id_student << ","
                << root->math_score<< ","
                << root->physic_score << ","
                << root->average_score << endl;

            save_history_to_file_preorder(root->left, file);
            save_history_to_file_preorder(root->right, file);
        }
    }

    void save_to_file(int choice) {
        fstream file;
        string file_name;

        if (choice == 1) {
            file_name = "logic.csv";
        }
        else if (choice == 2) {
            file_name = "sport.csv";
        }

        file.open(file_name, ios::out);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << file_name << " for saving data." << endl;
            return;
        }

        save_questions_to_file_preorder(root, file);

        file.close();
        cout << "Question data has been saved to " << file_name << "." << endl;
    }

    void save_questions_to_file_preorder(Question* root, fstream& file) {
        if (root != nullptr) {
            file << root->id_question << ","
                << root->question << ","
                << root->ans1 << ","
                << root->ans2 << ","
                << root->ans3 << ","
                << root->correct_ans << endl;

            save_questions_to_file_preorder(root->left, file);
            save_questions_to_file_preorder(root->right, file);
        }
    }

    void read_data_from_history(int choice) {
        string file_name = "history.txt" ;
        fstream f;

        f.open(file_name, ios::in);
        if (!f.is_open()) {
            cout << "Error: Unable to open file!" << endl;
            return ;
        }

        string line;
        while (getline(f, line)) {
            stringstream ss(line);
            string temp_id, temp_math, temp_physic, temp_aver;

            getline(ss, temp_id, ',');
            getline(ss, temp_math, ',');
            getline(ss, temp_physic, ',');
            getline(ss, temp_aver);

            int id = stoi(temp_id);
            int math = stoi(temp_math);
            int physic = stoi(temp_physic);
            int aver = stoi(temp_aver);
            if (choice == 1 ) {
                add_student_score(id, math, physic);
            }
            else if ( choice == 2 ) {
                add_high_score(id , math, physic) ;
            }

        }
        f.close();
    }

    void read_data_from_file(int choice){
        fstream f;
        string file_name;
        if ( choice == 1 ) {
            file_name = "logic.csv" ;
        }
        else if ( choice == 2 ) {
            file_name = "sport.csv" ;
        }

        f.open(file_name, ios::in);
        if (!f.is_open()) {
            cout << "Error: Unable to open file!" << endl;
            return ;
        }

        string line;
        while (getline(f, line)) {
            stringstream ss(line);
            string temp_id, q, anw1, anw2, anw3;
            char correct;

            getline(ss, temp_id, ',');
            getline(ss, q, ',');
            getline(ss, anw1, ',');
            getline(ss, anw2, ',');
            getline(ss, anw3, ',');
            ss >> correct;

            int id = stoi(temp_id);
            add(id, q, anw1, anw2, anw3, correct);
        }
        f.close();
    }

    int random(Question* root, int quantity) {
        char answer;
        srand(static_cast<unsigned>(time(0)));

        vector<int> numbers;
        for (int i = 1; i <= size; ++i) {
            numbers.push_back(i);
        }
        random_shuffle(numbers.begin(), numbers.end());

        cout << "Random Questions (no duplicates):" << endl;
        for (int i = 0; i < quantity; i++) {
            int question_id = numbers[i];

            Question* current = find_question(question_id);
            if (current == nullptr) {
                continue;
            }

            system("cls");
            cout << "Question: " << i + 1 << endl;
            cout << current->question << endl;
            cout << "a. " << current->ans1 << "\n";
            cout << "b. " << current->ans2 << "\n";
            cout << "c. " << current->ans3 << "\n";

            bool answered = false;

            while (!answered) {
                cout << "Your answer (a/b/c): ";
                cin >> answer;
                answer = tolower(answer);

                if (answer == 'a' || answer == 'b' || answer == 'c') {
                    answered = true;
                    if (answer == tolower(current->correct_ans)) {
                        score++;
                    }
                } else {
                    cout << "Invalid input. Enter 'a', 'b', or 'c'.\n";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
        display_Score(quantity);
        return score;
    }

    void display_Score(int total_questions){
        cout << "\nQuiz Complete! Your score: " << score << "/" << total_questions << endl;
    }

    int random_question(int quantity) {
        return random(root, quantity);
    }

    void edit_question(int id) {
        Question* current = find_question(id);

        if (current == nullptr) {
            cout << "Question with ID " << id << " does not exist." << endl;
            return;
        }

        cout << "Editing Question ID: " << id << endl;

        cout << "Current Question: " << current->question << endl;
        cout << "Enter new question: ";
        string new_question;
        cin.ignore();
        getline(cin, new_question);
        if (!new_question.empty()) {
            current->question = new_question;
        }

        cout << "Current Answer a: " << current->ans1 << endl;
        cout << "Enter new Answer a: ";
        string new_ans1;
        getline(cin, new_ans1);
        if (!new_ans1.empty()) {
            current->ans1 = new_ans1;
        }

        cout << "Current Answer b: " << current->ans2 << endl;
        cout << "Enter new Answer b: ";
        string new_ans2;
        getline(cin, new_ans2);
        if (!new_ans2.empty()) {
            current->ans2 = new_ans2;
        }

        cout << "Current Answer c: " << current->ans3 << endl;
        cout << "Enter new Answer c: ";
        string new_ans3;
        getline(cin, new_ans3);
        if (!new_ans3.empty()) {
            current->ans3 = new_ans3;
        }

        cout << "Current Correct Answer: " << current->correct_ans << endl;
        cout << "Enter new Correct Answer (a/b/c): ";
        string new_correct_ans;
        getline(cin, new_correct_ans);
        if (!new_correct_ans.empty() &&
            (new_correct_ans == "a" || new_correct_ans == "b" || new_correct_ans == "c")) {
            current->correct_ans = new_correct_ans[0];
        }
        cout << "Question ID " << id << " has been successfully updated." << endl;
    }

    History* insert_history(History* root, int id_student, int math_score, int physic_score , float aver_score) {
        if (root == nullptr) {
            root = new History;
            root->id_student = id_student;
            root->math_score = math_score;
            root->physic_score = physic_score;
            root->average_score = aver_score ;
            root->left = nullptr;
            root->right = nullptr;
        }
        else if (id_student < root->id_student) {
            root->left = insert_history(root->left, id_student, math_score, physic_score ,aver_score);
        }
        else if (id_student > root->id_student) {
            root->right = insert_history(root->right, id_student, math_score, physic_score, aver_score);
        }
        return root;
    }

    History* insert_high_score(History* root, int id_student, int math_score, int physic_score , float aver_score) {
        if (root == nullptr) {
            root = new History;
            root->id_student = id_student;
            root->math_score = math_score;
            root->physic_score = physic_score;
            root->average_score = aver_score ;
            root->left = nullptr;
            root->right = nullptr;
        }
        else if (aver_score < root->average_score) {
            root->left = insert_high_score(root->left, id_student, math_score, physic_score ,aver_score);
        }
        else if (id_student >= root->id_student) {
            root->right = insert_high_score(root->right, id_student, math_score, physic_score, aver_score);
        }
        return root;
    }

    void add_high_score(int id_student, int math_score, int physic_score) {
        float aver = static_cast<float>(math_score + physic_score) / 2.0f;
        history_root = insert_high_score(history_root, id_student, math_score, physic_score, aver);
    }


    void add_student_score(int id_student, int math_score, int physic_score) {
        float aver = static_cast<float>(math_score + physic_score) / 2.0f;
        history_root = insert_history(history_root, id_student, math_score, physic_score, aver);
    }



    void display_top_bot(History* root , int& i) {
        if (root != nullptr) {
            display_top_bot(root->right , i);
            cout << "TOP "<<i+1<< ':'<<endl;
            cout << "Student ID: " << root->id_student << endl;
            cout << "Logic Score: " << root->math_score << endl;
            cout << "Sport Score: " << root->physic_score << endl;
            cout << "Average Score: " << root->average_score << endl;
            cout<<endl;
            i++ ;
            display_top_bot(root->left ,i);
        }
    }

    void display_top_to_bot() {
        int i = 0 ;
        display_top_bot(history_root , i);
    }

    void display_all_scores(History* root) {
        if (root != nullptr) {
            display_all_scores(root->left);
            cout << "Student ID: " << root->id_student << endl;
            cout << "Logic Score: " << root->math_score << endl;
            cout << "Sport Score: " << root->physic_score << endl;
            cout << "Average Score: " << root->average_score << endl;
            cout<<endl;
            display_all_scores(root->right);
        }
    }

    void display_all_scores() {
        display_all_scores(history_root);
    }

    void check_and_create_student_history(int id_student) {
        History* existing_student = find_id_student(history_root, id_student);

        if (existing_student == nullptr) {
            int math_score = 0 ;
            int physic_score = 0 ;
            add_student_score(id_student, math_score, physic_score);
        }
    }

    History* find_id_student ( History* root, int id ) {
        while (root != nullptr) {
            if (id == root->id_student) {
                return root;
            }
            else if (id < root->id_student) {
                root = root->left;
            }
            else {
            root = root->right;
            }
        }
        return nullptr;
    }

    void display_student_scores(History* root, int id_student) {
        if (root == nullptr) {
            cout << "Student ID " << id_student << " not found." << endl;
            return;
        }
        if (id_student == root->id_student) {
            cout << "Student ID: " << root->id_student << endl;
            cout << "Logic Score: " << root->math_score << endl;
            cout << "Sport Score: " << root->physic_score << endl;
            cout << "Average Score: " << root->average_score << endl;
            return;
        }
        else if (id_student < root->id_student) {
            display_student_scores(root->left, id_student);
        }
        else {
            display_student_scores(root->right, id_student);
        }
    }

    void display_student_scores(int id_student) {
        History* history_root;
        display_student_scores(history_root, id_student);
    }


    History* find_id_student_history(int id ){
        return find_id_student(history_root , id );
    }

    void edit_score(int id , int score , int subject ){
        History* current = find_id_student_history(id);

        if (current == nullptr) {
            cout << "Student ID " << id << " not found." << endl;
            return;
        }
        if ( subject == 1 ) {
            current->math_score = score;
        }
        else if ( subject == 2 ) {
            current->physic_score = score;
        }
        current->average_score = static_cast<float>(current->math_score + current->physic_score) / 2.0f ;
    }

    int get_student_score(int student_id, int subject_id) {
        History* student_history = find_id_student_history(student_id);

        if (student_history == nullptr) {
            check_and_create_student_history(student_id);
            student_history = find_id_student_history(student_id);
        }

        if (subject_id == 1) {
            return student_history->math_score;
        }
        else if (subject_id == 2) {
            return student_history->physic_score;
        }
        return 0;
    }

    bool can_attempt_quiz(Quiz& quiz, int student_id, int subject_id) {
        int score = quiz.get_student_score(student_id, subject_id);
        if (score != 0) {
            cout << "You have already attempted this quiz (Subject ID: " << subject_id << "). Your score is: " << score << endl;
            return false;
        }
        return true;
    }

    void take_quiz(Quiz& quiz, int student_id, int subject_id , int choice) {

        if (choice == 1){
            quiz.read_data_from_history(1);
            quiz.check_and_create_student_history(student_id);

            if (quiz.can_attempt_quiz(quiz, student_id, subject_id)) {
                int point = quiz.random_question(10);
                quiz.edit_score(student_id, point, subject_id);
                quiz.display_student_scores(student_id);
                quiz.save_history();
            }
        }
        else if ( choice ==2 ){
            quiz.read_data_from_history(1);
            quiz.check_and_create_student_history(student_id);
            quiz.display_student_scores(student_id);
        }

    }

    void delete_history(History* root) {
        if (root != nullptr) {
            delete_history(root->left);
            delete_history(root->right);
            delete root;
        }
    }

    ~Quiz(){
        delete_tree(root);
        delete_history(history_root);
    }
};

void teacher_menu(Quiz& logic_quiz, Quiz& sport_quiz, login& operation) {
    int menu_choice, id, id_question;

    do {
        cout << "===== Teacher Menu =====" << endl;
        cout << "1. Add a new question" << endl;
        cout << "2. View all questions" << endl;
        cout << "3. Delete a question" << endl;
        cout << "4. Edit a question" << endl;
        cout << "5. View student history" << endl;
        cout << "6. View LeaderBoard" << endl;
        cout << "7. Create a Student Account" << endl;
        cout << "8. Log out" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> menu_choice;

        switch (menu_choice) {
            case 1: {
                int subject_choice;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }

                string question, ans1, ans2, ans3;
                char correct_ans;

                cout << "Enter Question ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Question: ";
                getline(cin, question);
                cout << "Enter Answer A: ";
                getline(cin, ans1);
                cout << "Enter Answer B: ";
                getline(cin, ans2);
                cout << "Enter Answer C: ";
                getline(cin, ans3);
                cout << "Enter Correct Answer (a/b/c): ";
                cin >> correct_ans;

                if (subject_choice == 1) {
                    logic_quiz.add(id, question, ans1, ans2, ans3, correct_ans);
                    logic_quiz.save_to_file(1);
                } else {
                    sport_quiz.add(id, question, ans1, ans2, ans3, correct_ans);
                    sport_quiz.save_to_file(2);
                }
                cout << "Question added successfully!" << endl;
                break;
            }
            case 2: {
                int subject_choice;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }

                if (subject_choice == 1) {
                    logic_quiz.read_data_from_file(1);
                    cout << "Math Quiz Questions:" << endl;
                    logic_quiz.inorder_();
                } else {
                    sport_quiz.read_data_from_file(2);
                    cout << "Physics Quiz Questions:" << endl;
                    sport_quiz.inorder_();
                }
                break;
            }
            case 3: {
                int subject_choice;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }

                cout << "Enter Question ID to delete: ";
                cin >> id_question;

                if (subject_choice == 1) {
                    logic_quiz.read_data_from_file(1);
                    logic_quiz.remove(id_question);
                    logic_quiz.save_to_file(1);
                } else {
                    sport_quiz.read_data_from_file(2);
                    sport_quiz.remove(id_question);
                    sport_quiz.save_to_file(2);
                }
                cout << "Question deleted successfully!" << endl;
                break;
            }
            case 4: {
                int subject_choice;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }
                cout << "Enter Question ID to edit: ";
                cin >> id_question;
                if (subject_choice == 1) {
                    logic_quiz.read_data_from_file(1);
                    logic_quiz.edit_question(id_question);
                    logic_quiz.save_to_file(1);
                } else {
                    sport_quiz.read_data_from_file(2);
                    sport_quiz.edit_question(id_question);
                    sport_quiz.save_to_file(2);
                }
                cout << "Question edited successfully!" << endl;
                break;
            }
            case 5: {
                cout << "Viewing student history:" << endl;
                Quiz history;
                history.read_data_from_history(1);
                history.display_all_scores();
                break;
            }
            case 6: {
                cout << "Viewing scores (Top to Bottom):" << endl;
                Quiz history;
                history.read_data_from_history(2);
                history.display_top_to_bot();
                break;
            }
            case 7: {
                int id1, permission = 1;
                string name1, password1, email1;
                cout << "Enter Student Name: ";
                cin >> name1;
                cout << "Enter Email: ";
                cin >> email1;
                cout << "Enter Password: ";
                cin >> password1;
                cout << "Enter Student ID: ";
                cin >> id1;
                operation.create_acc(id1, name1, email1, password1, permission);
                operation.save_to_file();
                cout << "Student account created successfully." << endl;
                break;
            }
            case 8:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (menu_choice != 8);
}

void admin_menu(login& operation, Quiz& logic_quiz, Quiz& sport_quiz) {
    int choice;
    do {
        cout << "===== Admin Menu =====" << endl;
        cout << "1. Create a teacher account" << endl;
        cout << "2. Create a student account" << endl;
        cout << "3. Delete a user account" << endl;
        cout << "4. View all users" << endl;
        cout << "5. Add a new question" << endl;
        cout << "6. View all questions" << endl;
        cout << "7. Delete a question" << endl;
        cout << "8. Edit a question" << endl;
        cout << "9. View student history" << endl;
        cout << "10. View Leaderboard" << endl;
        cout << "11. Log out" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id1, permission = 2;
                string name, password, email;
                cout << "Enter Teacher Name: ";
                cin >> name;
                cout << "Enter Email: ";
                cin >> email;
                cout << "Enter Teacher Password: ";
                cin >> password;
                cout << "Enter Teacher ID: ";
                cin >> id1;
                operation.create_acc(id1, name, email, password, permission);
                cout << "Teacher account created successfully." << endl;
                operation.save_to_file();
                break;
            }
            case 2: {
                int id1, permission = 1;
                string name, password, email;
                cout << "Enter Student Name: ";
                cin >> name;
                cout << "Enter Email: ";
                cin >> email;
                cout << "Enter Student Password: ";
                cin >> password;
                cout << "Enter Student ID: ";
                cin >> id1;
                operation.create_acc(id1, name, email, password, permission);
                cout << "Student account created successfully." << endl;
                operation.save_to_file();
                break;
            }
            case 3: {
                int id;
                cout << "Enter account ID to delete: ";
                cin >> id;
                operation.delete_acc(id);
                operation.save_to_file();
                break;
            }
            case 4:
                cout << endl;
                operation.display_acc();
                break;
            case 5: {
                int subject_choice, id;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }

                string question, ans1, ans2, ans3;
                char correct_ans;

                cout << "Enter Question ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Question: ";
                getline(cin, question);
                cout << "Enter Answer A: ";
                getline(cin, ans1);
                cout << "Enter Answer B: ";
                getline(cin, ans2);
                cout << "Enter Answer C: ";
                getline(cin, ans3);
                cout << "Enter Correct Answer (a/b/c): ";
                cin >> correct_ans;

                if (subject_choice == 1) {
                    logic_quiz.add(id, question, ans1, ans2, ans3, correct_ans);
                    logic_quiz.save_to_file(1);
                } else {
                    sport_quiz.add(id, question, ans1, ans2, ans3, correct_ans);
                    sport_quiz.save_to_file(2);
                }
                cout << "Question added successfully!" << endl;
                cout << endl;
                break;
            }
            case 6: {
                int subject_choice;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }

                if (subject_choice == 1) {
                    logic_quiz.read_data_from_file(1);
                    cout << "Math Quiz Questions:" << endl;
                    logic_quiz.inorder_();
                } else {
                    sport_quiz.read_data_from_file(2);
                    cout << "Physics Quiz Questions:" << endl;
                    sport_quiz.inorder_();
                }
                break;
            }
            case 7: {
                int subject_choice, id;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }

                cout << "Enter Question ID to delete: ";
                cin >> id;

                if (subject_choice == 1) {
                    logic_quiz.read_data_from_file(1);
                    logic_quiz.remove(id);
                    logic_quiz.save_to_file(1);
                } else {
                    sport_quiz.read_data_from_file(2);
                    sport_quiz.remove(id);
                    sport_quiz.save_to_file(2);
                }
                cout << "Question deleted successfully!" << endl;
                break;
            }
            case 8: {
                int subject_choice, id;
                cout << "1 for Math, 2 for Physics: ";
                cin >> subject_choice;

                if (subject_choice != 1 && subject_choice != 2) {
                    cout << "Invalid subject choice! Returning to main menu." << endl;
                    break;
                }

                cout << "Enter Question ID to edit: ";
                cin >> id;

                if (subject_choice == 1) {
                    logic_quiz.read_data_from_file(1);
                    logic_quiz.edit_question(id);
                    logic_quiz.save_to_file(1);
                } else {
                    sport_quiz.read_data_from_file(2);
                    sport_quiz.edit_question(id);
                    sport_quiz.save_to_file(2);
                }
                cout << "Question edited successfully!" << endl;
                break;
            }
            case 9: {
                cout << "Viewing student history:" << endl;
                Quiz history;
                cout << endl;
                history.read_data_from_history(1);
                history.display_all_scores();
                break;
            }
            case 10: {
                cout << "Viewing scores (Top to Bottom):" << endl;
                Quiz history;
                cout << endl;
                history.read_data_from_history(2);
                history.display_top_to_bot();
                break;
            }
            case 11:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 11);
}

void student_menu(Quiz& logic_quiz, Quiz& sport_quiz, int student_id) {
    int choice;
    do {
        cout << "\n===== Student Menu =====" << endl;
        cout << "1. Take Logic Quiz" << endl;
        cout << "2. Take Sport Quiz" << endl;
        cout << "3. View My Scores" << endl;
        cout << "4. Log Out" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                logic_quiz.take_quiz(logic_quiz, student_id, 1 , 1);
                break;
            }
            case 2: {
                sport_quiz.take_quiz(sport_quiz, student_id, 2 ,1);
                break;
            }
            case 3: {
                logic_quiz.take_quiz(logic_quiz, student_id, 1, 2);
                break;
            }
            case 4:
                cout << "Logging out...\n" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again.\n" << endl;
        }
    } while (choice != 4);
}

int main() {
    login operation;
    Quiz logic_quiz, sport_quiz;

    logic_quiz.read_data_from_file(1);
    sport_quiz.read_data_from_file(2);
    operation.read_from_file();

    string login_email;
    string pass_login;
    int permission_level;
    int id_user;

    while (true) {
        int choice;
        cout << "\n1. Login\n2. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 2) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else if (choice != 1) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        do {
            cout << "Enter Your Email: ";
            cin >> login_email;
            cout << "Enter Your Password: ";
            cin >> pass_login;
            id_user = operation.login_id(login_email, pass_login);
            permission_level = operation.login_permission(login_email, pass_login);

            if (permission_level == -1) {
                cout << "No accounts in the system. Exiting..." << endl;
                return 0;
            } else if (permission_level == 0) {
                cout << "Invalid credentials. Please try again." << endl;
            }
        } while (permission_level != 3 && permission_level != 2 && permission_level != 1);

        cout << "You have logged in with permission level " << permission_level << ". Access granted." << endl;
        cout << endl;

        if (permission_level == 1) {
            student_menu(logic_quiz, sport_quiz, id_user);
        } else if (permission_level == 2) {
            teacher_menu(logic_quiz, sport_quiz, operation);
        } else if (permission_level == 3) {
            admin_menu(operation, logic_quiz, sport_quiz);
        }
    }

    return 0;
}


