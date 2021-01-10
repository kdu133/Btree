#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define wait_time 2000
#define T 3
#define M (T*2)-1


typedef struct node {				// ��� ����ü ����
	bool isLeaf;					// ��尡 �������� Ȯ��
	int size;						// ��忡 ����� Ű ����
	int keys[M];					// ��忡 ����� Ű �迭
	struct node* p_arr[M + 1];	// ��忡 ����� ������ �迭
} node;

typedef struct Btree {				// BƮ�� ����ü ����
	node* root;					// BƮ���� ��Ʈ �ּ�
} Btree;

typedef struct p_idx {
	int idx;
	node* ptr;
} p_idx;

// �׽�Ʈ �Լ�

void test_create();
void test_insert(Btree* bt);
void test_delete(Btree* bt);

// ��� ���� �Լ�

node* create_node(void);
int find_index(node* cur, int key);
void split_node(node* parent, int index);
bool bind_node(Btree* bt, node* parent, int index);
void borrow_key_from_right(node* parent, int index);
void borrow_key_from_left(node* parent, int index);
void delete_node(node*);

// Btree ���� �Լ�

Btree* create_Btree(void);
void free_all_node(node* cur);
bool delete_Btree(Btree* bt);
void print_by_dfs(node* cur, int cnt);
void print_tree(node* cur, int cnt);
bool search_key(Btree* bt, int key);
bool insert_key(Btree* bt, int key);
bool delete_key(Btree* bt, int key);

// ���α׷� ���� ���� �Լ�

int get_key(char* action);
int select_menu(void);
void exit_program(void);
void start_program();


// ���� �Լ�

int main(void) {
	Btree* bt = create_Btree();
	test_insert(bt);
	test_delete(bt);
	delete_Btree(bt);
	//start_program();
	return true;
}

// �׽�Ʈ �Լ�

