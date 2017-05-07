#include "indexhandler.h"

indexHandler::indexHandler()
{

}

void indexHandler::createIndex(avlTreeLayered<string> invertedIndexTreeIn, string fileName, int pageCount)
{
    fileInOut.open(fileName, ios::out);
    {
        if (!fileInOut)
        {
            cout << fileName << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        fileInOut << invertedIndexTreeIn.nodeCount << " " << pageCount << endl;
       invertedIndexTreeIn.printIndexInfo(fileInOut);
    }
    fileInOut.close();
}

void indexHandler::searchStats(const char * indexFile)
{
    fileInOut.open(indexFile, ios::in);
    {
        if(!fileInOut)
        {
            cout << indexFile << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        int count = 0;
        int indexCount;
        int pageCount;
        vector<pair<int, string>> popular;
        string word;
        int frequency = 0;
        string trash;

        fileInOut >> indexCount;
        fileInOut >> pageCount;

        fileInOut >> word;
        while(!fileInOut.eof() && count < indexCount)
        {
            fileInOut >> frequency;
            popular.push_back(make_pair(frequency, word));
            fileInOut >> trash;
            while (trash != ">")
            {
                fileInOut >> trash;
                fileInOut >> frequency;
                fileInOut >> trash;
            }
            fileInOut >> word;
            count++;
        }

        cout << "Total number of pages indexed: " << pageCount << endl;
        cout << "Total number of words indexed: " << indexCount << endl;

        sort(popular.rbegin(), popular.rend());
        for (int i = 0; i < 50; i++)
        {
            cout << "Frequency: " << popular[i].first << " | Term: " << popular[i].second << endl;
        }
    }
}
