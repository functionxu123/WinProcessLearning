#include <stdio.h>
 #include <stdlib.h>
int a = 0; //全局初始化区 global
char *p1; //全局未初始化区 comm


int main()
{
    int b; //栈
    char s[] = "abc"; //栈
    char *p2; //栈
    char *p3 = "123456"; //123456\0在常量区，p3在栈上 .LC0:
    static int c =0; //全局（静态）初始化区
    p1 = (char *)malloc(10); //堆
    p2 = (char *)malloc(20);  //堆


    static int arr[1000] = {233};// 静态数组

    printf ("stack 1: %x \n", &b);
    printf ("stack 2: %x \n", s);
    printf ("stack 3: %x \n", &p2);
    printf ("const 1: %x \n", p3);
    printf ("global 1: %x \n", &c);
    printf ("heap 1: %x \n", p1);
    printf ("heap 2: %x \n", p2);
    printf ("global 1: %x \n", &a);
    printf ("bss 2: %x \n", &p1);

    return 0;
}