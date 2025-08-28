#include <stdio.h>

int main() {
    int a;
    char name[100];
    printf("Enter your number: ");
    scanf("%d", &a);

    printf("Enter you name: ");
    scanf("%s", name);

    printf("Your number is: %d", a);
    printf("Your name: %s", name);
    return 0;
}