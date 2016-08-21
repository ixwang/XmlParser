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


//----------------------------------write xml-----------------------------------------
void TinyXmlMgr::writeXml()
{
    //File save path, using cocos2d API here, could be any other
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
        
        firstLvlNode->LinkEndChild( secLvlNode );
    }
    plistElement->LinkEndChild( firstLvlNode );
    
    pDoc->SaveFile( filePath.c_str() );
    
    // print all generated xml doc
    //pDoc->Print();
    
    delete pDoc; pDoc = nullptr;
}

void TinyXmlMgr::addChildNode( XMLElement* rootNode,
                               string key,
                               string value )
{
    XMLElement *node = pDoc->NewElement( key.c_str() );
    node->LinkEndChild( pDoc->NewText( value.c_str() ) );
    rootNode->LinkEndChild( node );
}

//----------------------------------read xml-----------------------------------------
void TinyXmlMgr::readXml()
{
    //File save path, using cocos2d API here, could be any other
    string filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + _filename;
    
    //Load file and get node
    XMLDocument *pDoc = new XMLDocument(); pDoc->LoadFile( filePath.c_str() );
    
    //Get root node
    XMLElement *rootEle = pDoc->RootElement();
    
    //Get root attribute, why need?
    //const XMLAttribute *attribute = rootEle->FirstAttribute();
    
    //Read single node element
    XMLElement *singleNode = rootEle->FirstChildElement("singleNode");
    if( singleNode )
    {
        if( singleNode->GetText() != NULL)
        { string singleNodeStr = singleNode->GetText(); }
    }
    
    //Read array node
    XMLElement *arrayNode = rootEle->FirstChildElement("arrayNode");
    XMLElement *childEle;
    if( arrayNode )
    {
        childEle = arrayNode->FirstChildElement("arrayChildNode");
        while ( childEle )
        {
            string childNodeTxt = childEle->GetText();
            childEle = childEle->NextSiblingElement();
        }
    }
    
    // array‘s array node
    XMLElement *firstLvlNode = rootEle->FirstChildElement("firstLvlNode");
    while( firstLvlNode )
    {
        XMLElement *secLvlNode = firstLvlNode->FirstChildElement("secLvlNode");
        
        while( secLvlNode )
        {
            string trdLvlNode1 = secLvlNode->FirstChildElement("trdLvlNode1")->GetText();
            string trdLvlNode2 = secLvlNode->FirstChildElement("trdLvlNode2")->GetText();

            secLvlNode = secLvlNode->NextSiblingElement();
        }
        
        firstLvlNode = firstLvlNode->NextSiblingElement();
    }
}




