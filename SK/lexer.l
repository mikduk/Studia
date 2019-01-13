%option noyywrap
%option yylineno
%{
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
%}

%x COMMENT

%%

"["		{ BEGIN(COMMENT);	}
<COMMENT>"]"	{ BEGIN(INITIAL);	}
<COMMENT>(\n|.)
<COMMENT><<EOF>> { printf("Błąd: niezakończony komentarz.\n"); yyterminate(); }

"DECLARE"	{ return DECLARE;	}
"IN"		{ return IN;		}
"END"		{ return END;		}

";"		{ return SEM;		}
"("		{ return LB;		}
":"		{ return CLN;		}
")"		{ return RB;		}

":="		{ return ASG;		}
"IF"		{ return IF;		}
"THEN"		{ return THEN;		}
"ELSE"		{ return ELSE;		}
"ENDIF"		{ return ENDIF;		}
"WHILE"		{ return WHILE;		}
"ENDWHILE"	{ return ENDWHILE;	}
"FOR"		{ return FOR;		}
"FROM"		{ return FROM;		}
"TO"		{ return TO;		}
"DO"		{ return DO;		}
"ENDDO"		{ return ENDDO;		}
"ENDFOR"	{ return ENDFOR;	}
"DOWNTO"	{ return DOWNTO;	}
"WRITE"		{ return WRITE;		}
"READ"		{ return READ;		}

"+"		{ return ADD;		}
"-"		{ return SUB;		}
"*"		{ return MUL;		}
"/"		{ return DIV;		}
"%"		{ return MOD;		}

"="		{ return EQUAL;		}
"!="		{ return NOT_EQUAL;	}
"<"		{ return LT;		}
">"		{ return GT;		}
"<="		{ return LE;		}
">="		{ return GE;		}


[0-9]+	{ yylval.str = (char *)strdup(yytext);
                    return num;	}

[_a-z]+		{ yylval.str = (char *)strdup(yytext);
                    return pidentifier;	}

[ \t\r\n]+
.

%%
