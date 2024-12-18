#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

struct Question{
    int id_question ;
    string question;
    string ans1 , ans2 , ans3 , correct_ans;
    Question* left ,* right;
};

class Quiz {
    Question* root;
    int size ;

public: 
    Quiz () {
        root = nullptr ;
        size = 0;
    }

    Question* insert( Question* root , int id , string question , string ans1, string ans2, string ans3, string correct_ans ) {
        
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

    void add(int id , string question , string ans1, string ans2, string ans3, string correct_ans) {
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
            return false ;
        }
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
    

    ~Quiz(){
        delete_tree(root);
    }

};

int main () {

    Quiz question ;

    fstream f;
    string line;

    f.open("math.csv", ios::in);
    if (!f.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return 1;
    }
    
    while (getline(f, line)) {

        stringstream ss(line);
        string temp_id, q, anw1, anw2 , anw3, correct ;

        getline(ss, temp_id, ',');
        getline(ss, q, ',');
        getline(ss, anw1, ',');
        getline(ss, anw2, ',');
        getline(ss, anw3, ',');
        getline(ss, correct, '\n');

        int id = stoi(temp_id);   

        question.add(id,q,anw1,anw2,anw3,correct);

    }

    f.close();

    question.inorder_();
    return 0 ;
}