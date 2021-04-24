// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    April 11, 2021
// Project: P2
// File:    parser.cpp

#include "parser.h"
#include "scanner.h"
#include <iostream>

std::ifstream in_file; // file to read
unsigned int lineNum = 1;  // for counting lines
Token tokey; // so many things are named around token so tokey it is

std::string tokes[] = { "BEGIN_TK","END_TK","LOOP_TK","WHILE_TK", "VOID_TK", "EXIT_TK", "GETTER_TK", "OUTTER_TK", "MAIN_TK", "IF_TK", "THEN_TK", "ASSIGN_TK", "DATA_TK", "PROC_TK", "EQUALS_TK", "EQUALS_OR_LESS_THAN_TK", "EQUALS_OR_GREAT_THAN_TK", "EQUALS_EQUALS_TK", "COLON_TK", "COLON_EQUALS_TK", "PLUS_TK", "MINUS_TK", "ASTERISK_TK", "SLASH_TK", "PERCENT_TK", "PERIOD_TK", "LEFT_PAREN_TK", "RIGHT_PAREN_TK", "COMMA_TK", "LEFT_BRACE_TK", "RIGHT_BRACE_TK", "SEMI_COLON_TK", "LEFT_BRACKET_TK", "RIGHT_BRACKET_TK", "ID_TK", "INT_TK", "EOF_TK", "ERROR_TK" };

// FOR DEBUGGING
bool debug = false;
bool debug2 = false;


// Start and end parser
Node* parser()
{
    if (debug) {std::cout << "parser" << "\n";}
    
    Node* node;  // root
    // calls the scanner to load the first token for parsing
    tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token1: " << tokey.token_string << "\n"; }
   
    // root node
    node = program();
    // Check for end of file
    if (tokey.token_ID == EOF_TK)
    {
        std::cout << "Parsing completed!" << std::endl;
        return node; //return root
    }
    // error, no eof token
    else
        error1(EOF_TK, tokey);
}

// <program>  ->     <vars> main <block>
Node* program() {
    if (debug) {std::cout << "program" << "\n";} // for debugging
    int depth = 0;

    Node* node = new Node("<program>", depth);  // program node

    node->child_1 = vars(depth); // child vars node
    if (tokey.token_ID == MAIN_TK)  // check for main node
    {
        node->token_1 = tokey;  //insert token
        tokey = scanner(in_file, lineNum);  // scan for next token
        if (debug2) { std::cout << "Working on token2: " << tokey.token_string << "\n"; }  // for debugging
        node->child_2 = block(depth); 

    }
    else
        error1(MAIN_TK, tokey);
    return node; // 4-11 fix
}


// <block>       ->      begin <vars> <stats> end
Node* block(unsigned int depth) {
    if (debug) {std::cout << "block" << "\n";}  // for debugging
    depth++;
    Node* node = new Node("<block>", depth);
    // check for begin token
    if (tokey.token_ID == BEGIN_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token3: " << tokey.token_string << "\n"; }// for debugging
        node->child_1 = vars(depth);  // child node
        node->child_2 = stats(depth);
        
        if (tokey.token_ID == END_TK)
        {
            node->token_2 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token4: " << tokey.token_string << "\n"; }  // for debugging
            
            return node;
        }
        else
            error1(END_TK, tokey);
    }
    else
        error1(BEGIN_TK, tokey);
}

