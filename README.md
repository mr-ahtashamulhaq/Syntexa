# 🧱 📁 Project Structure

```text
Syntexa/
│
├── main.cpp
├── Document.h / Document.cpp
├── Preprocessor.h / Preprocessor.cpp
├── SimilarityEngine.h / SimilarityEngine.cpp
├── PhraseDetector.h / PhraseDetector.cpp
├── HistoryManager.h / HistoryManager.cpp
├── Result.h
│
├── textA.txt
├── textB.txt
```

---

# 🧠 📦 CLASSES YOU WILL MAKE (FINAL LIST)

## 1. `Document`

👉 Responsible for reading text files

### Attributes:

```cpp
string fileName;
string content;
```

### Methods:

* `Document(string fileName)`
  → Constructor, sets file name

* `void loadContent()`
  → Opens file and reads full text into `content` (**uses Array internally via string buffer**)

* `string getContent()`
  → Returns text content

---

## 2. `Preprocessor`

👉 Cleans and tokenizes text

### Methods:

* `vector<string> tokenize(string text)`
  → Splits text into words (**uses Array/Vector**)

* `string toLowerCase(string text)`
  → Converts all characters to lowercase

* `string removePunctuation(string text)`
  → Removes punctuation symbols

---

# ⚠️ Preprocessing Flow

```cpp
text → lowercase → remove punctuation → tokenize → vector<string>
```

---

## 3. `SimilarityEngine`

👉 Handles **word-level similarity**

### Attributes:

```cpp
unordered_map<string, int> freqA;
unordered_map<string, int> freqB;
```

### Methods:

* `void buildFrequencyMap(vector<string> words, unordered_map<string,int>& freq)`
  → Builds frequency map (**uses HashMap**)

* `int countCommonWords()`
  → Counts words present in both maps (**uses HashMap lookup**)

* `int countUniqueWords()`
  → Calculates union of words (**uses HashMap**)

* `double computeWordSimilarity()`
  → Returns similarity percentage

---

## 4. `PhraseDetector`

👉 Handles **phrase matching using Queue**

### Methods:

* `vector<string> generatePhrases(vector<string> words)`
  → Creates 3-word phrases using **Queue (sliding window)**

* `int countMatchingPhrases(vector<string> pA, vector<string> pB)`
  → Counts matching phrases (**uses Array + optional HashMap for speed**)

* `double computePhraseSimilarity(vector<string> pA, vector<string> pB)`
  → Returns phrase similarity score

---

# ⚠️ IMPORTANT (Queue Usage)

Inside `generatePhrases()`:

```cpp
queue<string> q;
```

👉 Purpose:

* Maintain sliding window of size 3
* Push word → if size == 3 → make phrase → pop

---

## 5. `Result`

👉 Simple data container

### Attributes:

```cpp
string textA;
string textB;
double wordScore;
double phraseScore;
double finalScore;
```

(No methods needed OR just constructor)

---

## 6. `HistoryManager`

👉 Handles **Stack (history + undo)**

### Attributes:

```cpp
stack<Result> history;
```

### Methods:

* `void pushResult(Result r)`
  → Stores result (**uses Stack push**)

* `void undoLast()`
  → Removes last result (**uses Stack pop**)

* `void showHistory()`
  → Displays all stored results (**iterate stack copy**)

---

# 🔗 HOW EVERYTHING CONNECTS (FLOW)

## 🔄 Execution Flow in `main.cpp`

```cpp
1. Load documents
2. Preprocess text
3. Generate tokens (Array)
4. Build frequency maps (HashMap)
5. Compute word similarity
6. Generate phrases (Queue)
7. Compute phrase similarity
8. Combine scores
9. Store in stack
10. Display result
```

---

# 🧪 MAIN FUNCTION (LOGIC FLOW)

```cpp
Document docA("textA.txt");
Document docB("textB.txt");

docA.loadContent();
docB.loadContent();

Preprocessor prep;

string cleanA = prep.removePunctuation(prep.toLowerCase(docA.getContent()));
string cleanB = prep.removePunctuation(prep.toLowerCase(docB.getContent()));

vector<string> wordsA = prep.tokenize(cleanA);
vector<string> wordsB = prep.tokenize(cleanB);

SimilarityEngine sim;

sim.buildFrequencyMap(wordsA, sim.freqA);
sim.buildFrequencyMap(wordsB, sim.freqB);

double wordScore = sim.computeWordSimilarity();

PhraseDetector pd;

vector<string> phrasesA = pd.generatePhrases(wordsA);
vector<string> phrasesB = pd.generatePhrases(wordsB);

double phraseScore = pd.computePhraseSimilarity(phrasesA, phrasesB);

double finalScore = 0.4 * wordScore + 0.6 * phraseScore;

Result res = {docA.getContent(), docB.getContent(), wordScore, phraseScore, finalScore};

HistoryManager hm;
hm.pushResult(res);
```

---

# 🎯 EXACT DATA STRUCTURE USAGE (CLEAR FOR VIVA)

| Data Structure     | Where Used       | Purpose                          |
| ------------------ | ---------------- | -------------------------------- |
| **Array (vector)** | Token storage    | Store words & phrases            |
| **HashMap**        | SimilarityEngine | Fast word lookup & frequency     |
| **Queue**          | PhraseDetector   | Sliding window phrase generation |
| **Stack**          | HistoryManager   | Store results & undo             |

---

# ⚠️ IMPORTANT DESIGN TIPS

* Keep each class **small & focused**
* Avoid mixing logic
* Use **.h for declarations** and **.cpp for implementation**

---

# 🔥 Final Advice

This structure is:

* Clean ✅
* Modular ✅
* Easy to debug ✅
* Easy to explain in viva ✅