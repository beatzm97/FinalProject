#include "indexhandler.h"

indexHandler::indexHandler()
{

}


void indexHandler::createIndex(avlTreeLayered<string> invertedIndexTreeIn, string fileName)
{
    indexCount = invertedIndexTreeIn.nodeCount;
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
        int count = 0;
        vector<pair<int, string>> popular;
        string word;
        int frequency = 0;
        string trash;

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
        cout << "done reading" << endl;
        sort(popular.begin(), popular.end());
        for (int i = 0; i < 50; i++)
        {
            cout << popular[i].first << " " << popular[i].second << endl;
        }
    }
}