// <vars>         ->      empty | data Identifier :=  Integer  ;  <vars> 
Node* vars(unsigned int depth)
{
    if (debug) {std::cout << "vars" << "\n";} // debugging
    depth++;
    // vars node
    Node* node = new Node("<vars>", depth);

    if (tokey.token_ID == DATA_TK)
    {
        //node->token_1 = tokey;
        tokey = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token5: " << tokey.token_string << "\n"; }  // for debugging
        if (tokey.token_ID == ID_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum);
            if (debug2) { std::cout << "Working on token6: " << tokey.token_string << "\n"; }  // for debugging
            if (tokey.token_ID == COLON_EQUALS_TK)
            {
                node->token_3 = tokey;
                tokey = scanner(in_file, lineNum);
                if (debug2) { std::cout << "Working on token7: " << tokey.token_string << "\n"; }  // for debugging
                if (tokey.token_ID == INT_TK)
                {
                    node->token_4 = tokey;
                    tokey = scanner(in_file, lineNum);
                    if (debug2) { std::cout << "Working on token8: " << tokey.token_string << "\n"; }  // for debugging
                    if (tokey.token_ID == SEMI_COLON_TK)
                    {
                        node->token_5 = tokey; // 4-11 fix
                        tokey = scanner(in_file, lineNum);
                        if (debug2) { std::cout << "Working on token9: " << tokey.token_string << "\n"; }  // for debugging
                        node->child_1 = vars(depth);
                        return node;
                    }
                    else {
                        if (debug) { std::cout << "yep" << "\n"; }
                        error1(SEMI_COLON_TK, tokey);
                    }
                }
                else
                    error1(INT_TK, tokey);
            }
            else
                error1(COLON_EQUALS_TK, tokey);
        }
        else
            error1(ID_TK, tokey);
    }
    // empty is ok
    else
        return NULL;
}

// <expr>        ->      <N> - <expr>  | <N>
Node* expr(unsigned int depth)
{
    if (debug) {std::cout << "expr" << "\n";}
    depth++;
    Node* node = new Node("<expr>", depth);
    
    node->child_1 = n(depth);
    // check for minus sign
    if (tokey.token_ID == MINUS_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token11: " << tokey.token_string << "\n"; }  // for debugging
        node->child_2 = expr(depth);
        return node;
    }
    else
        return node;
}

// <N>             ->       <A> / <N> | <A> * <N> | <A>
Node* n(unsigned int depth)
{
    if (debug) {std::cout << "n" << "\n";}
    depth++;
    Node* node = new Node("<N>", depth);
    node->child_1 = a(depth);
    // check for slash token
    if (tokey.token_ID == SLASH_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token12: " << tokey.token_string << "\n"; }  // for debugging
        node->child_2 = n(depth);
        return node;
    }
    // check for asterisk token
    else if (tokey.token_ID == ASTERISK_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token13: " << tokey.token_string << "\n"; }  // for debugging
        node->child_2 = n(depth);
        return node;
    }
    else
        return node;
}

// <A>             ->        <M> + <A> | <M>
Node* a(unsigned int depth)
{
    if (debug) {std::cout << "a" << "\n";}  // for debugging
    depth++;
    Node* node = new Node("<A>", depth);
    /* children are <M> and <A> or just <M> */
    node->child_1 = m(depth);
    if (tokey.token_ID == PLUS_TK)
    {
        /* store operator */
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token14: " << tokey.token_string << "\n"; }  // for debugging
        node->child_2 = a(depth);
        return node;
    }
    else { //4-11 fix
        return node;
    }// 4-11 fix
        
}

// <M>              ->     * <M> |  <R>
Node* m(unsigned int depth)
{
    if (debug) {std::cout << "m" << "\n";}  // for debugging
    depth++;
    Node* node = new Node("<M>", depth);
    if (tokey.token_ID == ASTERISK_TK)
    {
        /* strore operator */
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token15: " << tokey.token_string << "\n"; }  // for debugging
        node->child_1 = m(depth);
        return node;
    }
    else
    {
        node->child_1 = r(depth);
        return node;        
    }
}

// <R>              ->      ( <expr> ) | Identifier | Integer
Node* r(unsigned int depth)
{
    if (debug) {std::cout << "r" << "\n";}  // for debugging
    depth++;
    Node* node = new Node("<R>", depth);
    //tk = scanner(in_file, lineNum);
    if (tokey.token_ID == LEFT_PAREN_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token16: " << tokey.token_string << "\n"; }  // for debugging
        node->child_1 = expr(depth);
        
        if (tokey.token_ID == RIGHT_PAREN_TK)
        {
            node->token_2 = tokey;

            tokey = scanner(in_file, lineNum);  if (debug2) { std::cout << "Working on token17: " << tokey.token_string << "\n"; }  // for debugging
            return node;
        }
        else
            error1(RIGHT_PAREN_TK, tokey);
    }
    else if (tokey.token_ID == ID_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token18: " << tokey.token_string << "\n"; }  // for debugging
        
        return node;
    }
    else if (tokey.token_ID == INT_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token19: " << tokey.token_string << "\n"; }  // for debugging
        return node;
    }
    else
        error3(LEFT_PAREN_TK, ID_TK, INT_TK, tokey);
}