void test_create() {
	Btree* t = (Btree*)malloc(sizeof(Btree));
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

void test_insert(Btree* bt) {
	insert_key(bt, 10);
	insert_key(bt, 11);
	insert_key(bt, 12);
	insert_key(bt, 13);
	insert_key(bt, 14);
	insert_key(bt, 22);
	insert_key(bt, 23);
	insert_key(bt, 4);
	insert_key(bt, 5);
	insert_key(bt, 6);
	insert_key(bt, 15);
	insert_key(bt, 21);
	insert_key(bt, 16);
	insert_key(bt, 17);
	insert_key(bt, 1);
	insert_key(bt, 33);
	insert_key(bt, 34);
	insert_key(bt, 7);
	insert_key(bt, 30);
	insert_key(bt, 31);
	insert_key(bt, 32);
	insert_key(bt, 9);
	insert_key(bt, 18);
	insert_key(bt, 19);
	insert_key(bt, 35);
	insert_key(bt, 36);
	insert_key(bt, 24);
	insert_key(bt, 25);
	insert_key(bt, 29);
	insert_key(bt, 2);
	insert_key(bt, 3);
	insert_key(bt, 8);
	insert_key(bt, 20);
	insert_key(bt, 26);
	insert_key(bt, 27);
	insert_key(bt, 28);
}

void test_delete(Btree* bt) {
	print_tree(bt->root, 0);
	delete_key(bt, 33);
	print_tree(bt->root, 0);
	delete_key(bt, 10);
	print_tree(bt->root, 0);
	delete_key(bt, 11);
	print_tree(bt->root, 0);
	delete_key(bt, 12);
	print_tree(bt->root, 0);
	delete_key(bt, 13);
	print_tree(bt->root, 0);
	delete_key(bt, 14);
	print_tree(bt->root, 0);
	delete_key(bt, 22);
	print_tree(bt->root, 0);
	delete_key(bt, 36);
	print_tree(bt->root, 0);
	delete_key(bt, 24);
	print_tree(bt->root, 0);
	delete_key(bt, 25);
	print_tree(bt->root, 0);
	delete_key(bt, 29);
	print_tree(bt->root, 0);
	delete_key(bt, 2);
	print_tree(bt->root, 0);
	delete_key(bt, 3);
	print_tree(bt->root, 0);
	delete_key(bt, 8);
	print_tree(bt->root, 0);
	delete_key(bt, 20);
	print_tree(bt->root, 0);
	delete_key(bt, 23);
	print_tree(bt->root, 0);
	delete_key(bt, 4);
	print_tree(bt->root, 0);
	delete_key(bt, 5);
	print_tree(bt->root, 0);
	delete_key(bt, 6);
	print_tree(bt->root, 0);
	delete_key(bt, 15);
	print_tree(bt->root, 0);
	delete_key(bt, 21);
	print_tree(bt->root, 0);
	delete_key(bt, 16);
	print_tree(bt->root, 0);
	delete_key(bt, 17);
	print_tree(bt->root, 0);
	delete_key(bt, 1);
	print_tree(bt->root, 0);
	delete_key(bt, 34);
	print_tree(bt->root, 0);
	delete_key(bt, 7);
	print_tree(bt->root, 0);
	delete_key(bt, 30);
	print_tree(bt->root, 0);
	delete_key(bt, 31);
	print_tree(bt->root, 0);
	delete_key(bt, 32);
	print_tree(bt->root, 0);
	delete_key(bt, 9);
	print_tree(bt->root, 0);
	delete_key(bt, 18);
	print_tree(bt->root, 0);
	delete_key(bt, 19);
	print_tree(bt->root, 0);
	delete_key(bt, 35);
	print_tree(bt->root, 0);
	delete_key(bt, 26);
	print_tree(bt->root, 0);
	delete_key(bt, 27);
	print_tree(bt->root, 0);
	delete_key(bt, 28);
	print_tree(bt->root, 0);
}


// ��� ���� �Լ�

node* create_node(void) {
	node* new_node = (node*)malloc(sizeof(node));
	return new_node;
}

int find_index(node* cur, int key) {
	int index = cur->size;
	while (0 < index && key <= cur->keys[index - 1]) {
		index--;
	}
	return index; 
}

void split_node(node* parent, int index) {
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

	// ���� ��尡 ������尡 �ƴ϶��
	if (!(left_child->isLeaf)) {
		// ���� �ڽ��� ������ �迭���� �߰��� �����ʿ� �ִ� ���� ������ ���� �ű��
		for (int i = 0; i <= T - 1; i++) {
			right_child->p_arr[i] = left_child->p_arr[i + T];
		}
	}

	// ���� ��忡�� ���� �����͸� �ű�� ���� �������� ũ�⸦ �����Ѵ�
	left_child->size = T - 1;

	// ������ ����� �߰� ���� �� �ڸ��� �����
	// �θ��� Ű �迭���� �ڽ� ��带 ����Ű�� ��ġ ���� ���� �� ĭ�� �ڷ� �ű��
	for (int i = parent->size; i > index; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}

	// �θ��� ������ �迭���� �ڽ� ��带 ����Ű�� ��ġ ���� ���� �� ĭ�� �ڷ� �ű�� 
	for (int i = parent->size + 1; i > index; i--) {
		parent->p_arr[i] = parent->p_arr[i - 1];
	}

	// ������ ����� Ű �迭�� �߰� ���� �θ� ��忡 �����Ѵ�
	parent->keys[index] = left_child->keys[T-1];
	// �߰� ���� �� ��ġ�� ������ �����ʹ� ���ҵ� ������ ��带 ����Ų��
	// (���� �����ʹ� �̹� ������ ���� ��带 ����Ű�� �ִ�)
	parent->p_arr[index + 1] = right_child;

	// �θ� Ű ���� �߰��Ǿ����� ũ�⸦ 1 �����Ѵ�
	parent->size += 1;
}

bool bind_node(Btree* bt, node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];
	int left_size = left_child->size;
	int right_size = right_child->size;

	// ���� �ڽ� + Ű + ������ �ڽ�

	// key�� ���� �ڽĿ��� �����ְ�
	left_child->keys[left_size] = parent->keys[index];

	// ������ �ڽ��� Ű ���� ���� �ڽ����� �ű��
	// ���⼭ ���� ��� ���� �ڽ����� �Ű����� ������ �ڽ��� ����ų �ʿ䰡 ��������
	for (int i = 0; i < right_size; i++) {
		left_child->keys[left_size + 1 + i] = right_child->keys[i];
	}
	if (!left_child->isLeaf) {
		for (int i = 0; i < right_size + 1; i++) {
			left_child->p_arr[left_size + 1 + i] = right_child->p_arr[i];
		}
	}

	// ���� �ڽ��� Ű�� �þ�� ������ ũ�⸦ �������ش�
	left_child->size = left_size + 1 + right_size;

	// �θ� ��忡�� ������ �ڽ��� ����Ű�� �����͸� ���ְ� �� ĭ�� ������ ����
	for (int i = index; i < parent->size - 1; i++) {
		parent->keys[i] = parent->keys[i + 1];
	}
	
	for (int i = index + 1; i < parent->size; i++) {
		parent->p_arr[i] = parent->p_arr[i + 1];
	}
	// �θ� ����� ũ�⵵ 1 �ٿ��ش�
	parent->size -= 1;

	// ������ ���� ����� ���� ���� ������ �޸𸮸� ��ȯ���ش�
	free(right_child);

	// �θ��� ũ�Ⱑ 0 �̸�(��Ʈ�� ���� �߻�) 
	if (parent->size == 0) {
		free(bt->root);
		bt->root = left_child;
		return true;
	}
	return false;
}

