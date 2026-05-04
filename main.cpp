#include <iostream>
#include <vector>
#include "Preprocessor.h"
#include "SimilarityEngine.h"
#include "PhraseDetector.h"
#include "Result.h"
#include "HistoryManager.h"
#include "Document.h"

using namespace std;

int main()
{
    TextReader reader;

    // Load files
    string textA = reader.loadContent("file1.txt");
    string textB = reader.loadContent("file2.txt");

    if(textA.empty() || textB.empty())
    {
        cout << "Error loading files.\n";
        return 0;
    }

    Preprocessor prep;

    // Preprocessing
    prep.toLowerCase(textA);
    prep.removePunctuation(textA);

    prep.toLowerCase(textB);
    prep.removePunctuation(textB);

    vector<string> wordsA = prep.tokenize(textA);
    vector<string> wordsB = prep.tokenize(textB);

    // Word Similarity
    SimilarityEngine sim;
    sim.buildFrequencyMap(wordsA, sim.freqA);
    sim.buildFrequencyMap(wordsB, sim.freqB);

    double wordScore = sim.computeWordSimilarity();

    // Phrase Similarity
    PhraseDetector pd;

    vector<string> phrasesA = pd.generatePhrases(wordsA);
    vector<string> phrasesB = pd.generatePhrases(wordsB);

    double phraseScore = pd.computePhraseSimilarity(phrasesA, phrasesB);

    // Final Score
    double finalScore = (0.4 * wordScore) + (0.6 * phraseScore);

    // Store result
    Result res(textA, textB, wordScore, phraseScore, finalScore);

    History history;
    history.addResultInHistory(res);

    // Output
    cout << "\n==============================\n";
    cout << "       TEXT SIMILARITY\n";
    cout << "==============================\n";

    cout << "\nWord Similarity   : " << wordScore << "%";
    cout << "\nPhrase Similarity : " << phraseScore << "%";
    cout << "\nFinal Score       : " << finalScore << "%\n";

    cout << "\n==============================\n";
    history.displayHistory();
    cout << "==============================\n";

    return 0;
}