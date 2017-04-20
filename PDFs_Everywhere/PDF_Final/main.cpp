#include <iostream>
#include "documentparser.h"

int main(int argc, char *argv[])
{
    DocumentParser doc1;
    //doc1.createPdf();
    doc1.openPdf(argv[1]);
    return 0;
}
