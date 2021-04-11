#include "parser.h"
#include "scanner.h"
#include <iostream>

/*Globals*/
/* File to be scanned and parsed */
std::ifstream in_file;
/* Line number in in_file */
unsigned int lineNum = 1;
/* Current working token */
Token tk;

/* Array of strings mapped to token_id enum */
std::string tokes[] = { "BEGIN_TK","END_TK","LOOP_TK","WHILE_TK", "VOID_TK", "EXIT_TK", "GETTER_TK", "OUTTER_TK", "MAIN_TK", "IF_TK", "THEN_TK", "ASSIGN_TK", "DATA_TK", "PROC_TK", "EQUALS_TK", "EQUALS_OR_LESS_THAN_TK", "EQUALS_OR_GREAT_THAN_TK", "EQUALS_EQUALS_TK", "COLON_TK", "COLON_EQUALS_TK", "PLUS_TK", "MINUS_TK", "ASTERISK_TK", "SLASH_TK", "PERCENT_TK", "PERIOD_TK", "LEFT_PAREN_TK", "RIGHT_PAREN_TK", "COMMA_TK", "LEFT_BRACE_TK", "RIGHT_BRACE_TK", "SEMI_COLON_TK", "LEFT_BRACKET_TK", "RIGHT_BRACKET_TK", "ID_TK", "INT_TK", "EOF_TK", "ERROR_TK" };

bool debug = true;
bool debug2 = true;


/* Main parsing function called from main */
Node* parser()
{
    if (debug) {std::cout << "parser" << "\n";}
    /* creating the root node */
    Node* node;
    /* scanning for the first token */
    tk = scanner(in_file, lineNum);
    if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
    /* calling first non-terminal function */
    node = program();
    /* check for EOF tk */
    if (tk.token_ID == EOF_TK)
    {
        /* no errors and EOF tk recieved so parse was successful */
        std::cout << "Parse Success" << std::endl;
        /* return root node */
        return node;
    }
    /* unexpected token recieved */
    else
        error(EOF_TK, tk);
}

/* Function for <program> -> void <vars> <block> */
Node* program()
{
    if (debug) {std::cout << "program" << "\n";}
    /* depth of node in tree */
    int depth = 0;
    /* creating a node for <program> */
    Node* node = new Node("<program>", depth);

    node->child_1 = vars(depth);
    if (tk.token_ID == MAIN_TK)
    {
        /* scan for next token */
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        node->child_2 = block(depth);
        /* return node with attached children */
        return node;
    }
    else
        error(MAIN_TK, tk);
}


/* Non-terminal function for <block> -> begin <vars> <stats> end */
Node* block(int depth)
{
    if (debug) {std::cout << "block" << "\n";}
    depth++;
    Node* node = new Node("<block>", depth);
    /* predict: begin <vars> <stats> end */
    if (tk.token_ID == BEGIN_TK)
    {
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        /* children are <vars> and <stats> */
        node->child_1 = vars(depth);
        node->child_2 = stats(depth);
        if (tk.token_ID == END_TK)
        {
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            
            return node;
        }
        else
            error(END_TK, tk);
    }
    else
        error(BEGIN_TK, tk);
}

/* Function for <vars> -> empty | let Identifier = Integer <vars> */
Node* vars(int depth)
{
    if (debug) {std::cout << "vars" << "\n";}
    /* increase depth */
    depth++;
    /* create <vars> node */
    Node* node = new Node("<vars>", depth);

    if (tk.token_ID == DATA_TK)
    {
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == ID_TK)
        {
            /* store identifier token*/
            node->token_1 = tk;
            tk = scanner(in_file, lineNum);
            if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            if (tk.token_ID == COLON_EQUALS_TK)
            {
                tk = scanner(in_file, lineNum);
                if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
                if (tk.token_ID == INT_TK)
                {
                    /* store integer token */
                    node->token_2 = tk;
                    tk = scanner(in_file, lineNum);
                    if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
                    if (tk.token_ID == SEMI_COLON_TK)
                    {
                        tk = scanner(in_file, lineNum);
                        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
                        /* child is <vars> */
                        node->child_1 = vars(depth);
                        return node;
                    }
                    else {
                        if (debug) { std::cout << "yep" << "\n"; }
                        error(SEMI_COLON_TK, tk);
                    }
                }
                else
                    error(INT_TK, tk);
            }
            else
                error(COLON_EQUALS_TK, tk);
        }
        else
            error(ID_TK, tk);
    }
    /* empty production */
    else
        return nullptr;
}

