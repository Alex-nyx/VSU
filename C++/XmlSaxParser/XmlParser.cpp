#include "XmlParser.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void XmlParser::parse()
{
	handler->startDocument();

	while (ifs)
	{
		Token tok = get_token();

		switch (tok.type())
		{
		case Token_type::Tag_open:
		{
			handler->startElement(tok.get_tag_name(), tok.get_attr());
			break;
		}

		case Token_type::Tag_close:
		{
			handler->endElement(tok.get_tag_name());
			break;
		}

		case Token_type::Tag_empty:
		{
			handler->startElement(tok.get_tag_name());
			break;
		}

		case Token_type::Characters:
		{
			handler->characters(tok.get_characters());
			break;
		}
		}

	}
}

Token XmlParser::get_token()
{
	Token token;
	char ch;

	skip_white_space();

	ifs.get(ch);

	//ќпределение типа токена
	if (ch == '<' && ifs.peek() == '/')
	{
		ifs.get(ch);
		token.set_type(Token_type::Tag_close);
	}

	else if (ch == '<' && ifs.peek() != '/')
	{
		token.set_type(Token_type::Tag_open);
	}

	else
	{
		token.set_type(Token_type::Characters);
		ifs.putback(ch);
	}
	

	//—читывание токена
	switch (token.type())
	{

	case Token_type::Tag_close:
	{
		string _name = "";
		while ((ch = ifs.get()) != '>')
		{
			_name.push_back(ch);
		}

		token.set_tag_name(_name);
		return token;
	}

	case Token_type::Tag_open:
	{
		string name = "";
	
		while (!isspace(ch = ifs.get()))
	{
		if (ch == '/' && ifs.peek() == '>')
		{
			ifs.get(ch);

			token.set_type(Token_type::Tag_empty);
			token.set_tag_name(name);

			return token;
		}


		else if (ch == '>')
		{
			token.set_type(Token_type::Tag_open);
			token.set_tag_name(name);

			return token;
		}

		name.push_back(ch);
	}
	
		token.set_tag_name(name);
		
		while ((ch = ifs.get()) != '>')
		{
			string _attr_name = "", _attr_text = "";
	
			skip_white_space();
	
			ifs.get(ch);
			while (ch !=  '=')
			{
				_attr_name.push_back(ch);
				ifs.get(ch);
			}
			
			ifs.get(ch);

			while ((ch = ifs.get()) != '"')
			{
				_attr_text.push_back(ch);
			}
	
			token.add_attr(_attr_name, _attr_text);
		}
		
		return token;
	}

	case Token_type::Characters:
	{
		string str = "";

		while ((ch = ifs.get()) != '<')
		{
			if (ch == '\n')
			{
				str.push_back(ch);
				token.add_characters(str);
				str = "";
				skip_white_space();
			}
			else
			{
				str.push_back(ch);
			}
		}

		str.push_back('\n');
		token.add_characters(str);

		ifs.putback(ch);

		return token;
	}	

	}

}

void XmlParser::skip_white_space()
{
	char ch;

	while (isspace(ch = ifs.get()))
	{
		continue;
	}

	ifs.putback(ch);
}
