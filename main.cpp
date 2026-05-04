#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Preprocessor.h"
#include "SimilarityEngine.h"
#include "Result.h"
#include "HistoryManager.h"

using namespace std;

int main()
{

    string textA = " Data,  Structures!    ARE important In Programming.";
    string textB = "Data structures help in coding and programming";
    
    Preprocessor P1;
    Preprocessor P2;
    P1.removePunctuation(textA);
    P1.toLowerCase(textA);
    vector<string> wordsA = P1.tokenize(textA);

    P2.removePunctuation(textB);
    P2.toLowerCase(textB);
    vector<string> wordsB = P2.tokenize(textB);

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
    double wordSimilarityPercentage = SE.computeWordSimilarity();
    cout<<"\nCommon words : "<<common<<endl;
    cout<<"Unique Words : "<<unique<<endl;
    cout<<"Similaroty percentage is : "<<wordSimilarityPercentage<<"%"<<endl;
    
    Result R1(textA, textB,wordSimilarityPercentage,50.0,80.0); //added temporary numbers
    History H;
    H.addResultInHistory(R1);
    H.displayHistory();
    
    return 0;
}