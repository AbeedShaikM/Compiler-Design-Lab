%{
#include <bits/stdc++.h>
using namespace std;

int yylex();
void yyerror(const char *s);
int pointer_id = 1, cnt = 0;

string newTemp() {
    return "t" + to_string(cnt++);
}

#define pb push_back
%}

%union {
  vector<string> *stmts;
  pair<string, vector<string>> *expr;
  std::string *id;
}

/* Token declarations */
%token PLUS MINUS TIMES DIVIDE EQUAL LESS GREATER LPAREN RPAREN LBRACE RBRACE ASSIGN SEMICOLON
%token AND ELSE END IF INT DO FLOAT NOT OR PRINT PROG SCAN THEN WHILE
%token <id> ID IC FC STR

%type <stmts> IS WS IOS ES S SL
%type <expr> BE AE NE RE E T PE F

/* Start symbol */
%start P

%%

/* Grammar rules */
P: PROG DL SL END { 
  auto temp = *$3;
  for(int i = 0; i < temp.size(); i++){
    cout << temp[i] << "\n";
  }
}
    ;

DL: D DL
   | /* epsilon */
   ;

D: TY VL SEMICOLON
  ;

TY: INT
   | FLOAT
   ;

VL: ID VL
   | ID
   ;

SL: S SL
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->begin(), $1->end());
      temp->insert(temp->end(), $2->begin(), $2->end());
      $$ = temp;
      delete $1;
      delete $2;
    }
   | /* epsilon */
    {
      $$ = new vector<string>;
    }
   ;

S: ES 
  {
    $$ = $1;
  }
  | IS
  {
    auto temp = new vector<string>;
    temp->insert(temp->end(), $1->begin(), $1->end());
    temp->pb("Pointer " + to_string(pointer_id++) + ": ");
    $$ = temp;
    delete $1;
  }
  | WS
  {
    auto temp = new vector<string>;
    temp->insert(temp->end(), $1->begin(), $1->end());
    temp->pb("Pointer " + to_string(pointer_id++) + ": ");
    $$ = temp;
    delete $1;
  }
  | IOS
  {
    $$ = $1;
  }
  ;

ES: ID ASSIGN E SEMICOLON
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      temp->pb(*$1 + " = " + $3->first);
      $$ = temp;
      delete $1;  
      delete $3;  
    }
   ;

IS: IF BE THEN SL END
    {
      auto temp = new vector<string>;
      temp->pb("Pointer " + to_string(pointer_id++) + ": ");
      temp->insert(temp->end(), $2->second.begin(), $2->second.end());
      temp->pb("IF NOT " + $2->first + " GOTO Pointer" + to_string(pointer_id));
      temp->insert(temp->end(), $4->begin(), $4->end());
      $$ = temp;
      delete $2;
      delete $4;
    }
   | IF BE THEN SL ELSE SL END
   {
      auto temp = new vector<string>;
      temp->pb("Pointer " + to_string(pointer_id++) + ": ");
      temp->insert(temp->end(), $2->second.begin(), $2->second.end());
      temp->pb("IF NOT " + $2->first + " GOTO Pointer" + to_string(pointer_id));
      temp->insert(temp->end(), $4->begin(), $4->end());
      temp->pb("GOTO: Pointer " + to_string(pointer_id + 1));
      temp->pb("Pointer " + to_string(pointer_id++) + ": ");
      temp->insert(temp->end(), $6->begin(), $6->end());
      $$ = temp;
      delete $2;
      delete $4;
      delete $6;
   }
   ;

WS: WHILE BE DO SL END
    {
      auto temp = new vector<string>;
      temp->pb("Pointer " + to_string(pointer_id++) + ": ");
      temp->insert(temp->end(), $2->second.begin(), $2->second.end());
      temp->pb("IF NOT " + $2->first + " GOTO Pointer" + to_string(pointer_id));
      temp->insert(temp->end(), $4->begin(), $4->end());
      temp->pb("GOTO: Pointer " + to_string(pointer_id - 1));
      $$ = temp;
      delete $2;
      delete $4;
    }
   ;

IOS: PRINT PE
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $2->second.begin(), $2->second.end());
      temp->pb("Print " + $2->first);
      $$ = temp;
      delete $2;
    }
    | SCAN ID
    {
      auto temp = new vector<string>;
      temp->pb("Scan " + *$2);
      $$ = temp;
      delete $2;
    }
    ;

PE: E 
    {
      $$ = $1;
    }
   | STR
   {
      $$ = new pair<string, vector<string>>{*($1), {}};
      delete $1;
   }
   ;

BE: BE OR AE
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " OR " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | AE
    {
      $$ = $1;
    }
   ;

AE: AE AND NE
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " AND " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | NE
    {
      $$ = $1;
    }
   ;

NE: NOT NE 
  {
    auto temp = new vector<string>;
    temp->insert(temp->end(), $2->second.begin(), $2->second.end());
    string name = newTemp();
    temp->pb(name + " = NOT " + $2->first);
    $$ = new pair<string, vector<string>>{name, *temp};
    delete $2;
  }
  | LBRACE BE RBRACE
  {
    $$ = $2;
  }
   | RE
    {
      $$ = $1;
    }
   ;

RE: E LESS E
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " < " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | E GREATER E
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " > " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
  | E EQUAL E
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " == " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | E
    {
      $$ = $1;
    }
   ;

E: E PLUS T
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " + " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | E MINUS T
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " - " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | T
    {
      $$ = $1;
    }
   ;

T: T TIMES F
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " * " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | T DIVIDE F
    {
      auto temp = new vector<string>;
      temp->insert(temp->end(), $1->second.begin(), $1->second.end());
      temp->insert(temp->end(), $3->second.begin(), $3->second.end());
      string name = newTemp();
      temp->pb(name + " = " + $1->first + " / " + $3->first);
      $$ = new pair<string, vector<string>>{name, *temp};
      delete $1;
      delete $3;
    }
   | F
    {
      $$ = $1;
    }
   ;

F: LPAREN E RPAREN
    {
      $$ = $2;
    }
   | ID
    {
      $$ = new pair<string, vector<string>>{*($1), {}};
      delete $1;
    }
   | IC
    {
      $$ = new pair<string, vector<string>>{*($1), {}};
      delete $1;
    }
   | FC
    {
      $$ = new pair<string, vector<string>>{*($1), {}};
      delete $1;
    }
   ;


%%

void yyerror(const char *s) {
    printf("Error: %s\n", s);
    exit(-1);
}

int main() {
    yyparse();
    printf("Accepted\n");
    return 0;
}