// <stats>         ->      <stat>  <mStat>
Node* stats(unsigned int depth)
{
    if (debug) {std::cout << "stats" << "\n";}  // for debugging
    depth++;
    Node* node = new Node("<stats>", depth);
    node->child_1 = stat(depth);
    node->child_2 = mstat(depth);
    return node;
}

// <mStat>       ->      empty |  <stat>  <mStat>
Node* mstat(unsigned int depth)
{
    if (debug) {std::cout << "mstat" << "\n";}  // for debugging
    depth++;
    Node* node = new Node("<mstat>", depth);

    if (tokey.token_ID == GETTER_TK || tokey.token_ID == OUTTER_TK || tokey.token_ID == BEGIN_TK || tokey.token_ID == IF_TK || tokey.token_ID == LOOP_TK || tokey.token_ID == PROC_TK || tokey.token_ID == ASSIGN_TK || tokey.token_ID == VOID_TK)
    {
        if (debug2) { std::cout << "STill working on: " << tokey.token_string << "\n"; }
        node->child_1 = stat(depth);
        node->child_2 = mstat(depth);
        return node;
    }
    else
        return node;
}

// <stat>           ->      <in> ;  | <out> ;  | <block> | <if> ;  | <loop> ;  | <assign> ; | <goto> ; | <label> ;
Node* stat(unsigned int depth)
{
    if (debug) {std::cout << "stat" << "\n";}  // for debugging
    depth++;
    Node* node = new Node("<stat>", depth);
    

    if(tokey.token_ID == GETTER_TK)
    {
        node->child_1 = in(depth);
        if (tokey.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token22: " << tokey.token_string << "\n"; }  // for debugging
            return node;

        }
        else
            error1(SEMI_COLON_TK, tokey);
    }
    else if(tokey.token_ID == OUTTER_TK)
    {
        if (debug) { std::cout << "out= tru" << "\n"; }  // for debugging
        node->child_1 = out(depth);
        // check for ; token
        if (tokey.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token24: " << tokey.token_string << "\n"; }  // for debugging
            return node;

        }
        else
            error1(SEMI_COLON_TK, tokey);
    }
    else if(tokey.token_ID == BEGIN_TK)
    {
        node->child_1 = block(depth);
        return node;

    }
    else if(tokey.token_ID == IF_TK)
    {
        node->child_1 = iff(depth);
        //tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token27: " << tk.token_string << "\n"; }
        if (tokey.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token28: " << tokey.token_string << "\n"; }
            return node;

        }
        else
            error1(SEMI_COLON_TK, tokey);
    }
    else if (tokey.token_ID == LOOP_TK)
    {
        node->child_1 = loop(depth);
        //tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token29: " << tk.token_string << "\n"; }
        if (tokey.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token31: " << tokey.token_string << "\n"; }
            return node;

        }
        else
            error1(SEMI_COLON_TK, tokey);
    }
    else if (tokey.token_ID == ASSIGN_TK)
    {
        node->child_1 = assign(depth);
        //tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token34: " << tk.token_string << "\n"; }
        if (tokey.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token35: " << tokey.token_string << "\n"; }
            return node;

        }
        else
            error1(SEMI_COLON_TK, tokey);
    }
    else if (tokey.token_ID == PROC_TK)
    {
        node->child_1 = gotoo(depth);
        //tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token32: " << tk.token_string << "\n"; }
        if (tokey.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token33: " << tokey.token_string << "\n"; }
            return node;

        }
        else
            error1(SEMI_COLON_TK, tokey);
    }

    else
        error_mult(tokey);
}

// <in>              ->      getter  Identifier  
Node* in(unsigned int depth)
{
    if (debug) {std::cout << "in" << "\n";}
    depth++;
    Node* node = new Node("<in>", depth);
    if(tokey.token_ID == GETTER_TK)
    {
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token36: " << tokey.token_string << "\n"; }
        if(tokey.token_ID == ID_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum);   // i think this should uncommented //
            return node;

        }
        else
            error1(ID_TK, tokey);
    }
    else
        error1(GETTER_TK, tokey);
}

