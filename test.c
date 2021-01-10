#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define wait_time 2000
#define T 3
#define M (T*2)-1


typedef struct node {				// 노드 구조체 정의
	bool isLeaf;					// 노드가 리프인지 확인
	int size;						// 노드에 저장된 키 개수
	int keys[M];					// 노드에 저장된 키 배열
	struct node* p_arr[M + 1];	// 노드에 저장된 포인터 배열
} node;

typedef struct Btree {				// B트리 구조체 정의
	node* root;					// B트리의 루트 주소
} Btree;

typedef struct p_idx {
	int idx;
	node* ptr;
} p_idx;

// 테스트 함수
void test_code();
void test_insert(Btree* bt);
void test_delete(Btree* bt);

// 노드 관련 함수

node* create_node(void);
int find_index(node* cur, int key);
void split_node(node* parent, int index);
void bind_node(node* parent, int index);
void borrow_key(node* parent, int index);
void delete_node(node*);

// Btree 관련 함수

Btree* create_Btree(void);
void free_all_node(node* cur);
bool delete_Btree(Btree* bt);
void dfs(node* cur, int cnt);
void print_tree(node* cur, int cnt);
bool search_key(Btree* bt, int key);
bool insert_key(Btree* bt, int key);
bool delete_key(Btree* bt, int key);


// 프로그램 실행 관련 함수

int get_key(char* action);
int select_menu(void);
void exit_program(void);
void start_program();



int main(void) {
	start_program();
	return true;
}


// 테스트 함수

void test_code() {
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
	delete_key(bt, 33);
	//delete_key(bt, 10);
	//delete_key(bt, 11);
	//delete_key(bt, 12);
	//delete_key(bt, 13);
	//delete_key(bt, 14);
	//delete_key(bt, 22);
	//delete_key(bt, 36);
	//delete_key(bt, 24);
	//delete_key(bt, 25);
	//delete_key(bt, 29);
	//delete_key(bt, 2);
	//delete_key(bt, 3);
	//delete_key(bt, 8);
	//delete_key(bt, 20);
	//delete_key(bt, 23);
	//delete_key(bt, 4);
	//delete_key(bt, 5);
	//delete_key(bt, 6);
	//delete_key(bt, 15);
	//delete_key(bt, 21);
	//delete_key(bt, 16);
	//delete_key(bt, 17);
	//delete_key(bt, 1);
	//delete_key(bt, 34);
	//delete_key(bt, 7);
	//delete_key(bt, 30);
	//delete_key(bt, 31);
	//delete_key(bt, 32);
	//delete_key(bt, 9);
	//delete_key(bt, 18);
	//delete_key(bt, 19);
	//delete_key(bt, 35);
	//delete_key(bt, 26);
	//delete_key(bt, 27);
	//delete_key(bt, 28);
}


// 노드 관련 함수

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
	// 오른쪽 자식이 될 노드를 생성한다
	node* right_child = create_node();
	// 현재 노드는 왼쪽 자식이 된다
	node* left_child = parent->p_arr[index];

	// 오른쪽 자식의 리프노드 여부는 왼쪽 자식의 값과 동일하다
	right_child->isLeaf = left_child->isLeaf;

	// 오른쪽 자식의 크기는 M/2 or T-1 이 되고
	right_child->size = T - 1;

	// 왼쪽 자식의 키 배열에서 중간값 오른쪽에 있는 값을 오른쪽 노드로 옮긴다
	for (int i = 0; i < T - 1; i++) {
		right_child->keys[i] = left_child->keys[i + T];
	}

	// 왼쪽 노드가 리프노드가 아니라면
	if (!(left_child->isLeaf)) {
		// 왼쪽 자식의 포인터 배열에서 중간값 오른쪽에 있는 값을 오른쪽 노드로 옮긴다
		for (int i = 0; i <= T - 1; i++) {
			right_child->p_arr[i] = left_child->p_arr[i + T];
		}
	}

	// 왼쪽 노드에서 값과 포인터를 옮기고 남은 공간으로 크기를 조정한다
	left_child->size = T - 1;

	// 분할한 노드의 중간 값이 들어갈 자리를 만든다
	// 부모의 키 배열에서 자식 노드를 가리키던 위치 뒤의 값을 한 칸씩 뒤로 옮긴다
	for (int i = parent->size; i > index; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}

	// 부모의 포인터 배열에서 자식 노드를 가리키던 위치 뒤의 값을 한 칸씩 뒤로 옮긴다 
	for (int i = parent->size + 1; i > index; i--) {
		parent->p_arr[i] = parent->p_arr[i - 1];
	}

	// 분할한 노드의 키 배열의 중간 값을 부모 노드에 저장한다
	parent->keys[index] = left_child->keys[T-1];
	// 중간 값이 들어간 위치의 오른쪽 포인터는 분할된 오른쪽 노드를 가리킨다
	// (왼쪽 포인터는 이미 분할한 왼쪽 노드를 가리키고 있다)
	parent->p_arr[index + 1] = right_child;

	// 부모에 키 값이 추가되었으니 크기를 1 증가한다
	parent->size += 1;
}

