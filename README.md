# Readability Grade Level

A C++ program that estimates the U.S. school grade needed to understand a piece of text using the **Coleman–Liau index**.

Enter a sentence or paragraph. The program counts letters, words, and sentences, then prints a grade level such as `Grade 5`, `Before Grade 1`, or `Grade 16+`.

## Formula

```
index = 0.0588 * L - 0.296 * S - 15.8
```

| Symbol | Meaning |
|--------|---------|
| **L** | Average number of letters per 100 words |
| **S** | Average number of sentences per 100 words |

The index is rounded to the nearest whole number.

## How text is counted

| Item | Rule |
|------|------|
| **Letters** | Any alphabetic character (`a–z`, `A–Z`) |
| **Words** | Sequences of characters separated by spaces |
| **Sentences** | End with `.`, `!`, or `?` |

## Output

| Index | Printed result |
|-------|----------------|
| Less than 1 | `Before Grade 1` |
| 1 through 15 | `Grade X` |
| 16 or higher | `Grade 16+` |

## Requirements

- A C++17 compiler (`g++` recommended)
- On Windows, MinGW-w64 via [MSYS2](https://www.msys2.org/) works well

## Build

```bash
g++ -std=c++17 -o readability readability.cpp
```

On Windows:

```powershell
g++ -std=c++17 -o readability.exe readability.cpp
```

## Run

```bash
./readability
```

On Windows:

```powershell
.\readability.exe
```

When prompted, type a line of text and press Enter.

## Examples

```
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
```

```
Text: Harry Potter was a highly unusual boy in many ways.
Grade 5
```

```
Text: Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, "and what is the use of a book," thought Alice, "without pictures or conversation?"
Grade 8
```

## Project layout

```
.
├── readability.cpp   # Source program (uses std::string)
└── README.md
```

## License

This project is provided for educational use.