// <out>            ->      outter <expr>
Node* out(unsigned int depth)
{
    if (debug) {std::cout << "out" << "\n";}
    depth++;
    Node* node = new Node("<out>", depth);
    if (tokey.token_ID == OUTTER_TK)
    {

        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token37: " << tokey.token_string << "\n"; } //working before this
        node->child_1 = expr(depth);
        return node;
    }
    else
        error1(OUTTER_TK, tokey);
}

// <if>               ->      if [ <expr> <RO> <expr> ] then <stat>
Node* iff(unsigned int depth)
{
    if (debug) { std::cout << "if" << "\n"; }
    depth++;
    Node* node = new Node("<if>", depth);
    if (tokey.token_ID == IF_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token38: " << tokey.token_string << "\n"; }
        if (tokey.token_ID == LEFT_BRACKET_TK)
        {
            node->token_2 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token39: " << tokey.token_string << "\n"; }
            node->child_1 = expr(depth);
            node->child_2 = ro(depth);
            node->child_3 = expr(depth);
            if (tokey.token_ID == RIGHT_BRACKET_TK)
            {
                node->token_3 = tokey;
                if (tokey.token_ID == THEN_TK)
                {
                    node->token_4 = tokey;
                    tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token40: " << tokey.token_string << "\n"; }
                    node->child_4 = stat(depth);
                    return node;
                }
                else
                    error1(THEN_TK, tokey);
            }
            else
                error1(RIGHT_BRACKET_TK, tokey);
        }
        else
            error1(LEFT_BRACKET_TK, tokey);
    }
    else
        error1(LOOP_TK, tokey);
}



// <loop>          ->      loop  [ <expr> <RO> <expr> ]  <stat>
Node* loop(unsigned int depth)
{
    if (debug) {std::cout << "loop" << "\n";}
    depth++;
    Node* node = new Node("<loop>", depth);
    if(tokey.token_ID == LOOP_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token38: " << tokey.token_string << "\n"; }
        if(tokey.token_ID == LEFT_BRACKET_TK)
        {
            node->token_2 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token39: " << tokey.token_string << "\n"; }
            node->child_1 = expr(depth);
            node->child_2 = ro(depth);
            node->child_3 = expr(depth);
            if(tokey.token_ID == RIGHT_BRACKET_TK)
            {
                node->token_3 = tokey;
                tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token40: " << tokey.token_string << "\n"; }
                node->child_4 = stat(depth);
                return node;
            }
            else
                error1(RIGHT_BRACKET_TK, tokey);
        }
        else
            error1(LEFT_BRACKET_TK, tokey);
    }
    else
        error1(LOOP_TK, tokey);
}

// <assign>       ->      assign Identifier  := <expr>  
Node* assign(unsigned int depth)
{
    if (debug) {std::cout << "assign" << "\n";}
    depth++;
    Node* node = new Node("<assign>", depth);
    //tk = scanner(in_file, lineNum);
    if (tokey.token_ID == ASSIGN_TK)
    {
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token49: " << tokey.token_string << "\n"; }
        if (tokey.token_ID == ID_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token41: " << tokey.token_string << "\n"; }
            if (tokey.token_ID == COLON_EQUALS_TK)
            {
                tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token42: " << tokey.token_string << "\n"; }
                node->child_1 = expr(depth);
                return node;


            }
            else
                error1(COLON_EQUALS_TK, tokey);
        }
        else
            error1(ID_TK, tokey);
    }
    else
        error1(ASSIGN_TK, tokey);
}

