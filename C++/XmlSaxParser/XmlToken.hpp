#ifndef XmlToken_hpp
#define XmlToken_hpp

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

enum class Token_type { Tag_open, Tag_close, Characters, Tag_empty };

class Token
{
public:
	
	Token_type type() const
	{
		return _type;
	}

	std::vector<std::string> get_characters() const
	{
		return _characters;
	}

	std::vector<std::pair<std::string, std::string>> get_attr() const
	{
		return _attr;
	}

	std::string get_tag_name() const
	{
		return _tag_name;
	}

	void set_type(Token_type type)
	{
		_type = type;
	}

	void set_tag_name(std::string name)
	{
		_tag_name = name;
	}

	void add_attr(std::string attr_name, std::string attr_text)
	{
		_attr.push_back(make_pair(attr_name, attr_text));
	}

	void add_characters(std::string str)
	{
		_characters.push_back(str);
	}

private:

	Token_type _type;

	std::string _tag_name;
	std::vector<std::string> _characters;
	std::vector<std::pair<std::string, std::string>> _attr;



};


#endif