#include<iostream>
#include<string>
#include <fstream>
#include <vector>
#include "Preprocessor.h"
#include "SimilarityEngine.h"
using namespace std;

int main()
{

    string textA = " Data,  Structures!    ARE important In Programming.";
    string textB = "Data structures help in coding and programming";
    
    Preprocessor P;
    string processedText;
    processedText = P.removePunctuation(textA);
    processedText = P.toLowerCase(processedText);
    vector<string> wordsA = P.tokenize(processedText);

    processedText = P.removePunctuation(textB);
    processedText = P.toLowerCase(processedText);
    vector<string> wordsB = P.tokenize(processedText);
    for( string word : wordsA)
    {
        cout<<word<<" ";
    }
    cout<<endl;
    for( string word : wordsB)
    {
        cout<<word<<" ";
    }

    SimilarityEngine SE;
    SE.buildFrequencyMap(wordsA, SE.freqA); //Build frequencies which are class Variables
    SE.buildFrequencyMap(wordsB, SE.freqB);

    int common = SE.countCommonWords();
    int unique = SE.countUniqueWords();
    double similarityPercentage = SE.computeWordSimilarity();
    cout<<"\nCommon words : "<<common<<endl;
    cout<<"\nUnique Words : "<<unique<<endl;
    cout<<"\nSimilaroty percentage is : "<<similarityPercentage<<"%"<<endl;
    
    
    
    return 0;
}