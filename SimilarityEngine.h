#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class SimilarityEngine
{
    public:
    unordered_map <string, int> freqA; // word : how many times it appear
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
                similarCount += min(pair.second, freqB[word]);
            }
        }
        return similarCount;
    }

    int countUniqueWords()
    {
        //count All words of A and All words of B and subtract similarCount
        int totalA = 0;
        int totalB = 0;
        for(const auto& pair : freqA)
        {
            totalA += pair.second;  // Adding the number of times the word actually appeared
        }
        for(const auto& pair : freqB)
        {
            totalB += pair.second;
        }
    
        //subtract 
        int uniqueCount = totalA + totalB - countCommonWords();

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