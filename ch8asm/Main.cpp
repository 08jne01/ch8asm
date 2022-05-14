#include <fstream>
#include <iostream>
#include "extern.h"
#include "Assembler.h"

const char* commandStrings[NUMBER_COMMAND_TYPE] = {};
Table<uint16_t> commandTable(NUMBER_COMMAND_TYPE, 7, 7);

static const char* commandDescription[NUMBER_COMMAND_TYPE] = {};

static void setupCommands();
static void printCommandUsage();

int main(int argc, char** argv)
{
	const char* filename = NULL;
	setupCommands();

	for ( int i = 1; i < argc; i++ )
	{
		if ( strcmp( "--help", argv[i] ) == 0 || strcmp( "--h", argv[i] ) == 0 )
		{
			printCommandUsage();
			return 1;
		}
		else
		{
			filename = argv[i];
		}
	}

	if ( ! filename )
	{
		printf( "ERROR: No file supplied.\n" );
		return 1;
	}

	Assembler assembler;
	if ( assembler.assemble( filename ) )
	{
		std::cout << filename << " assembled correctly to a .rom file" << std::endl;
	}

	return 0;
}

void setupCommands()
{
	for (int i = 0; i < NUMBER_COMMAND_TYPE; i++)
	{
		commandStrings[i] = "";
	}

	commandStrings[NONE] = "none";
	commandStrings[INSTRUCTION_LABEL] = "instruction_label";
	commandStrings[LITERAL] = "literal";
	commandStrings[DATA_REGISTER] = "vx";
	commandStrings[MEMORY_REGISTER] = "ptr";
	commandStrings[SOUND_TIMER] = "snd";
	commandStrings[DELAY_TIMER] = "dly";
	commandStrings[CLR] = "clr";
	commandStrings[RET] = "ret";
	commandStrings[JMP] = "jmp";
	commandStrings[CALL] = "call";
	commandStrings[SE] = "se";
	commandStrings[SNE] = "sne";
	commandStrings[MOV] = "mov";
	commandStrings[ADD] = "add";
	commandStrings[OR] = "or";
	commandStrings[AND] = "and";
	commandStrings[XOR] = "xor";
	commandStrings[SUB] = "sub";
	commandStrings[SHR] = "shr";
	commandStrings[SHL] = "shl";
	commandStrings[SUBO] = "subo";
	commandStrings[SPT] = "spt";
	commandStrings[BCD] = "bcd";
	commandStrings[DUMP] = "dump";
	commandStrings[LOAD] = "load";
	commandStrings[DRAW] = "draw";
	commandStrings[RND] = "rnd";
	commandStrings[MJMP] = "mjmp";
	commandStrings[SK] = "sk";
	commandStrings[SNK] = "snk";
	commandStrings[WTK] = "wtk";
	commandStrings[COMMA] = "comma";
	commandStrings[COLON] = "colon";
	commandStrings[DOT] = "dot";
	commandStrings[SECTION_LABEL] = "section label";
	commandStrings[DATA] = "data";

	//commandTable = new uint16_t**[NUMBER_COMMAND_TYPE];
	for (int i = 0; i < NUMBER_COMMAND_TYPE; i++)
	{
		//commandTable[i] = new uint16_t*[7];
		for (int j = 0; j < 7; j++)
		{
			//commandTable[i][j] = new uint16_t[7];
			for (int k = 0; k < 7; k++)
			{
				commandTable(i,j,k) = 0;
			}
		}
	}

	commandTable(CLR,NONE,NONE) = 0x00E0;
	commandTable(RET,NONE,NONE) = 0x00EE;

	commandTable(JMP,LITERAL,NONE) = 0x1000;
	commandTable(JMP,INSTRUCTION_LABEL,NONE) = 0x1000;

	commandTable(CALL,LITERAL,NONE) = 0x2000;
	commandTable(CALL,INSTRUCTION_LABEL,NONE) = 0x2000;

	commandTable(DUMP,DATA_REGISTER,NONE) = 0xF055;
	commandTable(LOAD,DATA_REGISTER,NONE) = 0xF065;
	commandTable(BCD,DATA_REGISTER,NONE) = 0xF033;
	commandTable(SPT,DATA_REGISTER,NONE) = 0xF029;

	commandTable(SE,DATA_REGISTER,LITERAL) = 0x3000;
	commandTable(SE,DATA_REGISTER,DATA_REGISTER) = 0x5000;

	commandTable(SNE,DATA_REGISTER,LITERAL) = 0x4000;
	commandTable(SNE,DATA_REGISTER,DATA_REGISTER) = 0x9000;

	commandTable(SK,DATA_REGISTER,NONE) = 0xE09E;
	commandTable(SNK,DATA_REGISTER,NONE) = 0xE0A1;
	commandTable(WTK,DATA_REGISTER,NONE) = 0xF00A;

	commandTable(MOV,MEMORY_REGISTER, INSTRUCTION_LABEL ) = 0xA000;
	commandTable(MOV,MEMORY_REGISTER,LITERAL) = 0xA000;
	commandTable(MOV,SOUND_TIMER,DATA_REGISTER) = 0xF018;
	commandTable(MOV,DELAY_TIMER,DATA_REGISTER) = 0xF015;
	commandTable(MOV,DATA_REGISTER,DELAY_TIMER) = 0xF007;
	commandTable(MOV,DATA_REGISTER,LITERAL) = 0x6000;
	commandTable(MOV,DATA_REGISTER,DATA_REGISTER) = 0x8000;

	commandTable(ADD,DATA_REGISTER,LITERAL) = 0x7000;
	commandTable(ADD,DATA_REGISTER,DATA_REGISTER) = 0x8004;
	commandTable(ADD,MEMORY_REGISTER,DATA_REGISTER) = 0xF01E;

	commandTable(SUB,DATA_REGISTER,DATA_REGISTER) = 0x8005;

	commandTable(MJMP,LITERAL,NONE) = 0xB000;
	commandTable(MJMP, INSTRUCTION_LABEL,NONE) = 0xB000;
	commandTable(DRAW,DATA_REGISTER,DATA_REGISTER) = 0xD000;
	commandTable(RND,DATA_REGISTER,LITERAL) = 0xC000;
	commandTable(SPT,DATA_REGISTER,NONE) = 0xF029;
	commandTable(SUBO,DATA_REGISTER,DATA_REGISTER) = 0x8007;

	commandTable(SHR,DATA_REGISTER,NONE) = 0x8006;
	commandTable(SHL,DATA_REGISTER,NONE) = 0x800E;
	commandTable(AND,DATA_REGISTER,DATA_REGISTER) = 0x8002;
	commandTable(OR,DATA_REGISTER,DATA_REGISTER) = 0x8001;
	commandTable(XOR,DATA_REGISTER,DATA_REGISTER) = 0x8003;

	commandDescription[CLR] = "Clears the screen";
	commandDescription[RET] = "Returns from routine";
	commandDescription[JMP] = "Jump to instruction";
	commandDescription[CALL] = "Calls a routine";
	commandDescription[SE] = "Skips an instruction if operands are equal";
	commandDescription[SNE] = "Skips an instruction if operands are not equal";
	commandDescription[MOV] = "Moves the second operand's value into the first";
	commandDescription[ADD] = "Adds the second operand's value to the first";
	commandDescription[OR] = "Bitwise OR between operands";
	commandDescription[AND] = "Bitwise AND between operands";
	commandDescription[XOR] = "Bitwise XOR betwen operands";
	commandDescription[SUB] = "Subtracs the second operand's value from the first";
	commandDescription[SHR] = "Bitshifts operand right by 1";
	commandDescription[SHL] = "Bitshifts operand left by 1";
	commandDescription[SUBO] = "Subtracts the first operand from the second and puts it in the first operand";
	commandDescription[SPT] = "Sets the ptr to the sprite in the operand";
	commandDescription[BCD] = "Sets the binary coded decimal in the first operand at the current ptr location";
	commandDescription[DUMP] = "Dumps the registers up to the first operand at the current ptr";
	commandDescription[LOAD] = "Loads the registers up to the first operand at the current ptr";
	commandDescription[DRAW] = "Draws a sprite from ptr at the first operand for x and the second operand for y with a sprite height of the third operand";
	commandDescription[RND] = "Sets the first operand to a random number between 0-255 bitwise and with second operand";
	commandDescription[MJMP] = "Sets the ptr to the first operand + the current value of register 0";
	commandDescription[SK] = "Skips the next instruction if the key in the first operand is held";
	commandDescription[SNK] = "Skips the next instruction if the key in the first operand is not held";
	commandDescription[WTK] = "Waits for a key press and then puts the result in the first operand";

}

void printCommandUsage()
{
	for (int i = CLR; i < COMMA; i++)
	{
		std::cout << "=======================" << std::endl;
		printf( "INSTRUCTION: %s\n", commandStrings[i] );
		printf( "DESCRIPTION: %s\n", commandDescription[i] );
		printf( "OPERANDS: \n" );
		for (int j = 0; j < 7; j++)
		{
			for (int k = 0; k < 7; k++)
			{
				uint16_t code = commandTable(i, j, k);
				if (code)
				{
					std::cout << "\t" << commandStrings[i];
					if (j != NONE)
					{
						std::cout << "\t" << commandStrings[j];

						if (k != NONE)
						{
							std::cout << ",\t" << commandStrings[k];

							if (i == DRAW)
							{
								std::cout << ",\t" << commandStrings[LITERAL];
							}
						}
							
					}
					std::cout << std::endl;
				}
			}
		}
	}
}