# 🧠 Syntexa - Text Similarity Analyzer

Syntexa is a **DSA Semester Project** built in C++ that compares two text files and evaluates how similar they are using both word-level and phrase-level analysis.

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

* Word-based similarity using frequency mapping
* Phrase-based similarity using sliding window
* Combined final score using mathematical formula
* History tracking using stack (with undo)
* Clean modular class-based design

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

* Uses HashMap (`unordered_map`)
* Finds:

  * Common words
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
