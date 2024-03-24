#include "compilador.h"

int main(int argc, char const *argv[])
{
    char comando[20];
    
    fileToMemory(argc, argv);
    PC = 0x0;
    

    while (RUN != 0) {

        printf("Pressione P para executar proxima instrução ou Exit para sair):  ");
        scanf("%s", comando);

        if (strcmp(comando, "P") == 0) {
            cpu();
        } else if (strcmp(comando, "Exit") == 0) {
            break;
        } else {
           printf("Entrada não reconhecida. Por favor, pressione P para executar proxima instrução ou digite 'Exit'.\n");
        }
    }

    return 0;
}