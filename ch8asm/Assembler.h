#pragma once
#include <vector>
#include <string>
#include "Tokenizer.h"
class Assembler
{
public:
	Assembler();
	bool assemble(const char* filename);
private:

	enum class State
	{
		START,
		READTOKEN,
		DUMP,
		ERROR
	};

	struct Label
	{
		Token token;
		int index;
	};

	void start(const std::vector<Token>& tokens);
	void readToken(const std::vector<Token>& tokens);
	void dumpToken(const std::vector<Token>& tokens);

	bool isOperator(const Token& token);
	bool isDumpPoint(const Token& token);
	bool isOperand(const Token& token);

	
	uint16_t findAddress(const char* label);
	void processLabels(std::vector<Token>& tokens);

	//Utility
	void addByte( uint8_t byte );
	void addBytes(uint16_t word);
	void addBytesForZNNN(uint16_t z, uint16_t nnn);
	void addBytesForZXNN(uint16_t z, uint16_t x, uint16_t nn);
	void addBytesForZXYN(uint16_t z, uint16_t x, uint16_t y, uint16_t n);

	uint16_t checkTokenBufferZNNN(const char* error);

	uint8_t b1;
	uint8_t b2;
	int m_tokenIndex;
	int m_operands;
	State m_state;

	std::vector<Token> m_tokenBuffer;
	std::vector<Token> m_labels;
	std::vector<uint8_t> m_binary;

	std::vector<Label> m_addressIndices;
};