void bind_node(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];
	int left_size = left_child->size;
	int right_size = right_child->size;

	// 왼쪽 자식 + 키 + 오른쪽 자식

	// key를 왼쪽 자식에게 내려주고
	left_child->keys[left_size] = parent->keys[index];

	// 오른쪽 자식의 키 값을 왼쪽 자식으로 옮긴다
	// 여기서 값이 모두 왼쪽 자식으로 옮겨지고 오른쪽 자식은 가리킬 필요가 없어진다
	for (int i = 0; i < right_size; i++) {
		left_child->keys[left_size + 1 + i] = right_child->keys[i];
	}

	for (int i = 0; i < right_size + 1; i++) {
		left_child->p_arr[left_size + 1 + i] = right_child->p_arr[i];
	}

	// 왼쪽 자식의 키가 늘어났기 때문에 크기를 조정해준다
	left_child->size = left_size + 1 + right_size;

	// 부모 노드에서 오른쪽 자식을 가리키던 포인터를 없애고 한 칸씩 앞으로 당긴다
	for (int i = index; i < parent->size - 1; i++) {
		parent->keys[i] = parent->keys[i + 1];
	}
	for (int i = index + 1; i < parent->size; i++) {
		parent->p_arr[i] = parent->p_arr[i + 1];
	}
	// 부모 노드의 크기도 1 줄여준다
	parent->size -= 1;

	// 오른쪽 노드는 저장된 값이 없기 때문에 메모리를 반환해준다
	free(right_child);
}

void borrow_key(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];
	int left_size = left_child->size;
	int right_size = right_child->size;

	// 왼쪽 노드의 끝에 부모 노드의 현재 위치 값을 저장한다
	left_child->keys[T-1] = parent->keys[index];
	// 왼쪽 노드의 크기를 1 증가 시킨다
	left_child->size += 1;
	// 부모 노드의 키 값은 오른쪽 자식의 맨 앞의 값을 가져온다
	parent->keys[index] = right_child->keys[0];
	// 왼쪽 노드의 제일 오른쪽 값은 오른쪽 자식의 맨 앞의 값이 가리키던 값을 가져온다
	left_child->p_arr[T] = right_child->p_arr[0];
	// 왼쪽 노드의 크기는 T가 되고
	left_child->size = T;
	// 오른쪽 노드의 크기는 1 줄어든다
	right_child->size -= 1;
	// 오른쪽 노드의 맨 앞에서 뺀 키 값을 차례로 채워준다
	for (int i = 0; i < right_child->size - 1; i++) {
		right_child->keys[i] = right_child->keys[i + 1];
	}
}

void delete_node(node* cur) {
	free(cur);
}


// Btree 관련 함수

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

void dfs(node* cur, int cnt) {
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
			if (!cur->isLeaf) {
				dfs(cur->p_arr[i], cnt + 1);
			}
			for (int i = 0; i < cnt; i++) {
				printf("--------------------|");
			}
			printf("%4d            \n", cur->keys[i]);
		}
		dfs(cur->p_arr[cur->size], cnt + 1);
	}
}

