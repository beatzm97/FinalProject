#include "indexhandler.h"

indexHandler::indexHandler()
{

}


void indexHandler::createIndex(avlTreeLayered<string> invertedIndexTreeIn, string fileName)
{
    fileInOut.open(fileName, ios::out);
    {
        if (!fileInOut)
        {
            cout << fileName << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
       invertedIndexTreeIn.printIndexInfo(fileInOut);
    }
    fileInOut.close();
}

void indexHandler::top50Words(const char * indexFile)
{
    fileInOut.open(indexFile, ios::in);
    {
        if(!fileInOut)
        {
            cout << indexFile << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        vector<pair<int, string>> popular;
        string word;
        int frequency;
        string other;

        fileInOut >> word;
        while(!fileInOut.eof())
        {
            fileInOut >> frequency;
            popular.push_back(make_pair(frequency, word));
            getline(fileInOut, other);
            fileInOut >> word;
        }
        sort(popular.begin(), popular.end());
        for (int i = 0; i < popular.size(); i++)
        {
            cout << popular[i].first << " " << popular[i].second << endl;
        }
    }
}
