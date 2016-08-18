//
//  TinyXmlMgr.hpp
//  XWTinyXML
//
//  Created by xwang on 8/18/16.
//
//

#ifndef TinyXmlMgr_hpp
#define TinyXmlMgr_hpp

#include <stdio.h>
#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class TinyXmlMgr
{
private:
     TinyXmlMgr();
    ~TinyXmlMgr();
    
private:
    //** */
    static TinyXmlMgr* txMgr;

private:
    string _filename;
    XMLDocument* pDoc;

public:
    //** singleton */
    static TinyXmlMgr* getInstance();
    
public:
    void writeXml();
    

private:
    void addChildNode( XMLElement* rootNode,
                       string parentNode,
                       string childNode );

};

    
    
    
#endif /* TinyXmlMgr_hpp */
