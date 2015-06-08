// BFInterpreter.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <memory.h>

char* PC;//ָ��Ĵ���.
char* DT;//����ָ��Ĵ���.

char Inst[10000]={"+++++[>,.<-]"};//ָ�����
char Data[10000];//���ݻ�����.
char* PCStack[1000];//���ݹ����1K��.
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
	PCStack[stackindex]=PC;//ѹջ
}
char* POPSTACK()
{
	
	char*pret= PCStack[stackindex];
	stackindex--;
	return pret;
}
void Exec1Cmd(char ch)
{//ִ��һ��ָ��
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
			PUSHSTACK();//ѹջ.
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
			printf("�������.");
			exit(0);
		}
		printf("Syntax Error!!\n");//�������.
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

