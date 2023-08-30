#include"BiThrTree.h"


void BiThrTreeTest1()
{
	BiThrTree T;
	BiThrTreeInit(&T);

	StrAssign (str, "ABDH##I##EJ###CF##G##");	//����һ���� ����ǰ������

	//BiThrTreeCreate2(&T);

	BiThrTreeCreate(&T);
	BiThrTreeCreateParent(&T);
	// ��ͷ�ڵ��δ���ú�
	BiThrTree H; // ͷ�ڵ�

	BiThrTreeInThreading(&H, T);
	printf("\n�����������������:");
	BiThrTreeInOrderTraverse(H);

	BiThrTreeClearThread(&T);


	BiThrTreePostThreading(&H, T);
	printf("\n�����������������:");
	BiThrTreePostOrderTraverse(H);

	BiThrTreeClearThread(&T);

}

int main()
{
	BiThrTreeTest1();
	return 0;
}