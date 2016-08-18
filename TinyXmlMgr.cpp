//
//  TinyXmlMgr.cpp
//  XWTinyXML
//
//  Created by xwang on 8/18/16.
//
//

#include "TinyXmlMgr.hpp"

TinyXmlMgr::TinyXmlMgr()
{
    
}

TinyXmlMgr::~TinyXmlMgr()
{
    
}

TinyXmlMgr* TinyXmlMgr::txMgr = nullptr;

TinyXmlMgr* TinyXmlMgr::getInstance()
{
    if( txMgr == nullptr )
    {
        txMgr = new TinyXmlMgr();
    }
    return txMgr;
}