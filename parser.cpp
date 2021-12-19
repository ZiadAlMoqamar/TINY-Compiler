#include "parser.h"
Node :: Node()
{
    for(int i = 0; i < CHILDREN ; ++i)
    {
        childrenNode[i] = nullptr; //Initialize all nodes by nullptr
    }
}
Node::Node(Token t,std::string shape)
{
    this->t = t;
    this->shape = shape;
}
Token::Token(std::string strValue,std::string type )
{
    this->strValue = strValue;
    this->type = type;
}
void SyntaxTree::treeParser()
{

}
int genId()
{
    return uniqueId++;
}
void error()
{
    std::cout<<"Error:incorrect token at token no."<<tokenCounter<<"\n";
    exit(EXIT_FAILURE); //Stops the entire program
    //Add different error handling method later
}
void match(std::string token)
{
    if(token == inputTokens[tokenCounter].type)
    {   
        tokenCounter++;

    }
    else
        error();
}
void unmatch()
{
    tokenCounter--;
}
void testParser()
{
    std::string line;
    std::string fileText;
    std::ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
    while ( getline (myfile,line) )
    {   int index = 0;
        int temp = 0;
        bool ee= true;
        std::string value;
        Token empty;
        fileText+=line+"\n";
        for(int i = 0; i<2;++i)
            {
                int index= line.find_first_not_of(inputParse,temp);
                if(index !=std::string::npos)
                {   
                    temp = line.find_first_of(inputParse,index);
                    value= line.substr(index,temp-index);
                    if(ee)
                        {
                            empty.strValue= value;
                            //std::cout<<"strValue:"<<value<<", ";
                            ee = false;
                            }
                    else
                        {
                            empty.type=value;
                           // std::cout<<"Type:"<<value<<"\n";
                            }
                        
                    
                    index = temp;
                }
            }
            inputTokens.push_back(empty);

    }
    }
    else std::cout << "Unable to open file";
}
Node * factor()
{
    Node * t = new Node;
    if(inputTokens[tokenCounter].type == "OPENBRACKET")
    {
        match("OPENBRACKET");
        t= exp();
        match("CLOSEDBRACKET");
    }
    else if (inputTokens[tokenCounter].type == "NUMBER")
    {
        t->t = inputTokens[tokenCounter];
        match("NUMBER");
        t->shape = "ellipse";
        t->tokenId = genId();
    }
    else if(inputTokens[tokenCounter].type == "IDENTIFIER")
    {
        t->t = inputTokens[tokenCounter];
        match("IDENTIFIER");
        t->shape = "ellipse";
        t->tokenId = genId();
    }
    return t;
}
Node * term()
{
    Node * t = new Node;
    Node * q = factor();
    while (inputTokens[tokenCounter].type  == "MULT" || inputTokens[tokenCounter].type  == "DIV" )
    {
        if(inputTokens[tokenCounter].type  == "MULT")
        {
            t->t = inputTokens[tokenCounter];
            match("MULT");
            t->childrenNode[0] =q;
            t->childrenNode[1] = factor();
            t->shape = "ellipse";
            t->tokenId= genId();
            return t;
        }
        else if(inputTokens[tokenCounter].type  == "DIV")
        {
            t->t = inputTokens[tokenCounter];
            match("DIV");
            t->childrenNode[0] =q;
            t->childrenNode[1] = factor();
            t->shape = "ellipse";
            t->tokenId= genId();
            return t;
            
        }    
    }
    return q;   
}
Node * simpleExp()
{
    Node * t = new Node;
    Node * q = term();
    while(inputTokens[tokenCounter].type == "PLUS" || inputTokens[tokenCounter].type == "MINUS")
    {
        if(inputTokens[tokenCounter].type == "PLUS")
        {   t->t = inputTokens[tokenCounter];
            match("PLUS");
            t->childrenNode[0] = q;
            t->childrenNode[1] = term();
            t->shape= "ellipse";
            t->tokenId= genId();
            return t;
            
        }
        else if(inputTokens[tokenCounter].type == "MINUS")
        {   t->t = inputTokens[tokenCounter];
            match("MINUS");
            t->childrenNode[0] = q;
            t->childrenNode[1] = term();
            t->shape= "ellipse";
            t->tokenId= genId();
            return t;
        }
        return q;
    }   
}
Node * exp()
{   Node * t = new Node;
    Node * q = new Node;
    q =simpleExp();
    if(inputTokens[tokenCounter].type == "LESSTHAN")
    {   
        t->t = inputTokens[tokenCounter];
        match("LESSTHAN");
        t->childrenNode[0] = q;
        t->childrenNode[1] = simpleExp();
        t->tokenId = genId();
        t->shape = "ellipse";
        return t;
    }
    else if(inputTokens[tokenCounter].type == "EQUAL")
    {
        t->t= inputTokens[tokenCounter];
        match("EQUAL");
        t->childrenNode[0]= q;
        t->childrenNode[1]= simpleExp();
        t->tokenId = genId();
        t->shape = "ellipse";
        return t;
    }
    return q;
}
Node * ifStmt()
{   Node * t = new Node;
    t->t = inputTokens[tokenCounter];
    match("IF");
    match("OPENBRACKET");
    t->childrenNode[0] = exp();
    match("CLOSEDBRACKET");
    match("THEN");
    t->childrenNode[1] = stmtSeq();
    if(inputTokens[tokenCounter].type == "ELSE")
    {
        match("ELSE");
        t->childrenNode[2] = stmtSeq();
    }
    match("END");
    t->shape="rect";
    t->tokenId=genId();
    return t;
}
Node * repeatStmt()
{   Node * t = new Node;
    t->t = inputTokens[tokenCounter];
    match("REPEAT");
    t->childrenNode[0] = stmtSeq();//body
    match("UNTIL");
    t->childrenNode[1] = exp(); //Test
    t->shape="rect";
    t->tokenId=genId();
    return t;
}
Node * assignStmt()
{
    Node * t = new Node;
    t->t= inputTokens[tokenCounter];
    match("IDENTIFIER");
    t->subTitle= inputTokens[tokenCounter].strValue;
    match("ASSIGN");
    t->shape="rect";
    t->tokenId=genId();
    t->childrenNode[0] = exp();
    return t;
    
}
Node * readStmt()
{
    Node * t = new Node; 
    t->t=inputTokens[tokenCounter];
    match("READ");
    t->subTitle=inputTokens[tokenCounter].strValue;
    match("IDENTIFIER");
    t->shape="rect";
    t->tokenId=genId();
    return t;
}
Node * writeStmt()
{   Node * t = new Node; // write node  
    t->t=inputTokens[tokenCounter];
    match("WRITE");
    t->shape= "rect";   
    t->tokenId= genId(); // creates ID
    t->childrenNode[0] = exp();//Write only has one child
    return t;
}
Node * stmt()
{   
    std::string tokenType = inputTokens[tokenCounter].type;
    if(tokenType == "IF")
    {
       return ifStmt();
    }
    else if(tokenType == "REPEAT")
    {
        return repeatStmt();
    }
    else if(tokenType == "IDENTIFIER")
    {
        return assignStmt();
    }
    else if(tokenType == "READ")
    {
        return readStmt();
    }
     else if(tokenType == "WRITE")
    {
        return writeStmt();
    }
    else
    {
        error();
    }
}
Node *stmtSeq()
{   Node * t = nullptr;
    t = stmt(); // returns pointer and this will be the root pointer? of this tree
    Node * p = t;
    while(inputTokens[tokenCounter].type == "SEMICOLON")
    {   Node * q;
        match("SEMICOLON");
        q = stmt(); // returns pointer ex if
        p->neighbor = q; //links read with  if as neighbors
        p = q; // moves variable p to q and starts over. seems like a linked list
    }
    return t; // returns root/start node
}
int main()
{
    testParser(); //Loads inputTokens
    SyntaxTree program;
    program.rootptr= stmtSeq(); //Start the program
    program.treeParser();
}