#ifndef _PARSER_H
#define _PARSER_H

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
    Token t;
    std::string shape="";
    std::string subTitle="";
    Node * neighbor = nullptr; //neighbor node
    Node * childrenNode[CHILDREN];
    Node();
    Node(Token t,std::string shape);
    int tokenId; //Must be uniqueId
};
class SyntaxTree
{
    public:
    Node * rootptr = nullptr; //Start point
    //Fns
    void treeParser();

};
static std::vector<Token> inputTokens; 
static int tokenCounter = 0;
static int uniqueId = 0;
static std::string inputParse = " \n\t\r\v,";
static std::string outputString ="";
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