#include <iostream>
#include "include/IOType/XML/rapidxml.hpp"
#include "include/IOType/XML/rapidxml_utils.hpp"
#include "include/IOType/XML/rapidxml_iterators.hpp"
#include<stdio.h>
#include<fstream>
#include <TestCaseGen.h>
using namespace std;
namespace Fitting {
	int Xml2Txt(std::string xmlPath, std::string outDir, std::string package) {

		cout << xmlPath << endl;
		cout << outDir << endl;

        using namespace rapidxml;
        xml_document<> doc;

        file<> f(xmlPath.c_str());

        // 解析XML文档
        cout << doc.parse<rapidxml::parse_default>(f.data()) << endl;

        char* xmlns_tracim = "http://tracim.ptb.de/tracim";
        string xmlns_package = "http://tracim.ptb.de/" + package+"/test";
        cout << xmlns_package << endl;

        // 获取根元素
        rapidxml::xml_node<>* root = doc.first_node("tracim", xmlns_tracim)
            ->first_node("test", xmlns_tracim)->first_node("package", xmlns_package.c_str());
            
        /*rapidxml::xml_node<>* root = doc.first_node("chebyshevTestPackage", xmlns_package.c_str())
            ->first_node("package", xmlns_package.c_str());*/

        

        cout << root->prefix() << endl;
        cout << root->xmlns() << endl;

        
        FILE* kind = fopen((outDir + "kind.txt").c_str(), "w");
        //return;
        // 遍历子元素book
        for (rapidxml::xml_node<>* caseNode = root->first_node("testElement"); caseNode; caseNode = caseNode->next_sibling()) {
            char* tag = "basicID";
            puts(tag);
            puts(caseNode->first_node(tag)->value());
            char *ID = caseNode->first_node(tag)->value();
            fprintf(kind, "%s:", caseNode->first_node(tag)->value());
            tag = "computationObject";
            fprintf(kind, "%s\n", caseNode->first_node(tag)->value());
            puts(tag);
            puts(caseNode->first_node(tag)->value());
            tag = "pointCloud";
            puts(tag);
            FILE* coordsFile = fopen((outDir + ID+".asc").c_str(), "w");
            rapidxml::xml_node<>* ps = caseNode->first_node(tag);
            for (node_iterator<char> point(ps);
                point.valid();
                point++) {
                //puts("p name : ");
                //puts(point->name());
                int i = 0;
                for (node_iterator<char> coord(&*point); coord.valid(); coord++) {
                    printf("%s %s ", coord->name(), coord->value());
                    if (i++) {
                        fprintf(coordsFile, "\t");
                    }
                    fprintf(coordsFile, "%s", coord->value());
                }
                puts("");
                fprintf(coordsFile, "\n");
                //break;
            }

            fclose(coordsFile);
        }

        fclose(kind);

		return 0;
	}

    int Xml2Ans(std::string xmlPath, std::string outDir, std::string package) {

        cout << xmlPath << endl;
        cout << outDir << endl;

        using namespace rapidxml;
        xml_document<> doc;

        file<> f(xmlPath.c_str());

        // 解析XML文档
        cout << doc.parse<rapidxml::parse_default>(f.data()) << endl;

        string node_package = package + "ResultPackage";
        string xmlns_package = "http://tracim.ptb.de/" + package + "/test";
        cout << node_package << endl;

        // 获取根元素
        rapidxml::xml_node<>* root = doc.first_node(node_package.c_str(), xmlns_package.c_str())
            ->first_node("resultPackage");

        FILE* kind = fopen((outDir + "kind.txt").c_str(), "w");
        //return;
        // 遍历子元素book
        for (node_iterator<char> resultNode(root); resultNode.valid(); ++resultNode) {
            char* tag = "basicID";
            puts(tag);
            puts(resultNode->first_node(tag)->value());
            char* ID = resultNode->first_node(tag)->value();
            fprintf(kind, "%s:", resultNode->first_node(tag)->value());
            tag = "computationObject";
            fprintf(kind, "%s\n", resultNode->first_node(tag)->value());
            puts(tag);
            puts(resultNode->first_node(tag)->value());
            tag = "refParameter";
            puts(tag);
            FILE* ansFile = fopen((outDir + ID + ".txt").c_str(), "w");
            rapidxml::xml_node<>* params = resultNode->first_node(tag);
            for (node_iterator<char> ele(params);
                ele.valid();
                ele++) {
                //puts("p name : ");
                //puts(point->name());
                fprintf(ansFile, "%s\n", ele->value());
            }

            fclose(ansFile);
        }

        fclose(kind);

        return 0;
    }

}