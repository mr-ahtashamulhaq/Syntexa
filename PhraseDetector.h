#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

/*
 * NODE CLASS
 * ----------
 * A single unit (node) in our linked list based Queue.
 * Each node holds one word and a pointer to the next node.
 *
 *   [ "This" | next ] --> [ "is" | next ] --> [ "me" | null ]
 */
class Node{
public:
    string word;   // the word this node stores
    Node* next;    // pointer to the next node in the queue

    Node(string w){
        word = w;
        next = nullptr;  // new node points to nothing by default
    }
};

/*
 * QUEUE CLASS (Linked List based)
 * --------------------------------
 * A custom Queue built using the Node class above.
 * We use this as our SLIDING WINDOW container.
 *
 * How it works visually:
 *
 *   front                        rear
 *     |                            |
 *   [ "This" ] --> [ "is" ] --> [ "me" ]
 *
 *   push("again") → adds to rear
 *   pop()         → removes from front
 *
 * This gives us a moving window over words:
 *   [This is me] → pop "This", push "again" → [is me again]
 */
class Queue{
private:
    Node* front;  // points to the oldest word (left side of window)
    Node* rear;   // points to the newest word (right side of window)
    int sz;       // tracks how many words are currently in the queue

public:
    /*
     * Constructor: starts with an empty queue.
     * front and rear point to nothing, size is 0.
     */
    Queue(){
        front = rear = nullptr;
        sz = 0;
    }

    /*
     * PUSH — Add a new word to the REAR of the queue.
     *
     * Case 1: Queue is empty → new node becomes both front and rear.
     * Case 2: Queue has nodes → attach new node after current rear,
     *         then move rear forward to the new node.
     *
     *   Before: [This] --> [is]
     *                       ^rear
     *
     *   push("me")
     *
     *   After:  [This] --> [is] --> [me]
     *                               ^rear
     */
    void push(string word){
        Node* newNode = new Node(word);
        if(front == nullptr){
            front = rear = newNode;
            sz++;
            return;
        }
        rear->next = newNode;  // link current rear to new node
        rear = newNode;        // move rear forward to new node
        sz++;
    }

    /*
     * POP — Remove the word from the FRONT of the queue.
     * This is how we "slide" the window forward.
     *
     *   Before: [This] --> [is] --> [me]
     *            ^front
     *
     *   pop()
     *
     *   After:  [is] --> [me]
     *            ^front
     *
     * Memory is freed using delete to avoid memory leaks.
     * If the queue becomes empty, rear is also set to nullptr.
     */
    void pop(){
        if(front == nullptr){
            cout << "Queue is Empty";
            return;
        }
        Node* del = front;          // save front to delete later
        front = front->next;        // move front one step forward
        if(front == nullptr)
            rear = nullptr;         // queue is now empty, reset rear too
        del->next = nullptr;        // safely disconnect the deleted node
        delete del;                 // free memory
        sz--;
    }

    /*
     * CLEAR — Empties the entire queue by repeatedly popping.
     * Called at the start of generatePhrases() so leftover words
     * from the previous call don't mix into the new window.
     */
    void clear(){
        while(!isEmpty()) pop();
    }

    /*
     * GET PHRASE — Builds and returns a single string from all
     * words currently in the queue, joined by spaces.
     *
     *   Queue: [This] --> [is] --> [me]
     *   Returns: "This is me"
     *
     * This is called when the window hits exactly k words,
     * to capture the current window as one phrase.
     */
    string getPhrase(){
        string phrase = "";
        Node* temp = front;
        while(temp != nullptr){
            phrase += temp->word;
            if(temp->next != nullptr) phrase += " ";  // space between words
            temp = temp->next;
        }
        return phrase;
    }

    /*
     * GET FRONT — Returns the word at the front of the queue.
     * Returns empty string if queue is empty.
     */
    string getFront(){
        return front ? front->word : "";
    }

