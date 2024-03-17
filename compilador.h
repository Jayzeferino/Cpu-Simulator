#include<stdio.h> 
#include<stdlib.h>
#include <string.h>

unsigned int MEMORIA[100];
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

#define MAX_LINE_LENGTH 1000

typedef struct {
    int endereco;
    char tipo;
    char instruction[30];
} Linha;

void interface();

unsigned char textToOpCode(char inst[30]){

    if (strcmp(inst,"hlt") == 0){  return 0x0;}
    if (strcmp(inst,"nop") == 0){  return 0x1;}
    if (strcmp(inst,"not") == 0){  return 0x2;}
    if (strcmp(inst,"movr") == 0){ return 0x3;}
    if (strcmp(inst,"cmp") == 0 ){ return 0x4;}
    if (strcmp(inst,"ldbo") == 0){ return 0x5;}
    if (strcmp(inst,"stbo") == 0){ return 0x6;}
    if (strcmp(inst,"add") == 0){  return 0x7;}
    if (strcmp(inst,"sub") == 0){  return 0x8;}
    if (strcmp(inst,"mul") == 0){  return 0x9;}
    if (strcmp(inst,"div") == 0){  return 0xA;}
    if (strcmp(inst,"and") == 0){  return 0xB;}
    if (strcmp(inst,"or") == 0){   return 0xC;}
    if (strcmp(inst,"xor") == 0){  return 0xD;}
    if (strcmp(inst, "ld") == 0){  return 0xE;}
    if (strcmp(inst,"st") == 0){   return 0xF;}
    if (strcmp(inst,"movil") == 0){return 0x10;}
    if (strcmp(inst,"movih") == 0){return 0x11;}
    if (strcmp(inst,"addi") == 0){ return 0x12;}
    if (strcmp(inst,"subi") == 0){ return 0x13;}
    if (strcmp(inst,"muli") == 0){ return 0x14;}
    if (strcmp(inst,"divi") == 0){ return 0x15;}
    if (strcmp(inst,"lsh") == 0){  return 0x16;}
    if (strcmp(inst,"rsh") == 0){  return 0x17;}
    if (strcmp(inst,"je") == 0){   return 0x18;}
    if (strcmp(inst,"jne") == 0){  return 0x19;}
    if (strcmp(inst,"jl") == 0){   return 0x1A;}
    if (strcmp(inst,"jle") == 0){  return 0x1B;}
    if (strcmp(inst,"jg") == 0){   return 0x1C;}
    if (strcmp(inst,"jge") == 0){  return 0x1D;}
    if (strcmp(inst,"jmp") == 0){  return 0x1E;}
    return 0;
}

unsigned char textToReg(char inst[30]){

    if (strcmp(inst,"r0") == 0){  return 0x0;}
    if (strcmp(inst,"r1") == 0){  return 0x1;}
    if (strcmp(inst,"r2") == 0){  return 0x2;}
    if (strcmp(inst,"r3") == 0){  return 0x3;}
    if (strcmp(inst,"r4") == 0){  return 0x4;}
    if (strcmp(inst,"r5") == 0){  return 0x5;}
    if (strcmp(inst,"r6") == 0){  return 0x6;}
    if (strcmp(inst,"r7") == 0){  return 0x7;}
    if (strcmp(inst,"r8") == 0){  return 0x8;}
    if (strcmp(inst,"r9") == 0){  return 0x9;}
    if (strcmp(inst,"r10") == 0){  return 0xA;}
    if (strcmp(inst,"r11") == 0){  return 0xB;}
    if (strcmp(inst,"r12") == 0){  return 0xC;}
    if (strcmp(inst,"r13") == 0){  return 0xD;}
    if (strcmp(inst,"r14") == 0){  return 0xE;}
    if (strcmp(inst,"r15") == 0){  return 0xF;}
    
 
    return 0;
}

unsigned int string_to_hex(const char inst[]) {
    int hex_value;
    sscanf(inst, "%x", &hex_value);

    return hex_value;
}

