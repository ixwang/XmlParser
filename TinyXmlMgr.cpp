//
//  TinyXmlMgr.cpp
//  XWTinyXML
//
//  Created by xwang on 8/18/16.
//
//

#include "TinyXmlMgr.hpp"

TinyXmlMgr::TinyXmlMgr()
:_filename("userInfo.xml")
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

void TinyXmlMgr::writeXml()
{
    string filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + _filename;
    
    //Link and create child node by pdoc
    pDoc = new XMLDocument();
    
    //Declaration
    XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    pDoc->LinkEndChild(pDel);
    
    //Add plist node (parent node)
    XMLElement *plistElement = pDoc->NewElement("plist");
    plistElement->SetAttribute("version", "1.0");
    pDoc->LinkEndChild(plistElement);
    
    /**   Add single node
     **   <?xml version="1.0" encoding="UTF-8"?>
     **   <plist version="1.0">
     **
     **         <singleNode> single node text </singleNode>
     **
     **   </plist>
     **/
    addChildNode( plistElement, "singleNode", " single node text " );
    
    /**   Add array node
     **   <?xml version="1.0" encoding="UTF-8"?>
     **   <plist version="1.0">
     **
     **         <arrayNode>
     **              <arrayChildNode> array child node text </arrayChildNode>
     **              <arrayChildNode> array child node text </arrayChildNode>
     **         </arrayNode>
     **
     **   </plist>
     **/
    XMLElement *arrayNode = pDoc->NewElement("arrayNode");
    int childNodeSize = 2;
    for ( int i = 0; i < childNodeSize; ++i )
    {
        XMLElement *tmp = pDoc->NewElement("arrayChildNode");
        tmp->LinkEndChild( pDoc->NewText(" array child node text ") );
        arrayNode->LinkEndChild( tmp );
    }
    plistElement->LinkEndChild( arrayNode );

}

void TinyXmlMgr::addChildNode( XMLElement* rootNode,
                               string parentNode,
                               string childNode )
{
    XMLElement *singleNode = pDoc->NewElement( parentNode.c_str() );
    singleNode->LinkEndChild( pDoc->NewText( childNode.c_str() ) );
    rootNode->LinkEndChild(singleNode);
}

