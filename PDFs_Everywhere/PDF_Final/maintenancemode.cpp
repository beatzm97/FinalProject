#include "maintenancemode.h"

maintenanceMode::maintenanceMode(const char* stopWords, const char* pathName, const char* indexFile)
{
    int choice;
    string path;

    do
    {
        cout << endl << "Maintenance Mode Selected ---" << endl;
        cout << "\t 1 : Add documents to the index" << endl;
        cout << "\t 2 : Clear index" << endl;
        cout << "\t 0 : RETURN TO MAIN MENU" << endl;
        cout << "-------------------" << endl;
        cout << "Please choose an option by entering the corresponding number: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << endl << "Option 1 Selected --- Add to index" << endl;
            cout << "Please enter the path leading to the additional files:";
            cin >> path;
            appendIndex(path, stopWords, indexFile, pathName);
        }
        else if (choice  == 2)
        {
            cout << endl << "Option 2 Selected -- Clear index" << endl;
            clearIndex(indexFile);
            cout << "Index cleared" << endl;
        }
    }
    while (choice != 0);
}

void maintenanceMode::clearIndex(const char* fileName)
{
    fileInOut.open(fileName, ios::out | ios::trunc);
    {
        if (!fileInOut)
        {
            cout << fileName << " : File did not open " << endl;
            exit (EXIT_FAILURE);
        }
        //fileInOut << "";
    }
    fileInOut.close();
}

void maintenanceMode::appendIndex(string pathUser, const char* stopWords, const char* indexFile, const char* pathName)
{
    TextExtractor txtExt;
    txtExt.appendIndex(pathUser, stopWords, indexFile, pathName);



}
