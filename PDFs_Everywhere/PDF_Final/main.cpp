#include "documentparser.h"
#include <time.h>

int main(int argc, char *argv[])
{
    clock_t tStart, tEnd;
    tStart = clock();
    DocumentParser doc1;
    //doc1.createPdf();
    /*
    for (int i = 1; i < argc; i++)
    {
        doc1.openPdf(argv[i]);
    }*/
    doc1.throughDirectory(argv[1]);
    tEnd = clock();
    float durationTicks = ((float)tEnd - (float)tStart);
    float durationSec = durationTicks/ CLOCKS_PER_SEC;
    cout << durationSec<< endl;
    return 0;
}
