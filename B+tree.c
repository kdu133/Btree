#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define wait_time 2000
#define T 3
#define M (T*2)-1


typedef struct node {	
	bool isLeaf;					// ��尡 �������� Ȯ��
	int size;						// ��忡 ����� Ű ����
	int keys[M];					// ��忡 ����� Ű �迭
	struct node* prev;				// ���� ��尡 ����� �迭
	struct node* next;				// ���� ��尡 ����� �迭
	struct node* p_arr[M + 1];		// ��忡 ����� ������ �迭
} node;

typedef struct BPlusTree {			// BƮ�� ����ü ����
	node* root;						// BƮ���� ��Ʈ �ּ�
	node* head;						// ���� �������� �� �� �ּ�
	node* tail;						// ���� �������� �� �� �ּ�
} BPtree;

// �׽�Ʈ �Լ�

void test_create();
void test_insert(BPtree* bpt);
void test_insert_key_data(BPtree* bpt);
void test_delete(BPtree* bpt);
void test_test(BPtree* bpt);

// ��� ���� �Լ�

node* create_node(void);
int find_index(node* cur, int key);
void split_node(BPtree* bpt, node* parent, int index);
bool bind_node(BPtree* bpt, node* parent, int index);
void borrow_key_from_right(node* parent, int index);
void borrow_key_from_left(node* parent, int index);
void delete_node(node*);

// BPtree ���� �Լ�

BPtree* create_BPtree(void);
void free_all_node(node* cur);
bool delete_BPtree(BPtree* bpt);
void print_by_dfs(node* cur, int cnt);
void print_tree(node* cur, int cnt);
void print_data_ascending(node* cur);
void print_data_descending(node* cur);
bool search_key(BPtree* bpt, int key);
bool insert_key_data(BPtree* bpt, int key, int* data);
bool delete_key(BPtree* bpt, int key);

// ���α׷� ���� ���� �Լ�

int get_key(char* action);
int* get_data(char* action);
int select_menu(void);
void exit_program(void);
void start_program();


// ���� �Լ�

int main(void) {
	//test_insert(bpt);
	//test_delete(bpt);
	//test_test(bpt);
	//delete_BPtree(bpt);
	//test_test(bpt);
	start_program();
	return true;
}

// �׽�Ʈ �Լ�

void test_create() {
	BPtree* t = (BPtree*)malloc(sizeof(BPtree));
	t->root = create_node();
	printf("%d %d\n", t->root->isLeaf, t->root->size);

	for (int i = 0; i < M; i++) {
		t->root->keys[i] = i;
	}

	for (int i = 0; i < M; i++) {
		printf("%d ", t->root->keys[i]);
	}

	printf("\n");

	for (int i = 0; i < M; i++) {
		node** nnd = malloc(sizeof(node*));
		t->root->p_arr[i] = nnd;
	}

	for (int i = 0; i < M; i++) {
		printf("%d ", t->root->p_arr[i]);
	}

	for (int i = 0; i < M; i++) {
		free(t->root->p_arr[i]);
	}

	//start_program();
	free(t->root);
	free(t);
}

void test_insert(BPtree* bpt) {
	print_tree(bpt->root, 0);
	insert_key_data(bpt, 10, 10);
	insert_key_data(bpt, 11, 11);
	insert_key_data(bpt, 12, 12);
	insert_key_data(bpt, 13, 13);
	insert_key_data(bpt, 14, 14);
	insert_key_data(bpt, 22, 22);
	insert_key_data(bpt, 23, 23);
	insert_key_data(bpt, 4, 4);
	insert_key_data(bpt, 5, 5);
	insert_key_data(bpt, 6, 6);
	insert_key_data(bpt, 15, 15);
	insert_key_data(bpt, 21, 21);
	insert_key_data(bpt, 16, 16);
	insert_key_data(bpt, 17, 17);
	insert_key_data(bpt, 1, 1);
	insert_key_data(bpt, 33, 33);
	insert_key_data(bpt, 34, 34);
	insert_key_data(bpt, 7, 7);
	insert_key_data(bpt, 30, 30);
	insert_key_data(bpt, 31, 31);
	insert_key_data(bpt, 32, 32);
	insert_key_data(bpt, 9, 9);
	insert_key_data(bpt, 18, 18);
	insert_key_data(bpt, 19, 19);
	insert_key_data(bpt, 35, 35);
	insert_key_data(bpt, 36, 36);
	insert_key_data(bpt, 24, 24);
	insert_key_data(bpt, 25, 25);
	insert_key_data(bpt, 29, 29);
	insert_key_data(bpt, 2, 2);
	insert_key_data(bpt, 3, 3);
	insert_key_data(bpt, 8, 8);
	insert_key_data(bpt, 20, 20);
	insert_key_data(bpt, 26, 26);
	insert_key_data(bpt, 27, 27);
	insert_key_data(bpt, 28, 28);
}

