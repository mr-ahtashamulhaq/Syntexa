#pragma once
#include <iostream>
#include <string>
#include "Result.h"

using namespace std;

class Node
{
    public:
        Result data;
        Node* next;

        Node(Result d)
        {
            data = d;
            next = NULL; 
        }
};

class History
{
    Node* top;
    public:
        History(){ top = NULL; }
        void addResultInHistory(Result r)
        {
            Node* newNode = new Node(r);

            newNode->next = top;
            top = newNode;
        }

        void undoLast()
        {
            if(top == NULL)
            {
                cout<<"\nNo History to UNDO! "<<endl;
            }
            else
            {
                Node* temp = top;
                top = top->next;
                delete temp;
            }
        }
        void displayHistory()
        {
            if(top == NULL)
            {
                cout<<"--- History is Empty! --- "<<endl;
            }
            else
            {
                cout<<"\n--- HISTORY ---"<<endl<<endl;
                Node* temp = top;
                int count = 1;
                while (temp != NULL)
                {
                    cout<<count<<")"<<endl;
                    cout<<"Word: "<<temp->data.wordPercentage<<"%"<<endl;
                    cout<<"Phrase: "<<temp->data.phrasePercentage<<"%"<<endl;
                    cout<<"Final: "<<temp->data.finalPercentage<<"%"<<endl;
                    cout<<endl;
                    temp = temp->next;
                    count++;
                }
            }
        }
};