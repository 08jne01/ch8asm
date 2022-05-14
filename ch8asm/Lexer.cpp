#include "Lexer.h"

Lexer::Lexer()
{
	buffer = new char[512];
}

Lexer::~Lexer()
{
	if (buffer)
		delete[] buffer;
}

void Lexer::lex
(
	const std::string& text,
	std::vector<Lexeme>& s
)
{
	m_lineNumber = 1;
	m_textIndex = 0;
	m_lexemeIndex = 0;
	m_state = START;
	m_done = false;
	m_balance = 0;

	while (m_textIndex < text.size())
	{
		switch (m_state)
		{
		case START:
			start(text);
			break;
		case READCHAR:
			readChar(text, s);
			break;
		case READBLOCK:
			readBlock(text);
			break;
		case SKIP:
			skip(text);
			break;
		case DUMP:
			dump(text, s);
			break;
		case COMMENT:
			comment(text);
			break;
		case END:
			end(text);
			break;
		}
	}

	if (m_lexemeIndex > 0)
	{
		buffer[m_lexemeIndex] = 0;
		Lexeme l;
		l.text = buffer;
		l.lineNumber = m_lineNumber;
		s.push_back(l);
	}
}

void Lexer::start(const std::string& text)
{	
	if (isSpace(text[m_textIndex]))
		m_state = SKIP;
	else if (isGroup(text[m_textIndex]))
	{
		if (text[m_textIndex] == '"')
		{
			buffer[m_lexemeIndex] = text[m_textIndex];
			m_textIndex++;
			m_lexemeIndex++;
		}
		m_state = READBLOCK;
	}
	else if (text[m_textIndex] == ';')
	{
		m_textIndex++;
		m_state = COMMENT;
	}
	else
	{
		m_state = READCHAR;
	}
}

void Lexer::readChar(const std::string& text, std::vector<Lexeme>& s)
{
	if (isSpace(text[m_textIndex]))
		m_state = DUMP;
	else if (isSpecial(text[m_textIndex]))
	{
		dump(text, s);
		buffer[m_lexemeIndex] = text[m_textIndex];
		m_textIndex++;
		m_lexemeIndex++;
		m_state = DUMP;
	}
	else if (isGroup(text[m_textIndex]))
	{
		if (text[m_textIndex] == '"')
		{
			buffer[m_lexemeIndex] = text[m_textIndex];
			m_textIndex++;
			m_lexemeIndex++;
		}
		m_state = READBLOCK;
	}
	else if (text[m_textIndex] == ';')
	{
		m_textIndex++;
		m_state = COMMENT;
	}
	else
	{
		buffer[m_lexemeIndex] = text[m_textIndex];
		m_lexemeIndex++;
		m_textIndex++;
	}
}

void Lexer::readBlock(const std::string& text)
{
	if (text[m_textIndex] == m_begin && text[m_textIndex] != '"')
	{
		m_balance++;
		buffer[m_lexemeIndex] = text[m_textIndex];
		m_lexemeIndex++;
		m_textIndex++;
	}
	else if (text[m_textIndex] == m_end)
	{
		m_balance--;
		buffer[m_lexemeIndex] = text[m_textIndex];
		m_lexemeIndex++;
		m_textIndex++;
		if (m_balance <= 0)
			m_state = DUMP;
	}
	else
	{
		buffer[m_lexemeIndex] = text[m_textIndex];
		m_lexemeIndex++;
		m_textIndex++;
	}
}

void Lexer::skip(const std::string& text)
{
	if ( isSpace( text[m_textIndex] ) )
	{
		addLine( text[m_textIndex] );
		m_textIndex++;
	}
	else
		m_state = READCHAR;
}

void Lexer::dump(const std::string& text, std::vector<Lexeme>& s)
{
	if (m_lexemeIndex > 0)
	{
		buffer[m_lexemeIndex] = 0;
		Lexeme l;
		l.text = buffer;
		l.lineNumber = m_lineNumber;
		s.push_back(l);
		m_lexemeIndex = 0;
	}
	m_state = START;
}

void Lexer::comment(const std::string& text)
{
	if (text[m_textIndex] != '\n')
		m_textIndex++;
	else
		m_state = READCHAR;
}

void Lexer::end(const std::string& text)
{
	if (text[m_textIndex] != '\n')
		m_textIndex++;
	else
		m_state = READCHAR;
}