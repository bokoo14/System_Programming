/*
* 다음과 같이 구조체를 선언해서 프로그램 작성
   struct CalculatorNode {
         int a;
         int b;
         char name[20];
         int (*fptr) (int, int);
         struct CalculatorNode * next;
   };
* Linked List로 다음의 기능을 구현
  - 계산 노드 생성 (add/sub/multiply/divide) 
  - 현재까지 생성된 계산 노드 출력
  - 현재까지 생성된 계산 노드들의 계산 결과를 출력
  - 전체 삭제
  - 프로그램 종료
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CalculatorNode {
  int a;
  int b;
  char name[20];
  int (*fptr)(int, int); //함수 포인터
  struct CalculatorNode *next;
};

int addFunction(int m, int n) { return m + n; }
int subFunction(int m, int n) { return m - n; }
int multiFunction(int m, int n) { return m * n; }
int divideFunction(int m, int n) { return m / n; }

struct CalculatorNode* createNode (int a, int b, char name[], int (*fptr)(int, int))
{
  struct CalculatorNode *ptr;
  ptr = (struct CalculatorNode*) malloc (sizeof(struct CalculatorNode)); // 동적 메모리 할당
  ptr->a=a;
  ptr->b=b;
  strcpy (ptr->name, name);
  ptr->fptr=fptr; // 함수 포인터
  ptr->next = NULL;

  return ptr;
}

void printData (struct CalculatorNode *first)
{
  while (first != NULL) {
    printf ("%d %d %s %p \n", first->a, first->b, first->name, first->fptr);
    first = first->next;
  }
}

void insertData (struct CalculatorNode** first, int a, int b, char name[], int (*fptr)(int, int))
{
  struct CalculatorNode *ptr; 
  ptr = createNode (a, b, name, fptr);

  ptr->next = *first;
  *first = ptr;
}

void removeData(struct CalculatorNode *first) 
{
  struct CalculatorNode *curr = first->next;      
  while (curr != NULL){
    struct CalculatorNode *next = curr->next; 
    free(curr);
    curr = next;
  }
  free(first);
}

int main() {
  printf("계산 노드 생성(add/sub/multiply/divide)\n");
  printf("노드 4개 생성 중..\n");
  struct CalculatorNode * addNode = createNode(10,10,"add", addFunction);
  struct CalculatorNode * subNode = createNode(10,10,"sub", subFunction);
  struct CalculatorNode * multiNode = createNode(10,10,"multi", multiFunction);
  struct CalculatorNode * divideNode = createNode(10,10,"divide", divideFunction);
  
  addNode->next=subNode;
  subNode->next=multiNode;
  multiNode->next=divideNode;
  printf("노드 4개 생성 후 연결!\n");
  printf("---------------------------------------\n\n");

  printf("현재까지 생성된 계산 노드(add/sub/multiply/divide) 출력\n");
  printData (addNode);
  printf("---------------------------------------\n\n");

  printf("현재까지 생성된 계산 노드들의 계산 결과 출력\n");
  int addResult=(addNode->fptr)(addNode->a, addNode->b);
  int subResult=(subNode->fptr)(subNode->a, subNode->b);
  int multiResult=(multiNode->fptr)(multiNode->a, multiNode->b);
  int divideResult=(divideNode->fptr)(divideNode->a, divideNode->b);
  printf("add: %d \nsub: %d\nmulti: %d\ndivide: %d\n", addResult, subResult, multiResult, divideResult);
  printf("---------------------------------------\n\n");

  printf("전체 삭제\n");
  removeData(addNode);
  printData (addNode);
  printf("---------------------------------------\n\n");

  printf("프로그램 종료\n");
  exit(0);
  
  return 0;
}
