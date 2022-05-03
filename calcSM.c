/*
Autor: Henrique Ribeiro Favaro
RA: 115.408
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------- CABEÇALHO ---------------------------------------//
#define MAXLENGHT 16    /*16 bits para o numero, 1 bit para o '\0'*/
#define MAXNUM 32767    //2^15 - 1
#define MINNUM -32767   //-(2^15 - 1)
#define FALSE 0;
#define TRUE 1;
//-------------------------------------------------------------------------------//


//---------------------------- FUNÇÕES DEMONSTRATIVAS ---------------------------------------//
/*
Função que apresenta um erro conforme o código fornecido.
*/
char err[3][255] = {
    "Um numero decimal excede a quantidade de bits suportada quando transformado em binario\n", 
    "Estouro de Bits para o calculo\n",
    "Opcao Invalida\n"
};
void errorShow(int code){
    printf("\n[---WARNING---]: %s\n", err[code]);
}

/*
Função para apresentar uma operação no console, durane a execução dos cálculos, possibilitando
uma demonstração passo a passo para o usuário.
*/
void showOperation(char identificador, int *binary, int start, int end){
    int i;

    if(identificador != 'R' && identificador != 'F'){
        printf("\nBinario %c:   ", identificador);
    }else if(identificador == 'F'){
        printf("\n-------------------------------------------");
        printf("\nBinario %c:     ", identificador);
    }else{
        printf("\n\n\n-------------------------------------------");
        printf("\nBinario %c: ", identificador);
    }

    for(i = start; i < end; i++){
        printf("%d ", binary[i]);
    }
}

/*
Função para mostrar um numero binário representado em decimal.
*/
void showBinary(int decimal, int *binary){
    int i;
    printf("\n------------------");
    printf("\nNumero [%d] transformado em binario: ", decimal);
    for(i = 0; i<MAXLENGHT; i++){
        printf("%d", binary[i]);
    }
    printf("\n------------------");
}

/*
Função que apresenta o resultado da soma e da subtração.
*/
void showResult(int code,int *result){
    char opcoes[4][MAXLENGHT] = {
        "Soma", 
        "Subtracao", 
    };
    printf("\n[Resultado %s]: ", opcoes[code-1]);
    for(int i = 0; i < MAXLENGHT; i++){
        printf("%d", result[i]);
    }
    printf("\n");
    printf("--------------------------------------------------------------------------------\n");
}

/*
Função que auxilia na multiplicação, ao apresentar o binário em partes, durane sua operação bit a bit.
*/
void printBinaryMult(int *binary, int length){
    int i;
    for(i = 0; i < length; i++){
        printf("%d", binary[i]);
    }
}

//---------------------------- FUNÇÕES OPERACIONAIS ---------------------------------------//
/*
Função para a coleta de um numero decimal.
*/
int coletaNumero(int num){
    int numero;
    printf("Insira o numero %d: ", num);
    scanf("%d", &numero);
    return numero;
}

/*
Funcao para a coleta da opção desejada pelo usuario.
*/
int coletaOpcao(){
    int resp = 0;
    printf("Operacoes Disponiveis:\n\t[0] Sair\n\t[1] Soma\n\t[2] Subtracao\n\t[3] Multiplicacao\n");
    printf("\n\nDigite a operacao que deseja realizar: \n");
    scanf("%d", &resp);
    return resp;
}

/*
Funcao para resetar um numero binario, deixando seus bits todos como 0.
*/
void resetaBinarios(int *binario1, int *binario2, int *binario3){
    int i;
    for(i = 0; i < MAXLENGHT; i++){
        binario1[i] = 0;
        binario2[i] = 0;
        binario3[i] = 0;
    }
}

/*
Funcao para converter um numero decimal em um numero binario.
*/
int binaryConverter(int decimal, int *binary){
    int i = 0, j = 1;
    int num[MAXLENGHT];

    //Verificação do numero decimal, se for maior que o numero de bits suportado, retorna erro
    if(decimal > MAXNUM || decimal < MINNUM){
        errorShow(0);
        return 0;
    }

    //Verificação do sinal do numero decimal
    if(decimal > 0){
        num[0] = 0;
    }else{
        num[0] = 1;
        decimal = -decimal;
    }

    //Preparaçao do numero binario final
    for(int w = 1; w < MAXLENGHT; w++){
        num[w] = 0;
    }
    
    //Conversao Binaria
    while(decimal > 0){
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }
    j = MAXLENGHT-i;
    for(i=i-1;i>=0;i--,j++){
        num[j] = binary[i];   
    }

    //Reorganização do numero binario final
    for(i = 0; i < MAXLENGHT; i++){
        binary[i] = num[i];
    }
    
    return 1;
}

