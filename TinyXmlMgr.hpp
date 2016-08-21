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
    
    //** some usage samples */
    void writeXml();
    void readXml();

private:
    
    /**   Add single xml node
     **   <rootNode>
     **         <key>value</key>
     **   </rootNode>
     **/
    void addChildNode( XMLElement* rootNode,
                       string key,
                       string value );
};

    
    
    
#endif /* TinyXmlMgr_hpp */
