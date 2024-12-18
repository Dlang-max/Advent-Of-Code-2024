#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct QueueNode {
  long a;
  int n;

  struct QueueNode *prev;
  struct QueueNode *next;
}QueueNode;

typedef struct Queue {
  int size;
  QueueNode *head;
  QueueNode *tail;
}Queue;

Queue *queue_init();
void test_queue();
bool queue_empty(Queue *queue);
void queue_free(Queue *queue);
void queue_offer(Queue *queue, long num, int n);
QueueNode *queue_poll(Queue *queue);
void print_queue(Queue *queue);

void parse_program(long *parsedProgram, char *program);
bool build_program(long a, long b, long c, int n, long *program, int programLength);

int main() {  
  // Read in and parse program
  char *program = "2,4,1,1,7,5,0,3,4,3,1,6,5,5,3,0";
  int programLength = strlen(program);
  programLength = programLength - (programLength / 2);
  long parsedProgram[programLength];
  parse_program(parsedProgram, program);
  
  Queue *queue = queue_init();
  queue_offer(queue, 0, programLength - 1);

  bool foundA = false;
  while(!queue_empty(queue)) {
    QueueNode *pair = queue_poll(queue);
    long a = pair->a;
    int n = pair->n;
    
    for(int i = 0; i < 8; i++) {
      long new_a = (a << 3) | i;
      if(!build_program(new_a, 0, 0, n, parsedProgram, programLength)) {
        continue;
      }

      if(n == 0) {
        printf("A: %ld\n", new_a);
        foundA = true;
        break;
      }

      queue_offer(queue, new_a, n - 1);
    }
    
    free(pair);
    if(foundA) {
      break;
    }
  }

  queue_free(queue);
  return 0;
}

void parse_program(long *parsedProgram, char *program) {
  for(int i = 0; i < strlen(program); i+=2) {
    parsedProgram[i / 2] = (program[i] - '0');
  }
}


bool build_program(long a, long b, long c, int n, long *program, int programLength) {  
  int outIndex = n;
  for(int i = 0; i < programLength;) {    
    int opcode = program[i];
    // Get the value of the operand
    int operand = program[i + 1];
    
    long operandValue = -1;
    if(operand >= 0 && operand <= 3) {
      operandValue = operand;
    } else if (operand == 4) {
      operandValue = a;
    } else if (operand == 5) {
      operandValue = b;
    } else {
      operandValue = c;
    }

    switch (opcode) {
    case 0:
      a = a >> operandValue;
      i+=2;
      break;
      
    case 1:
      b ^= operand;
      i+=2;
      break;
      
    case 2:
      b = operandValue % 8;
      i+=2;
      break;
      
    case 3:
      if(a == 0) {
        i += 2;
      } else {
         i = operandValue;
      }
      break;
      
    case 4:
      b = b ^ c;
      i+=2;
      break;
      
    case 5:
      long printedValue = operandValue % 8;
      if(printedValue != program[outIndex]) {
        return false;
      }
      
      outIndex++;
      i+=2;
      break;
      
    case 6:
      b = a >> operandValue;
      i+=2;
      break;
      
    case 7:
      c = a >> operandValue;
      i+=2;
      break;
      
    default:
      break;
    }
  }

  return outIndex == programLength;
}

void test_queue() {
  Queue *queue = queue_init();

  queue_offer(queue, 100, 3);
  queue_offer(queue, 324, 324);
  print_queue(queue);

  queue_poll(queue);
  print_queue(queue);

  queue_poll(queue);
  print_queue(queue);

  queue_offer(queue, 324, 324);
  print_queue(queue);
  
  queue_free(queue);
  
}

// Queue Methods
Queue *queue_init() {

  QueueNode *head = calloc(1, sizeof(QueueNode)) ;
  head->a = -1;
  head->n = -1;
  head->prev = NULL;
  
  QueueNode *tail = calloc(1, sizeof(QueueNode)) ;
  tail->a = -1;
  tail->n = -1;
  tail->prev = head;
  tail->next = NULL;
  head->next = tail;

  
  Queue *queue = calloc(1, sizeof(Queue));
  queue->size = 0;
  queue->tail = tail;
  queue->head = head;
}


bool queue_empty(Queue *queue) {
  return queue->size == 0;
}

void queue_free(Queue *queue) {
  QueueNode *curr = queue->head->next;
  while(curr != queue->tail) {
    QueueNode *temp = curr;
    curr = curr->next;
    free(temp);
  }

  free(queue->tail);
  free(queue->head);
  free(queue);
}

void queue_offer(Queue *queue, long num, int n) {
  QueueNode *newNode = calloc(1, sizeof(QueueNode));
  newNode->a = num;
  newNode->n = n;

  // head <---> node <---> tail
  newNode->prev = queue->tail->prev;
  newNode->next = queue->tail;

  queue->tail->prev->next = newNode;
  queue->tail->prev = newNode;
  queue->size++;
  
}

QueueNode *queue_poll(Queue *queue) {
  QueueNode *polledNode = queue->head->next;
  queue->head->next = polledNode->next;
  polledNode->next->prev = queue->head;
  queue->size--;
  
  return polledNode;
}

void print_queue(Queue *queue) {
  if(queue_empty(queue)) {
    return;
  }
  QueueNode *curr = queue->head->next;
  while(curr != queue->tail) {
    printf("(%ld, %d) ", curr->a, curr->n);
    curr = curr->next;
  }
  printf("\n");
}
