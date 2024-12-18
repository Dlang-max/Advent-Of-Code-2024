#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void parse_program_str(int *parsedProgram, char *program);
void parse_program(int a, int b, int c, int *program, int programLength);

int main() {
  // Initial value of register a
  int a = 18427963;
  // Program
  char *program = "2,4,1,1,7,5,0,3,4,3,1,6,5,5,3,0";
  int programLength = strlen(program);
  programLength = programLength - (programLength / 2);
  int parsedProgram[programLength];
  parse_program_str(parsedProgram, program);

  parse_program(a, 0, 0, parsedProgram, programLength);
  return 0;
}


void parse_program_str(int *parsedProgram, char *program) {
  for(int i = 0; i < strlen(program); i+=2) {
    parsedProgram[i / 2] = (program[i] - '0');
  }
}

void parse_program(int a, int b, int c, int *program, int programLength) {  
  for(int i = 0; i < programLength;) {    
    int opcode = program[i];
    // Get the value of the operand
    int operand = program[i + 1];
    
    int operandValue = -1;
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
      printf("%d,", operandValue % 8);
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
  printf("\n");
}
