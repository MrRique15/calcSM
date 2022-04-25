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

int subtracao(char* x1, char* x2, char* x3){
    return 1;
}

int soma(char* x1, char* x2, char* x3){
    int acumulador = 0;
    int x = 0, y = 0;
    for(int i=(strlen(x1)-1); i > 0;i--){
        printf("Rodando I %d\n", i);
        x = x1[i] - '0';
        y = x2[i] - '0';
        if(x == 1 && y == 1){
            if(acumulador == 0){ 
                x3[i] = '0';
                acumulador = 1;
            }else{
                x3[i] = '1';
                acumulador = 1;
            }
        }else if(x == 1 || y == 1){
            if(acumulador == 0){
                x3[i] = '1';
                acumulador = 0;
            }else{
                x3[i] = '0';
                acumulador = 1;
            }
        }else{
            if(acumulador == 0){
                x3[i] = '0';
                acumulador = 0;
            }else{
                x3[i] = '1';
                acumulador = 0;
            }
        }
    }

    if(acumulador == 1){
        errorShow(1);
        return 0;
    }
    printf("StrLen x3 %d\n", strlen(x3));
    // x3[strlen(x3)-1] = '\0';
    return 1;
}

int coletaOpcao(){
    int resp = 0;
    printf("Operacoes Disponiveis:\n\t[0] Sair\n\t[1] Soma\n\t[2] Subtracao\n\t[3] Multiplicacao\n\t[4] Divisao\n");
    printf("\n\nDigite a operacao que deseja realizar: \n");
    scanf("%d", &resp);
    return resp;
}

int analisaNumSum(char* x1, char* x2, char* x3){
    if(x1[0] == '0' && x2[0] == '0'){
        x3[0] = '0';
        if(soma(x1,x2,x3)){
            return 1;
        }
        return 0;
    }else if(x1[0] == '0' && x2[0] == '1'){
        if(subtracao(x2,x1,x3)){
            return 1;
        }
        return 0;
    }else if(x1[0] == '1' && x2[0] == '0'){
        if(subtracao(x2,x1,x3)){
            return 1;
        }
        return 0;
    }else{
        x3[0] = '1';
        if(soma(x1,x2,x3)){
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
        printf("--------------------------------------------------------------------------------\n");
        switch(resp){
            case 0:
                break;

            case 1:
                num1 = coletaNumero(1);
                num2 = coletaNumero(2);
                if (binaryConverter(num1, bin1)){
                    if(binaryConverter(num2, bin2)){
                        possibleOperation = 1;
                    }
                }
                if(possibleOperation){
                   printf("\nBINARY FINAL is: %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",bin1[0],bin1[1],bin1[2],bin1[3],bin1[4],bin1[5],bin1[6],bin1[7],bin1[8],bin1[9],bin1[10],bin1[11],bin1[12],bin1[13],bin1[14],bin1[15]);
                }
                // printf("%d\n",strlen(str1));
                // if(strlen(str1) != 16 || strlen(str2) != 16){
                //     errorShow(0);
                //     break;
                // }
                // if(analisaNumSum(str1,str2,str3)){
                //     showResult(resp,str3);
                //     printf("%d\n",strlen(str3));
                // }
                break;

            case 2:
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