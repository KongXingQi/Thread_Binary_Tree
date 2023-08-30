#include"BiThrTree.h"


int treeindex = 1; // 0 �ŵ�Ԫ����ŵ����ַ����ĳ���

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



//��ʼ����
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

//����һ���� ����ǰ������
void BiThrTreeCreate(BiThrTree* T)
{
	TElemType ch;

	if (treeindex <= str[0])  // �� str �е��������ݸ�ֵ��ȥ����
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
			(*T)->ltag = (*T)->rtag = 0; //��ʼĬ�� ȫ�� Ϊ 0 
			BiThrTreeCreate(&(*T)->lchild);
			//IsLRtag(T);
			BiThrTreeCreate(&(*T)->rchild);
			//IsLRtag(T);

		}


	}
}

BiThrTree cur, lnext, rnext;

//ʹ�������ĵ�˫��֮����ϵ����
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


//���ص�ǰ�ڵ�����ֵ�
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


//������
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


//���������������� ����ͷ�ڵ�
Status BiThrTreeInThreading(BiThrTree* p, BiThrTree T)
{
	*p = (BiThrTree)malloc(sizeof(BiThrTreeNode));
	(*p)->ltag = 0;
	(*p)->lchild = T;
	(*p)->rchild = *p; //�����ָ ��Ȼ ���������� ���ж�prev->rchild ���������
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

//���������� ���ʶ����� //�ǵݹ��㷨
Status BiThrTreeInOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild;

	while (p != T)
	{
		while (p->ltag == 0) // �����
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


//���������
void BiThrTreeClearThread(BiThrTree* T)
{


	// ���
	if ((*T)->ltag == 1)
	{
		(*T)->lchild = NULL;

	}
	if ((*T)->rtag == 1)
	{
		(*T)->rchild = NULL;

	}

	if ((*T)->ltag == 0 ) // �ݹ� 
	{
		BiThrTreeClearThread(&(*T)->lchild);
	}

	if ((*T)->rtag == 0)
	{
		BiThrTreeClearThread(&(*T)->rchild);

	}


	

	prev = NULL;
}



//����������
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
//���������������� ����ͷ�ڵ�
Status BiThrTreePostThreading(BiThrTree* p, BiThrTree T)
{
	*p = (BiThrTree)malloc(sizeof(BiThrTreeNode));
	(*p)->ltag = (*p)->rtag = 0;
	(*p)->lchild = T;
	(*p)->rchild = *p; //��ָ
	if (T == NULL) // ��Ϊ�� ͷ�ڵ�ָ�Լ�
	{
		(*p)->lchild = *p;
	}
	else
	{
		prev = *p;
		PostThreading(T);
		(*p)->rtag = 1;
		(*p)->rchild = prev;
		//��ͬ������������ʱ�� ��Ҫ�� ���һ���ڵ�ָ��ͷ 
		//��Ϊ ����������ʱ��       ���һ���ڵ��Ǹ��ڵ� ���ܸı���ڵ�����Һ���
	}
	return OK;
}
//���ú��������������ʶ����� �ǵݹ�
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
