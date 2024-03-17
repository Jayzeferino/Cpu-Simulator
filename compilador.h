#include<stdio.h> 
#include<stdlib.h>

unsigned char MEMORIA[154];
unsigned int MBR;
unsigned int MAR;
unsigned char IR;
unsigned char RO0;
unsigned char RO1;
unsigned char RO2;
unsigned int IMM;
unsigned int PC;
unsigned char E, L, G;
unsigned int REG[16];

void interface();
void fileToMemory(int argc, char *argv[]){
    FILE *fp;
    char *filename;
    char ch;

    // Check if a filename has been specified in the command
    if (argc < 2)
    {
        printf("Missing Filename\n");
        return;
    }
    else
    {
        filename = argv[1];
        printf("Lendo Arquivo de Intruçoes ..  : %s\n", filename);
    }

    // Open file in read-only mode
    fp = fopen(filename,"r");

    // If file opened successfully, then print the contents
    if ( fp )
        {
        printf("Enviando para memoria:\n");
        while ( (ch = fgetc(fp)) != EOF )
            {
                printf("%c",ch);
            }

        }
    else
        {
            printf("Failed to open the file\n");
        }
}

void cpu();

void buscaCpu(){

}

void cpu(){

    //busca

    // decodifica

    // executa

}