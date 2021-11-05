
/**
* @author 백성수
* @studentId
*/

#include <stdio.h>
#include <stdlib.h>


// ■ 헤더

// ● 노드 구조체 정의 및 연결리스트 연산

typedef struct node {
	int data;
	struct node* lchild;
	struct node* rchild;
}node;

// 가용연결리스트
node* avail = NULL;

/**
* 새 노드를 생성하여 반환합니다.
* 
* @param data : 새 노드가 가질 값
* @return 생성된 노드의 포인터
*/
node* get_node(int data);

/**
* 입력된 노드를 반환합니다.
* 
* @param remove_node : 반환될 노드
*/
void ret_node(node* remove_node);

// ● 트리 생성 함수

/**
* 테스트용 트리를 생성합니다.
* 
* @return 생성된 트리의 루트노드 포인터
*/
node* make_tree_by_code();

/**
* 정수값을 담는 트리를 무작위로 생성합니다.
* 
* @param n : 트리가 담을 값의 범위 (1부터 n까지의 값들을 트리에 담습니다.)
* @return 생성된 트리의 루트노드 포인터
*/
node* make_auto_tree(int n);

// ● 트리 순회 함수

/**
* 트리를 중위 순회하여 트리를 출력합니다.
* 
* @param root : 출력할 트리의 루트노드 포인터
*/
void inorder(node* root);

/**
* 트리를 전위 순회하여 트리를 출력합니다.
*
* @param root : 출력할 트리의 루트노드 포인터
*/
void preorder(node* root);

/**
* 트리를 후위 순회하여 트리를 출력합니다.
*
* @param root : 출력할 트리의 루트노드 포인터
*/
void postorder(node* root);

// ● 트리 연산 함수

/**
* 입력된 트리를 복사 생성하여 반환합니다.
* 
* @param root : 복사할 원본 트리의 루트노드 포인터
* @return 복사된 트리의 루트노드 포인터
*/
node* copy(node* root);

/**
* 두 트리를 입력받아 동일한지 검사합니다.
* 
* @param A : 첫번째 입력트리의 루트노드 포인터
* @param B : 두번째 입력트리의 루트노드 포인터
* @return 같은지 여부 : 같으면 1, 다르면 0
*/
int equal(node* A, node* B);




// ■ main

int main() {

	node* testNode1 = make_tree_by_code();
	printf("1. 순회 알고리즘 테스트를 합니다.\n");
	printf("중위 순회 : ");
	inorder(testNode1);
	printf("\n");
	printf("전위 순회 : ");
	preorder(testNode1);
	printf("\n");
	printf("후위 순회 : ");
	postorder(testNode1);
	printf("\n");
	printf("\n\n");

	printf("2. 복사 알고리즘 테스트를 합니다.\n");
	printf("복사된 트리의 순회 결과 : \n");
	node* testNode2 = copy(testNode1);
	printf("중위 순회 : ");
	inorder(testNode2);
	printf("\n");
	printf("전위 순회 : ");
	preorder(testNode2);
	printf("\n");
	printf("후위 순회 : ");
	postorder(testNode2);
	printf("\n");
	printf("\n\n");

	printf("3. 동일성 검사 알고리즘 테스트를 합니다.\n");
	printf("복사된 트리와 원본 트리는 같은가 : %s\n",(equal(testNode1,testNode2))?("true") : ("false"));
	testNode2->data = 2;
	printf("루트노드값을 2로 바꾸었을때 결과 : %s\n", (equal(testNode1, testNode2)) ? ("true") : ("false"));
	testNode2->data = testNode1->data;
	testNode2->lchild->data = 9;
	printf("루트의 왼쪽 자식노드값을 9로 바꾸었을때 결과 : %s\n", (equal(testNode1, testNode2)) ? ("true") : ("false"));

	return 0;
}



// ■ 구현부

node* get_node(int data) {

	node* tmp;

	if (avail == NULL) {
		tmp = (node*)malloc(sizeof(node));
		if (tmp == NULL) {
			printf("메모리 공간을 할당할 수 없습니다.\n");
			exit(1);
		}
	}
	else {
		tmp = avail;
		avail = avail->lchild;
	}

	tmp->data = data;
	tmp->lchild = NULL;
	tmp->rchild = NULL;
	return tmp;
}

void ret_node(node* remove_node) {

	if (remove_node == NULL)
		return;

	remove_node->data = 0;
	remove_node->lchild = avail;
	remove_node->rchild = NULL;

	avail = remove_node;
}

node* make_tree_by_code() {
	// 생성할 트리는 이진트리.
	// 깊이는 3, 총 노드 수는 5개.
	// 루트노드가 2개의 자식을 가지며, 루트노드의 좌측 자식노드가 다시 2개의 자식을 가진다.
	node* root = get_node(5);
	root->lchild = get_node(3);
	root->rchild = get_node(8);

	root->lchild->lchild = get_node(1);
	root->lchild->rchild = get_node(4);

	return root;
}

void inorder(node* root) {
	if (root != NULL) {
		inorder(root->lchild);
		printf("%d",root->data);
		inorder(root->rchild);
	}
}

void preorder(node* root) {
	if (root != NULL) {
		printf("%d", root->data);
		preorder(root->lchild);
		preorder(root->rchild);
	}
}

void postorder(node* root) {
	if (root != NULL) {
		postorder(root->lchild);
		postorder(root->rchild);
		printf("%d", root->data);
	}
}

node* copy(node* root) {
	
	node* newNode;

	if (root != NULL) {
		newNode = get_node(root->data);
		newNode->lchild = copy(root->lchild);
		newNode->rchild = copy(root->rchild);
	}
	else {
		newNode = NULL;
	}

	return newNode;
}

int equal(node* A, node* B) {

	return ((!A && !B) || (A && B && (A->data == B->data) && equal(A->lchild, B->lchild) && equal(A->rchild, B->rchild)));

}