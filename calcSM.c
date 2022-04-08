#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGHT 17    //16 bits para o numero, 1 bit para o '\0'

//Mapeamento de erros
char err[3][255] = {
    "Numeros com tamanho inválido\n", 
    "Estouro de Bits para o calculo\n", 
    "Opcao Invalida\n"
};
void errorShow(int code){
    printf("\n[---WARNING---]: %s\n", err[code]);
}

void coletaNumero(int num, const char* numero){
    printf("Insira o numero %d: ", num);
    scanf("%s", numero);
}

void showResult(int code,char result[]){
    char opcoes[4][MAXLENGHT] = {
        "Soma", 
        "Subtracao", 
        "Multiplicacao",
        "Divisao"
    };
    printf("\n[Resultado %s]: ", opcoes[code-1]);
    for(int i = 0; i < MAXLENGHT; i++){
        printf("%c", result[i]);
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
    char str1[MAXLENGHT];
    char str2[MAXLENGHT];
    char str3[MAXLENGHT];
    int resp = 0;
    resp = coletaOpcao();
    do{
        printf("--------------------------------------------------------------------------------\n");
        switch(resp){
            case 0:
                break;

            case 1:
                coletaNumero(1,str1);
                coletaNumero(2,str2);
                printf("%d\n",strlen(str1));
                if(strlen(str1) != 16 || strlen(str2) != 16){
                    errorShow(0);
                    break;
                }
                if(analisaNumSum(str1,str2,str3)){
                    showResult(resp,str3);
                    printf("%d\n",strlen(str3));
                }
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