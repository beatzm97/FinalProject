#include "queryprocessor.h"

queryProcessor::queryProcessor(const char* stopList, const char* pathName, const char* indexFile)
{
    int choice;
    int option;
    bool preference;
    indexHandler iHandle;
    do
    {
        cout << "Query Mode Selected ---" << endl;
        cout << "\t 1 : Boolean Query -- Load existing index into an AVL Tree or a Hash Table" << endl;
        cout << "\t 2 : Search engine statistics" << endl;
        cout << "\t 0 : RETURN TO MAIN MENU" << endl;
        cout << "-------------------" << endl;
        cout << "Please choose an option by entering the corresponding number: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Option 1 Selected ---" << endl;
            cout << "\t 1 : Load index into an AVL Tree" << endl;
            cout << "\t 2 : Load index into a Hash Table" << endl;
            cout << "Please choose an option by entering the corresponding number: ";
            cin >> option;
            if (option == 1)
            {
                cout << "AVL Tree" << endl;
                preference = true;
                searchStructure(preference, stopList, indexFile);
            }
            else if (option == 2)
            {
                cout << "Hash Table" << endl;
                preference = false;
                //searchStructure(preference, stopList, indexFile);
            }
            else
            {
                cout << "Returning to Query Menu" << endl;
            }
        }
        else if (choice == 2)
        {
            iHandle.searchStats(indexFile);
        }
        else if (choice != 0)
        {
            cout << endl << "***Invalid entry, please try again***" << endl << endl;
        }
    }
    while (choice != 0);
    //searchEngine(stopList, pathName, indexFile);

}

void queryProcessor::searchStructure(bool preference, const char* stopList, const char* indexFile)
{
    string searchTerms;
    cout << "Boolean Query ---" << endl;
    cout << "\t Keywords: AND -> return the documents sharing all of trailing words" << endl;
    cout << "\t           OR -> reuturn documents containing all of the trailing words" << endl;
    cout << "\t           NOT -> return documents NOT containing the trailing word, cannot be used alone" << endl;
    cout << "Enter search term(s): ";
    cin.ignore();
    getline(cin, searchTerms);
    if (preference == true)
    {
        iHandle.searchAVL(searchTerms, stopList, indexFile);
    }
    else
    {
        //iHandle.searchHash(searchTerms, stopList, indexFile);
    }
}
