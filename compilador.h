#include<stdio.h> 
#include<stdlib.h>
#include <string.h>

unsigned char MEMORIA[154];
unsigned int MBR;
unsigned int MAR;
unsigned char IR;
unsigned char RO0;
unsigned char RO1;
unsigned char RO2;
unsigned int IMM;
unsigned int PC= 0x0;
unsigned char E, L, G;
unsigned int REG[16];
unsigned char RUN = 1;

#define MAX_LINE_LENGTH 1000

typedef struct {
    int endereco;
    char tipo;
    char instruction[30];
} Linha;

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
    
    if(opCode < 0x2){
        bitWord = opCode;
        bitWord  = bitWord << 27;
    }
    if(opCode == 0x2){
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
                bitWord = bitWord << 23;
            }
            
            cont ++;
        }
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
    int j=0;
    for (int i = 0x0; i <= 0x99 ; i++) {
        if(j==8){
            printf("\n");
            j=0;
        }
        printf("%X: %X    ", i, MEMORIA[i]);
        j++;
   }
   printf("\n\n");
}

void printState();
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
        
            if(nova_linha.tipo == 'd'){
                unsigned char data8;
                unsigned int data32 = string_to_hex(nova_linha.instruction);
                int count = 32;
                for (int i = hex_to_decimal(nova_linha.endereco); i < (hex_to_decimal(nova_linha.endereco) + 4) ; i++) {
                    count = count - 8;
                    data8 = data32 >> count;
                    MEMORIA[i] =   data8;
                }
               
            }    

            if(nova_linha.tipo == 'i'){
                unsigned char data8;
                unsigned int data32 = convertInstructionToBinary(nova_linha);
                int count = 32;
                for (int i = hex_to_decimal(nova_linha.endereco); i < (hex_to_decimal(nova_linha.endereco) + 4) ; i++) {
                    count = count - 8;
                    data8 = data32 >> count;
                    MEMORIA[i] =   data8;
                }
            }    
            
            linhas[num_linhas] = nova_linha;
            num_linhas++;
        }
        
        printState();
        fclose(fp); 
    } else {
            printf("Failed to open the file\n");
    }
}

void cpuBusca(){
    MBR = MEMORIA[PC];  // recebe os primeiros 8bits da memoria

    for (int i = PC; i < (PC + 4); i++) // transfere de 8 em 8 bits até os 32 bits
    {
        MBR = MBR << 8;
        MBR = MBR | MEMORIA[i];
    }
}

