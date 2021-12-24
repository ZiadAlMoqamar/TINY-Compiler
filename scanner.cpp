#include "scanner.h"
using namespace std;
Token::Token(string strValue ,string type )
{
    this->strValue = strValue;
    this->type = type;
}
string toUppercase(string str)
{   int strLen = str.length();
    for (int i = 0; i < strLen; ++i)
    {
        str[i] = toupper(str[i]);
    }
  return str;
}

string idRes (string strValue)
{

    if(find(reservedWords.begin(),reservedWords.end(),strValue)!=reservedWords.end())
        return toUppercase(strValue);
    return "IDENTIFIER";
}
string symbolType(char c)
{
     switch(c)
    {
        case '+': return "PLUS";
        case '-': return "MINUS";
        case '*': return "MULT";
        case '/': return "DIV";
        case '=': return "EQUAL";
        case '<': return "LESSTHAN";
        case '(': return "OPENBRACKET";
        case ')': return "CLOSEDBRACKET";
        case ';': return "SEMICOLON";
     default: return "error";
    }
}
string Scanner(string TinyFileText)
{
    vector<Token> tokenList; // List of tokens
    string tokenTable;
    int index = 0;
    int length = TinyFileText.length();
    //Loops over the string
        while(index<length)
        {
            int state = 1;
            string strValue = "";

            //Checks for a token
            //Basically, this is getToken()
            while (state != 6)
            {

                switch(state)
                {
                    case 1:

                    if(TinyFileText[index] == '{')
                        {
                            state=2;
                            index++;
                        }
                    else if(whitespace.find(TinyFileText[index])!= string::npos)
                        {
                            index++;
                            }
                    else if (isdigit(TinyFileText[index]))
                        {   strValue += TinyFileText[index];
                            state=3;
                            index++;
                            }
                    else if (isalpha(TinyFileText[index]))
                        {   strValue += TinyFileText[index];
                            state=4;
                            index++;
                            }
                    else if (TinyFileText[index] == ':')
                        {   strValue += TinyFileText[index];
                            state=5;
                            index++;
                            }
                    else if(specialSymbols.find(TinyFileText[index]) != string::npos)
                    {   strValue+=TinyFileText[index];
                        Token temp(strValue,symbolType(TinyFileText[index]));
                        tokenList.push_back(temp);
                        index++;
                        state = 6;
                    }
                    else if(index == length)
                    {
                        state =6;
                    }
                    else
                        {   strValue+=TinyFileText[index];
                            Token temp(strValue,"error");
                            tokenList.push_back(temp);
                            index++;
                            state=6;
                            }
                    break;
                    case 2:

                    while(TinyFileText[index] != '}' && index < length)
                        {

                            index++;

                        }

                    if(TinyFileText[index] == '}'){
                    index =index+1;}
                   else{
                    Token temp("{","error");
                    tokenList.push_back(temp);
                }
                        state=1;
                    break;
                    case 3:

                    if(isdigit(TinyFileText[index]))
                        {
                            strValue += TinyFileText[index];
                            index++;
                        }
                    else if(!isdigit(TinyFileText[index])||index == length -1)
                    {
                        Token temp(strValue,"NUMBER");
                        tokenList.push_back(temp);
                        state = 6;
                    }
                    break;
                    case 4:
                    if(isalpha(TinyFileText[index]))
                    {
                        strValue += TinyFileText[index];
                        index++;
                    }
                    else if (!isalpha(TinyFileText[index]) || index == length-1)
                    {
                        Token temp(strValue,idRes(strValue));
                        tokenList.push_back(temp);
                        state = 6;
                    }
                    break;
                    case 5:

                    if(TinyFileText[index] == '=')
                        {   strValue+= TinyFileText[index];
                            index++;
                            Token temp(strValue,"ASSIGN");
                            tokenList.push_back(temp);
                            state = 6;
                        }
                    else if(TinyFileText[index] != '='||index == length -1)
                    {
                        Token temp(strValue,"error");
                        tokenList.push_back(temp);
                        state = 6;
                    }
                    break;
                }

            }



}
//Output string
   for(auto i = tokenList.begin();i !=tokenList.end(); ++i)
    {

      tokenTable+=(*i).strValue+", "+(*i).type+"\n";
    }

    return tokenTable;
}
void testScanner()
{
    string line;
    string fileText;
    ifstream myfile ("tiny.txt");
    if (myfile.is_open())
    {
    while ( getline (myfile,line) )
    {
        fileText+=line+"\n";
    }
    string tokenTable = Scanner(fileText);
    cout<<tokenTable;

    }
    else cout << "Unable to open file";
}
//int main()
//{
//    testScanner();
//    return 0;
//}