/*
Funcao que realiza a subtracao dos numeros binarios, operando seu sinal e apresentado cada etapa
realizada durante os calculos.
*/
int subtracao(int *binary1, int *binary2, int *result, int inverted){
    int emprestimo = 0;
    int x = 0, y = 0;

    for(int i=(MAXLENGHT-1); i > 0; i--){
        if(inverted == 1){
            printf("\n\n------------------");
            printf("\nSomando os binarios no bit: [%d]", i);
            showOperation('1', binary1, i, MAXLENGHT);
            showOperation('2', binary2, i, MAXLENGHT);
        }else if(inverted == 2){
            printf("\n\n------------------");
            printf("\nSomando os binarios no bit: [%d]", i);
            showOperation('1', binary2, i, MAXLENGHT);
            showOperation('2', binary1, i, MAXLENGHT);
        }else if(inverted == 3){
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            showOperation('1', binary2, i, MAXLENGHT);
            showOperation('2', binary1, i, MAXLENGHT);
        }else{
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            showOperation('1', binary1, i, MAXLENGHT);
            showOperation('2', binary2, i, MAXLENGHT);
        }

        x = binary1[i];
        y = binary2[i];

        if(x == 1 && y == 1){
            result[i] = 0;
            emprestimo = 0;
        }else if(x == 1 && y == 0){
            result[i] = 1;
            emprestimo = 0;
        }else if(x == 0 && y == 1){
            result[i] = 1;
            emprestimo = 1;
        }else{
            result[i] = 0;
        }

        if(emprestimo == 1){
            if(i > 1){
                binary1[i-1] = 0;
                emprestimo = 0;
            }
        }
        showOperation('F', result, i+1, MAXLENGHT);
    }

    if(emprestimo == 1){
        errorShow(1);
        return 0;
    }

    return 1;
}

/*
Funcao que realiza a soma dos numeros binarios, operando seu sinal e apresentado cada etapa
realizada durante os calculos.
*/
int soma(int *binary1, int *binary2, int *result, int inverted){
    int acumulador = 0;
    int x = 0, y = 0;

    for(int i=(MAXLENGHT-1); i > 0; i--){
        if(inverted == 1){
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            showOperation('1', binary1, i, MAXLENGHT);
            showOperation('2', binary2, i, MAXLENGHT);
        }else if(inverted == 2){
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            showOperation('1', binary2, i, MAXLENGHT);
            showOperation('2', binary1, i, MAXLENGHT);
        }else{
            printf("\n\n------------------");
            printf("\nSomando os binarios no bit: [%d]", i);
            showOperation('1', binary1, i, MAXLENGHT);
            showOperation('2', binary2, i, MAXLENGHT);
        }

        x = binary1[i];
        y = binary2[i];

        if(x == 1 && y == 1){
            if(acumulador == 0){ 
                result[i] = 0;
                acumulador = 1;
            }else{
                result[i] = 1;
                acumulador = 1;
            }
        }else if(x == 1 || y == 1){
            if(acumulador == 0){
                result[i] = 1;
                acumulador = 0;
            }else{
                result[i] = 0;
                acumulador = 1;
            }
        }else{
            if(acumulador == 0){
                result[i] = 0;
                acumulador = 0;
            }else{
                result[i] = 1;
                acumulador = 0;
            }
        }
        showOperation('F', result, i+1, MAXLENGHT);
    }

    if(acumulador == 1){
        errorShow(1);
        return 0;
    }

    return 1;
}

/*
Funcao que realiza a soma para a multiplicacao dos numeros binarios, utilizada apenas em alguns casos
dentro dos ciclos da multiplicacao.
*/
int somaMult(int *A, int *M){
    int x, y;
    int acumulador = 0;
    int result[MAXLENGHT-1];
    for(int i=(MAXLENGHT-2); i >= 0; i--){
        x = A[i];
        y = M[i];
        if(x == 1 && y == 1){
            if(acumulador == 0){ 
                result[i] = 0;
                acumulador = 1;
            }else{
                result[i] = 1;
                acumulador = 1;
            }
        }else if(x == 1 || y == 1){
            if(acumulador == 0){
                result[i] = 1;
                acumulador = 0;
            }else{
                result[i] = 0;
                acumulador = 1;
            }
        }else{
            if(acumulador == 0){
                result[i] = 0;
                acumulador = 0;
            }else{
                result[i] = 1;
                acumulador = 0;
            }
        }
    }

    for(int k = 0; k < MAXLENGHT-1; k++){
        A[k] = result[k];
    }

    return acumulador;
}

