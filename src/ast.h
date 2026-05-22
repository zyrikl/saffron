#ifndef AST_H
#define AST_H

#include <string>
#include <any>

class Token {
    public:
        const std::string FUNC       = "FUNC";
        const std::string LET        = "LET";
        const std::string IF         = "IF";
        const std::string ELSE       = "ELSE";
        const std::string WHILE      = "WHILE";
        const std::string RETURN     = "RETURN";
        const std::string BREAK      = "BREAK";
        const std::string CONTINUE   = "CONTINUE";
        const std::string CONST      = "CONST";
        const std::string STRUCT     = "STRUCT";
        const std::string TRUE       = "TRUE";
        const std::string FALSE      = "FALSE";
        const std::string SELF       = "SELF";
        const std::string ENUM       = "ENUM";
        const std::string USE        = "USE";
        const std::string PUBLIC     = "PUBLIC";
        const std::string FOR        = "FOR";
        const std::string IN         = "IN";
        const std::string AS         = "AS";
        const std::string HASH       = "HASH"; // #

        // Literals
        const std::string INT_LIT = "INT_LIT";
        const std::string STR_LIT = "STR_LIT";

        // Identifier
        const std::string IDENT = "IDENT";

        // Punctuation
        const std::string LPAREN    = "LPAREN";    // (
        const std::string RPAREN    = "RPAREN";    // )
        const std::string LBRACE    = "LBRACE";    // {
        const std::string RBRACE    = "RBRACE";    // }
        const std::string LBRACKET  = "LBRACKET";  // [
        const std::string RBRACKET  = "RBRACKET";  // ]
        const std::string SEMICOLON = "SEMICOLON"; // ;
        const std::string COLON     = "COLON";     // :
        const std::string COMMA     = "COMMA";     // ,
        const std::string DOT       = "DOT";       // .

        // Operators
        const std::string PLUS     = "PLUS";     // +
        const std::string MINUS    = "MINUS";    // -
        const std::string STAR     = "STAR";     // *
        const std::string SLASH    = "SLASH";    // /
        const std::string PERCENT  = "PERCENT";  // %
        const std::string PLUS_EQ  = "PLUS_EQ";  // +=
        const std::string MINUS_EQ = "MINUS_EQ"; // -=
        const std::string STAR_EQ  = "STAR_EQ";  // *=
        const std::string SLASH_EQ = "SLASH_EQ"; // /=
        const std::string EQ       = "EQ";      // =
        const std::string EQEQ     = "EQEQ";  // ==
        const std::string NEQ      = "NEQ";   // !=
        const std::string LT       = "LT";    // <
        const std::string GT       = "GT";    // >
        const std::string LTE      = "LTE";   // <=
        const std::string GTE      = "GTE";   // >=
        const std::string BANG     = "BANG";  // !
        const std::string AND      = "AND";   // &&
        const std::string OR       = "OR";    // ||
        const std::string AMP      = "AMP";   // &
        const std::string PIPE     = "PIPE";  // |

        // End of file
        const std::string EOF = "EOF";

        std::string type;
        std::any value;
        int line;
        int column;

        // Constructor declaration
        Token(std::string type, std::any value, int line, int column = 1);
        location();
        toString();
};

#endif // AST_H