void print_tree(node* cur, int cnt) {
	dfs(cur, cnt);
	printf("\n");
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

	// 루트의 크기가 M이라면 (루트 노드가 꽉 찼다면)
	if (cur->size == M) {
		// 새 노드를 하나 생성한다
		node* new_root = create_node();
		// 새 노드를 Btree의 새 루트로 저장한다
		bt->root = new_root;
		// 새 루트의 값을 초기화 해주고 포인터의 맨 앞에 이전 루트 주소를 저장한다
		new_root->isLeaf = false;
		new_root->size = 0;
		new_root->p_arr[0] = cur;
		// 새 루트의 포인터 배열의 0 번째로 저장한 이전 루트 노드를 분할한다
		split_node(new_root, 0);
		// 현재 노드를 new_root로 갱신한다
		cur = new_root;
	}

	// 값의 삽입은 무조건 리프노드에 하기 때문에
	// 리프 노드까지 내려간다
	while (!cur->isLeaf) {
		// 키 값과 현재 노드에 있는 값을 비교하여 다음에 방문해야하는 노드 주소를 구한다
		int i = cur->size;
		while (i > 0 && key < cur->keys[i - 1]) {
			i--;
		}
		// 다음에 방문해야 하는 노드가 꽉 차있으면
		if (cur->p_arr[i]->size == M) {
			// 다음에 방문할 노드를 분할한다
			split_node(cur, i);
			// 분할하면서 현재 노드의 키 배열의 i번째 값이 변경되는데
			// 이 때 변경된 값보다 삽입할 키 값이 크면 다음 노드를 변경한다  
			if (key > cur->keys[i]) {
				i++;
			}
		}
		// 방문 노드를 다음 노드로 변경한다
		cur = cur->p_arr[i];
	}

	// 리프노드에 도착한 후 키를 삽입
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
	// 방문한 노드가 리프 노드가 될 때 까지 반복문을 수행한다
	while (!cur->isLeaf) {
		index = find_index(cur, key);
		// 방문한 노드의 키가 있으면
		if (cur->keys[index] == key) {
			// 다음 방문할 노드의 크기가 T보다 크거나 같으면
			if (cur->p_arr[index]->size >= T) {
				// 다음 노드에서 key보다 선행하는 값을 key 값 위치에 저장
				cur->keys[index] = cur->p_arr[index]->keys[find_index(cur->p_arr[index], key)];
				// 키를 갱신하고 삭제 과정을 계속
				key = cur->keys[index];
			}
			// 다음 방문할 노드의 크기가 T보다 작지만 다음 방문할 노드의 형제(오른쪽) 노드의 크기가 T+1보다 크거나 같으면
			else if (cur->p_arr[index + 1]->size >= T) {
				// 형제 노드에서 key 보다 후행하는 값(첫번째 값)을 key값 위치에 저장
				cur->keys[index] = cur->p_arr[index + 1]->keys[0];
				// 키를 갱신하고
				key = cur->keys[index];
				// 다음 방문할 노드를 오른쪽 노드로 변경한 뒤 삭제 과정을 계속
				index += 1;
			}
			// 다음 방문할 노드의 형제(오른쪽)노드의 크기도 T보다 작으면
			else {
				bind_node(cur, index);
			}
		}
		// 다음에 방문할 노드의 크기가 T보다 작다면
		if (cur->p_arr[index]->size < T) {
			// 다음 방문할 노드의 형제(오른쪽)노드의 크기가 T보다 크거나 같으면
			if (cur->p_arr[index + 1]->size >= T) {
				// 왼쪽 오른쪽 구분해서 만들것
				borrow_key(cur, index);
			}
			// 다음 방문할 노드의 형제(오른쪽)노드의 크기도 T보다 작으면
			else {
				bind_node(cur, index);
			}
		}
		cur = cur->p_arr[index];
	}

	// 리프노드에 도착한 후 키를 삭제

	for (int i = index; i < cur->size; i++) {
		cur->keys[i] = cur->keys[i + 1];
	}
	cur->size -= 1;

	// cur->size 가 0이 되는 경우, 루트까지 값이 모두 삭제된 경우에 root를 free 해줄지 결정

	return true;
}


