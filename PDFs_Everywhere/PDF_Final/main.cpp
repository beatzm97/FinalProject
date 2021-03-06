#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "searchEngine.h"
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
    searchEngine search1 (argv[2], argv[1], argv[3]);
    //search1.parse(argv[2], argv[1], argv[3]);
    //search1.searchStats(argv[3]);
    //search1.search();

    tEnd = clock();
    float durationTicks = ((float)tEnd - (float)tStart);
    float durationSec = durationTicks/ CLOCKS_PER_SEC;
    cout << durationSec << " seconds" << endl;

    if (argc > 1)
    {
        return runCatchTests(argc, argv);
    }
}


