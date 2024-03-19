# Para executar o programa:
- compile o programa e gere o executável ;
- insira as instrucoes no arquivo inputCMD.txt;


```
0;i;ld r0, 57
4;i;ld r1, 58
8;i;ld r2, 59
c;i;ld r3, 5A
10;i;ld r4, 63
14;i;sub r5, r3, r4
18;i;div r6, r2, r5
1c;i;mul r7, r6, r1
20;i;add r8, r0, r7
24;i;st r8, 82
28;i;hlt
57;d;20
58;d;3
59;d;4
5A;d;5
63;d;3
```

>[!NOTE]
   >
   >o codigo acima é um exemplo de como deve ser o conteúdo do arquivo inputCMD.txt
-  para rodar o programa  use o  seguinte comando no terminal 
` ./compilador inputCMD.txt `