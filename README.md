# Readability Grade Level

A C++ program that scores English text with several standard readability formulas and prints a full letter, word, sentence, and syllable analysis.

Enter a sentence or paragraph. The program reports counts, averages, and five indexes used to estimate how hard the text is to read.

## Indexes

| Index | Formula | What it reports |
|-------|---------|-----------------|
| **Flesch Reading Ease** | `206.835 − 1.015 × ASL − 84.6 × ASW` | 0–100 score (higher is easier) |
| **Flesch–Kincaid Grade Level** | `0.39 × ASL + 11.8 × ASW − 15.59` | U.S. grade level |
| **Gunning Fog Index** | `0.4 × (ASL + 100 × complex_words / words)` | U.S. grade level |
| **Automated Readability Index** | `4.71 × (characters / words) + 0.5 × ASL − 21.43` | U.S. grade level |
| **Coleman–Liau Index** | `0.0588 × L − 0.296 × S − 15.8` | U.S. grade level |

Where:

- **ASL** = average sentence length (words / sentences)
- **ASW** = average syllables per word (syllables / words)
- **L** = average letters per 100 words
- **S** = average sentences per 100 words
- **Complex words** = words with 3 or more syllables

### Flesch Reading Ease scale

| Score | Label |
|-------|--------|
| 90–100 | Very Easy |
| 80–89 | Easy |
| 70–79 | Fairly Easy |
| 60–69 | Standard |
| 50–59 | Fairly Difficult |
| 30–49 | Difficult |
| Below 30 | Very Difficult |

Grade-style indexes are also mapped as `Before Grade 1`, `Grade 1`–`Grade 15`, or `Grade 16+`.

## How text is counted

| Item | Rule |
|------|------|
| **Letters** | Alphabetic characters (`a–z`, `A–Z`) |
| **Characters** | Letters and digits (used by ARI) |
| **Words** | Runs of letters, digits, or apostrophes; extra spaces and punctuation are ignored |
| **Sentences** | End with `.`, `!`, or `?`; `What?!` counts as one sentence |
| **Syllables** | Vowel groups, with silent `e` and `-le` endings handled by a heuristic |
| **Complex words** | Words with 3 or more syllables |

If the text has words but no sentence punctuation, it is treated as one sentence. Empty input is rejected.

Syllable counts are heuristic, so results can differ slightly from published scores that use a dictionary.

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

## Example

```
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!

==================================================
  READABILITY REPORT
==================================================

  TEXT STATISTICS
  ---------------
  Letters                 : ...
  Characters (alnum)      : ...
  Words                   : ...
  Sentences               : ...
  Syllables               : ...
  Complex words (3+ syl.) : ...
  Avg. words / sentence   : ...
  Avg. syllables / word   : ...

  INDEXES
  -------
  Flesch Reading Ease           : ...  (Fairly Easy)
  Flesch-Kincaid Grade Level    : ...  (Grade ...)
  Gunning Fog Index             : ...  (Grade ...)
  Automated Readability Index   : ...  (Grade ...)
  Coleman-Liau Index            : ...  (Grade 3)
==================================================
```

## Project layout

```
.
├── readability.cpp   # Analyzer and all five indexes
└── README.md
```

## License

This project is provided for educational use.
