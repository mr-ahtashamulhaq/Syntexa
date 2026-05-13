#pragma once
#include<iostream>
#include<string>
using namespace std;

class Result
{
    public:
    string textA;
    string textB;
    string verdict;
    double wordPercentage;
    double phrasePercentage;
    double finalPercentage;

        Result(){}
        
        Result(string& textA, string& textB, double wordPercentage, double phrasePercentage, double finalPercentage)
        {
            this->textA = textA;
            this->textB = textB;
            this->wordPercentage = wordPercentage;
            this->phrasePercentage = phrasePercentage;
            this->finalPercentage = finalPercentage;

            verdict = displayverdict();
        }

        string displayverdict(){
            if(finalPercentage <= 100 && finalPercentage >= 85) verdict =  "Possible Plagiarism";
            else if(finalPercentage >= 60 && finalPercentage < 85) verdict = "Highly Similar";
            else if(finalPercentage >= 30 && finalPercentage < 60) verdict =  "Partially Similar";
            else verdict = "Not Similar";
            return verdict;
        }
};