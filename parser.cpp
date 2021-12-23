#include "parser.h"

Node :: Node()
{
    for(int i = 0; i < CHILDREN ; ++i)
    {
        childrenNode[i] = nullptr; //Initialize all nodes by nullptr
    }
}
Node::Node(string t ,string shape)
{
    this->t = t;
    this->shape = shape;
}
//Token::Token(string strValue,string type )
//{
//    this->strValue = strValue;
//    this->type = type;
//}
void SyntaxTree::treeParser(Node * root)
{
    if(root == nullptr)
        return;
    outputString += addNode(root->tokenId,root->shape,root->t,root->subTitle); //Creating the node itself
    for(int i = 0; i < CHILDREN; i++)
    {
        Node * child = root->childrenNode[i];
        if(child == nullptr)
            break;
        //draw children
        treeParser(child);
        string dashed ="";
        //Else case
        if(i == 2)
        {
        dashed = "[style = \"dashed\"]";
        }
        outputString += addChild(root->tokenId,child->tokenId,dashed);

        if(i>0)
        {   Node * prevChild = root->childrenNode[i-1];
        //Link expressions with statements or expressions
           if(prevChild->shape == "oval")
            {
                outputString += addInvisibleLine(prevChild->tokenId,child->tokenId);
            }
            //Repeat case:
            else if(child->shape == "oval" && prevChild->shape == "rect")
            {
                 Node * lastNeighbor = prevChild; //Prevchild
                while(true)
                {   //Loop until the node with no neighbors
                    //if there's none break
                    if(lastNeighbor->neighbor == nullptr)
                        break;
                    lastNeighbor = lastNeighbor->neighbor;
                }

                    outputString += addInvisibleLine(lastNeighbor->tokenId, child->tokenId);
            }
            //Only comes here for if else case
            else if(i == 2) //last child (ELSE)
            {
                Node * lastNeighbor = prevChild; //Prevchild
                while(true)
                {   //Loop until the node with no neighbors
                    //if there's none break
                    if(lastNeighbor->neighbor == nullptr)
                        break;
                    lastNeighbor = lastNeighbor->neighbor;
                }

                    outputString += addInvisibleLine(lastNeighbor->tokenId, child->tokenId);
            }
        }
    }
    //then draw neighbors
    Node * neighbor = root->neighbor;
    if(neighbor != nullptr)
    {
        treeParser(neighbor);
        outputString += addNeighbour(root->tokenId, neighbor->tokenId);
    }
}
string getTokenType()
{   if(tokenCounter<inputTokens.size())
        return inputTokens[tokenCounter].type;
    return "ENDFILE";
}
string getSubTitle()
{
    return "("+inputTokens[tokenCounter].strValue+")";
}
string addNode(long long id, string shape, string title, string subtitle){
string funcOutput ="\n";
funcOutput += "node[shape =" + shape + " label=\"" + title + "\\n" + subtitle + "\"] " + to_string(id);
return funcOutput;
}
string addChild(long long parentId, long long childId,string dashed) {
  string funcOutput = "\n";
  funcOutput += to_string(parentId) + "--" + to_string(childId)+dashed;

  return funcOutput;
}
string addNeighbour(long long leftId, long long rightId) {
  string funcOutput = "\n";
  funcOutput += "{rank = same;"+to_string(leftId)+"; "+to_string(rightId)+";}"+ to_string(leftId) + "--" + to_string(rightId);
  return funcOutput;
}
string addInvisibleLine(long long leftId, long long rightId) {
  string funcOutput = "\n";
  funcOutput += "{rank = same;" + to_string(leftId) + "; " + to_string(rightId) + ";}" + to_string(leftId) + "--" + to_string(rightId) +"[style = invis];";
  return funcOutput;
}
vector <Token> parseFileText(string file)
{
    int fileLength = file.length();
    int j = 0;
    string temp = "";
    vector<Token> output;
    bool value = true;
    Token p;
    for(int i = 0; i <fileLength; ++i)
    {   
        i = file.find_first_not_of(inputParse,j);
        if(i == string::npos) break;
        if(i != string::npos)
        {
            j = file.find_first_of(inputParse,i);
            temp = file.substr(i,j-i);
            if(value)
               {
                p.strValue = temp;
                value = false;
                }
            else
            {
                p.type = temp;
                output.push_back(p);
                value = true;
            }
            i = j;
        }
    }
    /*for(auto i = output.begin();i !=output.end(); ++i)
    {

      cout<<(*i).strValue+", "+(*i).type+"\n";
    }*/
    
    return output;
}
string dotLang(vector<Token> input)
{   //Initializing global variables
    tokenCounter = 0;
    uniqueId = 0;
    outputString ="";
    inputTokens = input;
    //Actual program
    SyntaxTree program;
    program.rootptr= stmtSeq(); //Start the program
    program.treeParser(program.rootptr);
    return "graph main{"+outputString+"\n}";
}
int genId()
{
    return uniqueId++;
}
void error()
{
    cout<<"Error:incorrect token at token no."<<tokenCounter<<" statements not accepted!\n";
    exit(EXIT_FAILURE); //Stops the entire program
    //Add different error handling method later
}
void match(string token)
{
    if(token == getTokenType())
    {
        tokenCounter++;

    }
    else
    {
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
    string line;
    string fileText;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
    while ( getline (myfile,line) )
    {
        fileText+=line+"\n";
    }
    //cout<<fileText<<endl;
    //parseFileText(fileText);
    cout<< dotLang(parseFileText(fileText))<<endl;
    }
    else cout << "Unable to open file";
}
Node * factor()
{
    Node * t = new Node;
    if(getTokenType() == "OPENBRACKET")
    {
        match("OPENBRACKET");
        t = exp();
        match("CLOSEDBRACKET");
        return t;
    }
    else if (getTokenType() == "NUMBER")
    {
        t->subTitle = getSubTitle();
        match("NUMBER");
        t->t = "const";
        t->shape = "oval";
        t->tokenId = genId();
        return t;
    }
    else if(getTokenType() == "IDENTIFIER")
    {
        t->subTitle = getSubTitle();
        match("IDENTIFIER");
        t->t = "id";
        t->shape = "oval";
        t->tokenId = genId();
        return t;
    }
    else
        error();
    t->t="failed";
    t->tokenId=genId();
    t->subTitle="failedS";
    return t;
}
Node * term()
{
   Node * t = factor();
    while(getTokenType() == "MULT" || getTokenType() =="DIV")
    {  
        Node * p = new Node;
        p->childrenNode[0] = t;
        p->t = "op";
        t = p;
        t->subTitle= getSubTitle();            
        match(getTokenType());
        t->childrenNode[1] = factor();
        t->shape = "oval";
        t->tokenId= genId();
    }
     return t;

   

}
Node * simpleExp()
{   
    Node * t = term(); 
    while(getTokenType() == "MINUS" || getTokenType() =="PLUS")
    {  
        Node * p = new Node;
        p->childrenNode[0] = t;
        p->t = "op";
        t = p;
        t->subTitle= getSubTitle();            
        match(getTokenType());
        t->childrenNode[1] = term();
        t->shape = "oval";
        t->tokenId= genId();
    }
     return t;

   

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
    string tokenType = getTokenType();
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
        q = stmt(); // returns pointer ex if
        p->neighbor = q; //links read with  if as neighbors
        p = q; // moves variable p to q and starts over. seems like a linked list
    }
    return t; // returns root/start node
}
