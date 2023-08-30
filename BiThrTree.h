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

typedef char TElemType;		//线索二叉树的数据类型
typedef char String[MAX_TREE_SIZE];	// 0 号存储字符串的长度
typedef int Status;			//Status是函数的类型,其值是函数结果状态代码,如OK等

//TElemType NIL = '#';		// NIl 表示存放的空数据
String str;

typedef struct BiThrTreeNode
{
	TElemType data;
	int ltag, rtag; // 0 表示左右孩子存放的是原本的左右孩子地址    1 表示 左右孩子 存放的是线索（前 中 后序 的前驱与后继的地址）
	struct BiThrTreeNode* lchild, * rchild,*parent;
}BiThrTreeNode,* BiThrTree;


Status StrAssign(String str, char* chs);


//初始化树
Status BiThrTreeInit(BiThrTree* T);

//访问
Status BiThrTreeVisit(TElemType c);

//构造一个树 按照前序输入
void BiThrTreeCreate(BiThrTree* T);

void BiThrTreeCreate2(BiThrTree* T);

//使二叉树的的双亲之间联系起来
void BiThrTreeCreateParent(BiThrTree* T);

//返回当前节点的右兄弟
BiThrTree BiThrTreeRinghtSibling(BiThrTree T);

//中序线索化
void InThreading(BiThrTree T);
//中序线索化二叉树 增加头节点
Status	BiThrTreeInThreading(BiThrTree* p,BiThrTree T);
//利用中序线索化 访问二叉树 //非递归算法
Status BiThrTreeInOrderTraverse(BiThrTree T);


//将线索清空   （前 中 后 ）序遍历法 都可以
void BiThrTreeClearThread(BiThrTree* T);

//后序线索化
void PostThreading(BiThrTree T);
//后序线索化二叉树 增加头节点
Status BiThrTreePostThreading(BiThrTree* p, BiThrTree T);
//利用后序线索话化访问二叉树 非递归
Status BiThrTreePostOrderTraverse(BiThrTree T);

