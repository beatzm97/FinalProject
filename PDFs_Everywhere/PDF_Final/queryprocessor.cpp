#include "queryprocessor.h"

queryProcessor::queryProcessor(const char* stopList, const char* pathName, const char* indexFile)
{
    int choice;
    int option;
    bool preference;
    indexHandler iHandle;
    do
    {
        cout << endl << "Query Mode Selected ---" << endl;
        cout << "\t 1 : Boolean Query -- Load existing index into an AVL Tree or a Hash Table" << endl;
        cout << "\t 2 : Search engine statistics" << endl;
        cout << "\t 0 : RETURN TO MAIN MENU" << endl;
        cout << "-------------------" << endl;
        cout << "Please choose an option by entering the corresponding number: ";
        cin >> choice;
        if (choice == 1)
        {
            bool judge = checkFile(indexFile);
            if (judge == true)
            {
                cout << "There is no index" << endl;
                cout << "Create an index using Maintence Mode" << endl;
            }
            else
            {
                cout << endl << "Option 1 Selected --- Query" << endl;
                cout << "\t 1 : Load index into an AVL Tree" << endl;
                cout << "\t 2 : Load index into a Hash Table" << endl;
                cout << "Please choose an option by entering the corresponding number: ";
                cin >> option;
                if (option == 1)
                {
                    cout << "AVL Tree" << endl;
                    preference = true;
                    searchStructure(preference, stopList, indexFile, pathName);
                }
                else if (option == 2)
                {
                    cout << "Hash Table" << endl;
                    preference = false;
                    searchStructure(preference, stopList, indexFile, pathName);
                }
                else
                {
                    cout << "Returning to Query Menu" << endl;
                }
            }
        }
        else if (choice == 2)
        {
            cout << endl << "Option 2 Selected ---" << endl;
            iHandle.searchStats(indexFile);
        }
        else if (choice != 0)
        {
            cout << endl << "***Invalid entry, please try again***" << endl << endl;
        }
        while (cin.fail())
        {
            cout << endl << "***Invalid entry, please try again***" << endl << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cout << endl << "Query Mode Selected ---" << endl;
            cout << "\t 1 : Boolean Query -- Load existing index into an AVL Tree or a Hash Table" << endl;
            cout << "\t 2 : Search engine statistics" << endl;
            cout << "\t 0 : RETURN TO MAIN MENU" << endl;
            cout << "-------------------" << endl;
            cout << "Please choose an option by entering the corresponding number: ";
            cin >> choice;
            if (choice == 1)
            {
                bool judge = checkFile(indexFile);
                if (judge == true)
                {
                    cout << "There is no index" << endl;
                    cout << "Create an index using Maintence Mode" << endl;
                }
                else
                {
                    cout << endl << "Option 1 Selected --- Query" << endl;
                    cout << "\t 1 : Load index into an AVL Tree" << endl;
                    cout << "\t 2 : Load index into a Hash Table" << endl;
                    cout << "Please choose an option by entering the corresponding number: ";
                    cin >> option;
                    if (option == 1)
                    {
                        cout << "AVL Tree" << endl;
                        preference = true;
                        searchStructure(preference, stopList, indexFile, pathName);
                    }
                    else if (option == 2)
                    {
                        cout << "Hash Table" << endl;
                        preference = false;
                        searchStructure(preference, stopList, indexFile, pathName);
                    }
                    else
                    {
                        cout << "Returning to Query Menu" << endl;
                    }
                }
            }
            else if (choice == 2)
            {
                 cout << endl << "Option 2 Selected --- Statistics" << endl;
                iHandle.searchStats(indexFile);
            }
            else if (choice != 0)
            {
                cout << endl << "***Invalid entry, please try again***" << endl << endl;
            }
        }
    }
    while (choice != 0);
    //searchEngine(stopList, pathName, indexFile);

}

void queryProcessor::searchStructure(bool preference, const char* stopList, const char* indexFile, const char* pathName)
{
    string searchTerms;
    cout << endl << "Boolean Query ---" << endl;
    cout << "\t Keywords: AND -> return the documents sharing all of trailing words" << endl;
    cout << "\t           OR -> reuturn documents containing all of the trailing words" << endl;
    cout << "\t           NOT -> return documents NOT containing the trailing word, cannot be used alone" << endl;
    cout << "Enter search term(s): ";
    cin.ignore();
    getline(cin, searchTerms);
    if (preference == true)
    {
        iHandle.searchAVL(searchTerms, stopList, indexFile, pathName);
    }
    else
    {
        iHandle.searchHash(searchTerms, stopList, indexFile, pathName);
    }
}

bool queryProcessor::checkFile(const char* indexFile)
{
    fileInOut.open(indexFile, ios::in);
    {
        if(!fileInOut)
        {
            cout << indexFile << " : File did not open" << endl;
            exit(EXIT_FAILURE);
        }
       int next = fileInOut.peek();
       if (next == EOF)
       {
           fileInOut.close();
           return true;
       }
       fileInOut.close();
       return false;
    }
}
