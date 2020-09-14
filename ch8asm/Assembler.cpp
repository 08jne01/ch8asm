#include "Assembler.h"
#include "Lexer.h"
#include <fstream>
#include <iostream>
#include "extern.h"
Assembler::Assembler()
{

}

bool Assembler::assemble(const char* filename)
{
	std::ifstream file(filename);
	std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	file.close();
	std::vector<std::string> lexemes;
	Lexer lexer;
	lexer.lex(content, lexemes);


	std::vector<Token> tokens;
	Tokenizer tokenizer;
	tokenizer.tokenize(lexemes, tokens);
	lexemes.clear();
	m_labels.clear();

	processLabels(tokens);

	m_tokenIndex = 0;
	m_state = State::START;
	m_binary.clear();
	while (m_tokenIndex < tokens.size() && m_state != State::ERROR)
	{
		switch (m_state)
		{
		case State::START:
			start(tokens);
			break;
		case State::READTOKEN:
			readToken(tokens);
			break;
		case State::DUMP:
			dumpToken(tokens);
			break;
		}
	}

	if (m_state != State::ERROR)
	{
		dumpToken(tokens);
		std::string outputFileName = "";
		for (int i = 0; filename[i] && filename[i] != '.'; i++)
		{
			outputFileName += filename[i];
		}
		outputFileName += ".rom";
		std::ofstream outputBinary(outputFileName, std::ios::out | std::ios::binary);
		if (outputBinary.is_open())
		{
			outputBinary.write((const char*)(&m_binary[0]), m_binary.size());
			outputBinary.close();
			return true;
		}
		else
		{
			return false;
		}	
	}
	return false;
}

void Assembler::start(const std::vector<Token>& tokens)
{
	if (isOperator(tokens[m_tokenIndex]))
	{
		m_state = State::READTOKEN;
		m_tokenBuffer.push_back(tokens[m_tokenIndex]);
		m_tokenIndex++;
	}
	else
		m_tokenIndex++;
}

void Assembler::readToken(const std::vector<Token>& tokens)
{
	if (isDumpPoint(tokens[m_tokenIndex]))
		m_state = State::DUMP;
	else if (isOperand(tokens[m_tokenIndex]))
	{
		m_tokenBuffer.push_back(tokens[m_tokenIndex]);
		m_tokenIndex++;
		m_operands++;
	}
	else
		m_tokenIndex++;
		
}

void Assembler::dumpToken(const std::vector<Token>& tokens)
{
	m_state = State::START;

	if (!m_tokenBuffer.size())
		return;

	uint16_t code = 0;
	if (m_tokenBuffer.size() == 1)
	{
		code = commandTable(m_tokenBuffer[0].type,NONE,NONE);
		if (!code)
		{
			m_state = State::ERROR;
			std::cout << "Invalid Operand " << commandStrings[m_tokenBuffer[0].type] << std::endl;
		}

		addBytes(code);
	}
	else if (m_tokenBuffer.size() == 2)
	{
		code = commandTable(m_tokenBuffer[0].type,m_tokenBuffer[1].type,NONE);
		if (!code)
		{
			m_state = State::ERROR;
			std::cout << "Invalid Operand " << commandStrings[m_tokenBuffer[0].type] << "," << commandStrings[m_tokenBuffer[1].type] << std::endl;
		}

		if (m_tokenBuffer[1].type == DATA_REGISTER)
			code |= (m_tokenBuffer[1].data.value & 0x000F) << 8;
		else
		{
			uint16_t address = checkTokenBufferZNNN("change-me");
			if (address)
				code |= (address & 0x0FFF);
		}

		addBytes(code);
	}
	else if (m_tokenBuffer.size() == 3)
	{
		code = commandTable(m_tokenBuffer[0].type,m_tokenBuffer[1].type,m_tokenBuffer[2].type);
		if (!code)
		{
			m_state = State::ERROR;
			std::cout << "Invalid Operand " << commandStrings[m_tokenBuffer[0].type] << "," << commandStrings[m_tokenBuffer[1].type] << "," << commandStrings[m_tokenBuffer[2].type] << std::endl;
		}
		uint16_t codeCopy = code;
		code |= (m_tokenBuffer[1].data.value & 0x000F) << 8;
		if (m_tokenBuffer[1].type == MEMORY_REGISTER)
		{
			if (m_tokenBuffer[0].type == MOV)
			{
				code = codeCopy;
				code |= (m_tokenBuffer[2].data.value & 0x0FFF);
			}
			else if (m_tokenBuffer[0].type == ADD)
			{
				code = codeCopy;
				code |= (m_tokenBuffer[2].data.value & 0x000F) << 8;
			}
		}
		else if (m_tokenBuffer[1].type == DELAY_TIMER || m_tokenBuffer[1].type == SOUND_TIMER)
		{
			code = codeCopy;
			code |= (m_tokenBuffer[2].data.value & 0x000F) << 8;
		}
		else if (m_tokenBuffer[2].type == DELAY_TIMER)
		{
			//do nothing
		}
		else if (m_tokenBuffer[2].type == LITERAL)
		{
			code |= (m_tokenBuffer[2].data.value & 0x00FF);
		}
		else
		{
			code |= (m_tokenBuffer[2].data.value & 0x000F) << 4;
		}
			
		addBytes(code);
	}
	else if (m_tokenBuffer.size() == 4)
	{
		code = commandTable(m_tokenBuffer[0].type,m_tokenBuffer[1].type,m_tokenBuffer[2].type);
		if (!code)
		{
			m_state = State::ERROR;
			std::cout << "Invalid Operand " << commandStrings[m_tokenBuffer[0].type] << "," << commandStrings[m_tokenBuffer[1].type] << "," << commandStrings[m_tokenBuffer[2].type] << "," << commandStrings[m_tokenBuffer[3].type] << std::endl;
		}
		code |= (m_tokenBuffer[1].data.value & 0x00F) << 8;
		code |= (m_tokenBuffer[2].data.value & 0x00F) << 4;
		code |= (m_tokenBuffer[3].data.value & 0x00F) << 0;
		addBytes(code);
	}
		


	m_tokenBuffer.clear();
	m_operands = 0;
}

