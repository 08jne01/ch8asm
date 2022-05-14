#pragma once
#include <vector>
#include <string>

struct Lexeme
{
	std::string text;
	int lineNumber;
};


class Lexer
{
public:
	Lexer();
	~Lexer();
	void lex(const std::string& text, std::vector<Lexeme>& s);
private:

	enum State
	{
		START,
		READCHAR,
		READBLOCK,
		SKIP,
		DUMP,
		COMMENT,
		END
	};

	int m_textIndex;
	int m_lexemeIndex;
	State m_state;
	bool m_done;
	int m_balance;
	char* buffer;
	int m_lineNumber;

	void start(const std::string& text);
	void readChar(const std::string& text, std::vector<Lexeme>& s);
	void readBlock(const std::string& text);
	void skip(const std::string& text);
	void dump(const std::string& text, std::vector<Lexeme>& s);
	void comment(const std::string& text);
	void end(const std::string& text);



	inline bool isSpace(char c);
	inline void addLine( char c );
	inline bool isSpecial(char c);
	inline bool isGroup(char c);
	char m_begin, m_end;
};

void Lexer::addLine( char c )
{
	if ( c == '\n' )
		m_lineNumber++;
}

bool Lexer::isSpace(char c)
{
	switch (c)
	{
	case '\n':
	case '\t':
	case ' ':
	case '\v':
	case '\r':
	case '\f':
		return true;
	default:
		return false;
	}
}

bool Lexer::isSpecial(char c)
{
	switch (c)
	{
	case ',':
	case ':':
	case '.':
		return true;
	default:
		return false;
	}
}

bool Lexer::isGroup(char c)
{
	m_begin = c;
	switch (c)
	{
	case '"':
		m_end = '"';
		return true;
	case '(':
		m_end = ')';
		return true;
	case ')':
		return true;
	default:
		return false;
	}
}