void test_insert_key_data(BPtree* bpt) {
	int* test_arr[1000];

	for (int i = 1; i < 40; i++) {
		int key = i * 10;
		test_arr[key] = (int*)malloc(sizeof(int));
		*test_arr[key] = key;
		insert_key_data(bpt, key, test_arr[key]);
		print_tree(bpt->root, 0);
		print_data_ascending(bpt->head);
		print_data_descending(bpt->tail);
	}

	for (int i = 1; i < 40; i++) {
		int key = (i * 10) + 5; 
		test_arr[key] = (int*)malloc(sizeof(int));
		*test_arr[key] = key;
		insert_key_data(bpt, key, test_arr[key]);
		print_tree(bpt->root, 0);
		print_data_ascending(bpt->head);
		print_data_descending(bpt->tail);
	}

	print_tree(bpt->root, 0);
}

void test_delete(BPtree* bpt) {
	print_tree(bpt->root, 0);
	delete_key(bpt, 40);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 50);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 60);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 130);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 280);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 290);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 210);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 150);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 160);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 170);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 180);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 220);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 230);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 240);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 75);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 85);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 95);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 105);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 200);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 140);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 190);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 270);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 250);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 260);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 115);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 10);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 20);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 30);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 125);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 135);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 315);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 325);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 365);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 375);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 145);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 155);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 300);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 310);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 345);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 355);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 295);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 305);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 385);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 395);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 340);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 350);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 100);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 110);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 120);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 215);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 225);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 235);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 245);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 360);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 370);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 70);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 80);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 90);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 255);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 380);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 390);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 15);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 25);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 35);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 45);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 320);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 330);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 335);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 55);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 65);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 165);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 175);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 185);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 195);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 205);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 265);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 275);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 285);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
}

void test_test(BPtree* bpt) {
	/*insert_key_data(bpt, 10);
	insert_key_data(bpt, 20);
	insert_key_data(bpt, 30);
	insert_key_data(bpt, 40);
	insert_key_data(bpt, 50);
	insert_key_data(bpt, 60);
	insert_key_data(bpt, 70);
	insert_key_data(bpt, 80);
	insert_key_data(bpt, 90);
	insert_key_data(bpt, 100);
	insert_key_data(bpt, 110);
	insert_key_data(bpt, 120);
	insert_key_data(bpt, 130);
	insert_key_data(bpt, 140);
	insert_key_data(bpt, 150);
	insert_key_data(bpt, 160);
	insert_key_data(bpt, 170);
	insert_key_data(bpt, 180);
	insert_key_data(bpt, 190);
	insert_key_data(bpt, 200);
	insert_key_data(bpt, 210);
	insert_key_data(bpt, 220);
	insert_key_data(bpt, 230);
	insert_key_data(bpt, 240);
	insert_key_data(bpt, 250);
	insert_key_data(bpt, 260);
	insert_key_data(bpt, 9);
	insert_key_data(bpt, 39);
	insert_key_data(bpt, 101);
	insert_key_data(bpt, 102);
	insert_key_data(bpt, 103);
	insert_key_data(bpt, 104);
	insert_key_data(bpt, 161);
	insert_key_data(bpt, 191);
	insert_key_data(bpt, 251);
	print_tree(bpt->root, 0);
	delete_key(bpt, 103);
	print_tree(bpt->root, 0);
	delete_key(bpt, 70);
	print_tree(bpt->root, 0);
	delete_key(bpt, 130);
	print_tree(bpt->root, 0);
	delete_key(bpt, 104);
	print_tree(bpt->root, 0);
	delete_key(bpt, 60);
	print_tree(bpt->root, 0);
	delete_key(bpt, 120);
	print_tree(bpt->root, 0);
	delete_key(bpt, 240);
	print_tree(bpt->root, 0);
	delete_key(bpt, 160);
	print_tree(bpt->root, 0);
	delete_key(bpt, 180);
	print_tree(bpt->root, 0);
	delete_key(bpt, 250);
	print_tree(bpt->root, 0);
	delete_key(bpt, 20);
	print_tree(bpt->root, 0);
	delete_key(bpt, 80);
	print_tree(bpt->root, 0);
	delete_key(bpt, 102);
	print_tree(bpt->root, 0);
	delete_key(bpt, 50);
	print_tree(bpt->root, 0);
	delete_key(bpt, 90);
	print_tree(bpt->root, 0);*/
}


