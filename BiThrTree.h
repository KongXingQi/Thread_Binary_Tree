#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>


#define OK 1
#define ERROR 0
#define MAX_TREE_SIZE 50

typedef char TElemType;		//��������������������
typedef char String[MAX_TREE_SIZE];	// 0 �Ŵ洢�ַ����ĳ���
typedef int Status;			//Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK��

//TElemType NIL = '#';		// NIl ��ʾ��ŵĿ�����
String str;

typedef struct BiThrTreeNode
{
	TElemType data;
	int ltag, rtag; // 0 ��ʾ���Һ��Ӵ�ŵ���ԭ�������Һ��ӵ�ַ    1 ��ʾ ���Һ��� ��ŵ���������ǰ �� ���� ��ǰ�����̵ĵ�ַ��
	struct BiThrTreeNode* lchild, * rchild,*parent;
}BiThrTreeNode,* BiThrTree;


Status StrAssign(String str, char* chs);


//��ʼ����
Status BiThrTreeInit(BiThrTree* T);

//����
Status BiThrTreeVisit(TElemType c);

//����һ���� ����ǰ������
void BiThrTreeCreate(BiThrTree* T);

void BiThrTreeCreate2(BiThrTree* T);

//ʹ�������ĵ�˫��֮����ϵ����
void BiThrTreeCreateParent(BiThrTree* T);

//���ص�ǰ�ڵ�����ֵ�
BiThrTree BiThrTreeRinghtSibling(BiThrTree T);

//����������
void InThreading(BiThrTree T);
//���������������� ����ͷ�ڵ�
Status	BiThrTreeInThreading(BiThrTree* p,BiThrTree T);
//�������������� ���ʶ����� //�ǵݹ��㷨
Status BiThrTreeInOrderTraverse(BiThrTree T);


//���������   ��ǰ �� �� ��������� ������
void BiThrTreeClearThread(BiThrTree* T);

//����������
void PostThreading(BiThrTree T);
//���������������� ����ͷ�ڵ�
Status BiThrTreePostThreading(BiThrTree* p, BiThrTree T);
//���ú��������������ʶ����� �ǵݹ�
Status BiThrTreePostOrderTraverse(BiThrTree T);

