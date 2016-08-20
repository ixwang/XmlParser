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
    
    //Add plist node (root node)
    XMLElement *plistElement = pDoc->NewElement("plist");
    plistElement->SetAttribute("version", "1.0");
    pDoc->LinkEndChild(plistElement);
    
    /**   Add single node
     **   <?xml version="1.0" encoding="UTF-8"?>
     **   <plist version="1.0">
     **
     **         <singleNode>single node text</singleNode>
     **
     **   </plist>
     **/
    addChildNode( plistElement, "singleNode", "single node text" );
    
    /**   Add array node
     **   <?xml version="1.0" encoding="UTF-8"?>
     **   <plist version="1.0">
     **
     **         <arrayNode>
     **              <arrayChildNode>array child node text</arrayChildNode>
     **              <arrayChildNode>array child node text</arrayChildNode>
     **         </arrayNode>
     **
     **   </plist>
     **/
    XMLElement *arrayNode = pDoc->NewElement("arrayNode");
    int childNodeSize = 2;
    for ( int i = 0; i < childNodeSize; ++i )
    {
        addChildNode( arrayNode, "arrayChildNode", "array child node text" );
    }
    plistElement->LinkEndChild( arrayNode );
    
    /**   Add array‘s array node
     **   <?xml version="1.0" encoding="UTF-8"?>
     **   <plist version="1.0">
     **
     **         <firstLvlNode>
     **              <secLvlNode> 
     **                      <trdLvlNode1>trdLvlNode1 text</trdLvlNode1>
     **                      <trdLvlNode2>trdLvlNode2 text</trdLvlNode2>
     **              </secLvlNode>
     **              <secLvlNode>
     **                      <trdLvlNode1>trdLvlNode1 text</trdLvlNode1>
     **                      <trdLvlNode2>trdLvlNode2 text</trdLvlNode2>
     **              </secLvlNode>
     **         </firstLvlNode>
     **
     **   </plist>
     **/
    XMLElement *firstLvlNode = pDoc->NewElement("firstLvlNode");
    
    int secNodeSize = 2;
    for ( int i = 0; i < secNodeSize; ++i )
    {
        XMLElement *secLvlNode = pDoc->NewElement("secLvlNode");
        addChildNode( secLvlNode, "trdLvlNode1", "trdLvlNode1 text" );
        addChildNode( secLvlNode, "trdLvlNode2", "trdLvlNode2 text" );
    }
    plistElement->LinkEndChild( firstLvlNode );
}

void TinyXmlMgr::addChildNode( XMLElement* rootNode,
                               string key,
                               string value )
{
    XMLElement *node = pDoc->NewElement( key.c_str() );
    node->LinkEndChild( pDoc->NewText( value.c_str() ) );
    rootNode->LinkEndChild( node );
}