// ��� ���� �Լ�

node* create_node(void) {
	node* new_node = (node*)malloc(sizeof(node));
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

int find_index(node* cur, int key) {
	int index = cur->size;
	while (0 < index && key <= cur->keys[index - 1]) {
		index--;
	}
	return index;
}

void split_node(BPtree* bpt, node* parent, int index) {
	// ������ �ڽ��� �� ��带 �����Ѵ�

	node* right_child = create_node();
	// ���� ���� ���� �ڽ��� �ȴ�
	node* left_child = parent->p_arr[index];

	// ������ �ڽ��� ������� ���δ� ���� �ڽ��� ���� �����ϴ�
	right_child->isLeaf = left_child->isLeaf;

	// ������ �ڽ��� ũ��� M/2 or T-1 �� �ǰ�
	right_child->size = T - 1;

	// ���� �ڽ��� Ű �迭���� �߰��� �����ʿ� �ִ� ���� ������ ���� �ű��
	for (int i = 0; i < T - 1; i++) {
		right_child->keys[i] = left_child->keys[i + T];
	}

	int end = T;
	if (left_child->isLeaf) {
		end -= 1;
	}

	for (int i = 0; i < end; i++) {
		right_child->p_arr[i] = left_child->p_arr[i + T];
	}
	// ���� ��忡�� ���� �����͸� �ű�� ���� �������� ũ�⸦ �����Ѵ�
	left_child->size = T-1;

	if (left_child->isLeaf) {
		left_child->size += 1;
	}

	// ������ ����� �߰� ���� �� �ڸ��� �����
	// �θ��� Ű �迭���� �ڽ� ��带 ����Ű�� ��ġ ���� ���� �� ĭ�� �ڷ� �ű��
	for (int i = parent->size; i > index; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}
	if (parent->size != 0) {
		// �θ��� ������ �迭���� �ڽ� ��带 ����Ű�� ��ġ ���� ���� �� ĭ�� �ڷ� �ű�� 
		for (int i = parent->size + 1; i > index; i--) {
			parent->p_arr[i] = parent->p_arr[i - 1];
		}
	}

	// ������ ����� Ű �迭�� �߰� ���� �θ� ��忡 �����Ѵ�
	if (left_child->isLeaf) {
		parent->keys[index] = left_child->keys[left_child->size - 1];
	}
	else {
		parent->keys[index] = left_child->keys[left_child->size];
	}

	// �߰� ���� �� ��ġ�� ������ �����ʹ� ���ҵ� ������ ��带 ����Ų��
	// (���� �����ʹ� �̹� ������ ���� ��带 ����Ű�� �ִ�)
	parent->p_arr[index + 1] = right_child;
	// �θ� Ű ���� �߰��Ǿ����� ũ�⸦ 1 �����Ѵ�
	parent->size += 1;
	if (left_child->next != NULL) {
		left_child->next->prev = right_child;
		right_child->next = left_child->next;
	}
	else {
		if (right_child->isLeaf) {
			bpt->tail = right_child;
		}
	}
	left_child->next = right_child;
	right_child->prev = left_child;
}

bool bind_node(BPtree* bpt, node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];
	int left_size = left_child->size;
	int right_size = right_child->size;

	if(!left_child->isLeaf){
	// key�� ���� �ڽĿ��� �����ְ�
		left_child->keys[left_size] = parent->keys[index];

		// ������ �ڽ��� Ű ���� ���� �ڽ����� �ű��
		// ���⼭ ���� ��� ���� �ڽ����� �Ű����� ������ �ڽ��� ����ų �ʿ䰡 ��������
		for (int i = 0; i < right_size; i++) {
			left_child->keys[left_size + 1 + i] = right_child->keys[i];
		}
		for (int i = 0; i < right_size + 1; i++) {
			left_child->p_arr[left_size + 1 + i] = right_child->p_arr[i];
		}

		// ���� �ڽ��� Ű�� �þ�� ������ ũ�⸦ �������ش�
		left_child->size = left_size + 1 + right_size;
	}
	else {
		for (int i = 0; i < right_size; i++) {
			left_child->keys[left_size + i] = right_child->keys[i];
		}
		for (int i = 0; i < right_size; i++) {
			left_child->p_arr[left_size + i] = right_child->p_arr[i];
		}
		left_child->size = left_size + right_size;

		left_child->next = right_child->next;
		if (left_child->next != NULL) {
			left_child->next->prev = left_child;
		}
		else {
			bpt->tail = left_child;
		}
	}
	// �θ� ��忡�� ������ �ڽ��� ����Ű�� �����͸� ���ְ� �� ĭ�� ������ ����
	for (int i = index; i < parent->size - 1; i++) {
		parent->keys[i] = parent->keys[i + 1];
	}
	for (int i = index + 1; i < parent->size; i++) {
		parent->p_arr[i] = parent->p_arr[i + 1];
	}
	parent->size -= 1;

	// ������ ���� ����� ���� ���� ������ �޸𸮸� ��ȯ���ش�
	delete_node(right_child);

	// �θ��� ũ�Ⱑ 0 �̸�(��Ʈ�� ���� �߻�) 
	if (parent->size == 0) {
		free(bpt->root);
		bpt->root = left_child;
		return true;
	}
	return false;
}

