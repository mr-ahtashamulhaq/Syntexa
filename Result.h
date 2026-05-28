#pragma once
#include <iostream>
#include <string>
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

        string displayverdict()
        {
            if(finalPercentage >= 60)
                verdict =  "Possible Plagiarism";

            else if(finalPercentage >= 40 && finalPercentage < 60) 
                verdict = "Highly Similar";

            else if(finalPercentage >= 20 && finalPercentage < 40)
                verdict =  "Partially Similar";

            else 
                verdict = "Not Similar";
            
            return verdict;
        }
};