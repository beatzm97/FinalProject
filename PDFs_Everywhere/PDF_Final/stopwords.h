#ifndef STOPWORDS_H
#define STOPWORDS_H

#include "avltree.h"
#include <string.h>

class stopWords
{
public:
    stopWords();
    ~stopWords();
private:
    avlTree<string> stopWordsList;
    //fstream fileIn;
};

#endif // STOPWORDS_H
