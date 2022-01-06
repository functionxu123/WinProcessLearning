#include <stdio.h>
#include <time.h>
#include <windows.h>

#include <iomanip>
#include <iostream>

int main() {
    volatile int pflag = 1;
    std::cout << std::hex << (void *)(&pflag) << std::endl;
    POINT mouse;  //用来储存鼠标的x y坐标
    while (pflag) {
        GetCursorPos(&mouse);  //调用GetCursorPos函数获取坐标值
        printf("%d : %d,%d\n", pflag, mouse.x, mouse.y);
        Sleep(1600);
        //++pflag;
    }
    return 0;
}
