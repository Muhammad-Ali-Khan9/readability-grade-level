#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::getline;
using std::round;
using std::setprecision;
using std::setw;
using std::string;
using std::vector;

struct TextStats
{
    int letters = 0;       // a-z, A-Z
    int characters = 0;    // letters and digits (ARI)
    int words = 0;
    int sentences = 0;
    int syllables = 0;
    int complex_words = 0; // 3 or more syllables (Gunning Fog)
};

bool has_letter(const string &token);
bool is_vowel(char c);
vector<string> extract_words(const string &text);
int syllables_in_word(const string &word);
TextStats analyze(const string &text);

double flesch_reading_ease(const TextStats &s);
double flesch_kincaid_grade(const TextStats &s);
double gunning_fog_index(const TextStats &s);
double automated_readability_index(const TextStats &s);
double coleman_liau_index(const TextStats &s);

string flesch_ease_label(double score);
string grade_label(int grade);
void print_report(const TextStats &s);

int main()
{
    cout << "Text: ";
    string text;
    getline(cin, text);

    TextStats stats = analyze(text);
    if (stats.words == 0)
    {
        cout << "No words found. Please enter some text." << endl;
        return 1;
    }

    print_report(stats);
    return 0;
}

bool has_letter(const string &token)
{
    for (unsigned char c : token)
    {
        if (std::isalpha(c))
        {
            return true;
        }
    }
    return false;
}

