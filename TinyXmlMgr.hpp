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


class TinyXmlMgr
{
private:
     TinyXmlMgr();
    ~TinyXmlMgr();
    
private:
    //** */
    static TinyXmlMgr* txMgr;

public:
    //** singleton */
    static TinyXmlMgr* getInstance();

};

    
    
    
#endif /* TinyXmlMgr_hpp */
