#include "xmlTest.h"
#include "include/IOType/XML/rapidxml.hpp"
#include "include/IOType/XML/rapidxml_utils.hpp"
#include "include/IOType/XML/rapidxml_iterators.hpp"
#include<stdio.h>
#include<iostream>
using namespace std;
// https://blog.csdn.net/m0_61629312/article/details/133769004

void XmlTest::test1() {
	cout << "test1" << endl;

    using namespace rapidxml;
    xml_document<> doc;
  
    file<> f("D:/selfad/alg_and_graph/3DAlgorithm/Tests/BasicTest/IOTypeTest/ReadExample.xml");

    // ����XML�ĵ�
    cout << doc.parse<rapidxml::parse_default>(f.data()) << endl;

    // ��ȡ��Ԫ��
    rapidxml::xml_node<>* root = doc.first_node("bookname");
    //cout << root->prefix() << endl;

    // ������Ԫ��book
    
    for (rapidxml::xml_node<>* book = root->first_node("book"); book; book = book->next_sibling("book")) {
        cout <<"book: type = "<< book->type() << endl;

        // ��ȡ����
        rapidxml::xml_node<>* name = book->first_node("name");
        cout << "name: type = " << name->type() << endl;
        if (name) {
            std::cout << "Book Name: " << name->value() << std::endl;
        }

        // ��ȡ����
        rapidxml::xml_node<>* author = book->first_node("author");
        if (author) {
            std::cout << "Author: " << author->value() << std::endl;
        }

        // ��ȡ�۸�
        rapidxml::xml_node<>* price = book->first_node("price");
        if (price) {
            std::cout << "Price: " << price->value() << std::endl;
        }

        std::cout << std::endl;
    }

    // ��ȡConnectorԪ�ص�����
    rapidxml::xml_node<>* connector = root->first_node("Connector");
    if (connector) {
        std::cout << "Connector Attributes:" << std::endl;
        for (rapidxml::xml_attribute<>* attr = connector->first_attribute(); attr; attr = attr->next_attribute()) {
            std::cout << "Attribute Name: " << attr->name() << ", Value: " << attr->value() << std::endl;
        }
    }
}
//https://www.cnblogs.com/lygin/p/17101100.html  ������ʵ��
void XmlTest::testGauss() {
    cout << "testGauss" << endl;

    using namespace rapidxml;
    xml_document<> doc;

    //file<> f("D:/selfad/alg_and_graph/3DAlgorithm/CBB3DAlgorithm/Fitting/gauss/TestData.xml");
    file<> f("D:/shining3d/doc/���������Խ��/chebyshev/��ʽ����/PtbTestData.xml");

    // ����XML�ĵ�
    cout<<doc.parse<rapidxml::parse_default>(f.data())<<endl;

    char* xmlns_tracim = "http://tracim.ptb.de/tracim";
    char *xmlns_gauss = "http://tracim.ptb.de/chebyshev/test";
    // ��ȡ��Ԫ��
    rapidxml::xml_node<>* root = doc.first_node("tracim", xmlns_tracim)
        ->first_node("test", xmlns_tracim);
    cout << root->value() << endl;
    
    root = doc.first_node("tracim", xmlns_tracim)
        ->first_node("test", xmlns_tracim) ->first_node("package", xmlns_gauss);

    cout << root->prefix() << endl;
    cout << root->xmlns() << endl;
    //return;
    // ������Ԫ��book
    for (node_iterator<char> caseNode(root); caseNode.valid(); ++caseNode) {
        char* tag = "basicID";
        puts(tag);
        puts(caseNode->first_node(tag)->value());
        tag = "computationObject";
        puts(tag);
        puts(caseNode->first_node(tag)->value());
        tag = "pointCloud";
        puts(tag);
        rapidxml::xml_node<>* ps = caseNode->first_node(tag);
        for (node_iterator<char> point(ps);
            point.valid();
            point++) {
            //puts("p name : ");
            //puts(point->name());
            for (node_iterator<char> coord(&*point); coord.valid(); coord++) {
                printf("%s %s ",coord->name(), coord->value());
            }
            puts("");
            //break;
        }
    }
}