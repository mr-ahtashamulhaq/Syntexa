#pragma once
#include <iostream>
#include <string>
#include "Result.h"

using namespace std;

class HistoryNode
{
public:
    Result data;
    HistoryNode* next;

    HistoryNode(Result d) : data(d), next(nullptr) {}
};

class History
{
    HistoryNode* top;

public:
    History() : top(nullptr) {}

    void addResultInHistory(Result r)
    {
        HistoryNode* newNode = new HistoryNode(r);
        newNode->next = top;
        top = newNode;
    }

    void undoLast()
    {
        if (top == nullptr)
        {
            cout << "\nNo History to UNDO!\n";
            return;
        }

        HistoryNode* temp = top;
        top = top->next;
        delete temp;
    }

    void displayHistory()
    {
        if (top == nullptr)
        {
            cout << "\n--- History is Empty ---\n";
            return;
        }

        cout << "\n--- HISTORY ---\n\n";

        HistoryNode* temp = top;
        int count = 1;

        while (temp != nullptr)
        {
            cout << count++ << ")\n";
            cout << "Word   : " << temp->data.wordPercentage << "%\n";
            cout << "Phrase : " << temp->data.phrasePercentage << "%\n";
            cout << "Final  : " << temp->data.finalPercentage << "%\n\n";
            cout << "Verdict: " << temp-> data.verdict << "\n";

            temp = temp->next;
        }
    }
};