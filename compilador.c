#include "compilador.h"

int main(int argc, char const *argv[])
{

    fileToMemory(argc, argv);
    cpu();
    cpu();
    return 0;
}