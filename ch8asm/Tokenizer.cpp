#include "Tokenizer.h"
#include <iostream>
#include "extern.h"
Tokenizer::Tokenizer()
{

}

void Tokenizer::tokenize(const std::vector<std::string>& lexemes, std::vector<Token>& tokens)
{
	for (int i = 0; i < lexemes.size(); i++)
	{
		const std::string& s = lexemes[i];
		Token token;
		if (s == commandStrings[CLR])
			token.type = CLR;
		else if (s == commandStrings[RET])
			token.type = RET;
		else if (s == commandStrings[JMP])
			token.type = JMP;
		else if (s == commandStrings[CALL])
			token.type = CALL;
		else if (s == commandStrings[SE])
			token.type = SE;
		else if (s == commandStrings[SNE])
			token.type = SNE;
		else if (s == commandStrings[MOV])
			token.type = MOV;
		else if (s == commandStrings[ADD])
			token.type = ADD;
		else if (s == commandStrings[OR])
			token.type = OR;
		else if (s == commandStrings[AND])
			token.type = AND;
		else if (s == commandStrings[XOR])
			token.type = XOR;
		else if (s == commandStrings[SUB])
			token.type = SUB;
		else if (s == commandStrings[SHR])
			token.type = SHR;
		else if (s == commandStrings[SHL])
			token.type = SHL;
		else if (s == commandStrings[SUBO])
			token.type = SUBO;
		else if (s == commandStrings[SPT])
			token.type = SPT;
		else if (s == commandStrings[BCD])
			token.type = BCD;
		else if (s == commandStrings[DUMP])
			token.type = DUMP;
		else if (s == commandStrings[LOAD])
			token.type = LOAD;
		else if (s == commandStrings[DRAW])
			token.type = DRAW;
		else if (s == commandStrings[MJMP])
			token.type = MJMP;
		else if (s == commandStrings[SNK])
			token.type = SNK;
		else if (s == commandStrings[SK])
			token.type = SK;
		else if (s == commandStrings[WTK])
			token.type = WTK;
		else if (s == commandStrings[SOUND_TIMER])
			token.type = SOUND_TIMER;
		else if (s == commandStrings[DELAY_TIMER])
			token.type = DELAY_TIMER;
		else if (s == commandStrings[MEMORY_REGISTER])
			token.type = MEMORY_REGISTER;
		else if (s == commandStrings[RND])
			token.type = RND;
		else if (s[0] == commandStrings[DATA_REGISTER][0])
			processDataRegister(token, s);
		else if (s == ",")
			token.type = COMMA;
		else if (s == ":")
			token.type = COLON;
		else if (s == ".")
			token.type = DOT;
		else
			processLabelOrLiteral(token, s);

		tokens.push_back(token);
	}
}

void Tokenizer::processDataRegister(Token& token, const std::string& s)
{
	token.type = DATA_REGISTER;
	if (s.size() != 2)
	{
		token.data.value = 16;
	}

	std::string numStr = s.substr(1, 2);
	int x;
	if (sscanf_s(numStr.c_str(), "%x", &x))
	{
		if (x < 16)
			token.data.value = x;
		else
			token.data.value = 16;
	}
	else
		token.data.value = 16;
}

void Tokenizer::processLabelOrLiteral(Token& token, const std::string& s)
{
	int literal;
	if (s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X') && sscanf_s(s.c_str(), "%x", &literal))
	{
		token.data.value = literal;
		token.type = LITERAL;
	}
	else if (sscanf_s(s.c_str(), "%d", &literal))
	{
		token.data.value = literal;
		token.type = LITERAL;
	}
	else
	{
		//token.data.text = s;
		strcpy_s(token.data.text, s.c_str());
		token.type = INSTRUCTION_LABEL;
	}
		
}