// BFInterpreter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <memory.h>

char* PC;//指令寄存器.
char* DT;//数据指针寄存器.

char Inst[10000]={"+++++[>,.<-]"};//指令缓冲区
char Data[10000];//数据缓冲区.
char* PCStack[1000];//最多递归调用1K次.
int stackindex;
void InitMachine()
{
	PC=Inst;
	DT=Data;
	memset(Data,0,10000);
	memset(PCStack,0,10000);
	stackindex=1;
}
void PUSHSTACK()
{
	stackindex++;
	PCStack[stackindex]=PC;//压栈
}
char* POPSTACK()
{
	
	char*pret= PCStack[stackindex];
	stackindex--;
	return pret;
}
void Exec1Cmd(char ch)
{//执行一句指令
	char* temppc;
	do{
		if(ch=='>')
		{
			DT++;
			break;
		}
		if(ch=='<')
		{
			DT--;
			break;
		}
		if(ch=='+')
		{
			(*DT)++;
			break;
		}
		if(ch=='-')
		{
			(*DT)--;
			break;
		}
		if(ch=='.')
		{
			printf("%c\n",*DT);
			break;
		}
		if(ch==',')
		{
			fflush(stdin);
			*DT=getch();
			break;
		}
		if(ch=='[')
		{
			PUSHSTACK();//压栈.
			break;
		}
		if(ch==']')
		{
			temppc=POPSTACK();
			if(*DT)
			{
				PC=temppc;
				PUSHSTACK();
			}
			break;
		}
		if(ch==0)
		{
			printf("程序结束.");
			exit(0);
		}
		printf("Syntax Error!!\n");//其他情况.
	}while(0);
	PC++;
	return;
}
void showstate()
{
	printf("PC=%d,ST=%d,DT=%d\nData:%d,Cmd:%c\n",PC-Inst,stackindex,DT-Data,*DT,*PC);
}
int _tmain(int argc, _TCHAR* argv[])
{
	InitMachine();
	while(1)
	{
		Exec1Cmd(*PC);
		//showstate();
	}
	return 0;
}

