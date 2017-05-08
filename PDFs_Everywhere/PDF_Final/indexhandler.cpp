#include "indexhandler.h"

indexHandler::indexHandler()
{

}

void indexHandler::createIndex(avlTreeLayered<string>& invertedIndexTreeIn, string fileName, int pageCount)
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
            cout <<"Term: " << popular[i].second << ", Frequency: " << popular[i].first << endl;
        }
    }
    fileInOut.close();
}

void indexHandler::searchAVL(string searchTerms, const char* stopList, const char* indexFile, const char* pathName)
{
    int indexCount;

    fileInOut.open(indexFile, ios::in);
    {
        if(!fileInOut)
        {
            cout << indexFile << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        int count = 0;
        int pageCount;
        string word;
        string doc;
        int frequency = 0;
        int frequencyInner = 0;
        string trash;

        fileInOut >> indexCount;
        fileInOut >> pageCount;

        fileInOut >> word;
        while(!fileInOut.eof() && count < indexCount)
        {
            fileInOut >> frequency;
            fileInOut >> trash;
            while (trash != ">")
            {
                fileInOut >> doc;
                fileInOut >> frequencyInner;
                for (int j = 0; j < frequencyInner; j++)
                {
                    indexAVL.insert(word, doc);
                }
                fileInOut >> trash;
            }
            fileInOut >> word;
            count++;
        }
    }
    fileInOut.close();

    TextExtractor textExt;
    string text;
    string result;
    int differentiator = 0;
    int term = 0;
    int past;
    bool andIn = false;
    vector <pair <int, string>> term1;
    vector <pair <int, string>> term2;
    vector <pair <int, string>> output;
    vector <pair <int, string>> intersection;
    vector <string> docSet;

    for (unsigned int i = 0; i < searchTerms.size() + 1; i++)
    {
        if (searchTerms[i] != ' ' && i < searchTerms.size())
        {
            text += searchTerms[i];
        }
        else
        {
            if (text == "OR")
            {
                differentiator = 1;
                term = 0;
                text.clear();
            }
            else if (text == "AND")
            {
                differentiator = 2;
                term = 0;
                text.clear();
            }
            else if (text == "NOT")
            {
                past = differentiator;
                differentiator = 3;
                term = 0;
                text.clear();
            }
            else
            {
                result = textExt.filter(text, stopList);
                if (result == "a")
                {
                    cout << "No documents with " << text << endl;
                }
                else if (indexAVL.find(result) == false)
                {
                    cout << "No documents with " << text << endl;
                }
                else
                {
                    if (term == 0)
                    {
                        if (differentiator == 3)
                        {
                            indexAVL.innerInfoV(intersection, result);
                        }
                        else if (differentiator == 2)
                        {
                            indexAVL.innerInfoV(output, result);
                        }
                        else
                        {
                            indexAVL.innerInfoV(term1, result);
                        }
                        term = 1;
                    }
                    else
                    {
                        if (differentiator == 3)
                        {
                            indexAVL.innerInfoV(intersection, result);
                        }
                        else if (differentiator == 2)
                        {
                            indexAVL.innerInfoV(output, result);
                        }
                        else
                        {
                            indexAVL.innerInfoV(term2, result);
                        }
                        andIn = true;
                        term = 0;
                    }
                    if (differentiator == 1)
                    {
                        std::set_union(term1.begin(), term1.end(),
                                           term2.begin(), term2.end(),
                                           std::back_inserter(output));
                    }
                    if (differentiator == 2)
                    {
                        if (andIn == true)
                        {
                            sort(output.rbegin(),output.rend());

                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = k + 1; j < output.size(); j++)
                                {
                                    if (output[j].second == output[k].second)
                                    {
                                        intersection.push_back(make_pair(output[k].first, output[k].second));
                                    }
                                }
                            }
                            output = intersection;
                            intersection.clear();
                        }
                    }
                }
                text.clear();
                if (i == searchTerms.size())
                {
                    if (differentiator == 1)
                    {
                        sort(output.rbegin(),output.rend());
                        auto last = std::unique(output.begin(), output.end());
                            output.erase(last, output.end());

                        for (unsigned int k = 0; k <output.size(); k++)
                        {
                            for (unsigned int j = k + 1; j < output.size(); j++)
                            {
                                if (output[j].second == output[k].second)
                                {
                                    output[j].first = 0;
                                    output[j].second = "empty";
                                }
                            }
                        }
                        int count = 0;
                        for (unsigned int k = 0 ; k < output.size(); k++)
                        {
                           if (output[k].first != 0 && output[k].second != "empty" && count < 15)
                           {
                               //cout << output[k].second << endl;
                               docSet.push_back(output[k].second);
                               count++;
                           }
                        }
                        output.clear();
                        term1.clear();
                        term2.clear();
                        intersection.clear();
                    }
                    else if (differentiator == 2)
                    {
                        sort(output.rbegin(),output.rend());
                        auto last = std::unique(output.begin(), output.end());
                            output.erase(last, output.end());

                        int count = 0;
                        for (unsigned int k = 0; k < output.size(); k++)
                        {
                            if (count < 15)
                            {
                                //cout << output[k].second << endl;
                                docSet.push_back(output[k].second);
                                count++;
                            }
                        }
                        output.clear();
                        term1.clear();
                        term2.clear();
                        intersection.clear();
                    }
                    else if (differentiator == 3)
                    {
                        if (past == 1)
                        {
                            sort(output.rbegin(),output.rend());
                            auto last = std::unique(output.begin(), output.end());
                                output.erase(last, output.end());

                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = k + 1; j < output.size(); j++)
                                {
                                    if (output[j].second == output[k].second)
                                    {
                                        output[j].first = 0;
                                        output[j].second = "empty";
                                    }
                                }
                            }
                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = 0; j < intersection.size(); j++)
                                {
                                    if (intersection[j].second == output[k].second)
                                    {
                                        output[k].first = 0;
                                        output[k].second = "empty";
                                    }
                                }
                            }
                            int count = 0;
                            for (unsigned int k = 0 ; k < output.size(); k++)
                            {
                               if (output[k].first != 0 && output[k].second != "empty" && count < 15)
                               {
                                   //cout << output[k].second << endl;
                                   docSet.push_back(output[k].second);
                                   count++;
                               }
                            }
                            output.clear();
                            term1.clear();
                            term2.clear();
                            intersection.clear();
                        }
                        else if (past == 2)
                        {
                            sort(output.rbegin(),output.rend());
                            auto last = std::unique(output.begin(), output.end());
                                output.erase(last, output.end());

                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = 0; j < intersection.size(); j++)
                                {
                                    if (intersection[j].second == output[k].second)
                                    {
                                        output[k].first = 0;
                                        output[k].second = "empty";
                                    }
                                }
                            }
                            int count = 0;
                            for (unsigned int k = 0 ; k < output.size(); k++)
                            {
                                if (output[k].first != 0 && output[k].second != "empty" && count < 15)
                                {
                                    //cout << output[k].second << endl;
                                    docSet.push_back(output[k].second);
                                    count++;
                                }
                            }
                            output.clear();
                            term1.clear();
                            term2.clear();
                            intersection.clear();
                        }
                        else
                        {
                            sort(term1.rbegin(), term1.rend());
                            for (unsigned int k = 0; k < term1.size(); k++)
                            {
                                for (unsigned int j = 0; j < intersection.size(); j++)
                                {
                                    if (intersection[j].second == term1[k].second)
                                    {
                                        term1[k].first = 0;
                                        term1[k].second = "empty";
                                    }
                                }
                            }
                            int count = 0;
                            for (unsigned int k = 0 ; k < term1.size(); k++)
                            {
                               if (term1[k].first != 0 && term1[k].second != "empty" && count < 15)
                               {
                                   //cout << term1[k].second << endl;
                                   docSet.push_back(term1[k].second);
                                   count++;
                               }
                            }
                        }
                    }
                    else
                    {
                        int count = 0;
                        sort(term1.rbegin(), term1.rend());
                        for (unsigned int k = 0; k < term1.size(); k++)
                        {
                            if (count < 15)
                            {
                                //cout << term1[k].second << endl;
                                docSet.push_back(term1[k].second);
                            }
                        }
                    }
                }
            }
        }
    }
    outputDoc(docSet, pathName);
}

