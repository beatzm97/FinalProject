#ifndef STOPWORDS_H
#define STOPWORDS_H

#include "myavl_tree.h"
#include <string.h>

class stopWords
{
public:
    stopWords();
    ~stopWords();
private:
    MyAVL_Tree<string> stopWordsList;
    //fstream fileIn;
};

#endif // STOPWORDS_H