bool Assembler::isOperator(const Token& token)
{
	switch (token.type)
	{
	case COMMA:
	case MEMORY_REGISTER:
	case LITERAL:
	case DATA_REGISTER:
	case SOUND_TIMER:
	case DELAY_TIMER:
	case INSTRUCTION_LABEL:
	case SECTION_LABEL:
	case DOT:
	case COLON:
		return false;
	default:
		return true;
	}
}

bool Assembler::isDumpPoint(const Token& token)
{
	switch (token.type)
	{
	case COMMA:
	case MEMORY_REGISTER:
	case LITERAL:
	case DATA_REGISTER:
	case SOUND_TIMER:
	case DELAY_TIMER:
	case INSTRUCTION_LABEL:
		return false;
	default:
		return true;
	}
}

bool Assembler::isOperand(const Token& token)
{
	switch (token.type)
	{
	case MEMORY_REGISTER:
	case LITERAL:
	case DATA_REGISTER:
	case SOUND_TIMER:
	case DELAY_TIMER:
	case INSTRUCTION_LABEL:
		return true;
	default:
		return false;
	}
}

void Assembler::processLabels(std::vector<Token>& tokens)
{
	int instructionOffset = 0;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == INSTRUCTION_LABEL)
		{
			tokens[i].address = instructionOffset + 0x200;
			if (i > 0 && tokens[i - 1].type == DOT)
				m_labels.push_back(tokens[i]);
		}
		else if (isOperator(tokens[i]))
		{
			instructionOffset += 2;
		}
	}
}

void Assembler::addBytes(uint16_t word)
{
	uint8_t b1 = (word & 0xFF00) >> 8;
	uint8_t b2 = word & 0x00FF;
	m_binary.push_back(b1);
	m_binary.push_back(b2);
}

void Assembler::addBytesForZNNN(uint16_t z, uint16_t nnn)
{
	uint8_t b1 = ((0x000Fu & z) << 4) | ((nnn & 0x0F00u) >> 8);
	uint8_t b2 = (nnn & 0x00FFu);
	m_binary.push_back(b1);
	m_binary.push_back(b2);
}

void Assembler::addBytesForZXNN(uint16_t z, uint16_t x, uint16_t nn)
{
	uint8_t b1 = ((0x000Fu & z) << 4) | (x & 0x000Fu);
	uint8_t b2 = (0x00FFu & nn);
	m_binary.push_back(b1);
	m_binary.push_back(b2);
}

void Assembler::addBytesForZXYN(uint16_t z, uint16_t x, uint16_t y, uint16_t n)
{
	uint8_t b1 = ((0x000Fu & z) << 4) | (x & 0x000Fu);
	uint8_t b2 = ((0x000Fu & y) << 4) | (n & 0x000Fu);
	m_binary.push_back(b1);
	m_binary.push_back(b2);
}

uint16_t Assembler::checkTokenBufferZNNN(const char* error)
{
	if (m_tokenBuffer.size() != 2 || (m_tokenBuffer[1].type != LITERAL && m_tokenBuffer[1].type != INSTRUCTION_LABEL))
	{
		std::cout << error << " error" << std::endl;
		m_state = State::ERROR;
		return false;
	}

	uint16_t address;
	if (m_tokenBuffer[1].type == INSTRUCTION_LABEL)
	{
		address = findAddress(m_tokenBuffer[1].data.text);
	}
	else
	{
		address = m_tokenBuffer[1].data.value;
	}

	if (!address)
	{
		std::cout << error << " error, address was not found or NULL" << std::endl;
		m_state = State::ERROR;
	}
	return address;
}

uint16_t Assembler::findAddress(const char* label)
{
	for (int i = 0; i < m_labels.size(); i++)
	{
		if (strcmp(m_labels[i].data.text, label) == 0)
		{
			return m_labels[i].address;
		}
	}
	return NULL;
}