/* Non-terminal function for <expr> -> <A> / <expr> | <A> * <expr> | <A> */
Node* expr(int depth)
{
    if (debug) {std::cout << "expr" << "\n";}
    depth++;
    Node* node = new Node("<expr>", depth);
    /* children are <a> and <expr> or just <a> */
    node->child_1 = n(depth);
    /* predict: / <expr> */
    if (tk.token_ID == MINUS_TK)
    {
        /* store operator */
        node->token_1 = tk;
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        node->child_2 = expr(depth);
        return node;
    }
    else
        return node;
}

/* Non-terminal function for <M> -> <M> + <A> | <M> - <A> | <M> */
Node* n(int depth)
{
    if (debug) {std::cout << "n" << "\n";}
    depth++;
    Node* node = new Node("<N>", depth);
    /* children are <M> and <A> or just <M> */
    node->child_1 = a(depth);
    if (tk.token_ID == SLASH_TK)
    {
        /* store operator */
        node->token_1 = tk;
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        node->child_2 = n(depth);
        return node;
    }
    else if (tk.token_ID == ASTERISK_TK)
    {
        /* store operator */
        node->token_1 = tk;
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        node->child_2 = n(depth);
        return node;
    }
    else
        return node;
}

/* Non-terminal function for <M> -> <M> + <A> | <M> - <A> | <M> */
Node* a(int depth)
{
    if (debug) {std::cout << "a" << "\n";}
    depth++;
    Node* node = new Node("<A>", depth);
    /* children are <M> and <A> or just <M> */
    node->child_1 = m(depth);
    if (tk.token_ID == PLUS_TK)
    {
        /* store operator */
        node->token_1 = tk;
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        node->child_2 = a(depth);
        return node;
    }
    else
        return node;
}

/* Non-terminal function for <M> -> * <M> |  <R> */
Node* m(int depth)
{
    if (debug) {std::cout << "m" << "\n";}
    depth++;
    Node* node = new Node("<M>", depth);
    if (tk.token_ID == ASTERISK_TK)
    {
        /* strore operator */
        node->token_1 = tk;
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        node->child_1 = m(depth);
        return node;
    }
    else
    {
        node->child_1 = r(depth);
        return node;        
    }
}

/* Non-terminal function for <R> -> ( <expr> ) | Identifier | Integer */
Node* r(int depth)
{
    if (debug) {std::cout << "r" << "\n";}
    depth++;
    Node* node = new Node("<R>", depth);
    //tk = scanner(in_file, lineNum);
    if (tk.token_ID == LEFT_PAREN_TK)
    {
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        node->child_1 = expr(depth);
        
        if (tk.token_ID == RIGHT_PAREN_TK)
        {
            tk = scanner(in_file, lineNum);
            if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;
        }
        else
            error(RIGHT_PAREN_TK, tk);
    }
    else if (tk.token_ID == ID_TK)
    {
        node->token_1 = tk;
        tk = scanner(in_file, lineNum);
        if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        return node;
    }
    else if (tk.token_ID == INT_TK)
    {
        node->token_1 = tk;
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        return node;
    }
    else
        error(LEFT_PAREN_TK, ID_TK, INT_TK, tk);
}

/* Non-terminal function for <stats> -> <stat>  <mStat> */
Node* stats(int depth)
{
    if (debug) {std::cout << "stats" << "\n";}
    depth++;
    Node* node = new Node("<stats>", depth);
    node->child_1 = stat(depth);
    node->child_2 = mstat(depth);
    return node;
}

/* Non-terminal function for <mstat> -> empty |  <stat>  <mStat> */
Node* mstat(int depth)
{
    if (debug) {std::cout << "mstat" << "\n";}
    depth++;
    Node* node = new Node("<mstat>", depth);
    if (is_stat(tk.token_ID))
    {
        std::cout << "stat = true" << "\n";
        node->child_1 = stat(depth);
        node->child_2 = mstat(depth);
        return node;
    }
    else
        return nullptr;
}

