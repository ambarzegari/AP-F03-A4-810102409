#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const string ADD_FLASHCARD = "add_flashcard";
const string REVIEW_TODAY = "review_today";
const string NEXT_DAY = "next_day";
const string STREAK = "streak";

const string COMPLETE_REVIEW_MASSAGE = "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!";
const string FLASHCARD_ADDED_MASSAGE = "flashcards added to the daily box";

class Flashcard
{
private:
    string question;
    string answer;
    int number_of_incorrect_answer;

public:
    Flashcard(string _question, string _answer)
    {
        question = _question;
        answer = _answer;
        number_of_incorrect_answer = 0;
    }
    string getQuestion() { return question; }
    string getAnswer() { return answer; }
    int getNumberOfIncorrectAnswer() { return number_of_incorrect_answer; }
    void increaseNumberOfIncorrectAnswer()
    {
        number_of_incorrect_answer += 1;
    }
    void resetToZeroNumberOfIncorrectAnswer()
    {
        number_of_incorrect_answer = 0;
    }
    bool checkAnswer(string userAnswer)
    {
        if (answer == userAnswer)
        {
            return true;
        }
        return false;
    }
};

class Box
{
private:
    vector<Flashcard *> flashcard;

public:
    Box()
    {
        flashcard = {};
    }
    void addFlashcardToBox(Flashcard *flashcard_ptr)
    {
        flashcard.push_back(flashcard_ptr);
    }
    Flashcard *getFlashcard(int i)
    {
        return flashcard[i];
    }
    void deleteFlashcardFromBox(Flashcard *flashcard_ptr)
    {
        flashcard.erase(find(flashcard.begin(), flashcard.end(), flashcard_ptr));
    }
    int numberOfFlashcardInBox()
    {
        return flashcard.size();
    }
};

class Day
{
private:
    int dayNumber;
    int correctAnswer;
    int incorrectAnswer;

public:
    Day(int day)
    {
        dayNumber = day;
        correctAnswer = 0;
        incorrectAnswer = 0;
    }
    int getDayNumber() { return dayNumber; }
    int getCorrectAnswerNumber() { return correctAnswer; }
    int getIncorrectAnswerNumber() { return incorrectAnswer; }
    void increseCorrectAnswer()
    {
        correctAnswer += 1;
    }
    void increseIncorrectAnswer()
    {
        incorrectAnswer += 1;
    }
};

class Leitner
{
private:
    vector<Flashcard *> flashcard;

    vector<Day> days;

    int streak;
    int mastered_flashcards;

    Box daily;
    Box once_in_three_days;
    Box weekly;
    Box monthly;

public:
    Leitner()
    {
        flashcard = {};
        days = {Day(1)};
        streak = 0;
        mastered_flashcards = 0;
    };
    void addFlashcard()
    {
        string question;
        string answer;

        Flashcard *fc;


        string s;
        getline(cin, s);
        int number_of_question = stoi(s);

        for (int i = 0; i < number_of_question; i++)
        {
            getline(cin, question);
            getline(cin, answer);
            fc = new Flashcard(question, answer);
            flashcard.push_back(fc);
            daily.addFlashcardToBox(fc);
        }

        cout << FLASHCARD_ADDED_MASSAGE << endl;
    }
    void reviewToday()
    {
        Flashcard *fc;

        Day today = days[days.size() - 1];

        int num_of_fc_in_monthly = monthly.numberOfFlashcardInBox();
        int num_of_fc_in_weekly = weekly.numberOfFlashcardInBox();
        int num_of_fc_in_once_in_three_days = once_in_three_days.numberOfFlashcardInBox();
        int num_of_fc_in_daily = daily.numberOfFlashcardInBox();

        string user_answer;

        int number_of_flashcards;
        cin >> number_of_flashcards;
        int num_fc = number_of_flashcards;

        if (today.getDayNumber() % 30 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < num_of_fc_in_monthly; i++)
            {
                fc = monthly.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;
                cout << endl;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "You'r answer was correct! Well done, keep it up!" << endl;
                    monthly.deleteFlashcardFromBox(fc);
                    mastered_flashcards += 1;
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                    fc->increaseNumberOfIncorrectAnswer();
                    if (fc->getNumberOfIncorrectAnswer() == 2)
                    {
                        weekly.addFlashcardToBox(fc);
                        monthly.deleteFlashcardFromBox(fc);
                        fc->resetToZeroNumberOfIncorrectAnswer();
                    }
                }
            }
            num_fc -= num_of_fc_in_monthly;
        }

        if (today.getDayNumber() % 7 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < num_of_fc_in_weekly; i++)
            {
                fc = weekly.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;
                cout << endl;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "Your answer was correct! Well done, keep it up!" << endl;
                    monthly.addFlashcardToBox(fc);
                    weekly.deleteFlashcardFromBox(fc);
                    fc->resetToZeroNumberOfIncorrectAnswer();
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                    fc->increaseNumberOfIncorrectAnswer();
                    if (fc->getNumberOfIncorrectAnswer() == 2)
                    {
                        once_in_three_days.addFlashcardToBox(fc);
                        weekly.deleteFlashcardFromBox(fc);
                        fc->resetToZeroNumberOfIncorrectAnswer();
                    }
                }
            }
            num_fc -= num_of_fc_in_weekly;
        }

        if (today.getDayNumber() % 3 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < num_of_fc_in_once_in_three_days; i++)
            {
                fc = once_in_three_days.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;
                cout << endl;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "Your answer was correct! Well done, keep it up!" << endl;
                    weekly.addFlashcardToBox(fc);
                    once_in_three_days.deleteFlashcardFromBox(fc);
                    fc->resetToZeroNumberOfIncorrectAnswer();
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                    fc->increaseNumberOfIncorrectAnswer();
                    if (fc->getNumberOfIncorrectAnswer() == 2)
                    {
                        daily.addFlashcardToBox(fc);
                        once_in_three_days.deleteFlashcardFromBox(fc);
                        fc->resetToZeroNumberOfIncorrectAnswer();
                    }
                }
            }
            num_fc -= num_of_fc_in_once_in_three_days;
        }

        if (today.getDayNumber() % 1 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < num_of_fc_in_daily; i++)
            {
                fc = daily.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;
                cout << endl;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "Your answer was correct! Well done, keep it up!" << endl;
                    once_in_three_days.addFlashcardToBox(fc);
                    daily.deleteFlashcardFromBox(fc);
                    fc->resetToZeroNumberOfIncorrectAnswer();
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                }
            }
        }

        cout << COMPLETE_REVIEW_MASSAGE << endl;
    }
    void nextDay()
    {

        Day oldDay = days[days.size() - 1];
        Day newDay = Day(days.size() + 1);
        days.push_back(newDay);

        if (oldDay.getCorrectAnswerNumber() == 0 && oldDay.getIncorrectAnswerNumber() == 0)
        {
            streak = 0;
        }
        else
        {
            streak += 1;
        }
        cout << "Good morning! Today is day " << newDay.getDayNumber() << " of our journey." << endl;
        cout << "Your current streak is: " << streak << endl;
        cout << "Start reviewing to keep your streak!" << endl;
    }
};

int main()
{
    Leitner leitner_boxes;

    string command;
    while (cin >> command)
    {
        if (command == ADD_FLASHCARD)
        {
            leitner_boxes.addFlashcard();
        }
        else if (command == REVIEW_TODAY)
        {
            leitner_boxes.reviewToday();
        }
        else if (command == NEXT_DAY)
        {
            leitner_boxes.nextDay();
        }

        
    }
}