// <RO>            ->       =>  | =< |  ==  |   [ == ]  (three tokens)  | %
Node* ro(unsigned int depth)
{
    if (debug) {std::cout << "ro" << "\n";}
    depth++;
    Node* node = new Node("<RO>", depth);

    if (tokey.token_ID == EQUALS_OR_LESS_THAN_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token49: " << tokey.token_string << "\n"; }
        return node;
    }

    else if (tokey.token_ID == EQUALS_OR_GREAT_THAN_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token49: " << tokey.token_string << "\n"; }
        return node;
    }
    else if (tokey.token_ID == EQUALS_EQUALS_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token49: " << tokey.token_string << "\n"; }
        return node;
    }
    else if (tokey.token_ID == PERCENT_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token49: " << tokey.token_string << "\n"; }
        return node;
    }
    else if (tokey.token_ID == LEFT_BRACKET_TK)
    {
        node->token_1 = tokey;
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token49: " << tokey.token_string << "\n"; }
        if (tokey.token_ID == EQUALS_EQUALS_TK)
        {
            node->token_2 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token41: " << tokey.token_string << "\n"; }
            if (tokey.token_ID == RIGHT_BRACKET_TK)
            {
                // take any 3 tokens
                node->token_3 = tokey;
                tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token61: " << tokey.token_string << "\n"; }
                node->token_4 = tokey;
                tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token62: " << tokey.token_string << "\n"; }
                node->token_5 = tokey;
                tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token63: " << tokey.token_string << "\n"; }
                node->token_6 = tokey;
                return node;


            }
            else
                error1(RIGHT_BRACKET_TK, tokey);
        }
        else
            error1(EQUALS_EQUALS_TK, tokey);
    }
    
    else
        error_mult(tokey);

}
// <label>          ->    void Identifier
Node* label(unsigned int depth)
{
    if (debug) {std::cout << "label" << "\n";}
    depth++;
    Node* node = new Node("<label>", depth);
    if (tokey.token_ID == VOID_TK)
    {
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token45: " << tokey.token_string << "\n"; }
        if (tokey.token_ID == ID_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token46: " << tokey.token_string << "\n"; }
            return node;

        }
        else
            error1(ID_TK, tokey);
    }
    else
        error1(VOID_TK, tokey);
}

// <goto>           ->    proc Identifier
Node* gotoo(unsigned int depth)
{
    if (debug) {std::cout << "gotoo" << "\n";}
    depth++;
    Node* node = new Node("<goto>", depth);
    if (tokey.token_ID == PROC_TK)
    {
        tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token47: " << tokey.token_string << "\n"; }
        if (tokey.token_ID == ID_TK)
        {
            node->token_1 = tokey;
            tokey = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token48: " << tokey.token_string << "\n"; }
            return node;

        }
        else
            error1(ID_TK, tokey);
    }
    else
        error1(PROC_TK, tokey);
}




//error for single token
void error1(tokens need, Token got)
{
    std::cout << "!!! ERROR !!!" << std::endl;
    std::cout << "Needed token: " << tokes[need] << std::endl;
    std::cout << "Got token: " << tokes[got.token_ID];
    std::cout << " LINE NUMBER: " << got.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

// error for 2 tokens
void error2(tokens need_1, tokens need_2, Token got)
{
    std::cout << "!!! ERROR !!!" << std::endl;
    std::cout << "Needed tokens: " << tokes[need_1] << " or " << tokes[need_2] << std::endl;
    std::cout << "Got token: " << tokes[got.token_ID];
    std::cout << " LINE NUMBER: " << got.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

// error for 3 tokens
void error3(tokens need_1, tokens need_2, tokens need_3, Token got)
{
    std::cout << "!!! ERROR !!!" << std::endl;
    std::cout << "Needed tokens: " << tokes[need_1] << ", " << tokes[need_2];
    std::cout << ", or " << tokes[need_3] << std::endl;
    std::cout << "Got token: " << tokes[got.token_ID];
    std::cout << " LINE NUMBER: " << got.lineNum << std::endl;
    exit(EXIT_FAILURE);
}
// multiple tokens (4+) error
void error_mult(Token recieved)
{
    std::cout << "Token did not follow rule: " << tokes[recieved.token_ID];
    std::cout << " LINE NUMBER: " << recieved.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

void print_tree(Node* node)
{
    if(node == nullptr)
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }
    else
    {
        std::string indents((node->depth * 2), ' ');
        std::cout << indents;
        std::cout << node->name << "  ";
        std::cout << node->token_1.token_string << " " << node->token_2.token_string << " " << node->token_3.token_string << " " << node->token_4.token_string << " " << node->token_5.token_string << " " << node->token_6.token_string << std::endl;

        if(node->child_1 != nullptr)
            print_tree(node->child_1);
        if(node->child_2 != nullptr)
            print_tree(node->child_2);
        if(node->child_3 != nullptr)
            print_tree(node->child_3);
        if(node->child_4 != nullptr)
            print_tree(node->child_4);
    }
    return;
}