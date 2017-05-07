#include "searchEngine.h"

searchEngine::searchEngine()
{
}

void searchEngine::parse(const char* stopList, const char* pathName, const char* indexFile)
{
    docParse.stopWords(stopList, pathName, indexFile);
}


void searchEngine::top50Words(const char* indexFile)
{
    iHandle.top50Words(indexFile);
}