void borrow_key_from_right(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];

	// ���� ����� ���� �θ� ����� ���� ��ġ ���� �����Ѵ�
	left_child->keys[left_child->size] = parent->keys[index];
	// ���� ����� ũ�⸦ 1 ���� ��Ų��
	left_child->size += 1;

	// �θ� ����� Ű ���� ������ �ڽ��� �� ���� ���� �����´�
	parent->keys[index] = right_child->keys[0];

	// ���� ��尡 ������尡 �ƴϸ� ���� ����� ���� ������ ���� ������ �ڽ��� �� ���� ���� ����Ű�� ���� �����´�
	if (!left_child->isLeaf) {
		left_child->p_arr[left_child->size] = right_child->p_arr[0];
	}

	// ������ ����� ũ��� 1 �پ���
	right_child->size -= 1;

	// ������ ����� �� �տ��� �� Ű ���� ���ʷ� ä���ش�
	for (int i = 0; i < right_child->size; i++) {
		right_child->keys[i] = right_child->keys[i + 1];
	}
	// ������ ����� �� �տ��� �� ������ ���� ���ʷ� ä���ش�
	if (!right_child->isLeaf) {
		for (int i = 0; i < right_child->size + 1; i++) {
			right_child->p_arr[i] = right_child->p_arr[i + 1];
		}
	}
}

void borrow_key_from_left(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];

	// ������ ����� �� �տ� Ű�� �� �ڸ��� ����� ���� ���� �� ĭ�� �ڷ� �ű��
	for (int i = right_child->size; 0 < i; i--) {
		right_child->keys[i] = right_child->keys[i - 1];
	}

	if (!right_child->isLeaf) {
		// ������ ����� �� �տ� �����Ͱ� �� �ڸ��� ����� ���� ���� �� ĭ�� �ڷ� �ű��
		for (int i = right_child->size + 1; 0 < i; i--) {
			right_child->p_arr[i] = right_child->p_arr[i - 1];
		}
	}

	// ������ ����� �� �տ� �θ� ����� ���� ��ġ ���� �����Ѵ�
	right_child->keys[0] = parent->keys[index];
	// ������ ����� ũ�⸦ 1 ���� ��Ų��
	right_child->size += 1;

	// �θ� ����� Ű ���� ���� �ڽ��� �� ���� �����´�
	parent->keys[index] = left_child->keys[left_child->size-1];

	// ���� ����� ���� ������ ���� ������ �ڽ��� �� ���� ���� ����Ű�� ���� �����´�
	if (!left_child->isLeaf) {
		right_child->p_arr[0] = left_child->p_arr[left_child->size];
	}

	// ������ ����� ũ��� 1 �پ���
	left_child->size -= 1;
}

