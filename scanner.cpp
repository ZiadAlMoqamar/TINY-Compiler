#include "scanner.h"
using namespace std;
Token::Token(string strValue ,string type )
{
    this->strValue = strValue;
    this->type = type;
}
string idRes (string strValue)
{
    //if(reservedWords.find(strValue) != string::npos) return "reserved word";
    if(find(reservedWords.begin(),reservedWords.end(),strValue)!=reservedWords.end())
        return "reserved word";
    return "identifier";
}
string symbolType(char c)
{
     switch(c)
    {
        case '+': return "plus";
        case '-': return "minus";
        case '*': return "times";
        case '/': return "over";
        case '=': return "equal";
        case '<': return "less than";
        case '(': return "left parenthesis";
        case ')': return "right parenthesis";
        case ';': return "semicolon";
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
            while (state != 6&& index<length)
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
                    else
                        {   strValue+=TinyFileText[index];
                            Token temp(strValue,"error");
                            tokenList.push_back(temp);
                            index++;
                            state=6;
                            }
                    break;
                    case 2:

                    while(TinyFileText[index] != '}')
                        {

                            index++;

                        }
                        index++;
                        state=1;
                    break;
                    case 3:

                    if(isdigit(TinyFileText[index]))
                        {
                            strValue += TinyFileText[index];
                            index++;
                        }
                    else {
                        Token temp(strValue,"number");
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
                    else
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
                            Token temp(strValue,"assign");
                            tokenList.push_back(temp);
                            state = 6;
                        }
                    else
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


