//Kyle Olson and Natasha Serrano

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100

int base(int stack[], int level, int BP);

typedef struct instruction
{
	int opcode;
	char op[4];
	int l;
	int m;
} instruction;

int main(int argc, char *argv[])
{
	// Initialize variables.
	int i;

	int size = 0;
	int halt = 1;
	int SP = -1;
	int BP = 0;
	int PC = 0;
	int instructNum;
	char *str;
	instruction IR;

	// Initialize the arrays to their correct size.
	bool *lex = malloc(sizeof(bool) * MAX_STACK_HEIGHT);
	int *stack = malloc(sizeof(int) * MAX_STACK_HEIGHT);
	instruction *text = malloc(sizeof(instruction) * MAX_CODE_LENGTH);

	// Open the .txt file given the input from the command line.
	FILE *ifp = fopen (argv[1], "r");

	// Loop through the .txt file and place each sequence in the struct array.
	for (i = 0; !feof(ifp); i++)
		fscanf(ifp, "%d %d %d", &text[i].opcode, &text[i].l, &text[i].m);

	// Print initial values.
	printf("		PC 	BP 	SP 	stack\n");
	printf("Initial values:	%d	%d	%d\n", PC, BP, SP);

	// Loop through and execute each IR until the halt is called.
	while(halt == 1)
	{
		// Set the IR to the correct IR in the struct array
		// and increment PC.
		instructNum = PC;
		IR = text[PC];
		PC += 1;

		// Use a switch statement to execute correct instruction
  		switch(IR.opcode)
  		{
  			// LIT
 			case 1:
				SP += 1;
    			stack[SP] = IR.m;
    			strcpy(IR.op, "LIT");
    			size++;
    			break;
    		// OPR
			case 2:
				switch (IR.m)
				{
					// RTN
					case 0:
						stack[BP - 1] = stack[SP];
						SP = BP - 1;
						BP = stack[SP + 2];
						PC = stack[SP + 3];
						for (i = MAX_STACK_HEIGHT; i >= 0; i--)
						{
							if (lex[i] == true)
							{
								lex[i] = false;
								size = i;
							}
						}
						strcpy(IR.op, "RTN");
						break;
					// NEG
					case 1:
						stack[SP] *= - 1;
						strcpy(IR.op, "NEG");
						break;
					// ADD
					case 2:
						SP -= 1;
						stack[SP] += stack[SP + 1];
						strcpy(IR.op, "ADD");
						size--;
						break;
					// SUB
					case 3:
						SP -= 1;
						stack[SP] -= stack[SP + 1];
						strcpy(IR.op, "SUB");
						size--;
						break;
					// MUL
					case 4:
						SP -= 1;
						stack[SP] *= stack[SP + 1];
						strcpy(IR.op, "MUL");
						size--;
						break;
					// DIV
					case 5:
						SP -= 1;
						stack[SP] /= stack[SP + 1];
						strcpy(IR.op, "DIV");
						size--;
						break;
					// ODD
					case 6:
						stack[SP] %= 2;
						strcpy(IR.op, "ODD");
						size--;
						break;
					// MOD
					case 7:
						SP =- 1;
						stack[SP] %= stack[SP + 1];
						strcpy(IR.op, "MOD");
						size--;
						break;
					// EQL
					case 8:
						SP -= 1;
						stack[SP] = (stack[SP] == stack[SP + 1]) ? 1 : 0;
						strcpy(IR.op, "EQL");
						size--;
						break;
					// NEQ
					case 9:
						SP -= 1;
						stack[SP] = (stack[SP] != stack[SP + 1]) ? 1 : 0;
						strcpy(IR.op, "NEQ");
						size--;
						break;
					// LSS
					case 10:
						SP -= 1;
						stack[SP] = (stack[SP] < stack[SP + 1]) ? 1 : 0;
						strcpy(IR.op, "LSS");
						size--;
						break;
					// LEQ
					case 11:
						SP -= 1;
						stack[SP] = (stack[SP] <= stack[SP + 1]) ? 1 : 0;
						strcpy(IR.op, "LEQ");
						size--;
						break;
					// GTR
					case 12:
						SP -= 1;
						stack[SP] = (stack[SP] > stack[SP + 1]) ? 1 : 0;
						strcpy(IR.op, "GTR");
						size--;
						break;
					// GEQ
					case 13:
						SP -= 1;
						stack[SP] = (stack[SP] >= stack[SP + 1]) ? 1 : 0;
						strcpy(IR.op, "GEQ");
						size--;
						break;
				}
				break;
			// LOD
			case 3:
				SP += 1;
				stack[SP] = stack[base(stack, IR.l, BP) + IR.m];
				strcpy(IR.op, "LOD");
				size++;
				break;
			// STO
			case 4:
				stack[base(stack, IR.l, BP) + IR.m] = stack[SP];
				SP -= 1;
				strcpy(IR.op, "STO");
				size--;
				break;
			// CAL
			case 5:
				stack[SP + 1] = base(stack, IR.l, BP);
				stack[SP + 2] = BP;
				stack[SP + 3] = PC;
				stack[SP + 4] = stack[SP];
				BP = SP + 1;
				PC = IR.m;
				lex[size] = true;
				strcpy(IR.op, "CAL");
				break;
			// INC
			case 6:
				SP = SP + IR.m;
				strcpy(IR.op, "INC");
				size += IR.m;
				break;
			// JMP
			case 7:
				PC = IR.m;
				strcpy(IR.op, "JMP");
				break;
			// JPC
			case 8:
				if(stack[SP] == 0)
				{
					PC = IR.m;
				}
				SP -= 1;
				strcpy(IR.op, "JPC");
				size--;
				break;
			// SYS
			case 9:
				if (IR.m == 1)
				{
					printf("Top of Stack Value: %d\n", stack[SP]);
    				SP -= 1;
    				size--;
				}
				else if (IR.m == 2)
				{
					SP += 1;
					printf("Please Enter an Integer: ");
					scanf("%d", &stack[SP]);
					printf("\n");
					size++;
				}
				else if (IR.m == 3)
					halt = 0;
				strcpy(IR.op, "SYS");
				break;
		}
		
		// Print current values after instruction execute.
		printf(" %d %s %d %d 	%d 	%d 	%d 	",
			instructNum, IR.op, IR.l, IR.m, PC, BP, SP);

		// Loop through and print each stack value.
		// Print a '|' between activation records.
		for (i = 0; i < size; i++)
		{
			if (lex[i] == true)
				printf(" | ");
			printf("%d ", stack[i]);
		}

		// Print a newline character at the very end.
		printf("\n");
	}

	// Close the file and return.
	fclose(ifp);
	return 0;
}

// Implement given base() function.
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

