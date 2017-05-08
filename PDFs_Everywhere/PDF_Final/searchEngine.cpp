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
        cout << "\t >>> Boolean query" << endl;
        cout << "\t >>> Search engine statistics" << endl;
        cout << "0 : EXIT" << endl;
        cout << "-------------------" << endl;
        cout << "Please choose an option by entering the corresponding number: ";
        cin >> choice;
        if (choice == 1)
        {
            mMode(stopList, pathName, indexFile);
        }
        else if (choice == 2)
        {
            qMode(stopList, pathName, indexFile);
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
            cout << "Menu --------------" << endl;
            cout << "1 : Maintanence Mode" << endl;
            cout << "\t >>> Add documents to index by supplying path" << endl;
            cout << "\t >>> Completely clear index" << endl;
            cout << "2 : Query Mode" << endl;
            cout << "\t >>> Boolean query" << endl;
            cout << "\t >>> Search engine statistics" << endl;
            cout << "0 : EXIT" << endl;
            cout << "-------------------" << endl;
            cout << "Please choose an option by entering the corresponding number: ";
            cin >> choice;
            if (choice == 1)
            {
                mMode(stopList, pathName, indexFile);
            }
            else if (choice == 2)
            {
                qMode(stopList, pathName, indexFile);
            }
            else if (choice != 0)
            {
                cout << endl << "***Invalid entry, please try again***" << endl << endl;
            }
            cin >> choice;
        }
    }
    while (choice != 0);
    if (choice == 0)
    {
        cout << endl << "---Exiting program---" << endl << endl;
        return;
    }

}
void searchEngine::qMode(const char* stopList, const char* pathName, const char* indexFile)
{
    queryProcessor(stopList, pathName, indexFile);
}

void searchEngine::mMode(const char* stopList, const char* pathName, const char* indexFile)
{
    maintenanceMode(stopList, pathName, indexFile);
}

void searchEngine::parse(const char* stopList, const char* pathName, const char* indexFile)
{
    TextExtractor docParse;
    docParse.stopWords(stopList, pathName, indexFile);
}


/*void searchEngine::searchStats(const char* indexFile)
{
    indexHandler iHandle;
    iHandle.searchStats(indexFile);
}*/
