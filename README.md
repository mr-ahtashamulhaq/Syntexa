# 🧠 Syntexa — Text Similarity Analyzer

Syntexa is a C++ project that compares two text files and evaluates how similar they are using both **word-level** and **phrase-level analysis**.

It combines multiple data structures to produce a final similarity score and maintains a history of comparisons with undo support.

---

## 🚀 Features

* 🔤 Word-based similarity using frequency mapping
* 🧩 Phrase-based similarity using sliding window
* 📊 Combined final score (weighted calculation)
* 📚 History tracking using stack (with undo)
* ⚡ Clean and efficient modular design

---

## 🏗️ Project Structure

```
Syntexa/
│
├── main.cpp
├── Preprocessor.h
├── SimilarityEngine.h
├── PhraseDetector.h
├── HistoryManager.h
├── Result.h
├── Document.h
│
├── file1.txt
├── file2.txt
```

---

## ⚙️ How It Works

### Step 1: Input

Reads two text files:

```
file1.txt
file2.txt
```

---

### Step 2: Preprocessing

* Convert to lowercase
* Remove punctuation
* Tokenize into words

---

### Step 3: Word Similarity

* Uses `unordered_map`
* Counts:

  * Common words
  * Unique words

[
\text{Word Similarity} = \frac{\text{Common Words}}{\text{Unique Words}} \times 100
]

---

### Step 4: Phrase Similarity

* Uses **Queue (Linked List)**
* Sliding window of size 3

Example:

```
data structures are
structures are important
are important concepts
```

[
Phrase Similarity = (Matching Phrases ÷ Total Unique Phrases) × 100
]

---

### Step 5: Final Score

[
\text{Final Score} = (0.4 × Word Similarity) + (0.6 × Phrase Similarity)
]

---

### Step 6: History Management

* Stored using **Stack (Linked List)**
* Supports:

  * View history
  * Undo last comparison

---

## 🧪 Example Output

```
==============================
       TEXT SIMILARITY
==============================

Word Similarity   : 68.75%
Phrase Similarity : 45.45%
Final Score       : 54.77%

==============================

--- HISTORY ---

1)
Word   : 68.75%
Phrase : 45.45%
Final  : 54.77%

==============================
```

---

## 🧰 Data Structures Used

| Data Structure | Purpose                            |
| -------------- | ---------------------------------- |
| Vector         | Store words & phrases              |
| HashMap        | Word frequency & lookup            |
| Queue          | Phrase generation (sliding window) |
| Stack          | History & undo functionality       |

---

## 🛠️ How to Run

### Compile

```
g++ main.cpp -o main
```

### Run

```
./main
```

---

## 📄 Sample Input Files

### file1.txt

```
Data structures are very important in programming.
```

### file2.txt

```
Data structures are essential in coding and programming.
```

---

## 🎯 Why This Project Matters

* Demonstrates practical use of multiple data structures
* Shows real-world text analysis logic
* Clean modular design improves readability and maintainability
* Interactive features like history and undo add depth

---

## 👨‍💻 Author

Developed as a Data Structures project to demonstrate applied concepts in C++.

---

## 📌 Future Improvements

* Menu-based interaction system
* GUI interface
* Support for larger documents
* Advanced NLP techniques

---

## ⭐ Summary

Syntexa combines clean design with core DSA concepts to build a functional and presentable text similarity system.

---