void delete_node(node* cur) {
	free(cur);
}


// Btree ���� �Լ�

Btree* create_Btree(void) {
	Btree* t = (Btree*) malloc(sizeof(Btree));
	t->root = create_node();
	t->root->isLeaf = true;
	t->root->size = 0;
	return t;
}

void free_all_node(node* cur) {
	if (!cur->isLeaf) {
		for (int i = 0; i < cur->size+1; i++) {
			free_all_node(cur->p_arr[i]);
		}
	}
	delete_node(cur);
}

bool delete_Btree(Btree* bt) {
	free_all_node(bt->root);
	free(bt);
	return true;
}

void print_by_dfs(node* cur, int cnt) {
	if (cur->isLeaf) {
		for (int i = 0; i < cnt; i++) {
			printf("--------------------|");
		}
		for (int i = 0; i < cur->size; i++) {
			printf("%4d", cur->keys[i]);
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

bool search_key(Btree* bt, int key) {
	node* cur = bt->root;
	int index = find_index(cur, key);
	while (index <= cur->size) {
		if (cur->keys[index] == key) {
			printf("\n----- key \"%d\" exist in tree.  -----\n\n", key);
			return true;
		}

		if (cur->isLeaf) break;

		cur = cur->p_arr[index];
		index = find_index(cur, key);
	}
	printf("\n----- key \"%d\" does not exist in tree. -----\n\n", key);
	return false;
}

bool insert_key(Btree* bt, int key) {
	node* cur = bt->root;

	// ��Ʈ�� ũ�Ⱑ M�̶�� (��Ʈ ��尡 �� á�ٸ�)
	if (cur->size == M) {
		// �� ��带 �ϳ� �����Ѵ�
		node* new_root = create_node();
		// �� ��带 Btree�� �� ��Ʈ�� �����Ѵ�
		bt->root = new_root;
		// �� ��Ʈ�� ���� �ʱ�ȭ ���ְ� �������� �� �տ� ���� ��Ʈ �ּҸ� �����Ѵ�
		new_root->isLeaf = false;
		new_root->size = 0;
		new_root->p_arr[0] = cur;
		// �� ��Ʈ�� ������ �迭�� 0 ��°�� ������ ���� ��Ʈ ��带 �����Ѵ�
		split_node(new_root, 0);
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
			split_node(cur, i);
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
		i--;
	}
	cur->keys[i] = key;
	cur->size += 1;

	return true;
}

bool delete_key(Btree* bt, int key) {
	node* cur = bt->root;
	int index = 0;
	// �湮�� ��尡 ���� ��尡 �� �� ���� �ݺ����� �����Ѵ�
	while (!cur->isLeaf) {
		index = find_index(cur, key);
		// �湮�� ����� Ű�� ������
		if (cur->keys[index] == key) {
			// ���� �湮�� ����� ũ�Ⱑ T���� ũ�ų� ������
			if (cur->p_arr[index]->size >= T) {
				// ���� ��忡�� key���� �����ϴ� ���� key �� ��ġ�� ����
				cur->keys[index] = cur->p_arr[index]->keys[cur->p_arr[index]->size-1];
				// Ű�� �����ϰ� ���� ������ ���
				key = cur->keys[index];
			}
			// ���� �湮�� ����� ũ�Ⱑ T���� ������ ���� �湮�� ����� ����(������) ����� ũ�Ⱑ T+1���� ũ�ų� ������
			else if (cur->p_arr[index + 1]->size >= T) {
				// ���� ��忡�� key ���� �����ϴ� ��(ù��° ��)�� key�� ��ġ�� ����
				cur->keys[index] = cur->p_arr[index + 1]->keys[0];
				// Ű�� �����ϰ�
				key = cur->keys[index];
				// ���� �湮�� ��带 ������ ���� ������ �� ���� ������ ���
				index += 1;
			}
			// ���� �湮�� ����� ����(������)����� ũ�⵵ T���� ������
			else {
				if (bind_node(bt, cur, index)) {
					cur = bt->root;
					continue;
				}
			}
		}
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
					if (bind_node(bt, cur, index)) {
						cur = bt->root;
						continue;
					}
				}
			}
			// ���� �湮�� ��尡 ���� �������̸�
			else {
				// ���� �湮�� ����� ���� ����� ũ�Ⱑ T���� ũ�ų� ������
				if (cur->p_arr[index-1]->size >= T) {
					// ���� ��忡�� ������
					borrow_key_from_left(cur, index-1);
				}
				// ���� �湮�� ����� ���� ���� ����� ũ�⵵ T���� ������
				else {
					index -= 1;
					if (bind_node(bt, cur, index)) {
						cur = bt->root;
						continue;
					}
				}
			}
		}
		cur = cur->p_arr[index];
	}

	// ������忡 ������ �� Ű�� ����
	index = find_index(cur, key);
	for (int i = index; i < cur->size - 1; i++) {
		cur->keys[i] = cur->keys[i + 1];
	}
	cur->size -= 1;

	// cur->size �� 0�� �Ǵ� ���, ��Ʈ���� ���� ��� ������ ��쿡 root�� free ������ ����

	return true;
}


