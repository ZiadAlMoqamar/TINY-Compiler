#ifndef PARSER_H
#define PARSER_H

#define CHILDREN 3
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
class Token
{
public:
std::string strValue = "";
std::string type ="";
Token(std::string strValue = "",std::string type = "");
};
class Node
{
    public:
    std::string t;
    std::string shape="";
    std::string subTitle="";
    Node * neighbor = nullptr; //neighbor node
    Node * childrenNode[CHILDREN];
    Node();
    Node(std::string t,std::string shape);
    int tokenId; //Must be uniqueId
};
class SyntaxTree
{
    public:
    Node * rootptr = nullptr; //Start point
    //Fns
    void treeParser(Node * root);

};
static std::vector<Token> inputTokens; 
static int tokenCounter = 0;
static int uniqueId = 0;
static std::string inputParse = " \n\t\r\v,";
static std::string outputString ="";//Body : graph main{body}
std::string getTokenType();
std::string getSubTitle();
std::string addNode(long long id, std::string shape, std::string title, std::string subtitle);
std::string addChild(long long parentId, long long childId);
std::string addNeighbour(long long leftId, long long rightId);
std::string addInvisibleLine(long long leftId, long long rightId);
std::string dotLang(std::vector<Token> input);
std::vector <Token> parseFileText(std::string file);
int genId();
void error();
void match(std::string token);
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