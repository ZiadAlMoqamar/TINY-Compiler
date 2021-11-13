#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
class Token
{
public:
string strValue = "";
string type ="";
Token(string strValue = "",string type = "");

};
static string whitespace = " \n\t\r\v";
static string reservedWords = "if then else end repeat until read write";
static string specialSymbols = "+-*/=<();";
string lowerCase(string x);
string idRes (string strValue);
string symbolType(char c);
string Scanner(string TinyFileText);
void testScanner();

#endif // SCANNER_H
