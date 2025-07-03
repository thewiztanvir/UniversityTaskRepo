#include <stdio.h>

int main(){

    int firstNumber,secondNumber,sum;

    printf("Enter your first number:  ");
    scanf("%d", &firstNumber);

    printf("Enter your second number: ");
    scanf("%d", &secondNumber);
    sum = firstNumber + secondNumber;

    printf("The sum of %d and %d is: %d \n", firstNumber, secondNumber, sum);
    printf("Thank you for using this program.\n");
    return 0;
}