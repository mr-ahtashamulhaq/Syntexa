#pragma once
#include<iostream>
#include<string>
using namespace std;

class Result
{
    string textA;
    string textB;
    double wordPercentage;
    double phrasePercentage;
    double finalPercentage;

    public:
        Result(string& textA, string& textB, double wordPercentage, double phrasePercentage, double finalPercentage)
        {
            this->textA = textA;
            this->textB = textB;
            this->wordPercentage = wordPercentage;
            this->phrasePercentage = phrasePercentage;
            this->finalPercentage = finalPercentage;
        }
};