#pragma once
#include <vector>
#include <string>
#include <cinttypes>
#include "Lexer.h"
enum Type
{
	NONE,
	INSTRUCTION_LABEL, //something:
	LITERAL, //0xYY or 0xYYY or number
	DATA_REGISTER, //vx where x is 0 -> F
	MEMORY_REGISTER, //ptr
	SOUND_TIMER, //snd
	DELAY_TIMER, //dly
	CLR, //Clear screen : 00EO @
	RET, //Return Function : 00EE @
	JMP, //Jump : 1NNN @
	CALL, //Call function : 2NNN @
	SE, //Skip Equal 3XNN, 5XY0 @
	SNE, //Skip not Equal : 4XNN, 9XY0 @
	MOV, //Set a to b 6XNN, 8XY0, ANNN, FX15, FX18, FX07 @
	ADD, //Add a to b and put int a 7XNN, 8XY4, FX1E @
	OR, //Bitwise OR : 8XY1 @
	AND, //Bitwise AND : 8XY2 @
	XOR, //Bitwise XOR : 8XY3 @ 
	SUB, //Sub a - b and put it in a : 8XY4 @
	SHR, //shift right by 1 8XY6 @
	SHL, //sift left by 1 8XYE @
	SUBO, //Sub b - a and put it in a : 8XY7
	SPT, //set mem to sprite address : FX29
	BCD, //Set Binary Code Decimal : FX33 @
	DUMP, //Dump registers up to a : FX55 @
	LOAD, //Load registers up to a : FX65 @
	DRAW, //Draw to Screen : DXYN @
	RND, //Random number : CXNN @
	MJMP, //Mem jmp to V0 + NNN  BNNN @
	SK,
	SNK,
	WTK,
	COMMA,
	COLON,
	DOT,
	SECTION_LABEL, //.something
	DATA,
	NUMBER_COMMAND_TYPE
};

#define LABEL_SIZE 40

struct Token
{
	union Data
	{
		char text[LABEL_SIZE];
		uint16_t value;
	} data;
	Type type;
	uint16_t address;
	int lineNumber;
};

class Tokenizer
{
public:
	Tokenizer();
	void tokenize(const std::vector<Lexeme>& lexemes, std::vector<Token>& tokens);
	void processDataRegister(Token& token, const std::string& s);
	void processLabelOrLiteral(Token& token, const std::string& s);
private:
	static inline void toLower( std::string& s );
};

void Tokenizer::toLower( std::string& s )
{
	for ( int i = 0; i < s.size(); i++ )
	{
		s[i] = tolower( s[i] );
	}
}