#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <unordered_map>
using namespace std;

class SimilarityEngine
{
    public:
    unordered_map <string, int> freqA;
    unordered_map <string, int> freqB;

    void buildFrequencyMap(vector<string> words, unordered_map<string, int>& freq)
    {
        for(string word : words)
        {
            freq[word]++; //if not exist it make zero - if exist increment of 1.
        }
    }
    int countCommonWords()
    {
        int similarCount = 0;
        for(const auto& pair : freqA) //auto allows us to not write data type it automatically detect the data type.
        {
            string word = pair.first;
            if(freqB.find(word) != freqB.end()) // .find(word) return value if found otherwise it returns .end()
            {
                similarCount++;
            }
        }
        return similarCount;
    }

    int countUniqueWords()
    {
        //count All words of A and then iteratte B and add only which are not common in A and B.
        int uniqueCount = 0;
        for(const auto& pair : freqA)
        {
            uniqueCount++;
        }

        for(const auto& pair : freqB)
        {
            string word = pair.first;
            if(freqA.find(word) == freqA.end())
            {
                uniqueCount++;
            }
        }
        return uniqueCount;
    }

    double computeWordSimilarity()
    {
        int uniqueNum = countUniqueWords();
        int commonNum = countCommonWords();

        //Similarity Percentage = ( common / unique ) * 100

        if(uniqueNum == 0)
        {
            return 0.0;
        }
        double similarityPercentage = ( (double)commonNum / uniqueNum ) * 100;
        return similarityPercentage;
    }
};