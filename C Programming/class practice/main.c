#include<stdio.h>
int main()
{
    int num1, num2, result;

    printf("Enter value for number 1: ");
    scanf("%d", &num1);
    printf("Enter value for number 2: ");
    scanf("%d", &num2);

    if(num1> num2){

        result = num1 - num2;
    }

    else{
        result = num2 - num1;
    }

    printf("The result is: %d", result);

return 0;
}