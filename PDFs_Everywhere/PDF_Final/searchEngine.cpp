#include "searchEngine.h"

searchEngine::searchEngine(const char* stopList, const char* pathName, const char* indexFile)
{
    int choice = 1;
    do
    {
        cout << "Menu --------------" << endl;
        cout << "1 : Maintanence Mode" << endl;
        cout << "\t >>> Add documents to index by supplying path" << endl;
        cout << "\t >>> Completely clear index" << endl;
        cout << "2 : Query Mode" << endl;
        cout << "\t >>> Load existing index into an AVL Tree or a Hash Table" << endl;
        cout << "\t >>> Boolean query" << endl;
        cout << "\t >>> Search engine statistics" << endl;
        cout << "0 : EXIT" << endl;
        cout << "-------------------" << endl;
        cout << "Please choose an option by entering the corresponding number: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Maintenence Mode Selected" << endl;
        }
        else if (choice == 2)
        {
            queryMode(stopList, pathName, indexFile);
        }
        else if (choice != 0)
        {
            cout << endl << "***Invalid entry, please try again***" << endl << endl;
        }
    }
    while (choice != 0);
    if (choice == 0)
    {
        cout << endl << "---Exiting program---" << endl << endl;
        return;
    }

}
void searchEngine::queryMode(const char* stopList, const char* pathName, const char* indexFile)
{
    int choice;
    do
    {
        cout << "Query Mode Selected ---" << endl;
        cout << "\t 1 : Load existing index into an AVL Tree or a Hash Table" << endl;
        cout << "\t 2 : Boolean query" << endl;
        cout << "\t 3 : Search engine statistics" << endl;
        cout << "\t 0 : RETURN TO MAIN MENU" << endl;
        cout << "-------------------" << endl;
        cout << "Please choose an option by entering the corresponding number: ";
        cin >> choice;
        if (choice == 1)
        {
            int option;
            cout << "Option 1 Selected ---" << endl;
            cout << "\t 1 : Load index into an AVL Tree" << endl;
            cout << "\t 2 : Load index into a Hash Table" << endl;
            cout << "Please choose an option by entering the corresponding number: ";
            cin >> option;
            if (option == 1)
            {
                cout << "AVL Tree" << endl;
                iHandle.intoAVL(indexFile);
                preference = true;
            }
            else if (option == 2)
            {
                cout << "Hash Table" << endl;
            }
            else
            {
                cout << "Returning to Query Menu" << endl;
            }
            //queryMode(stopList, pathName, indexFile);
        }
        else if (choice == 2)
        {
            string searchTerms;
            cout << "Option 2 Selected ---" << endl;
            cout << "\t Keywords: AND -> return the documents sharing all of trailing words" << endl;
            cout << "\t           OR -> reuturn documents containing all of the trailing words" << endl;
            cout << "\t           NOT -> return documents NOT containing the trailing word, cannot be used alone" << endl;
            cout << "Enter search term(s): ";
            cin >> searchTerms;
            if (preference == true)
            {
                iHandle.searchAVL(searchTerms);
            }

        }
        else if (choice == 3)
        {
            searchStats(indexFile);
        }
        else if (choice != 0)
        {
            cout << endl << "***Invalid entry, please try again***" << endl << endl;
        }
    }
    while (choice != 0);
    //searchEngine(stopList, pathName, indexFile);
}

void searchEngine::parse(const char* stopList, const char* pathName, const char* indexFile)
{
    docParse.stopWords(stopList, pathName, indexFile);
}


void searchEngine::searchStats(const char* indexFile)
{
    iHandle.searchStats(indexFile);
}