bool is_vowel(char c)
{
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

// A word is a run of letters, digits, or apostrophes (so "you're" is one word).
vector<string> extract_words(const string &text)
{
    vector<string> words;
    string current;

    for (unsigned char c : text)
    {
        if (std::isalnum(c) || c == '\'')
        {
            current += static_cast<char>(c);
        }
        else if (!current.empty())
        {
            if (has_letter(current))
            {
                words.push_back(current);
            }
            current.clear();
        }
    }

    if (!current.empty() && has_letter(current))
    {
        words.push_back(current);
    }

    return words;
}

// Heuristic syllable count: vowel groups, silent e, and -le endings.
int syllables_in_word(const string &word)
{
    string letters;
    for (unsigned char c : word)
    {
        if (std::isalpha(c))
        {
            letters += static_cast<char>(std::tolower(c));
        }
    }

    if (letters.empty())
    {
        return 0;
    }
    if (letters.size() <= 3)
    {
        return 1;
    }

    const bool ends_with_consonant_le =
        letters.size() >= 3 &&
        letters[letters.size() - 2] == 'l' &&
        letters.back() == 'e' &&
        !is_vowel(letters[letters.size() - 3]);

    string core = letters;
    if (core.back() == 'e' && !ends_with_consonant_le)
    {
        core.pop_back();
    }

    int count = 0;
    bool prev_vowel = false;
    for (char c : core)
    {
        const bool vowel = is_vowel(c);
        if (vowel && !prev_vowel)
        {
            count++;
        }
        prev_vowel = vowel;
    }

    return count > 0 ? count : 1;
}

TextStats analyze(const string &text)
{
    TextStats stats;

    for (unsigned char c : text)
    {
        if (std::isalpha(c))
        {
            stats.letters++;
        }
        if (std::isalnum(c))
        {
            stats.characters++;
        }
    }

    // Consecutive . ! ? count as a single sentence ending.
    bool in_terminator = false;
    for (unsigned char c : text)
    {
        if (c == '.' || c == '!' || c == '?')
        {
            if (!in_terminator)
            {
                stats.sentences++;
                in_terminator = true;
            }
        }
        else if (!std::isspace(c))
        {
            in_terminator = false;
        }
    }

    const vector<string> words = extract_words(text);
    stats.words = static_cast<int>(words.size());

    for (const string &word : words)
    {
        const int syllables = syllables_in_word(word);
        stats.syllables += syllables;
        if (syllables >= 3)
        {
            stats.complex_words++;
        }
    }

    // Text with words but no . ! ? is still one sentence.
    if (stats.words > 0 && stats.sentences == 0)
    {
        stats.sentences = 1;
    }

    return stats;
}

double flesch_reading_ease(const TextStats &s)
{
    const double asl = static_cast<double>(s.words) / s.sentences;
    const double asw = static_cast<double>(s.syllables) / s.words;
    return 206.835 - 1.015 * asl - 84.6 * asw;
}

double flesch_kincaid_grade(const TextStats &s)
{
    const double asl = static_cast<double>(s.words) / s.sentences;
    const double asw = static_cast<double>(s.syllables) / s.words;
    return 0.39 * asl + 11.8 * asw - 15.59;
}

double gunning_fog_index(const TextStats &s)
{
    const double asl = static_cast<double>(s.words) / s.sentences;
    const double percent_complex = 100.0 * s.complex_words / s.words;
    return 0.4 * (asl + percent_complex);
}

double automated_readability_index(const TextStats &s)
{
    return 4.71 * (static_cast<double>(s.characters) / s.words) +
           0.5 * (static_cast<double>(s.words) / s.sentences) - 21.43;
}

double coleman_liau_index(const TextStats &s)
{
    const double L = (static_cast<double>(s.letters) / s.words) * 100.0;
    const double S = (static_cast<double>(s.sentences) / s.words) * 100.0;
    return 0.0588 * L - 0.296 * S - 15.8;
}

string flesch_ease_label(double score)
{
    if (score >= 90.0)
    {
        return "Very Easy";
    }
    if (score >= 80.0)
    {
        return "Easy";
    }
    if (score >= 70.0)
    {
        return "Fairly Easy";
    }
    if (score >= 60.0)
    {
        return "Standard";
    }
    if (score >= 50.0)
    {
        return "Fairly Difficult";
    }
    if (score >= 30.0)
    {
        return "Difficult";
    }
    return "Very Difficult";
}

string grade_label(int grade)
{
    if (grade < 1)
    {
        return "Before Grade 1";
    }
    if (grade >= 16)
    {
        return "Grade 16+";
    }
    return "Grade " + std::to_string(grade);
}

void print_report(const TextStats &s)
{
    const double asl = static_cast<double>(s.words) / s.sentences;
    const double asw = static_cast<double>(s.syllables) / s.words;

    const double ease = flesch_reading_ease(s);
    const double fk = flesch_kincaid_grade(s);
    const double fog = gunning_fog_index(s);
    const double ari = automated_readability_index(s);
    const double cli = coleman_liau_index(s);
    const int cli_grade = static_cast<int>(round(cli));

    cout << endl;
    cout << "==================================================" << endl;
    cout << "  READABILITY REPORT" << endl;
    cout << "==================================================" << endl;
    cout << endl;

    cout << "  TEXT STATISTICS" << endl;
    cout << "  ---------------" << endl;
    cout << "  Letters                 : " << s.letters << endl;
    cout << "  Characters (alnum)      : " << s.characters << endl;
    cout << "  Words                   : " << s.words << endl;
    cout << "  Sentences               : " << s.sentences << endl;
    cout << "  Syllables               : " << s.syllables << endl;
    cout << "  Complex words (3+ syl.) : " << s.complex_words << endl;
    cout << fixed << setprecision(2);
    cout << "  Avg. words / sentence   : " << asl << endl;
    cout << "  Avg. syllables / word   : " << asw << endl;
    cout << endl;

    cout << "  INDEXES" << endl;
    cout << "  -------" << endl;
    cout << setprecision(2);
    cout << "  Flesch Reading Ease           : " << setw(6) << ease
         << "  (" << flesch_ease_label(ease) << ")" << endl;
    cout << "  Flesch-Kincaid Grade Level    : " << setw(6) << fk
         << "  (" << grade_label(static_cast<int>(round(fk))) << ")" << endl;
    cout << "  Gunning Fog Index             : " << setw(6) << fog
         << "  (" << grade_label(static_cast<int>(round(fog))) << ")" << endl;
    cout << "  Automated Readability Index   : " << setw(6) << ari
         << "  (" << grade_label(static_cast<int>(round(ari))) << ")" << endl;
    cout << "  Coleman-Liau Index            : " << setw(6) << cli
         << "  (" << grade_label(cli_grade) << ")" << endl;
    cout << "==================================================" << endl;
}
