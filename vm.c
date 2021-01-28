#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100

int base(int stack[], int level, int BP);

typedef struct instruction
{
	int opcode;
	int l;
	int m;
} instruction;

int main(int argc, char *argv[])
{
	// Initialize variables.
	int i;
	int halt = 1;
	int SP = -1;
	int BP = 0;
	int PC = 0;
	instruction IR;
	char *str;


	// Initialize the arrays to their correct size.
	int *stack = malloc(sizeof(int) * MAX_STACK_HEIGHT);
	instruction *text = malloc(sizeof(instruction) * MAX_CODE_LENGTH);

	// Open the .txt file given the input from the command line.
	FILE *ifp = fopen (argv[1], "r");

	// Loop through the .txt file and place each sequence in the struct array.
	for (i = 0; !feof(ifp); i++)
		fscanf(ifp, "%d %d %d", &text[i].opcode, &text[i].l, &text[i].m);

	for(i = 0; i < MAX_CODE_LENGTH - 1; i++)
		printf("%d %d %d\n", text[i].opcode, text[i].l, text[i].m);
	
	for (i = 0; i < 50; i++)
		if (&text[i] == NULL)
		{
			printf("ERROR AT INDEX %d\n", i);

		}

	// Print initial values.
	printf("				PC 	BP 	SP 	stack\n");
	printf("Initial values:	0	0	-1\n");

	// Loop through and execute each IR until the halt is called.
	while(halt == 1)
	{
		// Set the IR to the correct IR in the struct array
		// and increment PC.
		IR = text[PC];
		PC += 1;

		// Use a switch statement to
  		switch(IR.opcode)
  		{
  			//LIT
 			case 1:
				SP += 1;
    			stack[SP] = IR.m;
    			break;
			case 2: //OPR
				switch (IR.m)
				{
					// RET
					case 0:
						stack[BP - 1] = stack[SP];
						SP = BP - 1;
						BP = stack[SP + 2];
						PC = stack[SP + 3];
						break;
					// NEG
					case 1:
						stack[SP] *= - 1;
						break;
					// ADD
					case 2:
						SP -= 1;
						stack[SP] += stack[SP + 1];
						break;
					// SUB
					case 3:
						SP -= 1;
						stack[SP] -= stack[SP + 1];
						break;
					// MUL
					case 4:
						SP -= 1;
						stack[SP] *= stack[SP + 1];
						break;
					// DIV
					case 5:
						SP -= 1;
						stack[SP] /= stack[SP + 1];
						break;
					// ODD
					case 6:
						stack[SP] %= 2;
						break;
					// MOD
					case 7:
						SP =- 1;
						stack[SP] %= stack[SP + 1];
					// EQL
					case 8:
						SP -= 1;
						stack[SP] = (stack[SP] == stack[SP + 1]) ? 1 : 0;
					// NEQ
					case 9:
						SP -= 1;
						stack[SP] = (stack[SP] != stack[SP + 1]) ? 1 : 0;
					// LSS
					case 10:
						SP -= 1;
						stack[SP] = (stack[SP] < stack[SP + 1]) ? 1 : 0;
					// LEQ
					case 11:
						SP -= 1;
						stack[SP] = (stack[SP] <= stack[SP + 1]) ? 1 : 0;
					// GTR
					case 12:
						SP -= 1;
						stack[SP] = (stack[SP] > stack[SP + 1]) ? 1 : 0;
					// GEQ
					case 13:
						SP -= 1;
						stack[SP] = (stack[SP] >= stack[SP + 1]) ? 1 : 0;
				}
			case 3: //LOD
				SP += 1;
				stack[SP] = stack[base(stack, IR.l, BP) + IR.m];
				break;
			case 4: //STO
				stack[base(stack, IR.l, BP) + IR.m] = stack[SP];
				SP -= 1; 
				break;
			case 5: //CAL
				stack[SP += 1] = base(stack, IR.l, BP);
				stack[SP += 2] = BP;
				stack[SP += 3] = PC;
				stack[SP += 4] = stack[SP];
				BP = SP += 1;
				PC = IR.m;
				break;
			case 6: //INC
				SP = SP + IR.m;
				break;
			case 7: //JmP
				PC = IR.m;
			case 8: //JPC
				if(stack[SP] == 0)
				{
					PC = IR.m;
				}
				SP -= 1;
			case 9: //SYS
				if (IR.m == 1)
				{
					printf("%d", stack[SP]);
    				SP -= 1;
				}
				else if (IR.m == 2)
				{
					SP += 1;
					scanf("%d", &stack[SP]);
				}
				else if (IR.m == 3)
					halt = 0;
				break;
		}
		// insert some for loop that loops and prints each stack value until
		// it reaches a NULL value.
	}

	printf("WE HIT A HALT CASE LADS IT WORKS!!!\n");
	fclose(ifp);
	return 0;
}







int base(int stack[], int level, int BP)
{
	int base = BP;
	int counter = level;
	while (counter > 0)
	{
		base = stack[base];
		counter--;
	}

	return base;
}

