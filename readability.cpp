#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::round;
using std::string;

int count_letters(const string &text);
int count_words(const string &text);
int count_sentences(const string &text);
int coleman_liau_grade(int letters, int words, int sentences);
void print_grade(int grade);

int main()
{
    cout << "Text: ";
    string text;
    getline(cin, text);

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int grade = coleman_liau_grade(letters, words, sentences);

    print_grade(grade);
    return 0;
}

// A letter is any alphabetic character (a-z or A-Z).
int count_letters(const string &text)
{
    int letters = 0;
    for (char c : text)
    {
        if (std::isalpha(static_cast<unsigned char>(c)))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(const string &text)
{
    if (text.empty())
    {
        return 0;
    }

    int words = 1;
    for (char c : text)
    {
        if (c == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(const string &text)
{
    int sentences = 0;
    for (char c : text)
    {
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

int coleman_liau_grade(int letters, int words, int sentences)
{
    if (words == 0)
    {
        return 0;
    }

    double L = (static_cast<double>(letters) / words) * 100.0;
    double S = (static_cast<double>(sentences) / words) * 100.0;
    double index = 0.0588 * L - 0.296 * S - 15.8;

    return static_cast<int>(round(index));
}

void print_grade(int grade)
{
    if (grade < 1)
    {
        cout << "Before Grade 1" << endl;
    }
    else if (grade >= 16)
    {
        cout << "Grade 16+" << endl;
    }
    else
    {
        cout << "Grade " << grade << endl;
    }
}
