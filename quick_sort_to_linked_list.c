#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
  int value;
  void *next;
} Node;

void printNode(Node* node) {
  printf("{\n");
  printf("    value :%d\n", node->value);
  printf("    next  :%p\n", node->next);
  printf("}\n");
}

void printList(Node* node, bool asStruct) {
  while(node != NULL) {
      if (asStruct) {
          printNode(node);
      } else {
          printf("%d->", node->value);
      }
      node = node->next;
  }
  printf("\n");
}

Node* createNode(int value) {
  Node* newNode = malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

Node* addNode(Node* head, int value) {
  Node* newNode = createNode(value);
  if(head->next != NULL) {
     newNode->next = head->next;
  }
  head->next = newNode;
  return newNode;
}

Node* lastNode(Node* head) {
  //tira warning por que no manejo el NULL pero ta bonito así que no lo toco
  if(head->next == NULL) return head;
  lastNode(head->next);
}

Node* findElement(Node* start, int value) {
  Node* current = start;
  while(current != NULL){
      if(current->value == value) {
          return current;
      }
      current = current->next;
  }
  return NULL;
}

Node* findElementByReference(Node* start, Node* target) {
  Node *current = start;
  while(current != NULL){
      if(current == target) {
          return current;
      }
      current = current->next;
  }
  return NULL;
}

Node* appendNode(Node* node, int value){
  Node* newNode = createNode(value);
  while(node->next != NULL) {
      node = node->next;
  }

  node->next = newNode;
  return newNode;
}

void linkedListCollector(Node* head) {
  if(head->next == NULL) {
      free(head);
      return;
  }
    
  linkedListCollector(head->next);
  free(head);
}

bool deleteNode(Node* head, Node* node) {
  if(head->next == node) {
      head->next = node->next;
      free(node);
      return true;
  }
    
  deleteNode(head->next, node);
  return false;
}

int linkedListLength(Node* head) {
  Node* current = head;
  int count = 0;
    
  while(current != NULL) {
       printNode(current);
       current = current->next;
       count++;
   }

  return count;
}

void swap(Node* a, Node* b) {
  int temp = a->value;
  a->value = b->value;
  b->value = temp;
}

Node* partition(Node* start, Node* finish) {
  if(start == NULL || finish == NULL) return NULL;
  Node* min = start;
  Node* prev = start;

  while(start != finish) {
    if(start->value < finish->value) {
      swap(min, start);
      prev = min;
      min = min->next;
    }

    start = start->next;
  }

  swap(min, finish);
  return prev;
}

void quickSort(Node* start, Node* finish) {
  if(findElementByReference(finish, start)) return;
  Node* prev = partition(start, finish);

  if(prev == NULL) return;
  Node* pi = prev->next;

  quickSort(pi->next, finish);
  quickSort(start, prev);
}

int main() {
  Node* head = createNode(5);
  Node* node1 = addNode(head, 3);
  Node* node2 = appendNode(head, 7);
  Node* node3 = appendNode(head, 6);
  Node* node4 = appendNode(head, 8);
  Node* node5 = appendNode(head, 4);
  Node* node6 = appendNode(head, 9);
  Node* node7 = appendNode(head, 6);

  printList(head, false);
  quickSort(head, lastNode(head));
  printList(head, false);
  linkedListCollector(head);
  return 0;
}