void cpuDecodifica(){

    IR = MBR >> 27;
    PC= PC + 0x4;

    if(IR < 0x3){
    }
    if(IR ==2){
        RO0 = MBR >> 23 & 0xF;
    }

    if(IR >= 0x3 && IR < 0x5){
       RO0 = MBR >> 23 & 0xF;
       RO1 = MBR >> 19 & 0xF;
    }

    if(IR >= 0x5 && IR < 0x7){
        RO0 = MBR >> 23 & 0xF;
        RO1 = MBR >> 19 & 0xF;
        MAR = MBR & 0x7FFFF;
    }

    if(IR >= 0x7 && IR < 0xE){
        RO0 = MBR >> 23 & 0xF;
        RO1 = MBR >> 19 & 0xF;
        RO2 = MBR >> 15 & 0xF;
    }

    if(IR >= 0xE && IR < 0x10){
        RO0 = MBR >> 23 & 0xF;
        MAR = MBR & 0X7FFFFF;
    }

    if(IR >= 0x10 && IR < 0x18){
        RO0 = MBR >> 23 & 0xF;
        IMM = MBR & 0X7FFFFF;
       
    }

    if(IR >= 0x18 && IR < 0x1E){
        MAR = MBR & 0X7FFFFF;
    }
    
}
void printState(){
    
    printf("R0=%X, R1=%X, R2=%X, R3=%X \n", REG[0],REG[1],REG[2],REG[3]);
    printf("R4=%X, R5=%X, R6=%X, R7=%X \n", REG[4],REG[5],REG[6],REG[7]);
    printf("R8=%X, R9=%X, R10=%X, R11=%X \n", REG[8],REG[9],REG[10],REG[11]);
    printf("R12=%X, R13=%X, R14=%X, R15=%X \n", REG[12],REG[13],REG[14],REG[15]);
    printf("MBR=%X, MAR=%X, IMM=%X, PC=%X \n", MBR, MAR, IMM, PC);
    printf("IR= %X, RO0=%X, RO1=%X, RO2=%X\n",IR, RO0, RO1, RO2);
    printf("E= %X, L= %X , G= %X \n", E, L, G);
    printf("\n\n\n");
    printMemory();
}
void cpuExe(){

    if (IR == 0x0){
        RUN = 0;
    }
    if (IR == 0x1){
        PC=PC+4;
    }
    if (IR == 0x2){
        REG[RO0] = ~REG[RO0];
    }
    if (IR == 0x3){
        REG[RO0] = REG[RO1];
    }
    if (IR == 0x4){
        if (REG[RO0] == REG[RO1] ){ E = 1; }else{ E = 0;}
        if (REG[RO0] < REG[RO1] ){ L = 1; }else{ L = 0;}
        if (REG[RO0] > REG[RO1] ){ G = 1; }else{ G = 0;}
    }
    if (IR == 0x5){
        MAR = MAR + REG[RO1];
        for (int i = 1; i <=4 ; i++)
        {
            REG[RO0]= MEMORIA[MAR]; 
            MAR++;
        }
        
    }
    if (IR == 0x6){
        MAR = MAR + REG[RO1];
        for (int i = 1; i <=4 ; i++)
        {
            MEMORIA[MAR] = REG[RO0];
            MAR++;
        }
    }
    if (IR == 0x7){
        REG[RO0]= REG[RO1] + REG[RO2];
    }
    if (IR == 0x8){
        REG[RO0]= REG[RO1] - REG[RO2];
    }
    if (IR == 0x9){
        REG[RO0]= REG[RO1] * REG[RO2];
    }
    if (IR == 0xA){
        REG[RO0]= REG[RO1] / REG[RO2];
    }
    if (IR == 0xB){
        REG[RO0]= REG[RO1] & REG[RO2];
    }
    if (IR == 0xC){
        REG[RO0]= REG[RO1] | REG[RO2];
    }
    if (IR == 0xD){
        REG[RO0]= REG[RO1] ^ REG[RO2];
    }
    if (IR == 0xE){
        REG[RO0]= MEMORIA[MAR];  // recebe os primeiros 8bits da memoria
        for (int i = MAR; i < (MAR + 4); i++) // transfere de 8 em 8 bits até os 32 bits
        {
            REG[RO0] = REG[RO0] << 8;
            REG[RO0] = REG[RO0] | MEMORIA[i];
            
        }
    }
    if (IR == 0xF){
        int count = 32;
        for (int i = MAR; i < (MAR + 4) ; i++) {
            count = count - 8;
            MEMORIA[i] = REG[RO0] >> count;
        }
    }
    if (IR == 0x10){
      REG[RO0] = 0;
      REG[RO0] = IMM & 0xFFFF;
    }
    if (IR == 0x11){
      
      REG[RO0] = REG[RO0] | IMM >> 16;
    }
    if (IR == 0x12){
      REG[RO0]= REG[RO0] + IMM;
    }
    if (IR == 0x13){
      REG[RO0]= REG[RO0] - IMM;
    }
    if (IR == 0x14){
      REG[RO0]= REG[RO0] * IMM;
    }
    if (IR == 0x15){
      REG[RO0]= REG[RO0] / IMM;
    }
    if (IR == 0x16){
      REG[RO0]= REG[RO0] >> IMM;
    }
    if (IR == 0x17){
      REG[RO0]= REG[RO0] << IMM;
    }
    if (IR == 0x18){
        if (E == 1)
        {
            PC = MAR;
        }
    }
    if (IR == 0x19){
        if (!(E == 1))
        {
            PC = MAR;
        }
    }
    if (IR == 0x1A){
        if (L == 1)
        {
            PC = MAR;
        }
    }
    if (IR == 0x1B){
        if ((L == 1 || E == 1))
        {
            PC = MAR;

        }
    }
    if (IR == 0x1C){
        if (G == 1)
        {
            PC = MAR;
        }
    }
    if (IR == 0x1D){
        if ((G == 1 || E == 1))
        {
           PC = MAR;
        }
    }
    if (IR == 0x1E){
       
        PC = MAR;
        
    }
  
}

void cpu(){
    //busca 
   
    cpuBusca();

    // decodifica

    cpuDecodifica();

    // executa
    
    cpuExe();

    //imprime o estado da cpu
    printState();
}