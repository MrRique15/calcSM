#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGHT 17    //16 bits para o numero, 1 bit para o '\0'

//Mapeamento de erros
char err[3][255] = {
    "Numero muito grande\n", 
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
    printf("\n[Resultado %s]: %s\n", opcoes[code-1], result);
    printf("--------------------------------------------------------------------------------\n");
}

int soma(char* x1, char* x2, char* x3){
    int acumulador = 0;
    int x = 0, y = 0;
    x3[0] = '0';
    for(int i=(strlen(x1)-1); i > 0;i--){
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
    x3[strlen(x3)-1] = '\0';
    return 1;
}

int coletaOpcao(){
    int resp = 0;
    printf("Operacoes Disponiveis:\n\t[0] Sair\n\t[1] Soma\n\t[2] Subtracao\n\t[3] Multiplicacao\n\t[4] Divisao\n");
    printf("\n\nDigite a operacao que deseja realizar: \n");
    scanf("%d", &resp);
    return resp;
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
                if(strlen(str1)+1 > MAXLENGHT || strlen(str2) > MAXLENGHT){
                    errorShow(0);
                    break;
                }
                if (soma(str1,str2,str3)){
                    showResult(resp,str3);
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