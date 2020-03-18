
#ifndef XmlParser_hpp
#define XmlParser_hpp

#include <iostream>
#include "XmlHandler.hpp"
#include "XmlToken.hpp"
#include <fstream>


using namespace std;

class XmlParser
{
public:
  
    XmlParser(string new_ifs, XmlHandler* new_handler)
    {
        ifs.open(new_ifs);
        
        handler =  new_handler;
    };
    
    ~XmlParser()
    {
        ifs.close();
        handler = nullptr;
    };
    
    void setHandler(XmlHandler* new_handler)
    {
        handler =  new_handler;
        
    };
    
    void setFile(string new_ifs)
    {
        ifs.close();
        ifs.open(new_ifs);
    }
    
    void parse();
    
private:

    XmlHandler* handler;
    ifstream ifs;
    
    void skip_white_space();
	Token get_token();

};


#endif /* XmlParser_hpp */
