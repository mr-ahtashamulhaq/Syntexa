#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Node
{
    public:
        string word;
        Node* next;

        Node(string w)
        {
            word = w;
            next = nullptr;
        }
};

class Queue
{
    Node* front;  // (left side of window)
    Node* rear;   // right side of window)
    int size;

    public:
        Queue()
        {
            front = rear = nullptr;
            size = 0;
        }

        void push(string word)
        {
            Node* newNode = new Node(word);
            if(front == nullptr)
            {
                front = rear = newNode;
                size++;
                return;
            }
            rear->next = newNode;
            rear = newNode;
            size++;
        }

        void pop()
        {
            if(front == nullptr)
            {
                cout << "Queue is Empty";
                return;
            }
            Node* del = front;
            front = front->next;
            if(front == nullptr)
                rear = nullptr;

            del->next = nullptr;
            delete del;
            size--;
        }

        void clear() // Make Queue Empty
        {
            while(!isEmpty()) pop();
        }

        string getPhrase() // Make String phrase from queue - when queue hit 3 size
        {
            string phrase = "";
            Node* temp = front;
            while(temp != nullptr)
            {
                phrase += temp->word;
                if(temp->next != nullptr) 
                    phrase += " ";  // space between words
                temp = temp->next;
            }
            return phrase;
        }

        string getFront()
        {
            return front ? front->word : "";
        }

        void display()
        {
            Node* temp = front;
            while(temp != nullptr)
            {
                cout << temp->word << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        bool isEmpty(){ return size == 0; }

        int getSize(){ return size; }
    };

class PhraseDetector
{
    private:
        int len;
        int k;
        vector<string> phrases; // stores all phrases
        Queue tempQueue; //Sliding Window

    public:
        PhraseDetector()
        {
            k = 3;
            len = 0;
        }

        vector<string> generatePhrases(vector<string> words)
        {
            len = words.size();
            phrases.clear();
            tempQueue.clear();

            for(int i = 0; i < len; i++)
            {
                tempQueue.push(words[i]);

                if(tempQueue.getSize() == k)
                {
                    string newPhrase = tempQueue.getPhrase();
                    phrases.push_back(newPhrase); // save the current window
                    tempQueue.pop();             // slide window: remove leftmost word
                }
            }
            return phrases;
        }

        int countMatchingPhrases(vector<string> phrasesA, vector<string> phrasesB)
        {
            int count = 0;
            unordered_map<string, int> freq;
            
            for(string& ph : phrasesA) 
                freq[ph]++;

            for(string& ph : phrasesB)
            {
                if(freq.count(ph) && freq[ph] > 0)
                {
                    count++;
                    freq[ph]--;  // decrement so same phrase isn't matched twice
                }
            }
            return count;
        }

        double computePhraseSimilarity(vector<string> pA, vector<string> pB)
        {
            if(pA.empty() && pB.empty()) //Both Empty 
                return 100.0;

            if(pA.empty() || pB.empty()) // One Empty mean nothing common
                return 0.0;

            int matches   = countMatchingPhrases(pA, pB);
            int unionSize = pA.size() + pB.size() - matches;

            return ( (double)matches / unionSize ) * 100; // (Common / Union)* 100
        }

        void display(vector<string> phr)
        {
            for(string& p : phr)
                cout << "(" << p << ")" << endl;
        }
};