#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100

void int base(int stack[], int level, int BP);

typedef struct IR{
  int opcode;
  int l;
  int m;
}IR;

int main(void) {

int SP = -1;
int BP = 0;
int PC = 0;
int IR = null;

IR *instruction = malloc(sizeof(IR));

FILE *ifp = fopen ("input.txt", "r");


while(!feof(ifp){
  fscanf(ifp, %d, %d, %d, &instruction->opcode, &instruction->l, &instruction->m);
  
  switch(instruction->opcode){
  //LIT
  case 1:
    *sp += 1;
    stack [sp] = instruction->m;
    break;
  case 2: //OPR
  
  case 3: //LOD
    *sp += 1;
    stack[sp] = stack[base(stack, l, bp) + m];
    break;
  case 4: //STO
    stack[base(stack, l, bp) + m] = stack[sp];
    sp -= 1; 
    break;
  case 5: //CAL
    stack[sp += 1] = base(stack, l, bp);
    stack[sp += 2] = bp;
    stack[sp += 3] = pc;
    stack[sp += 4] = stack[sp];
    bp = sp += 1;
    pc = m;
    break;
  case 6: //INC
    sp = sp + m;
    break;
  case 7: //JMP
    pc = M;
  case 8: //JPC
    if(stack[sp] == 0){
      pc = m;
    }
    sp -= 1;
  case 9: //SYS
    printf("%d", stack [sp]);
    sp -= 1;
    
    sp += 1;
    scanf("%d", stack[sp]);
    break;  
}

fclose(ifp);
return 0;

void int base(int stack[], int level, int BP) {
  int base = BP;
  int counter = level;
  while (counter > 0)
  {
    base = stack[base];
    counter--;
} 
return base;


}
