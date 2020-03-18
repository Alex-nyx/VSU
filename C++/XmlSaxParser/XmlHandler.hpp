
#ifndef XmlHandler_hpp
#define XmlHandler_hpp

#include <string>
#include <vector>
#include <utility>

using namespace std;

class XmlHandler
{
public:
    
    XmlHandler() : tab_size(0) {}
    
    void startDocument();
    
	void startElement(string);

    void startElement(string name, vector<std::pair<std::string, std::string>>);
    
    void endElement(string);
    
    void characters(vector<string>);
    
private:
    int tab_size;
    
    void print_tab();
};

#endif /* XmlHandler_hpp */

