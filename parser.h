#ifndef PARSER_H
#define PARSER_H

#define CHILDREN 3
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "scanner.h"
using namespace std;
//class Token
//{
//public:
//string strValue = "";
//string type ="";
//Token(string strValue = "",string type = "");
//};
class Node
{
    public:
    string t;
    string shape="";
    string subTitle="";
    Node * neighbor = nullptr; //neighbor node
    Node * childrenNode[CHILDREN];
    Node();
    Node(string t,string shape);
    int tokenId; //Must be uniqueId
};
class SyntaxTree
{
    public:
    Node * rootptr = nullptr; //Start point
    //Fns
    void treeParser(Node * root);

};
static vector<Token> inputTokens; 
static int tokenCounter = 0;
static int uniqueId = 0;
static string inputParse = " \n\t\r\v,";
static string outputString ="";//Body : graph main{body}
string getTokenType();
string getSubTitle();
string addNode(long long id, string shape, string title, string subtitle);
string addChild(long long parentId, long long childId);
string addNeighbour(long long leftId, long long rightId);
string addInvisibleLine(long long leftId, long long rightId);
string dotLang(vector<Token> input);
vector <Token> parseFileText(string file);
int genId();
void error();
void match(string token);
void unmatch();

//Node *  program();
Node * stmtSeq();
Node *  stmt();
Node *  ifStmt();
Node *  repeatStmt();
Node *  assignStmt();
Node *  readStmt();
Node *  writeStmt();
Node *  exp();
Node *  simpleExp();
Node *  term();
Node *  factor();
#endif
