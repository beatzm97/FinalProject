#include "documentparser.h"

int main(int argc, char *argv[])
{
    DocumentParser doc1;
    //doc1.createPdf();
    /*
    for (int i = 1; i < argc; i++)
    {
        doc1.openPdf(argv[i]);
    }*/
    doc1.throughDirectory(argv[1]);
    return 0;
}