// 프로그램 실행 관련 함수

int get_key(char* action) {
	int key = 0;
	int cnt = 0;
	while (true) {
		printf("   %s할 데이터를 입력하세요      : ", action);
		scanf_s("%d", &key);
		cnt = 0;
		while (getchar() != '\n') {	// 입력 버퍼 비우기
			cnt++;
		}
		if (cnt > 0) {	// 입력 버퍼에 남은 값이 남아 있었다면 다시 입력
			system("cls");
			printf("   숫자를 정확하게 입력해주세요(공백도 X)\n");
			continue;
		}
		break;
	}
	return key;
}

int select_menu(void) {
	int menu = 0;
	char cnt = 0;	// 입력 버퍼 확인을 위한 변수
	while (true) {
		cnt = 0;	// cnt 초기화
		system("cls");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------             B 트리 구현하기            --------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------                                       --------\n");
		printf("   ---------             1. 트리 조회              --------\n");
		printf("   ---------             2. 데이터 조회            --------\n");
		printf("   ---------             3. 데이터 삽입            --------\n");
		printf("   ---------             4. 데이터 삭제            --------\n");
		printf("   ---------             0. 프로그램 종료          --------\n");
		printf("   ---------                                       --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------<<           메뉴 선택 :              >>-------");
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		// 메뉴 선택 값 입력
		scanf_s("%d", &menu);
		// 입력 버퍼 비우기
		while (getchar() != '\n') {
			cnt++;
		}
		if (cnt > 0) {	// 입력 버퍼에 남은 값이 있었다면 
			printf("       메뉴에 해당하는 숫자 하나만 입력하세요(공백도 X)\n");
			system("pause");
			continue;	// 반복문 다시 시작
		}
		else break;		// 입력 버퍼에 남은 값이 없었으면 break
	}
	return menu;		// 반복문에서 벗어나면 입력받은 menu 값 반환
}

void exit_program(void) {
	printf("   --------------------------------------------------------\n");
	printf("   -----------   잠시 후 프로그램을 종료합니다  -----------\n");
	printf("   --------------------------------------------------------\n");
}

void start_program() {
	Btree* bt = create_Btree();
	test_insert(bt);
	int key = 0;
	while (true) {
		switch (select_menu()) {
			// 입력 값이 1인 경우 현재 tree를 출력한다
		case 1:
			system("cls");
			printf(" [트리의 현재 상태] \n");
			print_tree(bt->root, 0);
			break;
			// 입력 값이 2인 경우 데이터를 받아서 트리에서 조회한다
		case 2:
			system("cls");
			key = get_key("조회");
			printf(" [트리의 확인] \n");
			search_key(bt, key);
			print_tree(bt->root, 0);
			break;
			// 입력 값이 3인 경우 데이터를 받아서 트리에 삽입한다
		case 3:
			system("cls");
			key = get_key("삽입");
			printf("\n [삽입 전 트리] \n");
			print_tree(bt->root, 0);
			insert_key(bt, key);
			printf("\n [삽입 후 트리] \n");
			print_tree(bt->root, 0);
			break;
			//입력 값이 4인 경우 데이터를 받아서 트리에서 삭제한다
		case 4:
			system("cls");
			printf("\n [삭제 전 트리] \n");
			print_tree(bt->root, 0);
			key = get_key("삭제");
			delete_key(bt, key);
			printf("\n [삭제 후 트리] \n");
			print_tree(bt->root, 0);
			break;
			//입력 값이 0인 경우 프로그램을 종료한다
		case 0:
			exit_program();
			delete_Btree(bt);
			Sleep(wait_time * 2);
			exit(1);		// 프로그램 종료
		default:	// 그 외에 입력인 경우 에러 메시지 출력 다시 메뉴 입력
			printf("       메뉴를 잘못 입력하셨습니다\n");
		}
		system("pause");
	}
}