void borrow_key_from_right(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];

	if (!left_child->isLeaf) {
		// ���� ����� ���� �θ� ����� ���� ��ġ ���� �����Ѵ�
		left_child->keys[left_child->size] = parent->keys[index];
		left_child->size += 1;

		// �θ� ����� Ű ���� ������ �ڽ��� �� ���� ���� �����´�
		parent->keys[index] = right_child->keys[0];
		left_child->p_arr[left_child->size] = right_child->p_arr[0];

		// ������ ����� ũ��� 1 �پ���
		right_child->size -= 1;

		// ������ ����� �� �տ��� �� Ű ���� ���ʷ� ä���ش�
		for (int i = 0; i < right_child->size; i++) {
			right_child->keys[i] = right_child->keys[i + 1];
		}
		for (int i = 0; i < right_child->size + 1; i++) {
			right_child->p_arr[i] = right_child->p_arr[i + 1];
		}
	}
	else {
		left_child->keys[left_child->size] = right_child->keys[0];
		left_child->p_arr[left_child->size] = right_child->p_arr[0];

		left_child->size += 1;

		parent->keys[index] = right_child->keys[0];

		// ������ ����� ũ��� 1 �پ���
		right_child->size -= 1;

		// ������ ����� �� �տ��� �� Ű ���� ���ʷ� ä���ش�
		for (int i = 0; i < right_child->size; i++) {
			right_child->keys[i] = right_child->keys[i + 1];
		}
		for (int i = 0; i < right_child->size + 1; i++) {
			right_child->p_arr[i] = right_child->p_arr[i + 1];
		}
	}
}

void borrow_key_from_left(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];

	for (int i = right_child->size; 0 < i; i--) {
		right_child->keys[i] = right_child->keys[i - 1];
	}

	if (!right_child->isLeaf) {
		// ������ ����� �� �տ� �����Ͱ� �� �ڸ��� ����� ���� ���� �� ĭ�� �ڷ� �ű��
		for (int i = right_child->size + 1; 0 < i; i--) {
			right_child->p_arr[i] = right_child->p_arr[i - 1];
		}

		// ������ ����� �� �տ� �θ� ����� ���� ��ġ ���� �����Ѵ�
		right_child->keys[0] = parent->keys[index];
		// ������ ����� ũ�⸦ 1 ���� ��Ų��
		right_child->size += 1;

		// �θ� ����� Ű ���� ���� �ڽ��� �� ���� �����´�
		parent->keys[index] = left_child->keys[left_child->size - 1];
		right_child->p_arr[0] = left_child->p_arr[left_child->size];
	}
	else {
		for (int i = right_child->size; 0 < i; i--) {
			right_child->p_arr[i] = right_child->p_arr[i - 1];
		}
		right_child->keys[0] = left_child->keys[left_child->size - 1];
		right_child->p_arr[0] = left_child->p_arr[left_child->size - 1];
		parent->keys[index] = left_child->keys[left_child->size - 2];
	}

	left_child->size -= 1;
}

