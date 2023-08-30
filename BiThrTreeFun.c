#include"BiThrTree.h"


int treeindex = 1; // 0 号单元所存放的是字符串的长度

Status StrAssign(String str, char* chs)
{
	assert(strlen(chs) < MAX_TREE_SIZE);

	str[0] = (int)strlen(chs);
	int i = 1;
	for (i = 1; i < str[0]+1; i++)
	{
		str[i] = chs[i - 1];
	}

	return OK;
}



//初始化树
Status BiThrTreeInit(BiThrTree* T)
{
	*T = NULL;

	return OK;
}

//Status IsLRtag(BiThrTree* T)
//{
//	if ((*T)->lchild == NULL)
//	{
//		(*T)->ltag = 1;
//	}
//
//	if ((*T)->rchild == NULL)
//	{
//		(*T)->rtag = 1;
//	}
//
//	return OK;
//}

//构造一个树 按照前序输入
void BiThrTreeCreate(BiThrTree* T)
{
	TElemType ch;

	if (treeindex <= str[0])  // 把 str 中的所有数据赋值过去即可
	{
		ch = str[treeindex++];

		if (ch == '#')
		{
			*T = NULL;
		}
		else
		{
			*T = (BiThrTree)malloc(sizeof(BiThrTreeNode));
			if (*T == NULL)
			{
				exit(-1);
			}
			
			(*T)->data = ch;
			(*T)->ltag = (*T)->rtag = 0; //开始默认 全部 为 0 
			BiThrTreeCreate(&(*T)->lchild);
			//IsLRtag(T);
			BiThrTreeCreate(&(*T)->rchild);
			//IsLRtag(T);

		}


	}
}

BiThrTree cur, lnext, rnext;

//使二叉树的的双亲之间联系起来
void BiThrTreeCreateParent(BiThrTree* T)
{
	if ((*T)->lchild != NULL)
	{
		BiThrTreeCreateParent(&(*T)->lchild);
	}

	if ((*T)->rchild != NULL)
	{
		BiThrTreeCreateParent(&(*T)->rchild);
	}

	lnext = (*T)->lchild;
	rnext = (*T)->rchild;

	if (lnext != NULL)
	{
		lnext->parent = *T;
	}
	if (rnext != NULL)
	{
		rnext->parent = *T;
	}
	
}


//返回当前节点的右兄弟
BiThrTree BiThrTreeRinghtSibling(BiThrTree T)
{

	if (T->parent->rchild != T)
	{
		return T->parent->rchild;
	}
	else
	{
		return NULL;
	}
}

void BiThrTreeCreate2(BiThrTree* T)
{
	TElemType c;
	scanf("%c", &c);

	if (c == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiThrTree)malloc(sizeof(BiThrTreeNode));
		(*T)->data = c;
		(*T)->ltag = (*T)->rtag = 0;
		BiThrTreeCreate2(&(*T)->lchild);
		BiThrTreeCreate2(&(*T)->rchild);
	}
}

Status BiThrTreeVisit(TElemType c)
{
	printf("%c ",c);
	return OK;
}


BiThrTree prev = NULL;


//线索化
void InThreading(BiThrTree T)
{
	if (T != NULL)
	{
		InThreading(T->lchild);
		if (T->lchild == NULL)
		{
			T->ltag = 1;
			T->lchild = prev;
		}

		if (prev->rchild == NULL)
		{
			prev->rtag = 1;
			prev->rchild = T;
		}

		prev = T;
		InThreading(T->rchild);
	}


}


//中序线索化二叉树 增加头节点
Status BiThrTreeInThreading(BiThrTree* p, BiThrTree T)
{
	*p = (BiThrTree)malloc(sizeof(BiThrTreeNode));
	(*p)->ltag = 0;
	(*p)->lchild = T;
	(*p)->rchild = *p; //必须回指 不然 在线索化是 第判断prev->rchild 会出现问题
	if (T == NULL)
	{
		(*p)->lchild = *p;
	}	
	else
	{
		prev = *p;
		InThreading(T);
		prev->rtag = 1;
		prev->rchild = *p;
		(*p)->rtag = 1;
		(*p)->rchild = prev;
	}

	return OK;
}

//利用线索化 访问二叉树 //非递归算法
Status BiThrTreeInOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild;

	while (p != T)
	{
		while (p->ltag == 0) // 找左根
		{
			p = p->lchild;
		}
		BiThrTreeVisit(p->data);
		while (p->rtag == 1 && p->rchild != T)
		{
			p = p->rchild;
			BiThrTreeVisit(p->data);
		}

		p = p->rchild;

	}

	return OK;
}


//将线索清空
void BiThrTreeClearThread(BiThrTree* T)
{


	// 清空
	if ((*T)->ltag == 1)
	{
		(*T)->lchild = NULL;

	}
	if ((*T)->rtag == 1)
	{
		(*T)->rchild = NULL;

	}

	if ((*T)->ltag == 0 ) // 递归 
	{
		BiThrTreeClearThread(&(*T)->lchild);
	}

	if ((*T)->rtag == 0)
	{
		BiThrTreeClearThread(&(*T)->rchild);

	}


	

	prev = NULL;
}



//后序线索化
void PostThreading(BiThrTree T)
{
	if (T != NULL)
	{
		PostThreading(T->lchild);
		PostThreading(T->rchild);

		if (T->lchild == NULL)
		{
			T->ltag = 1;
			T->lchild = prev;
		}

		if (prev->rchild == NULL)
		{
			prev->rtag = 1;
			prev->rchild = T;
		}
		prev = T;
	}
}
//后序线索化二叉树 增加头节点
Status BiThrTreePostThreading(BiThrTree* p, BiThrTree T)
{
	*p = (BiThrTree)malloc(sizeof(BiThrTreeNode));
	(*p)->ltag = (*p)->rtag = 0;
	(*p)->lchild = T;
	(*p)->rchild = *p; //回指
	if (T == NULL) // 数为空 头节点指自己
	{
		(*p)->lchild = *p;
	}
	else
	{
		prev = *p;
		PostThreading(T);
		(*p)->rtag = 1;
		(*p)->rchild = prev;
		//不同于中序线索化时候 需要把 最后一个节点指向头 
		//因为 后续线索化时候，       最后一个节点是根节点 不能改变根节点的左右孩子
	}
	return OK;
}
//利用后序线索话化访问二叉树 非递归
Status BiThrTreePostOrderTraverse(BiThrTree T)
{
	BiThrTree p = T->lchild;

	while (1)
	{
		
		while (p->ltag == 0)
		{
			p = p->lchild;
		}
		BiThrTreeVisit(p->data);
		while (p->rtag == 1)
		{
			p = p->rchild;
			BiThrTreeVisit(p->data);
		}
		p = BiThrTreeRinghtSibling(p);
		if (p == NULL)
		{
			BiThrTreeVisit(T->lchild->data);
			break;
		}
	}

	return OK;
}
