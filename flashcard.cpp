#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <limits> // for numeric_limits

using namespace std;

// Flashcard class to hold a question-answer pair
class Flashcard {
public:
    string question;
    string answer;

    Flashcard(string q, string a) {
        question = q;
        answer = a;
    }
};

// Loads flashcards from a file
void loadFlashcards(vector<Flashcard>& flashcards) {
    ifstream file("flashcards.txt");
    string question, answer;

    while (getline(file, question) && getline(file, answer)) {
        flashcards.emplace_back(question, answer);
    }

    file.close();
}

// Saves flashcards to a file
void saveFlashcards(const vector<Flashcard>& flashcards) {
    ofstream file("flashcards.txt");

    for (const auto& card : flashcards) {
        file << card.question << endl;
        file << card.answer << endl;
    }

    file.close();
}

// Adds a new flashcard
void addFlashcard(vector<Flashcard>& flashcards) {
    string question, answer;

    cout << "\nEnter the question: ";
    getline(cin, question);

    cout << "Enter the answer: ";
    getline(cin, answer);

    flashcards.emplace_back(question, answer);
    cout << "Flashcard added!" << endl;
}

// Runs the quiz using all stored flashcards
void quiz(const vector<Flashcard>& flashcards) {
    int score = 0;
    string userAnswer;

    for (const auto& card : flashcards) {
        cout << "\nQuestion: " << card.question << endl;
        cout << "Your answer: ";
        getline(cin, userAnswer);

        if (userAnswer == card.answer) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Wrong. Correct answer: " << card.answer << endl;
        }
    }

    cout << "\nYou got " << score << " out of " << flashcards.size() << " correct.\n";
}

// Main program loop
int main() {
    vector<Flashcard> flashcards;
    int choice;

    loadFlashcards(flashcards);

    while (true) {
        cout << "\nFLASHCARD MATH QUIZ GAME\n";
        cout << "1. Take Quiz\n";
        cout << "2. Add Flashcard\n";
        cout << "3. Save & Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear(); // clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the rest of the line
            cout << "Please enter a valid number.\n";
            continue;
        }

        cin.ignore(); // safely clear newline after entering number

        switch (choice) {
            case 1:
                if (flashcards.empty()) {
                    cout << "No flashcards available.\n";
                } else {
                    quiz(flashcards);
                }
                break;
            case 2:
                addFlashcard(flashcards);
                break;
            case 3:
                saveFlashcards(flashcards);
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