void delete_node(node* cur) {
	free(cur);
}


// BPtree ���� �Լ�

BPtree* create_BPtree(void) {
	BPtree* t = (BPtree*)malloc(sizeof(BPtree));
	t->root = create_node();
	t->head = t->root;
	t->tail = t->root;
	t->root->isLeaf = true;
	t->root->size = 0;
	t->head->prev = NULL;
	t->head->next = NULL;
	return t;
}

void free_all_node(node* cur) {
	if (!cur->isLeaf) {
		for (int i = 0; i < cur->size + 1; i++) {
			free_all_node(cur->p_arr[i]);
		}
	}
	for (int i = 0; i < cur->size; i++) {
		free_all_node(cur->p_arr[i]);
	}
	delete_node(cur);
}

bool delete_BPtree(BPtree* bpt) {
	free_all_node(bpt->root);
	free(bpt);
	return true;
}

void print_by_dfs(node* cur, int cnt) {
	if (cur->isLeaf) {
		for (int i = 0; i < cnt; i++) {
			printf("--------------------|");
		}
		for (int i = 0; i < cur->size; i++) {
			printf("[%4d, %4d]", cur->keys[i], *(int*)cur->p_arr[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < cur->size; i++) {
			print_by_dfs(cur->p_arr[i], cnt + 1);
			for (int i = 0; i < cnt; i++) {
				printf("--------------------|");
			}
			printf("%4d            \n", cur->keys[i]);
		}
		print_by_dfs(cur->p_arr[cur->size], cnt + 1);
	}
}

void print_tree(node* cur, int cnt) {
	print_by_dfs(cur, cnt);
	printf("\n\n");
}

void print_data_ascending(node* cur) {
	while (cur->next != NULL) {
		for (int i = 0; i < cur->size; i++) {
			printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
		}
		cur = cur->next;
	}
	for (int i = 0; i < cur->size; i++) {
		printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
	}
	printf("\n\n");
}

void print_data_descending(node* cur) {
	while (cur->prev != NULL) {
		for (int i = cur->size - 1; 0 <= i; i--) {
			printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
		}
		cur = cur->prev;
	}
	for (int i = cur->size - 1; 0 <= i; i--) {
		printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
	}
	printf("\n\n");
}

bool search_key(BPtree* bpt, int key) {
	node* cur = bpt->root;
	int index = find_index(cur, key);
	while (!cur->isLeaf) {
		cur = cur->p_arr[index];
		index = find_index(cur, key);
	}
	if (index < cur->size && cur->keys[index] == key) {
		printf("\n----- [key \"%d\", data \"%d\"] exist in tree.  -----\n\n", key, *(cur->p_arr[index]));
		return true;
	}

	printf("\n----- key \"%d\" does not exist in tree. -----\n\n", key);
	return false;
}

bool insert_key_data(BPtree* bpt, int key, int* data) {
	node* cur = bpt->root;

	// ��Ʈ�� ũ�Ⱑ M�̶�� (��Ʈ ��尡 �� á�ٸ�)
	if (cur->size == M) {
		// �� ��带 �ϳ� �����Ѵ�
		node* new_root = create_node();
		// �� ��带 BPtree�� �� ��Ʈ�� �����Ѵ�
		bpt->root = new_root;
		// �� ��Ʈ�� ���� �ʱ�ȭ ���ְ� �������� �� �տ� ���� ��Ʈ �ּҸ� �����Ѵ�
		new_root->isLeaf = false;
		new_root->size = 0;
		new_root->p_arr[0] = cur;
		// �� ��Ʈ�� ������ �迭�� 0 ��°�� ������ ���� ��Ʈ ��带 �����Ѵ�
		split_node(bpt, new_root, 0);
		// ���� ��带 new_root�� �����Ѵ�
		cur = new_root;
	}

	// ���� ������ ������ ������忡 �ϱ� ������
	// ���� ������ ��������
	while (!cur->isLeaf) {
		// Ű ���� ���� ��忡 �ִ� ���� ���Ͽ� ������ �湮�ؾ��ϴ� ��� �ּҸ� ���Ѵ�
		int i = cur->size;
		while (i > 0 && key < cur->keys[i - 1]) {
			i--;
		}
		// ������ �湮�ؾ� �ϴ� ��尡 �� ��������
		if (cur->p_arr[i]->size == M) {
			// ������ �湮�� ��带 �����Ѵ�
			split_node(bpt, cur, i);
			// �����ϸ鼭 ���� ����� Ű �迭�� i��° ���� ����Ǵµ�
			// �� �� ����� ������ ������ Ű ���� ũ�� ���� ��带 �����Ѵ�  
			if (key > cur->keys[i]) {
				i++;
			}
		}
		// �湮 ��带 ���� ���� �����Ѵ�
		cur = cur->p_arr[i];
	}

	// ������忡 ������ �� Ű�� ����
	int i = cur->size;
	while (i > 0 && key < cur->keys[i - 1]) {
		cur->keys[i] = cur->keys[i - 1];
		cur->p_arr[i] = cur->p_arr[i - 1];
		i--;
	}
	cur->keys[i] = key;
	cur->p_arr[i] = (void*)data;
	cur->size += 1;

	return true;
}

bool delete_key(BPtree* bpt, int key) {
	node* cur = bpt->root;
	int index = 0;
	// �湮�� ��尡 ���� ��尡 �� �� ���� �ݺ����� �����Ѵ�
	while (!cur->isLeaf) {
		index = find_index(cur, key);
		// ������ �湮�� ����� ũ�Ⱑ T���� �۴ٸ�
		if (cur->p_arr[index]->size < T) {
			// ���� �湮�� ��尡 ���� �������� �ƴϸ�
			if (index < cur->size) {
				// ���� �湮�� ����� ������ ����� ũ�Ⱑ T���� ũ�ų� ������
				if (cur->p_arr[index + 1]->size >= T) {
					// ������ ��忡�� ������
					borrow_key_from_right(cur, index);
				}
				// ���� �湮�� ����� ����(������)����� ũ�⵵ T���� ������
				else {
					if (bind_node(bpt, cur, index)) {
						cur = bpt->root;
						continue;
					}
				}
			}
			// ���� �湮�� ��尡 ���� �������̸�
			else {
				// ���� �湮�� ����� ���� ����� ũ�Ⱑ T���� ũ�ų� ������
				if (cur->p_arr[index - 1]->size >= T) {
					// ���� ��忡�� ������
					borrow_key_from_left(cur, index - 1);
				}
				// ���� �湮�� ����� ���� ���� ����� ũ�⵵ T���� ������
				else {
					index -= 1;
					if (bind_node(bpt, cur, index)) {
						cur = bpt->root;
						continue;
					}
				}
			}
		}
		cur = cur->p_arr[index];
	}

	// ������忡 ������ �� Ű�� ������ ����
	index = find_index(cur, key);
	if (index < cur->size && cur->keys[index] == key) {
		for (int i = index; i < cur->size - 1; i++) {
			cur->keys[i] = cur->keys[i + 1];
			cur->p_arr[i] = cur->p_arr[i + 1];
		}
		cur->size -= 1;
	}
	else {
		return false;
	}
	return true;
}


// ���α׷� ���� ���� �Լ�

int get_key(char* action) {
	int key = 0;
	int cnt = 0;
	while (true) {
		printf("   %s�� Ű�� �Է��ϼ���      : ", action);
		scanf_s("%d", &key);
		cnt = 0;
		while (getchar() != '\n') {	// �Է� ���� ����
			cnt++;
		}
		if (cnt > 0) {	// �Է� ���ۿ� ���� ���� ���� �־��ٸ� �ٽ� �Է�
			system("cls");
			printf("   ���ڸ� ��Ȯ�ϰ� �Է����ּ���(���鵵 X)\n");
			continue;
		}
		break;
	}
	return key;
}

int* get_data(char* action) {
	int* data = (int*) malloc(sizeof(int));
	int cnt = 0;
	while (true) {
		printf("   %s�� �����͸� �Է��ϼ���      : ", action);
		scanf_s("%d", data);
		cnt = 0;
		while (getchar() != '\n') {	// �Է� ���� ����
			cnt++;
		}
		if (cnt > 0) {	// �Է� ���ۿ� ���� ���� ���� �־��ٸ� �ٽ� �Է�
			system("cls");
			printf("   ���ڸ� ��Ȯ�ϰ� �Է����ּ���(���鵵 X)\n");
			continue;
		}
		break;
	}
	return data;
}

int select_menu(void) {
	int menu = 0;
	char cnt = 0;	// �Է� ���� Ȯ���� ���� ����
	while (true) {
		cnt = 0;	// cnt �ʱ�ȭ
		system("cls");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------             B+Ʈ�� �����ϱ�            --------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------                                       --------\n");
		printf("   ---------             1. Ʈ�� ��ȸ              --------\n");
		printf("   ---------             2. Ű, ������ ��ȸ        --------\n");
		printf("   ---------             3. Ű, ������ ����        --------\n");
		printf("   ---------             4. Ű ����                --------\n");
		printf("   ---------             5. ������ ���� ��ȸ       --------\n");
		printf("   ---------             5. ������ ���� ��ȸ       --------\n");
		printf("   ---------             0. ���α׷� ����          --------\n");
		printf("   ---------                                       --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------<<           �޴� ���� :              >>-------");
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		// �޴� ���� �� �Է�
		scanf_s("%d", &menu);
		// �Է� ���� ����
		while (getchar() != '\n') {
			cnt++;
		}
		if (cnt > 0) {	// �Է� ���ۿ� ���� ���� �־��ٸ� 
			printf("       �޴��� �ش��ϴ� ���� �ϳ��� �Է��ϼ���(���鵵 X)\n");
			system("pause");
			continue;	// �ݺ��� �ٽ� ����
		}
		else break;		// �Է� ���ۿ� ���� ���� �������� break
	}
	return menu;		// �ݺ������� ����� �Է¹��� menu �� ��ȯ
}

void exit_program(void) {
	printf("   --------------------------------------------------------\n");
	printf("   -----------   ��� �� ���α׷��� �����մϴ�  -----------\n");
	printf("   --------------------------------------------------------\n");
}

void start_program() {
	BPtree* bpt = create_BPtree();
	test_insert_key_data(bpt);
	test_delete(bpt);
	int key = 0;
	int* data = NULL;
	while (true) {
		switch (select_menu()) {
			// �Է� ���� 1�� ��� ���� tree�� ����Ѵ�
		case 1:
			system("cls");
			printf(" [Ʈ���� ���� ����] \n");
			print_tree(bpt->root, 0);
			break;
			// �Է� ���� 2�� ��� �����͸� �޾Ƽ� Ʈ������ ��ȸ�Ѵ�
		case 2:
			system("cls");
			key = get_key("��ȸ");
			printf(" [Ʈ���� Ȯ��] \n");
			search_key(bpt, key);
			print_tree(bpt->root, 0);
			break;
			// �Է� ���� 3�� ��� �����͸� �޾Ƽ� Ʈ���� �����Ѵ�
		case 3:
			system("cls");
			key = get_key("����");
			data = get_data("����");
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bpt->root, 0);
			insert_key_data(bpt, key, data);
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bpt->root, 0);
			break;
			//�Է� ���� 4�� ��� �����͸� �޾Ƽ� Ʈ������ �����Ѵ�
		case 4:
			system("cls");
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bpt->root, 0);
			key = get_key("����");
			delete_key(bpt, key);
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bpt->root, 0);
			break;
			// �Է� ���� 5�� ��� ���ĵ� ������� �����͸� �����ش�
		case 5:
			system("cls");
			printf("\n [Ʈ�� ����] \n");
			print_tree(bpt->root, 0);
			print_data_ascending(bpt->head);
			break;
			// �Է� ���� 6�� ��� ���ĵ� ������� �����͸� �����ش�
		case 6:
			system("cls");
			printf("\n [Ʈ�� ����] \n");
			print_tree(bpt->root, 0);
			print_data_descending(bpt->tail);
			break;
		case 0:
			exit_program();
			delete_BPtree(bpt);
			Sleep(wait_time * 2);
			exit(1);		// ���α׷� ����
		default:	// �� �ܿ� �Է��� ��� ���� �޽��� ��� �ٽ� �޴� �Է�
			printf("       �޴��� �߸� �Է��ϼ̽��ϴ�\n");
		}
		system("pause");
	}
}