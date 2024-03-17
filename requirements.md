# Trabalho cpu 

# interface
## O simulador deve possuir uma maneira de ler um arquivo texto para carregar a memória com instruções e dados. É importante ressaltar, porém, que o simulador não precisa ser “bonito”, mas precisa ser fácil de usar.

- [] Capturar entradas ler um arquivo texto para carregar a memória com instruções e dados.
- [] Transformar as entradas de instrução em texto para binário(OpCode)
- [x] Criar uma mémoria Virtual em Vetor de unsigned char memoria[154], a memória possui apenas 154 endereços, abrangendo os endereços de 0 (0x0) a 153 (0x99).
- [] Salvar instruçoes tranformadas nas posições de mémoria virtual.
- [] Imprimir mapa da memoria no terminal
- [] Mostrar o conteúdo dos registradores no fim de cada ciclo de máquina, 
- - [] Imprimir mapa da CPU, valores dos registradores internos a cada execução. 

# implementacao CPU 
## a CPU a ser implementada processa apenas números inteiros contidos em palavras de 32 bits e, portanto, não há nenhuma operação com ponto-flutuante, BCD ou números inteiros de outros tamanhos.

- [x] Criar MBR – Memory Buffer Register – unsigned int mbr - 32 bits
- [x] Criar MAR – Memory Address Register – unsigned int mar - 32 bits
- [x] Criar IR – Instruction Register – unsigned char ir - 8 bits
- [x] Criar RO0 – Register Operand 0 – unsigned char ro0 - 8 bits
- [x] Criar RO1 – Register Operand 0 – unsigned char ro1 - 8 bits
- [x] IMM – Immediate – unsigned int imm - 32bits
- [x] E, L e G – registradores internos que armazenam as flags ‘equal to’, ‘lower than’ e ‘greater than’- unsigned char e, unsigned char l, unsigned char g - 8 bits
- [x] PC – Program Counter –  unsigned int pc - 32bits
- [x] r0 a r15 –  registradores de propósito-geral - unsigned int reg[16] - vetor de 16 posiçoes de 32 bits.
- [] implementar o conjunto de instruçoes
- []  todas as transferências entre MBR e a memória devem
ser de byte em byte.