/* Non-terminal function for <stat> -> <in> | <out> | <block> | <cond> | <loop> | <assign> */
Node* stat(int depth)
{
    if (debug) {std::cout << "stat" << "\n";}
    depth++;
    Node* node = new Node("<stat>", depth);
    

    if(tk.token_ID == GETTER_TK)
    {
        node->child_1 = in(depth);
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(SEMI_COLON_TK, tk);
    }
    else if(tk.token_ID == OUTTER_TK)
    {
        if (debug) { std::cout << "out= tru" << "\n"; }
        node->child_1 = out(depth);
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(SEMI_COLON_TK, tk);
    }
    else if(tk.token_ID == BEGIN_TK)
    {
        node->child_1 = block(depth);
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(SEMI_COLON_TK, tk);
    }
    else if(tk.token_ID == ID_TK)
    {
        node->child_1 = assign(depth);
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(SEMI_COLON_TK, tk);
    }
    else if (tk.token_ID == LOOP_TK)
    {
        node->child_1 = loop(depth);
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(SEMI_COLON_TK, tk);
    }
    else if (tk.token_ID == PROC_TK)
    {
        node->child_1 = gotoo(depth);
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(SEMI_COLON_TK, tk);
    }
    else if (tk.token_ID == VOID_TK)
    {
        node->child_1 = label(depth);
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(SEMI_COLON_TK, tk);
    }
    else
        error_stat(tk);
}

/* Non-terminal function for <in> -> read ( Identifier ) : */
Node* in(int depth)
{
    if (debug) {std::cout << "in" << "\n";}
    depth++;
    Node* node = new Node("<in>", depth);
    if(tk.token_ID == GETTER_TK)
    {
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if(tk.token_ID == ID_TK)
        {
            node->token_1 = tk;
            //tk = scanner(in_file, lineNum);
            return node;

        }
        else
            error(ID_TK, tk);
    }
    else
        error(GETTER_TK, tk);
}

/* Non-terminal function for <out> -> print ( <expr>  ) : */
Node* out(int depth)
{
    if (debug) {std::cout << "out" << "\n";}
    depth++;
    Node* node = new Node("<out>", depth);
    if (tk.token_ID == OUTTER_TK)
    {
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        //tk = scanner(in_file, lineNum);
        node->child_1 = expr(depth);
        return node;
    }
    else
        error(OUTTER_TK, tk);
}


/* Non-terminal function for <loop> -> iter ( <expr> <RO> <expr> ) <stat> */
Node* loop(int depth)
{
    if (debug) {std::cout << "loop" << "\n";}
    depth++;
    Node* node = new Node("<loop>", depth);
    if(tk.token_ID == LOOP_TK)
    {
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if(tk.token_ID == LEFT_PAREN_TK)
        {
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            node->child_1 = expr(depth);
            node->child_2 = ro(depth);
            node->child_3 = expr(depth);
            if(tk.token_ID == RIGHT_PAREN_TK)
            {
                tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
                node->child_4 = stat(depth);
                return node;
            }
            else
                error(RIGHT_PAREN_TK, tk);
        }
        else
            error(LEFT_PAREN_TK, tk);
    }
    else
        error(LOOP_TK, tk);
}

/* Non-terminal function for <assign> -> Identifier  = <expr> : */
Node* assign(int depth)
{
    if (debug) {std::cout << "assign" << "\n";}
    depth++;
    Node* node = new Node("<assign>", depth);
    //tk = scanner(in_file, lineNum);
    if (tk.token_ID == ASSIGN_TK)
    {
        if (tk.token_ID == ID_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            if (tk.token_ID == COLON_EQUALS_TK)
            {
                tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
                node->child_1 = expr(depth);
                return node;


            }
            else
                error(COLON_EQUALS_TK, tk);
        }
        else
            error(ID_TK, tk);
    }
    else
        error(ASSIGN_TK, tk);
}