void indexHandler::outputDoc(vector<string> docSet, const char* pathName)
{
    int choice;
    TextExtractor textExt;
    do
    {
        cout << endl << "Document Results --------------" << endl;
        for (unsigned int i = 0; i < docSet.size(); i++)
        {
            cout << "  " << (i+1) << ": ";
            cout << docSet[i] << endl;
        }
        cout << "\t 0: BACK TO BOOLEAN SEARCH MENU" << endl;
        cout << "Choose a file to see contents: ";
        cin >> choice;
        if (choice > 0 && choice < (docSet.size() + 1))
        {
            textExt.documentContents(docSet[choice-1], pathName);
        }
        else if (choice != 0)
        {
            cout << endl << "***Invalid entry, please try again***" << endl << endl;
        }
    }
    while (choice != 0);
}

void indexHandler::searchHash(string searchTerms, const char* stopList, const char* indexFile, const char* pathName)
{
    int indexCount;

    fileInOut.open(indexFile, ios::in);
    {
        if(!fileInOut)
        {
            cout << indexFile << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        int count = 0;
        int pageCount;
        string word;
        string doc;
        int frequency = 0;
        int frequencyInner = 0;
        string trash;

        fileInOut >> indexCount;
        fileInOut >> pageCount;

        fileInOut >> word;
        while(!fileInOut.eof() && count < indexCount)
        {
            fileInOut >> frequency;
            fileInOut >> trash;
            while (trash != ">")
            {
                fileInOut >> doc;
                fileInOut >> frequencyInner;
                for (int j = 0; j < frequencyInner; j++)
                {
                    indexHash.insert(word, doc);
                }
                fileInOut >> trash;
            }
            fileInOut >> word;
            count++;
        }
    }
    fileInOut.close();

    TextExtractor textExt;
    string text;
    string result;
    int differentiator = 0;
    int term = 0;
    int past;
    bool andIn = false;
    vector <pair <int, string>> term1;
    vector <pair <int, string>> term2;
    vector <pair <int, string>> output;
    vector <pair <int, string>> intersection;
    vector <string> docSet;

    for (unsigned int i = 0; i < searchTerms.size() + 1; i++)
    {
        if (searchTerms[i] != ' ' && i < searchTerms.size())
        {
            text += searchTerms[i];
        }
        else
        {
            if (text == "OR")
            {
                differentiator = 1;
                term = 0;
                text.clear();
            }
            else if (text == "AND")
            {
                differentiator = 2;
                term = 0;
                text.clear();
            }
            else if (text == "NOT")
            {
                past = differentiator;
                differentiator = 3;
                term = 0;
                text.clear();
            }
            else
            {
                result = textExt.filter(text, stopList);
                if (result == "a")
                {
                    cout << "No documents with " << text << endl;
                }
                else if (indexHash.search(result) == false)
                {
                    cout << "No documents with " << text << endl;
                }
                else
                {
                    if (term == 0)
                    {
                        if (differentiator == 3)
                        {
                            indexHash.innerInfo(intersection, result);
                        }
                        else if (differentiator == 2)
                        {
                            indexHash.innerInfo(output, result);
                        }
                        else
                        {
                            indexHash.innerInfo(term1, result);
                        }
                        term = 1;
                    }
                    else
                    {
                        if (differentiator == 3)
                        {
                            indexHash.innerInfo(intersection, result);
                        }
                        else if (differentiator == 2)
                        {
                            indexHash.innerInfo(output, result);
                        }
                        else
                        {
                            indexHash.innerInfo(term2, result);
                        }
                        andIn = true;
                        term = 0;
                    }
                    if (differentiator == 1)
                    {
                        std::set_union(term1.begin(), term1.end(),
                                           term2.begin(), term2.end(),
                                           std::back_inserter(output));
                    }
                    if (differentiator == 2)
                    {
                        if (andIn == true)
                        {
                            sort(output.rbegin(),output.rend());

                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = k + 1; j < output.size(); j++)
                                {
                                    if (output[j].second == output[k].second)
                                    {
                                        intersection.push_back(make_pair(output[k].first, output[k].second));
                                    }
                                }
                            }
                            output = intersection;
                            intersection.clear();
                        }
                    }
                }
                text.clear();
                if (i == searchTerms.size())
                {
                    if (differentiator == 1)
                    {
                        sort(output.rbegin(),output.rend());
                        auto last = std::unique(output.begin(), output.end());
                            output.erase(last, output.end());

                        for (unsigned int k = 0; k <output.size(); k++)
                        {
                            for (unsigned int j = k + 1; j < output.size(); j++)
                            {
                                if (output[j].second == output[k].second)
                                {
                                    output[j].first = 0;
                                    output[j].second = "empty";
                                }
                            }
                        }
                        int count = 0;
                        for (unsigned int k = 0 ; k < output.size(); k++)
                        {
                           if (output[k].first != 0 && output[k].second != "empty" && count < 15)
                           {
                               //cout << output[k].second << endl;
                               docSet.push_back(output[k].second);
                               count++;
                           }
                        }
                        output.clear();
                        term1.clear();
                        term2.clear();
                        intersection.clear();
                    }
                    else if (differentiator == 2)
                    {
                        sort(output.rbegin(),output.rend());
                        auto last = std::unique(output.begin(), output.end());
                            output.erase(last, output.end());

                        int count = 0;
                        for (unsigned int k = 0; k < output.size(); k++)
                        {
                            if (count < 15)
                            {
                                //cout << output[k].second << endl;
                                docSet.push_back(output[k].second);
                                count++;
                            }
                        }
                        output.clear();
                        term1.clear();
                        term2.clear();
                        intersection.clear();
                    }
                    else if (differentiator == 3)
                    {
                        if (past == 1)
                        {
                            sort(output.rbegin(),output.rend());
                            auto last = std::unique(output.begin(), output.end());
                                output.erase(last, output.end());

                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = k + 1; j < output.size(); j++)
                                {
                                    if (output[j].second == output[k].second)
                                    {
                                        output[j].first = 0;
                                        output[j].second = "empty";
                                    }
                                }
                            }
                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = 0; j < intersection.size(); j++)
                                {
                                    if (intersection[j].second == output[k].second)
                                    {
                                        output[k].first = 0;
                                        output[k].second = "empty";
                                    }
                                }
                            }
                            int count = 0;
                            for (unsigned int k = 0 ; k < output.size(); k++)
                            {
                               if (output[k].first != 0 && output[k].second != "empty" && count < 15)
                               {
                                   //cout << output[k].second << endl;
                                   docSet.push_back(output[k].second);
                                   count++;
                               }
                            }
                            output.clear();
                            term1.clear();
                            term2.clear();
                            intersection.clear();
                        }
                        else if (past == 2)
                        {
                            sort(output.rbegin(),output.rend());
                            auto last = std::unique(output.begin(), output.end());
                                output.erase(last, output.end());

                            for (unsigned int k = 0; k < output.size(); k++)
                            {
                                for (unsigned int j = 0; j < intersection.size(); j++)
                                {
                                    if (intersection[j].second == output[k].second)
                                    {
                                        output[k].first = 0;
                                        output[k].second = "empty";
                                    }
                                }
                            }
                            int count = 0;
                            for (unsigned int k = 0 ; k < output.size(); k++)
                            {
                                if (output[k].first != 0 && output[k].second != "empty" && count < 15)
                                {
                                    //cout << output[k].second << endl;
                                    docSet.push_back(output[k].second);
                                    count++;
                                }
                            }
                            output.clear();
                            term1.clear();
                            term2.clear();
                            intersection.clear();
                        }
                        else
                        {
                            sort(term1.rbegin(), term1.rend());
                            for (unsigned int k = 0; k < term1.size(); k++)
                            {
                                for (unsigned int j = 0; j < intersection.size(); j++)
                                {
                                    if (intersection[j].second == term1[k].second)
                                    {
                                        term1[k].first = 0;
                                        term1[k].second = "empty";
                                    }
                                }
                            }
                            int count = 0;
                            for (unsigned int k = 0 ; k < term1.size(); k++)
                            {
                               if (term1[k].first != 0 && term1[k].second != "empty" && count < 15)
                               {
                                   //cout << term1[k].second << endl;
                                   docSet.push_back(term1[k].second);
                                   count++;
                               }
                            }
                        }
                    }
                    else
                    {
                        int count = 0;
                        sort(term1.rbegin(), term1.rend());
                        for (unsigned int k = 0; k < term1.size(); k++)
                        {
                            if (count < 15)
                            {
                                //cout << term1[k].second << endl;
                                docSet.push_back(term1[k].second);
                            }
                        }
                    }
                }
            }
        }
    }
    outputDoc(docSet, pathName);
}
