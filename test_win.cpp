#include<stdio.h>
#include<windows.h>
#include<time.h>

int main(){
	POINT mouse;   //用来储存鼠标的x y坐标 
	while(1){
		GetCursorPos(&mouse);    //调用GetCursorPos函数获取坐标值
		printf("%d,%d\n",mouse.x,mouse.y);
		Sleep(700);
	}
	return 0; 
}
