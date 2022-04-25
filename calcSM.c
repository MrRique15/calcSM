#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGHT 16    //16 bits para o numero, 1 bit para o '\0'
#define MAXNUM 32767    //2^15 - 1
#define MINNUM -32767   //-(2^15 - 1)

//Mapeamento de erros
char err[3][255] = {
    "Um numero decimal excede a quantidade de bits suportada quando transformado em binario\n", 
    "Estouro de Bits para o calculo\n", 
    "Opcao Invalida\n"
};
void errorShow(int code){
    printf("\n[---WARNING---]: %s\n", err[code]);
}

//Funções Operacionais
int coletaNumero(int num){
    int numero;
    printf("Insira o numero %d: ", num);
    scanf("%d", &numero);
    return numero;
}
void resetaBinarios(int *binario1, int *binario2, int *binario3){
    int i;
    for(i = 0; i < MAXLENGHT; i++){
        binario1[i] = 0;
        binario2[i] = 0;
        binario3[i] = 0;
    }
}

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

void showResult(int code,int *result){
    char opcoes[4][MAXLENGHT] = {
        "Soma", 
        "Subtracao", 
        "Multiplicacao",
        "Divisao"
    };
    printf("\n[Resultado %s]: ", opcoes[code-1]);
    for(int i = 0; i < MAXLENGHT; i++){
        printf("%d", result[i]);
    }
    printf("\n");
    printf("--------------------------------------------------------------------------------\n");
}

int subtracao(int *binary1, int *binary2, int *result, int inverted){
    int emprestimo = 0;
    int x = 0, y = 0;
    for(int i=(MAXLENGHT-1); i > 0; i--){
        if(inverted == 1){
            printf("\n\n------------------");
            printf("\nSomando os binarios no bit: [%d]", i);
            printf("\nBinario1: %d", binary1[i]);
            printf("\nBinario2: %d", binary2[i]);
        }else if(inverted == 2){
            printf("\n\n------------------");
            printf("\nSomando os binarios no bit: [%d]", i);
            printf("\nBinario1: %d", binary2[i]);
            printf("\nBinario2: %d", binary1[i]);
        }else if(inverted == 3){
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            printf("\nBinario1: %d", binary2[i]);
            printf("\nBinario2: %d", binary1[i]);
        }else{
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            printf("\nBinario1: %d", binary1[i]);
            printf("\nBinario2: %d", binary2[i]);
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
    }

    if(emprestimo == 1){
        errorShow(1);
        return 0;
    }
    return 1;
}

int soma(int *binary1, int *binary2, int *result, int inverted){
    int acumulador = 0;
    int x = 0, y = 0;

    for(int i=(MAXLENGHT-1); i > 0; i--){
        if(inverted == 1){
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            printf("\nBinario1: %d", binary1[i]);
            printf("\nBinario2: %d", binary2[i]);
        }else if(inverted == 2){
            printf("\n\n------------------");
            printf("\nSubtraindo os binarios no bit: [%d]", i);
            printf("\nBinario1: %d", binary2[i]);
            printf("\nBinario2: %d", binary1[i]);
        }else{
            printf("\n\n------------------");
            printf("\nSomando os binarios no bit: [%d]", i);
            printf("\nBinario1: %d", binary1[i]);
            printf("\nBinario2: %d", binary2[i]);
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
    }

    if(acumulador == 1){
        errorShow(1);
        return 0;
    }
    return 1;
}

int coletaOpcao(){
    int resp = 0;
    printf("Operacoes Disponiveis:\n\t[0] Sair\n\t[1] Soma\n\t[2] Subtracao\n\t[3] Multiplicacao\n\t[4] Divisao\n");
    printf("\n\nDigite a operacao que deseja realizar: \n");
    scanf("%d", &resp);
    return resp;
}

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
void main(){
    int num1, num2;
    int bin1[MAXLENGHT], bin2[MAXLENGHT], bin3[MAXLENGHT];
    int resp = 0;
    int possibleOperation = 0;
    resp = coletaOpcao();
    do{
        possibleOperation = 0;
        resetaBinarios(bin1,bin2,bin3);
        printf("--------------------------------------------------------------------------------\n");
        num1 = coletaNumero(1);
        num2 = coletaNumero(2);
        if (binaryConverter(num1, bin1)){
            if(binaryConverter(num2, bin2)){
                possibleOperation = 1;
            }
        }
        switch(resp){
            case 0:
                break;
            case 1:
                if(possibleOperation){
                    if(analisaNumSum(num1, num2, bin1, bin2, bin3)){
                        showResult(resp, bin3);
                    }
                }
                break;

            case 2:
                if(possibleOperation){
                    if(analisaNumSub(num1, num2, bin1, bin2, bin3)){
                        showResult(resp, bin3);
                    }
                }
                break;

            case 3:
                break;

            case 4:
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