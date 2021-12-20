#include "parser.h"
Node :: Node()
{
    for(int i = 0; i < CHILDREN ; ++i)
    {
        childrenNode[i] = nullptr; //Initialize all nodes by nullptr
    }
}
Node::Node(std::string t ,std::string shape)
{
    this->t = t;
    this->shape = shape;
}
Token::Token(std::string strValue,std::string type )
{
    this->strValue = strValue;
    this->type = type;
}
void SyntaxTree::treeParser(Node * root)
{   
    if(root == nullptr)
        return;

    outputString += addNode(root->tokenId,root->shape,root->t,root->subTitle); //Creating the node itself
    if(root->childrenNode[0] != nullptr) // has children
    {
        //draw children
    }
    //then draw neighbors
    Node * neighbor = root->neighbor;
    if(neighbor != nullptr)
    {
        treeParser(neighbor);
        outputString += addNeighbour(root->tokenId, neighbor->tokenId);
    }
        
    
}
std::string getTokenType()
{   if(tokenCounter<inputTokens.size())
        return inputTokens[tokenCounter].type;
    return "ENDFILE";
}
std::string getSubTitle()
{
    return "("+inputTokens[tokenCounter].strValue+")";
}
std::string addNode(long long id, std::string shape, std::string title, std::string subtitle){
std::string funcOutput ="\n";
funcOutput += "node[shape =" + shape + " label=\"" + title + "\\n" + subtitle + "\"] " + std::to_string(id);
return funcOutput;
}
std::string addChild(long long parentId, long long childId) {
  std::string funcOutput = "\n";
  funcOutput += std::to_string(parentId) + "--" + std::to_string(childId);
  return funcOutput;
}
std::string addNeighbour(long long leftId, long long rightId) {
  std::string funcOutput = "\n";
  funcOutput += "{rank = same;"+std::to_string(leftId)+"; "+std::to_string(rightId)+";}"+ std::to_string(leftId) + "--" + std::to_string(rightId);
  return funcOutput;
}
std::string addInvisibleLine(long long leftId, long long rightId) {
  std::string funcOutput = "\n";
  funcOutput += "{rank = same;" + std::to_string(leftId) + "; " + std::to_string(rightId) + ";}" + std::to_string(leftId) + "--" + std::to_string(rightId) +"[style = invis];";
  return funcOutput;
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
    if(token == getTokenType())
    {   
        tokenCounter++;

    }
    else
    {   //it just works idk
        if(token !="ENDFILE")
            error();
    }
        
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
    if(getTokenType() == "OPENBRACKET")
    {
        match("OPENBRACKET");
        t= exp();
        match("CLOSEDBRACKET");
    }
    else if (getTokenType() == "NUMBER")
    {
        t->subTitle = getSubTitle();
        match("NUMBER");
        t->t = "const";
        t->shape = "oval";
        t->tokenId = genId();
    }
    else if(getTokenType() == "IDENTIFIER")
    {
        t->subTitle = getSubTitle();
        match("IDENTIFIER");
        t->t = "id";
        t->shape = "oval";
        t->tokenId = genId();
    }
    else
        error();
    return t;
}
Node * term()
{
    Node * t = new Node;
    Node * q = factor();
    while (getTokenType()  == "MULT" || getTokenType()  == "DIV" )
    {
        if(getTokenType()  == "MULT")
        {   
            t->subTitle= getSubTitle();
            match("MULT");
            t->t = "op";
            t->childrenNode[0] =q;
            t->childrenNode[1] = factor();
            t->shape = "oval";
            t->tokenId= genId();
            return t;
        }
        else if(getTokenType()  == "DIV")
        {
            t->subTitle= getSubTitle();
            match("DIV");
            t->t = "op";
            t->childrenNode[0] =q;
            t->childrenNode[1] = factor();
            t->shape = "oval";
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
    while(getTokenType() == "PLUS" || getTokenType() == "MINUS")
    {
        if(getTokenType() == "PLUS")
        {   
            t->subTitle= getSubTitle();
            match("PLUS");
            t->t = "op";
            t->childrenNode[0] = q;
            t->childrenNode[1] = term();
            t->shape= "oval";
            t->tokenId= genId();
            return t;
            
        }
        else if(getTokenType() == "MINUS")
        {   
            t->subTitle= getSubTitle();
            match("MINUS");
            t->t = "op";
            t->childrenNode[0] = q;
            t->childrenNode[1] = term();
            t->shape= "oval";
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
    if(getTokenType()== "LESSTHAN")
    {   
        t->subTitle= getSubTitle();
        match("LESSTHAN");
        t->t = "op";
        t->childrenNode[0] = q;
        t->childrenNode[1] = simpleExp();
        t->tokenId = genId();
        t->shape = "oval";
        return t;
    }
    else if(getTokenType() == "EQUAL")
    {
        t->subTitle= getSubTitle();
        match("EQUAL");
        t->t= "op";
        t->childrenNode[0]= q;
        t->childrenNode[1]= simpleExp();
        t->tokenId = genId();
        t->shape = "oval";
        return t;
    }
    return q;
}
Node * ifStmt()
{   Node * t = new Node;
    match("IF");
    t->t = "if";
    
    t->childrenNode[0] = exp();
    match("THEN");
    t->childrenNode[1] = stmtSeq();
    if(getTokenType() == "ELSE")
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
    match("REPEAT");
    t->t = "repeat";
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
    t->subTitle= getSubTitle();
    match("IDENTIFIER");
    t->t= "assign";
    match("ASSIGN");
    t->shape="rect";
    t->tokenId=genId();
    t->childrenNode[0] = exp();
    return t;
    
}
Node * readStmt()
{
    Node * t = new Node; 
    match("READ");
    t->t="read";
    t->subTitle=getSubTitle();
    match("IDENTIFIER");
    t->shape="rect";
    t->tokenId=genId();
    return t;
}
Node * writeStmt()
{   Node * t = new Node; // write node  
    match("WRITE");
    t->t="write";
    t->shape= "rect";   
    t->tokenId= genId(); // creates ID
    t->childrenNode[0] = exp();//Write only has one child
    return t;
}
Node * stmt()
{   
    std::string tokenType = getTokenType();
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
    while(getTokenType()  == "SEMICOLON")
    {   Node * q;
        match("SEMICOLON");
        //checks if the file ends since it parses statements
        if(getTokenType() == "ENDFILE")
            break;
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
   /* if(getTokenType()!= "ENDFILE"&&getTokenType()=="READ")
    {
        readStmt();
    }*/
    program.rootptr= stmtSeq(); //Start the program
    program.treeParser(program.rootptr);
    std::cout<<outputString<<std::endl;
    return 0;
}