#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "documentparser.h"
#include <time.h>
using namespace std;

int runCatchTests(int argc, char* const argv[])
{
    //catt the run method in catch
    return Catch::Session().run(argc, argv);
    return 0;
}

int main(int argc, char* const argv[])
{
    clock_t tStart, tEnd;
    tStart = clock();
    DocumentParser doc1;
    doc1.stopWords(argv[2]);
    doc1.throughDirectory(argv[1]);

    tEnd = clock();
    float durationTicks = ((float)tEnd - (float)tStart);
    float durationSec = durationTicks/ CLOCKS_PER_SEC;
    cout << durationSec << " seconds" << endl;

    if (argc > 1)
    {
        return runCatchTests(argc, argv);
    }
}


