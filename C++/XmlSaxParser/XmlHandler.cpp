#include "XmlHandler.hpp"
#include <iostream>
#include <vector>

using namespace std;

void XmlHandler::startDocument()
{
    cout << "<__StartDoc__>" << endl;
}

void XmlHandler::startElement(string name)
{
	print_tab();
	cout << name << " <->__tag_empty" << endl;
}

void XmlHandler::startElement(string name,  vector<std::pair<std::string, std::string>> attr)
{
    print_tab();
    cout << name << " ->__tag_open" << endl;
    
	if (attr.size() != 0)
	{
		print_tab();
		cout << "__attr:" << endl;

		for (pair<string, string> _attr : attr)
		{
			this->print_tab();
			cout << _attr.first << " = " << _attr.second << endl;
		}
	}

	tab_size++;
}

void XmlHandler::endElement(std::string tag)
{
	tab_size--;
    
    this->print_tab();
    
    cout << tag  << " <-__tag_close" << endl;
}

void XmlHandler::characters(vector<string> vec_str)
{
	//cout << endl;
	for (string str : vec_str)
	{
		this->print_tab();
		cout << str;
	}
	//cout << endl;
}

void XmlHandler::print_tab()
{
    for (int i = 0; i < tab_size; ++i)
    {
        cout << "    ";
    }
}
