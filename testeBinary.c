#include<stdio.h>    
#include<stdlib.h>  

int main(){  
    int a[10],n,i,num[10];   
    int j = 0; 
    system ("cls");  
    printf("Enter the number to convert: ");    
    scanf("%d",&n);    
    for(i=0;n>0;i++){    
        a[i]=n%2;    
        n=n/2;    
    }
    printf("\nI is: %d", i);
    printf("\nBinary of Given Number is=");    
    for(i=i-1;i>=0;i--,j++){
        num[j] = a[i];
        printf("%d",a[i]);    
    }
    printf("\nJ is: %d", j);
    printf("\nA is: %d%d%d%d",a[3],a[2],a[1],a[0]);
    printf("\nNUM is: %d%d%d%d",num[0],num[1],num[2],num[3]);
    return 0;  
}  