// ���α׷� ���� ���� �Լ�

int get_key(char* action) {
	int key = 0;
	int cnt = 0;
	while (true) {
		printf("   %s�� �����͸� �Է��ϼ���      : ", action);
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
		printf("   --------             B Ʈ�� �����ϱ�            --------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------                                       --------\n");
		printf("   ---------             1. Ʈ�� ��ȸ              --------\n");
		printf("   ---------             2. ������ ��ȸ            --------\n");
		printf("   ---------             3. ������ ����            --------\n");
		printf("   ---------             4. ������ ����            --------\n");
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
	Btree* bt = create_Btree();
	test_insert(bt);
	int key = 0;
	while (true) {
		switch (select_menu()) {
			// �Է� ���� 1�� ��� ���� tree�� ����Ѵ�
		case 1:
			system("cls");
			printf(" [Ʈ���� ���� ����] \n");
			print_tree(bt->root, 0);
			break;
			// �Է� ���� 2�� ��� �����͸� �޾Ƽ� Ʈ������ ��ȸ�Ѵ�
		case 2:
			system("cls");
			key = get_key("��ȸ");
			printf(" [Ʈ���� Ȯ��] \n");
			search_key(bt, key);
			print_tree(bt->root, 0);
			break;
			// �Է� ���� 3�� ��� �����͸� �޾Ƽ� Ʈ���� �����Ѵ�
		case 3:
			system("cls");
			key = get_key("����");
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			insert_key(bt, key);
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			break;
			//�Է� ���� 4�� ��� �����͸� �޾Ƽ� Ʈ������ �����Ѵ�
		case 4:
			system("cls");
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			key = get_key("����");
			delete_key(bt, key);
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			break;
			//�Է� ���� 0�� ��� ���α׷��� �����Ѵ�
		case 0:
			exit_program();
			delete_Btree(bt);
			Sleep(wait_time * 2);
			exit(1);		// ���α׷� ����
		default:	// �� �ܿ� �Է��� ��� ���� �޽��� ��� �ٽ� �޴� �Է�
			printf("       �޴��� �߸� �Է��ϼ̽��ϴ�\n");
		}
		system("pause");
	}
}

