#include <iostream>
#include <vector>
#include <string>
#include "Preprocessor.h"
#include "SimilarityEngine.h"
#include "PhraseDetector.h"
#include "Result.h"
#include "HistoryManager.h"
#include "Document.h"

using namespace std;

int main()
{
    History history;
    TextReader reader;
    int choice = 0;

    while (choice != 4)
    {
        cout << "\n==============================\n";
        cout << "      SYNTEXA MAIN MENU\n";
        cout << "==============================\n";
        cout << "1. Compare Two Files\n";
        cout << "2. View History\n";
        cout << "3. Undo Last Comparison\n";
        cout << "4. Exit\n";
        cout << "==============================\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string pathA, pathB;

            cout << "Enter the name of the first file to compare: ";
            getline(cin, pathA);

            cout << "Enter the name of the second file to compare: ";
            getline(cin, pathB);

            // Load files
            string textA = reader.loadContent(pathA);
            string textB = reader.loadContent(pathB);

            if (textA.empty() || textB.empty())
            {
                cout << "Error loading files. Please check the paths and try again.\n";
                continue;
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
            history.addResultInHistory(res);

            // Output
            cout << "\n==============================\n";
            cout << "       TEXT SIMILARITY\n";
            cout << "==============================\n";
            cout << "\nWord Similarity   : " << wordScore << "%";
            cout << "\nPhrase Similarity : " << phraseScore << "%";
            cout << "\nFinal Score       : " << finalScore << "%\n";
            cout << "Verdict           : " << res.displayverdict() << endl;
            cout << "\n==============================\n";
        }
        else if (choice == 2)
        {
            history.displayHistory();
        }
        else if (choice == 3)
        {
            history.undoLast();
            cout << "Last comparison undone.\n";
        }
        else if (choice == 4)
        {
            cout << "Exiting Syntexa. Goodbye!\n";
        }
        else
        {
            cout << "Invalid choice! Please select an option between 1 and 4.\n";
        }
    }

    return 0;
}