/* Non-terminal function for <RO> ->  < | <  = | > | >  = | =  = | = */
Node* ro(int depth)
{
    if (debug) {std::cout << "ro" << "\n";}
    depth++;
    Node* node = new Node("<RO>", depth);
    if(is_ro(tk.token_ID))
    {
        node->token_1 = tk;
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if(tk.token_ID == EQUALS_TK)
        {
            node->token_2 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;
        }
        else
            return node;
    }
    else
        error(EQUALS_OR_LESS_THAN_TK, EQUALS_OR_GREAT_THAN_TK, EQUALS_TK, tk);
}
/* Non-terminal function for <in> -> read ( Identifier ) : */
Node* label(int depth)
{
    if (debug) {std::cout << "label" << "\n";}
    depth++;
    Node* node = new Node("<label>", depth);
    if (tk.token_ID == VOID_TK)
    {
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == ID_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(ID_TK, tk);
    }
    else
        error(VOID_TK, tk);
}

/* Non-terminal function for <in> -> read ( Identifier ) : */
Node* gotoo(int depth)
{
    if (debug) {std::cout << "gotoo" << "\n";}
    depth++;
    Node* node = new Node("<goto>", depth);
    if (tk.token_ID == PROC_TK)
    {
        tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
        if (tk.token_ID == ID_TK)
        {
            node->token_1 = tk;
            tk = scanner(in_file, lineNum); if (debug2) { std::cout << "Working on token: " << tk.token_string << "\n"; }
            return node;

        }
        else
            error(ID_TK, tk);
    }
    else
        error(PROC_TK, tk);
}




/* error function for single expected token */
void error(tokens expected, Token recieved)
{
    std::cout << "parsing error" << std::endl;
    std::cout << "expected token: " << tokes[expected] << std::endl;
    std::cout << "recieved token: " << tokes[recieved.token_ID];
    std::cout << " at line: " << recieved.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

/* error function for two expected tokens */
void error(tokens expected1, tokens expected2, Token recieved)
{
    std::cout << "parsing error" << std::endl;
    std::cout << "expected tokens: " << tokes[expected1] << " or " << tokes[expected2] << std::endl;
    std::cout << "recieved token: " << tokes[recieved.token_ID];
    std::cout << " at line: " << recieved.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

/* error function for three expected tokens */
void error(tokens expected1, tokens expected2, tokens expected3, Token recieved)
{
    std::cout << "parsing error" << std::endl;
    std::cout << "expected tokens: " << tokes[expected1] << ", " << tokes[expected2];
    std::cout << ", or " << tokes[expected3] << std::endl;
    std::cout << "recieved token: " << tokes[recieved.token_ID];
    std::cout << " at line: " << recieved.lineNum << std::endl;
    exit(EXIT_FAILURE);
}
/* error function for expected statement token */
void error_stat(Token recieved)
{
    std::cout << "Parsing Error" << std::endl;
    std::cout << "Expected tokens: " << tokes[GETTER_TK] << ", " << tokes[OUTTER_TK];
    std::cout << ", " << tokes[BEGIN_TK] << ", " << tokes[IF_TK]; 
    std::cout << ", " << tokes[WHILE_TK] << ", or " << tokes[ID_TK] << std::endl;
    std::cout << "Recieved token: " << tokes[recieved.token_ID];
    std::cout << " At line: " << recieved.lineNum << std::endl;
    exit(EXIT_FAILURE);
}
/* function to determine if token is a statement token */
bool is_stat(tokens tk)
{
    if (tk == GETTER_TK || tk == OUTTER_TK || tk == BEGIN_TK || tk == IF_TK || tk == WHILE_TK || tk == ID_TK)
        return true;
    else
        return false;
}

bool is_ro(tokens tk)
{
    if (tk == EQUALS_OR_LESS_THAN_TK || tk == EQUALS_OR_GREAT_THAN_TK || tk == EQUALS_TK)
        return true;
    else
        return false;
}

void print_tree(Node* node)
{
    if(node == nullptr)
    {
        std::cout << "<Empty Tree>" << std::endl;
        return;
    }
    else
    {
        std::string indents((node->depth * 2), ' ');
        std::cout << indents;
        std::cout << node->name << "  ";
        std::cout << node->token_1.token_string << "  " << node->token_2.token_string; 
        std::cout << std::endl;

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