/*
Funcao que desloca os numeros binarios para a direita, utilizada para realizar a multiplicacao,
chamda em todos os ciclos, conforme o esquema da multiplicacao para sinal magnitude.
*/
int deslocarDireita(int C, int *A, int *Q){
    for(int i=(MAXLENGHT-2); i >= 0; i--){
        if(i == 0){
           Q[i] = A[MAXLENGHT-2];
        }else{
            Q[i] = Q[i-1];
        }
    }
    for(int h=(MAXLENGHT-2); h >= 0; h--){
        if(h == 0){
            A[h] = C;
        }else{
            A[h] = A[h-1];
        }
    }
    return 0;
}

/*
Função que analisa previamente as operação à serem realizadas com o numero, para que sua multiplicacao
seja possivel, adequando valores do sinal e estruturas para execição dos ciclos da multiplicacao.
*/
int analisaNumMult(int dec1, int dec2, int *bin1, int *bin2){
    int signal = 0;
    int C = 0, A[MAXLENGHT-1],  Q[MAXLENGHT-1], M[MAXLENGHT-1], contador = 0;
    int sum = FALSE;

    for(int i = 0; i < MAXLENGHT-1; i++){
        A[i] = 0;
    }

    for(int j = 0; j < MAXLENGHT-1; j++){
        Q[j] = bin1[j+1];
        M[j] = bin2[j+1];
    }

    if(bin1[0] == 1 && bin2[0] == 1){
        signal = 0;
    }else if(bin1[0] == 1 || bin2[0] == 1){
        signal = 1;
    }else{
        signal = 0;
    }

    printf("\n\n------------------------------------");
    printf("\n--[VALORES INICIAIS]--", contador);
    printf("\n[C]: %d", C);
    printf("\n[A]: ");
    printBinaryMult(A, MAXLENGHT-1);
    printf("\n[Q]: ");
    printBinaryMult(Q, MAXLENGHT-1);
    printf("\n[M]: ");
    printBinaryMult(M, MAXLENGHT-1);
    printf("\n------------------------------------");

    while(contador < MAXLENGHT-1){
        sum = FALSE;
        if(Q[MAXLENGHT-2] == 1){
            printf("\n-----[Ciclo %d | A = (A+M)]-----", contador+1);
            C = somaMult(A, M);
            sum = TRUE;
        }
        if(sum){
            // printBinaryMult(A, MAXLENGHT-1);
            printf("\n-----[A = A + M]-----");
            printf("\n[C]: %d", C);
            printf("\n[A]: ");
            printBinaryMult(A, MAXLENGHT-1);
            printf("\n[Q]: ");
            printBinaryMult(Q, MAXLENGHT-1);
            printf("\n[M]: ");
            printBinaryMult(M, MAXLENGHT-1);
        }else{
            printf("\n-----[Ciclo %d]-----", contador+1);
        }
        C = deslocarDireita(C, A, Q);
        printf("\n-----[ DESLOCA ]-----");
        printf("\n[C]: %d", C);
        printf("\n[A]: ");
        printBinaryMult(A, MAXLENGHT-1);
        printf("\n[Q]: ");
        printBinaryMult(Q, MAXLENGHT-1);
        printf("\n[M]: ");
        printBinaryMult(M, MAXLENGHT-1);
        printf("\n---------------------");
        contador++;
        printf("\n------------------------------------");
    }

    //Mostrar Resultado:
    printf("\n------------------------------------");
    printf("\nResultado da Multiplicacao: ");
    printf("\n[%d", signal);
    for(int i = 0; i < MAXLENGHT-1; i++){
        printf("%d", A[i]);
    }
    for(int i = 0; i < MAXLENGHT-1; i++){
        printf("%d", Q[i]);
    }
    printf("]\n------------------------------------\n");
}