unsigned int convertInstructionToBinary(Linha linha){
    
    char* token = strtok(linha.instruction, " ");
    unsigned int bitWord;
    unsigned char opCode = textToOpCode(token);
    bitWord = opCode;
    int cont = 1;
    
    
    if(opCode < 0x3){
        bitWord = opCode;
        bitWord  = bitWord << 27;
    }

    if(opCode >= 0x3 && opCode < 0x5){
        bitWord = opCode;
        bitWord = bitWord << 4;
        unsigned char reg;

        while (cont <= 2) {
            token = strtok(NULL, ", ");
            reg = textToReg(token);
            bitWord =  bitWord | reg;
            if(cont!=2){
                bitWord = bitWord << 4;
            }
            cont ++;
        }
        bitWord = bitWord << 19;

    }

    if(opCode >= 0x5 && opCode < 0x7){
        bitWord = opCode;
        unsigned char reg;
        unsigned int memPos;

        while (cont <= 3) {
            token = strtok(NULL, ", ");
    
            if(cont==3){
                memPos = string_to_hex(token);
                bitWord = bitWord << 19;
                bitWord =  bitWord | memPos;
                
            }else{
                reg = textToReg(token);
                bitWord = bitWord << 4;
                bitWord =  bitWord | reg;
            }
            cont ++;
        }

    }

    if(opCode >= 0x7 && opCode < 0xE){
        bitWord = opCode;
        bitWord = bitWord << 4;
        unsigned char reg;

        while (cont <= 3) {
            token = strtok(NULL, ", ");
            reg = textToReg(token);
            bitWord =  bitWord | reg;
            if(cont!=3){
                bitWord = bitWord << 4;
            }
            cont ++;
        }
        bitWord = bitWord << 15;

        
    }

    if(opCode >= 0xE && opCode < 0x18){
        bitWord = opCode;
        bitWord = bitWord << 4;
        unsigned char reg;
        unsigned int memPos;

        while (cont <= 2) {

            token = strtok(NULL, ", ");

            if(cont == 1){
                reg = textToReg(token);
                bitWord =  bitWord | reg;
            }
            
            if(cont == 2){
                memPos = string_to_hex(token);
                bitWord = bitWord << 23;
                bitWord =  bitWord | memPos;
            }
            
            cont ++;
        }

    }

    if(opCode >= 0x18 && opCode < 0x1E){
        bitWord = opCode;
        bitWord = bitWord << 4;
        unsigned int memPos;

        while (cont <= 1) {

            token = strtok(NULL, ", ");

            memPos = string_to_hex(token);
            bitWord = bitWord << 23;
            bitWord =  bitWord | memPos;

            cont ++;
        }

    }

    return bitWord;
}

int hex_to_decimal(unsigned int hex_num) {
    char hex_str[20]; // Tamanho suficiente para armazenar um inteiro de 32 bits em hexadecimal
    sprintf(hex_str, "%X", hex_num); // Converte o número hexadecimal para uma string hexadecimal
    return (int)strtol(hex_str, NULL, 16); // Converte a string hexadecimal para decimal
}

void printMemory(){
    int index = 0;
  
    for (int i = 0; i < 100; i++) {
        
        printf("%X %X  \n ", i, MEMORIA[i]);
    }
}

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
    if ( fp ) {

        char linha[MAX_LINE_LENGTH];
        Linha linhas[MAX_LINE_LENGTH];
        int num_linhas = 0;

        while (fgets(linha, sizeof(linha), fp) != NULL && num_linhas < MAX_LINE_LENGTH) {
            Linha nova_linha;
            sscanf(linha, "%x;%c;%[^\n]", &nova_linha.endereco, &nova_linha.tipo, nova_linha.instruction);
            // printf("Endereco: %x, Tipo: %c, Instruction: %s \n", 
            // nova_linha.endereco, nova_linha.tipo, nova_linha.instruction);
            if(nova_linha.tipo == 'd'){

              MEMORIA[hex_to_decimal(nova_linha.endereco)] = string_to_hex(nova_linha.instruction);
            }    

            if(nova_linha.tipo == 'i'){
               MEMORIA[hex_to_decimal(nova_linha.endereco)] =   convertInstructionToBinary(nova_linha);
            }    
            
            linhas[num_linhas] = nova_linha;
            num_linhas++;
        }
        
        printMemory();
        fclose(fp); 
    } else {
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