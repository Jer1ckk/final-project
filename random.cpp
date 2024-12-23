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