/*
Funcao que analiza os numeros para a subtracao, ajustando seu valor de sinal, e realizando
decisoes sobre quais etapas serao realizadas para que o numero resultante seja correto.
*/
int analisaNumSub(int dec1, int dec2, int *bin1, int *bin2, int *bin3){
    if(bin1[0] == 0 && bin2[0] == 0){
        if(abs(dec1) == abs(dec2)){
            bin3[0] = 0;
            if(subtracao(bin1, bin2, bin3, 0)){
                return 1;
            }
            return 0;
        }else if(dec1 < -dec2){
            bin3[0] = 1;
            if(subtracao(bin2, bin1, bin3, 3)){
                return 1;
            }
            return 0;
        }else{
            bin3[0] = 1;
            if(subtracao(bin1, bin2, bin3, 2)){
                return 1;
            }
            return 0;
        }
    }else if(bin1[1] == 1 && bin2[0] == 0){
        bin3[0] = 1;
        if(soma(bin1, bin2, bin3, 1)){
            return 1;
        }
        return 0;
    }else if(bin1[0] == 0 && bin2[1] == 1){
        bin3[0] = 0;
        if(soma(bin2, bin1, bin3, 1)){
            return 1;
        }
        return 0;
    }else if(bin1[0] == 1 && bin2[0] == 1){
        if(abs(dec1) == abs(dec2)){
            bin3[0] = 0;
            if(subtracao(bin1, bin2, bin3, 0)){
                return 1;
            }
            return 0;
        }else if(-dec1 < -dec2){
            bin3[0] = 0;
            if(subtracao(bin2, bin1, bin3, 3)){
                return 1;
            }
            return 0;
        }else if(-dec1 > -dec2){
            bin3[0] = 1;
            if(subtracao(bin1, bin2, bin3, 2)){
                return 1;
            }
            return 0;
        }
    }else{
        if(abs(dec1) == abs(dec2)){
            bin3[0] = 0;
            if(subtracao(bin1, bin2, bin3, 0)){
                return 1;
            }
            return 0;
        }else{
            bin3[0] = 1;
            if(soma(bin1, bin2, bin3, 1)){
                return 1;
            }
            return 0;
        }
    }
}

/*
Funcao que analiza os numeros para a soma, ajustando seu valor de sinal, e realizando
decisoes sobre quais etapas serao realizadas para que o numero resultante seja correto.
*/
int analisaNumSum(int dec1, int dec2, int *bin1, int *bin2, int *bin3){
    if(bin1[0] == 0 && bin2[0] == 0){
        bin3[0] = 0;
        if(soma(bin1,bin2,bin3,0)){
            return 1;
        }
        return 0;
    }else if(bin1[0] == 0 && bin2[0] == 1){
        if(dec1 > -dec2){
            bin3[0] = 0;
            if(subtracao(bin1,bin2,bin3,1)){
                return 1;
            }
        }else{
            bin3[0] = 1;
            if(subtracao(bin2,bin1,bin3,2)){
                return 1;
            }
        }
        return 0;
    }else if(bin1[0] == 1 && bin2[0] == 0){
        if(-dec1 > dec2){
            bin3[0] = 1;
            if(subtracao(bin1,bin2,bin3,1)){
                return 1;
            }
        }else{
            bin3[0] = 0;
            if(subtracao(bin2,bin1,bin3,2)){
                return 1;
            }
        }
        return 0;
    }else{
        bin3[0] = 1;
        if(soma(bin1,bin2,bin3,0)){
            return 1;
        }
        return 0;
    }
}

//---------------------------- FUNÇÃO MAIN ---------------------------------------//
void main(){
    int num1, num2;
    int bin1[MAXLENGHT], bin2[MAXLENGHT], bin3[MAXLENGHT];
    int resp = 0;
    int possibleOperation = 0;
    resp = coletaOpcao();
    do{
        possibleOperation = 0;
        printf("--------------------------------------------------------------------------------\n");
        resetaBinarios(bin1,bin2,bin3);

        if(resp != 0){
            num1 = coletaNumero(1);
            num2 = coletaNumero(2);
            if (binaryConverter(num1, bin1)){
                if(binaryConverter(num2, bin2)){
                    possibleOperation = 1;
                }
            }
            showBinary(num1, bin1);
            showBinary(num2, bin2);
        }

        switch(resp){
            case 0:
                break;
            case 1:
                if(possibleOperation){
                    if(analisaNumSum(num1, num2, bin1, bin2, bin3)){
                        showOperation('R', bin3, 0, MAXLENGHT);
                        printf("\n--------------------------------------------------------------------------------");
                        showResult(resp, bin3);
                    }
                }
                break;

            case 2:
                if(possibleOperation){
                    if(analisaNumSub(num1, num2, bin1, bin2, bin3)){
                        showOperation('R', bin3, 0, MAXLENGHT);
                        printf("\n--------------------------------------------------------------------------------");
                        showResult(resp, bin3);
                    }
                }
                break;

            case 3:
                if(possibleOperation){
                    analisaNumMult(num1, num2, bin1, bin2);
                }
                break;

            default: 
                errorShow(2);
                break;
        }
        resp = coletaOpcao();
        system("cls");
    }while(resp != 0);

    printf("Finalizando Calculadora Sinal Magnitude...\n");
}
//----------------------------------------------------------------------------------//