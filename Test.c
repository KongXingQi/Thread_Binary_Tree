#include"BiThrTree.h"


void BiThrTreeTest1()
{
	BiThrTree T;
	BiThrTreeInit(&T);

	StrAssign (str, "ABDH##I##EJ###CF##G##");	//构造一个树 按照前序输入

	//BiThrTreeCreate2(&T);

	BiThrTreeCreate(&T);
	BiThrTreeCreateParent(&T);
	// 从头节点出未设置好
	BiThrTree H; // 头节点

	BiThrTreeInThreading(&H, T);
	printf("\n中序遍历线索二叉树:");
	BiThrTreeInOrderTraverse(H);

	BiThrTreeClearThread(&T);


	BiThrTreePostThreading(&H, T);
	printf("\n后序遍历线索二叉树:");
	BiThrTreePostOrderTraverse(H);

	BiThrTreeClearThread(&T);

}

int main()
{
	BiThrTreeTest1();
	return 0;
}