#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

struct Question{
    int id_question ;
    string question;
    string ans1 , ans2 , ans3 ;
    char correct_ans ;
    Question* left ,* right;
};

struct History {
    int id_student;
    int math_score , logic_score , average_score;

    History* next;
};

class Quiz {
    Question* root;
    int size ;
    int score ;

public: 
    Quiz () {
        root = nullptr ;
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
            cout<<"a "<<root->ans1<<"\t b "<<root->ans2<<"\t c "<<root->ans3<<endl;
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

    void read_data_from_file(int choice){
        fstream f;
        string file_name;
        if ( choice == 1 ) {
            file_name = "math.csv" ;
        }
        else if ( choice == 2 ) {
            file_name = "physic.csv" ;
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

    void random(Question *root , int quantity){
        char answer;
        srand(static_cast<unsigned>(time(0)));

        vector<int> numbers;
        for (int i = 1; i <= 50; ++i) {
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
            cout << "Question: " << i+1 << endl;
            cout << current->question << endl;
            cout << "a. " << current->ans1 << "\n";
            cout << "b. " << current->ans2 << "\n";
            cout << "c. " << current->ans3 << "\n";
        
            do {
                cout << "Please Enter the Answer (a/b/c): ";
                cin >> answer;
                answer = tolower(answer);
            } while (answer != 'a' && answer != 'b' && answer != 'c');


            if (answer == tolower(current->correct_ans)) {
                score++;
            } 
        }
        display_Score(quantity);
    }

    void display_Score(int total_questions){
        cout << "\nQuiz Complete! Your score: " << score << "/" << total_questions << endl;
    }

    void random_question(int quantity) {
        random(root, quantity);
    }

    ~Quiz(){
        delete_tree(root);
    }

};

int main() {
    Quiz question;

    question.read_data_from_file(2);
    question.random_question(5);

    return 0;
}