    /*
     * DISPLAY — Prints all words in the queue on one line.
     * Useful for debugging the current window state.
     */
    void display(){
        Node* temp = front;
        while(temp != nullptr){
            cout << temp->word << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool isEmpty(){ return sz == 0; }
    int getSize(){ return sz; }
};

/*
 * PHRASE DETECTOR CLASS
 * ----------------------
 * The main class that uses the Queue above to:
 *   1. Generate 3-word phrases from a list of words  (sliding window)
 *   2. Count how many phrases are shared between two lists (HashMap)
 *   3. Score how similar two phrase lists are          (Jaccard formula)
 */
class PhraseDetector{
private:
    int len;              // length of the input word list
    int k;                // window size (3 words per phrase)
    vector<string> phrases; // stores generated phrases
    Queue queue;          // our sliding window

public:
    /*
     * Constructor: window size k is fixed at 3.
     * A phrase is always 3 consecutive words.
     */
    PhraseDetector(){
        k = 3;
        len = 0;
    }

    /*
     * GENERATE PHRASES — Sliding window using the Queue.
     * ------------------------------------------------
     * Slides a window of size k=3 across the word list.
     * Each time the window fills up, the current 3 words
     * become one phrase, then the oldest word is removed
     * to slide the window one step forward.
     *
     *   words = ["This", "is", "me", "again"]
     *
     *   Step 1: push "This" → queue: [This]           size=1
     *   Step 2: push "is"   → queue: [This, is]       size=2
     *   Step 3: push "me"   → queue: [This, is, me]   size=3 → phrase: "This is me"
     *                         pop "This" → queue: [is, me]
     *   Step 4: push "again"→ queue: [is, me, again]  size=3 → phrase: "is me again"
     *                         pop "is"  → queue: [me, again]
     *
     *   Result: ["This is me", "is me again"]
     */
    vector<string> generatePhrases(vector<string> words){
        len = words.size();
        phrases.clear();   // reset phrases so previous results don't carry over
        queue.clear();     // reset queue so previous words don't carry over

        for(int i = 0; i < len; i++){
            queue.push(words[i]);       // expand window from the right

            if(queue.getSize() == k){
                phrases.push_back(queue.getPhrase()); // capture the current window
                queue.pop();                          // slide window: remove leftmost word
            }
        }
        return phrases;
    }

    /*
     * COUNT MATCHING PHRASES — HashMap approach O(n + m).
     * ---------------------------------------------------
     * Counts how many phrases appear in BOTH pA and pB.
     *
     * Step 1: Load all phrases from pA into a HashMap with their frequency.
     *         freqMap["This is me"] = 1
     *         freqMap["is me again"] = 1
     *
     * Step 2: Loop through pB and check each phrase against the map.
     *         If found and count > 0 → it's a match, increment count,
     *         decrement the map (prevents double counting the same phrase).
     *
     *   pA = ["This is me", "is me again"]
     *   pB = ["This is me", "is me too"]
     *   → 1 match: "This is me"
     */
    int countMatchingPhrases(vector<string> pA, vector<string> pB){
        int count = 0;
        unordered_map<string, int> freqMap;

        /* Pass 1: store pA phrases and their frequency in the map */
        for(const string& p : pA) freqMap[p]++;

        /* Pass 2: check each pB phrase against the map */
        for(const string& p : pB){
            if(freqMap.count(p) && freqMap[p] > 0){
                count++;
                freqMap[p]--;  // decrement so same phrase isn't matched twice
            }
        }
        return count;
    }

    /*
     * COMPUTE PHRASE SIMILARITY — Jaccard Similarity Score.
     * ------------------------------------------------------
     * Measures how similar two phrase lists are.
     * Returns a value between 0.0 (nothing in common) and 1.0 (identical).
     *
     * Formula:
     *   score = matches / (|pA| + |pB| - matches)
     *
     * Example:
     *   pA = ["This is me", "is me again"]   → size 2
     *   pB = ["This is me", "is me too"]     → size 2
     *   matches   = 1
     *   unionSize = 2 + 2 - 1 = 3
     *   score     = 1 / 3 = 0.333
     *
     * Edge cases:
     *   Both empty → 1.0 (identical by definition)
     *   One empty  → 0.0 (nothing in common)
     */
    double computePhraseSimilarity(vector<string> pA, vector<string> pB){
        if(pA.empty() && pB.empty()) return 1.0;
        if(pA.empty() || pB.empty()) return 0.0;

        int matches   = countMatchingPhrases(pA, pB);
        int unionSize = pA.size() + pB.size() - matches;

        return (double)matches / unionSize;
    }

    /*
     * DISPLAY — Prints each phrase in the list wrapped in parentheses.
     *   ["This is me", "is me again"] → (This is me)
     *                                   (is me again)
     */
    void display(vector<string> p){
        for(const string& s : p)
            cout << "(" << s << ")" << endl;
    }
};

// int main(){
//     PhraseDetector pd;

//     vector<string> wordsA = {"This", "is", "me", "again"};
//     vector<string> wordsB = {"This", "is", "me", "too"};

//     vector<string> phrasesA = pd.generatePhrases(wordsA);
//     vector<string> phrasesB = pd.generatePhrases(wordsB);

//     cout << "Phrases A:" << endl;
//     pd.display(phrasesA);

//     cout << "Phrases B:" << endl;
//     pd.display(phrasesB);

//     cout << "\nMatching phrases : " << pd.countMatchingPhrases(phrasesA, phrasesB) << endl;
//     cout << "Similarity score : " << pd.computePhraseSimilarity(phrasesA, phrasesB) << endl;

//     return 0;
// }