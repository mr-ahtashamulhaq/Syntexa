# 🧠 Syntexa - Text Similarity Analyzer

Syntexa is a **DSA Semester Project** built in C++ that compares two text or PDF files and evaluates how similar they are using both word-level and phrase-level analysis.

The goal was not just to build a working system, but to apply core data structure concepts in a clear and practical way.

---

## 🎓 Project Requirement

As part of the semester, the project required:

* Use of **minimum 4 data structures**
* Clear justification of each structure
* Proper implementation (not forced usage)

We designed the system around:

* Array (vector)
* HashMap
* Queue
* Linked List (Stack implementation)

---

## 🚀 Features

* **PDF & Text Support:** Reads and extracts text from `.txt` and `.pdf` files using Poppler.
* **Menu-Driven Interface:** Interactive terminal UI for multiple operations without restarting.
* **Word-based similarity:** Using frequency mapping.
* **Phrase-based similarity:** Using sliding window.
* **Combined final score:** Using mathematical formula.
* **History tracking:** Using a stack (with undo functionality).
* **Clean modular class-based design.**

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
├── poppler-26.02.0/ (For PDF Extraction)
├── file1.txt
├── file2.txt
```

---

## ⚙️ How It Works

### Step 1: Input

Reads two files via an interactive menu. Supported formats:
* `.txt`
* `.pdf` (Uses Poppler `pdftotext` extraction utility)

---

### Step 2: Preprocessing

* Convert to lowercase
* Replace punctuation with spaces
* Tokenize into words

---

### Step 3: Word Similarity

* Uses HashMap (`unordered_map`)
* Finds:
  * Common words (taking frequency into account)
  * Total unique words

Formula:

```
Word Similarity = (Common Words / Unique Words) × 100
```

---

### Step 4: Phrase Similarity

* Uses Queue (Linked List)
* Sliding window of size 3

Example:

```
data structures are
structures are important
are important concepts
```

Formula:

```
Phrase Similarity = (Matching Phrases / Total Unique Phrases) × 100
```

---

### Step 5: Final Score

```
Final Score = (0.4 × Word Similarity) + (0.6 × Phrase Similarity)
```

The verdict is decided based on practical boundaries:
* `> 60%`: Possible Plagiarism
* `40% - 60%`: Highly Similar
* `20% - 40%`: Partially Similar
* `< 20%`: Not Similar

---

### Step 6: History Management

* Implemented using Stack (Linked List)
* Supports:
  * View history
  * Undo last comparison

---

## 🧪 Example Output

```
==============================
      SYNTEXA MAIN MENU
==============================
1. Compare Two Files
2. View History
3. Undo Last Comparison
4. Exit
==============================
Enter your choice: 1
Enter the path of the first file to compare: file-1.pdf
Enter the path of the second file to compare: file-2.pdf

==============================
       TEXT SIMILARITY
==============================

Word Similarity   : 64.1026%
Phrase Similarity : 2.04082%
Final Score       : 26.8655%
Verdict           : Partially Similar

==============================
```

---

## 🧰 Data Structures Used

| Data Structure | Purpose                            |
| -------------- | ---------------------------------- |
| Vector         | Store words & phrases              |
| HashMap        | Fast lookup and frequency mapping  |
| Queue          | Phrase generation (sliding window) |
| Linked List    | Stack for history + undo           |

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

## 🎯 Learning Outcome

* Applied core DSA concepts in a real system
* Understood how different data structures solve specific problems
* Improved logic building by implementing everything from scratch
* Learned debugging, integration, and modular design

---

## 👨‍💻 Developers

* [Muhammad Ahtasham Ul Haq](https://www.linkedin.com/in/mr-ahtasham-ul-haq/)
* [Hasnain Ali Asghar](https://www.linkedin.com/in/hasnain-ali-asghar-2123222a6/)
