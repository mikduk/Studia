%{
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <map>
//#include <coś>
using namespace std;
// jeszcze coś

typedef struct {
	string name;
	string type; //NUMBER, IDENTIFIER, ARRAY
	int initialized;
	int counter;
	int reg;
//	long long int mem;
	long long int local;
	long long int tableStart;
	long long int tableEnd;
} Identifier;

typedef struct {
    long long int placeInStack;
    long long int depth;
} Jump;

vector<string> codeStack;
vector<Jump> jumpStack;
vector<Identifier> forStack;
map<string, Identifier> identifierStack;
//
int yylex();
extern int yylineno;
int yyerror(const string str);

void pokazRejestr();
int findIndex(string name);
int findIndex_value(long long int value);
void addToReg(string name, string empty_name, long long int value);
void removeFromReg_index(int index, string empty_name, long long int empty_value);
void pushCommand(string str, int index1, int index2);
void createIdentifier(Identifier *s, string name, long long int isLocal, long long int tableStart, long long int tableEnd, string type);
void insertIdentifier(string key, Identifier i);
void removeIdentifier(string key);
void createJump(Jump *j, long long int stack, long long int depth);
void genNum(long long int number, int rX);
void genNum_condition(long long int number, int rX);
void add_function(long long int a, long long int b);
void sub_function(long long int a, long long int b);
void mul_function(long long int a, long long int b);
void div_function(long long int a, long long int b);
void mod_function(long long int a, long long int b);
void gt_function(long long int a, long long int b);
void knownMultiplication(long long int a, long long int b);
void unknownMultiplication(long long int a, long long int b);
void knownDivision(long long int a, long long int b);
void unknownDivision(long long int a, long long int b);
void knownModulo(long long int a, long long int b);
void unknownModulo(long long int a, long long int b);
long long int dzielenie(long long int a, long long int b);
void rozkazDoKolejki(int nr_rozkazu, int rX, int rY);
void rozkazDoKolejki_expression(int nr_rozkazu, int rX, int rY); // -2 - rejestr X, -3 - rejestr Y, -1 - brak
void rozkazDoKolejki_condition(int nr_rozkazu, int rX, int rY); // -2 - rejestr X, -3 - rejestr Y, -1 - brak
void wykonajRozkazy();
void wykonajRozkazy_expression();
void wykonajRozkazy_condition();
//nagłówki funkcji
bool assignFlag;
bool errFlag;
int temp_reg = -1;
long long int depth;
Identifier assignTarget;
string tabAssignTargetIndex = "-1";
string expressionArguments[2] = {"-1", "-1"};
string argumentsTabIndex[2] = {"-1", "-1"};
string regis_name[8] = {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"};
long long int regis_value[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
// TODO zmienić z tablic na listę
int rozkazy[100][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
int rozkazy_expression[100][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
int rozkazy_condition[100][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1},
			{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
int rozkazy_index=0;
int rozkazy_index_expression=0;
int rozkazy_index_condition=0;
long long int temp_ll;
string temp_str;
int temp_flag; // -1 -> nie wiem, 0 -> false, 1 -> true 
int regisX_index = 0;
int regisY_index = 0;
int num_ide = -1; // 0 -> num, 1 -> identifier
int dzialanie_przemienne = -1; // 0 -> / - ; 1 -> * +
int krok = 0;
int jump = 0;

%}

//%define
//%union
%define parse.error verbose
%define parse.lac full
%union {
    char* str;
    long long int num;
}

%token <str> DECLARE IN END
%token <str> SEM LB CLN RB
%token <str> ASG IF THEN ELSE ENDIF WHILE ENDWHILE
%token <str> FOR FROM TO DO ENDFOR DOWNTO WRITE READ
%token <str> ADD SUB MUL DIV MOD
%token <str> EQUAL NOT_EQUAL LT GT LE GE
%token <str> num pidentifier 

//%type
%type <str> value
%type <str> identifier

%%
program:
	DECLARE declarations IN commands END {
		pushCommand("HALT", -1, -1);
	}
;

declarations:
	declarations pidentifier SEM {
		if(identifierStack.find($2)!=identifierStack.end()){
			string err = $2;
			yyerror("Kolejna deklaracja zmiennej "+err+".");
      
		}
		else {
			Identifier s;
			createIdentifier(&s, $2, 0, 0, 0, "IDENTIFIER");
			insertIdentifier($2, s);
		
        	}
	}
|	declarations pidentifier LB num CLN num RB SEM {
		if ( atoll($4) > atoll($6) ){
			string err = $2;
			string err2 = $4;
			string err1 = $6;
			yyerror("Niewłaściwy zakres tablicy "+err+". "+err2+" > "+err1);
		}
		else if (identifierStack.find($2)!=identifierStack.end()){
			string err = $2;
			yyerror("Kolejna deklaracja tablicy "+err+".");		
		}
		else{
			cout << "Wypisz: " << $4 << " : " << $6 << endl;
			long long int first = atoll($4);
			long long int last = atoll($6);
			Identifier s;
            		createIdentifier(&s, $2, 0, first, last, "ARRAY");
            		insertIdentifier($2, s);
		}
	}
|	
;

commands:
	commands command
|	command
;

command:
	identifier ASG { assignFlag = false; } expression SEM {
		cout << ">>wejście w command<<" << endl;
		if(assignTarget.type == "ARRAY") {
            		Identifier index = identifierStack.at(tabAssignTargetIndex);
			cout << "Cech" << endl;
            
			if(index.type == "NUMBER") {
				
                		pushCommand("STORE", regisX_index, -1);
                		removeIdentifier(index.name);
				cout << "Terry" << endl;
            		}
            		else {
				
                		pushCommand("STORE", regisX_index, -1);
				cout << "Lampard" << endl;
                		/*czarna magia*/
			}
        	}
        
		else if(assignTarget.local == 0){
				cout << "sprawdzam num_ide" << endl;
				if (num_ide == 0 || num_ide == 10){
					if (num_ide == 10){

						cout << "Wartość do rejestru (identifier : num)" << endl;
						
						regisY_index = findIndex(temp_str); 								
					}

					else{
						cout << "Wartość do rejestru (liczba)" << endl;
					}

					cout << "command: identifier PRZED (1) -> temp_ll = " << temp_ll << endl;
					addToReg($2, "-1", temp_ll);
					cout << "command: identifier PO (1) -> temp_ll = " << temp_ll << endl;

					cout << "Przeszła pętla" << endl;
            				pokazRejestr();

					if (num_ide == 0){
						cout << "command: identifier PRZED (2) -> temp_ll = " << temp_ll << endl;
						genNum(temp_ll, regisX_index);
						cout << "command: identifier PO (2) -> temp_ll = " << temp_ll << endl;
						wykonajRozkazy_expression();
					}
					else{
						if (regisX_index != regisY_index)
							pushCommand("COPY", regisX_index, regisY_index);
						wykonajRozkazy_expression();
						regisY_index=0;
					}
					if (temp_reg != -1){
						removeFromReg_index(temp_reg, "-1", 0);
						temp_reg = -1;				
					}	
					regisX_index=0;
				}

				else if (num_ide == 1){
					cout << "Wartość do rejestru (identifier)" << endl;

					regisY_index = findIndex(temp_str); 
				
					addToReg($2, "-1", regis_value[regisY_index]);	
					
 					cout << "Przeszła pętla" << endl;
            				pokazRejestr();
					if (regisX_index != regisY_index)
	                			pushCommand("COPY", regisX_index, regisY_index);
					cout << "regisX_index = " << regisX_index << ", regisY_index = " << regisY_index << endl;
					wykonajRozkazy_expression();
					if (temp_reg != -1){
						removeFromReg_index(temp_reg, "-1", 0);
						temp_reg = -1;				
					}
					regisX_index=0;
					regisY_index=0;
				}

				else if (num_ide == 81){
					cout << "Wartość do rejestru (num : identifier)" << endl;

					regisY_index = findIndex(temp_str); 
				
					cout << "command: identifier PRZED (3) -> temp_ll = " << temp_ll << endl;
					addToReg($2, "-1", temp_ll);	
					cout << "command: identifier PO (3) -> temp_ll = " << temp_ll << endl;	
					
 					cout << "Przeszła pętla" << endl;
            				pokazRejestr();
					
					if (dzialanie_przemienne == 1){
						if (regisX_index != regisY_index)
	                			pushCommand("COPY", regisX_index, regisY_index);
					}
					
					else{
						//TODO
					}
		
					wykonajRozkazy_expression();
					if (temp_reg != -1){
						removeFromReg_index(temp_reg, "-1", 0);
						temp_reg = -1;				
					}
					regisX_index = 0;
					regisY_index = 0;
					dzialanie_przemienne = -1;
				}

				else if (num_ide == 11){
					cout << "Wartość do rejestru (identifier : identifier)" << endl;

					regisY_index = findIndex(temp_str); 
				
					cout << "command: identifier PRZED (4) -> temp_ll = " << temp_ll << endl;
					addToReg($2, "-1", temp_ll);
					cout << "command: identifier PO (4) -> temp_ll = " << temp_ll << endl;	
					
 					cout << "Przeszła pętla" << endl;
            				pokazRejestr();
					if (dzialanie_przemienne == 1){
						if (regisX_index != regisY_index)
	                				pushCommand("COPY", regisX_index, regisY_index);
					}
					else{
						//TODO			
					}
					cout << "regisX_index = " << regisX_index << ", regisY_index = " << regisY_index << endl;
					wykonajRozkazy_expression();
					
					if (temp_reg != -1){
						removeFromReg_index(temp_reg, "-1", 0);
						temp_reg = -1;				
					}
					regisX_index = 0;
					regisY_index = 0;
					dzialanie_przemienne = -1;
				}

				else if (num_ide == 80){
					cout << "Wartość do rejestru (num : num)" << endl;

					cout << "command: identifier PRZED (5) -> temp_ll = " << temp_ll << endl;
					addToReg($2, "-1", temp_ll);	
					cout << "command: identifier PO (5) -> temp_ll = " << temp_ll << endl;					

 					cout << "Przeszła pętla" << endl;
            				pokazRejestr();

					if (regisX_index != regisY_index)
	                			pushCommand("COPY", regisX_index, regisY_index);
					
					
					cout << "regisX_index = " << regisX_index << ", regisY_index = " << regisY_index << endl;
					wykonajRozkazy_expression();
					if (temp_reg != -1){
						removeFromReg_index(temp_reg, "-1", 0);
						temp_reg = -1;				
					}
					regisX_index = 0;
				}
	
				num_ide = -1; cout << "num_ide = -1;" << endl;
				cout << "Drogba " << endl;
				
	        }

	      	else {
            		yyerror("Próba modyfikacji iteratora pętli.");
	      	}
        	
		wykonajRozkazy();
		identifierStack.at(assignTarget.name).initialized = 1;
		assignFlag = true;
	}

|	IF { assignFlag = false; depth++; } condition { assignFlag = true; } THEN {
		cout << "Jestem w IF condition THEN { " << endl; //test
		cout << "wykonuje: wykonajRozkazy_condition();" << endl; 			
		wykonajRozkazy_condition();
		rozkazDoKolejki_condition(11, temp_reg, -4); //pushCommand("JZERO", temp_reg, krok + x);
		cout << "wykonuje: wykonajRozkazy();" << endl;
		wykonajRozkazy();
		
		
			
	} commands if_body  

|	WHILE { 
		assignFlag = false; 
		depth++; 
		Jump j;
        	createJump(&j, codeStack.size(), depth);
        	jumpStack.push_back(j);	
	} condition { assignFlag = true; } DO commands ENDWHILE {
	
		long long int stack;
        	long long int jumpCount = jumpStack.size()-1;
        
		if(jumpCount > 2 && jumpStack.at(jumpCount-2).depth == depth) {
            		stack = jumpStack.at(jumpCount-2).placeInStack;
            		pushCommand("JUMP", stack+100, -1);
            		//addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
			codeStack.at(jumpStack.at(jumpCount).placeInStack) = codeStack.at(jumpStack.at(jumpCount).placeInStack) + " " + to_string(codeStack.size());
            		//addInt(jumpStack.at(jumpCount-1).placeInStack, codeStack.size());
			codeStack.at(jumpStack.at(jumpCount-1).placeInStack) = codeStack.at(jumpStack.at(jumpCount-1).placeInStack) + " " + to_string(codeStack.size());
            		jumpStack.pop_back();
        	}
        	else {
            		stack = jumpStack.at(jumpCount-1).placeInStack;
            		pushCommand("JUMP", stack+100, -1);
            		//addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
			codeStack.at(jumpStack.at(jumpCount).placeInStack) = codeStack.at(jumpStack.at(jumpCount).placeInStack) + " " + to_string(codeStack.size());
        	}
        
		jumpStack.pop_back();
        	jumpStack.pop_back();

        	/*registerValue = -1;*/
        	depth--;
        	assignFlag = true;

	}

|	DO commands WHILE condition END DO {
	
	}
|	FOR pidentifier {
        			if(identifierStack.find($2)!=identifierStack.end()) {
					string err = $2;
					yyerror("Kolejna deklaracja zmiennej "+err+".");
        			}
        			else {
            				Identifier s;
            				createIdentifier(&s, $2, 1, 0, 0, "IDENTIFIER");
            				insertIdentifier($2, s);
        			}
				assignFlag = false;
			        assignTarget = identifierStack.at($2);
			        depth++;
    			
			} FROM value for_body 


|	READ identifier { assignFlag = true; } SEM {			
		
		
		if(assignTarget.type == "ARRAY") {
            		Identifier index = identifierStack.at(tabAssignTargetIndex);
            
			if(index.type == "NUM") {
                		pushCommand("GET", regisX_index, -1);
                		removeIdentifier(index.name);
            		}
            
			else {
		                //memToRegister(assignTarget.mem);
                		//pushCommandOneArg("ADD", index.mem);
                		//registerToMem(2);
                		pushCommand("GET", regisX_index, -1);
                		//pushCommandOneArg("STOREI", 2);
            		}
        	}
        
		else if(assignTarget.local == 0) {
			cout << "Jestem niestety w READ - wartość do rejestru" << endl;
			addToReg($2, "-1", -100); //TODO wartość wczytana
			cout << "Przeszła pętla" << endl;
            		rozkazDoKolejki_condition(0, regisX_index, -1); //pushCommand("GET", regisX_index, -1); 
            		pokazRejestr();
			regisX_index=0;
        	}
        	
		else {
            		yyerror("Próba modyfikacji iteratora pętli.");
       		}

        	identifierStack.at(assignTarget.name).initialized = 1;
		assignFlag = true;
	}

|	WRITE { assignFlag = false; } value SEM {
		pushCommand("PUT", regisX_index, -1);
		assignFlag = true;
	}
;

if_body:
	ELSE {
        
		cout << "Jestem w ELSE, WOW!" << endl;
        	wykonajRozkazy_condition();
		wykonajRozkazy();
		cout << "Wykonałem rozkazy w ELSE" << endl;
		rozkazDoKolejki_condition(12, temp_reg, -4); //JODD X 
		rozkazDoKolejki_condition(9, temp_reg, -1); // DEC X
		rozkazDoKolejki_condition(12, temp_reg, -4); // JODD X
	        assignFlag = true;

	} commands ENDIF {

	        cout << "commands ENDIF - dzięki Bogu <3" << endl;
		wykonajRozkazy_condition();
		wykonajRozkazy();

	        depth--;
        	assignFlag = true;
	}

|	ENDIF {
        
		cout << "ENDIF - całe szczęście :)" << endl;
		wykonajRozkazy_condition();
		wykonajRozkazy();		

	        depth--;
	        assignFlag = true;
	}
;

for_body:
	TO value DO {

        	Identifier a = identifierStack.at(expressionArguments[0]);
        	Identifier b = identifierStack.at(expressionArguments[1]);

		if(a.type == "NUMBER"){
            
        	}

		else if(a.type == "IDENTIFIER") {
            
        	}
        
		else {
			Identifier index = identifierStack.at(argumentsTabIndex[0]);
            
			if(index.type == "NUMBER") {
              
			}
            
			else{
		               pushCommand("ADD mejbi", -1, -1);
		               pushCommand("STORE mejbi", -1, -1);
		               pushCommand("LOADI mejbi", -1, -1);
            		}
		}

		identifierStack.at(assignTarget.name).initialized = 1;

        	if(a.type != "ARRAY" && b.type != "ARRAY"){
            		//sub(b, a, 1, 1);
		}

        	else {
            		Identifier aI, bI;
            
			if(identifierStack.count(argumentsTabIndex[0]) > 0)
		                aI = identifierStack.at(argumentsTabIndex[0]);

			if(identifierStack.count(argumentsTabIndex[1]) > 0)
				bI = identifierStack.at(argumentsTabIndex[1]);
            
			//subTab(b, a, bI, aI, 1, 1);
            
			argumentsTabIndex[0] = "-1";
			argumentsTabIndex[1] = "-1";
        	}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";

		Identifier s;
		string name = "C" + to_string(depth);
        	createIdentifier(&s, name, 1, 0, 0, "IDENTIFIER");
        	insertIdentifier(name, s);

        	forStack.push_back(identifierStack.at(assignTarget.name));

		pushCommand("JZERO", codeStack.size()+2, -1);
        
        	Jump j;
        	createJump(&j, codeStack.size(), depth);
        	jumpStack.push_back(j);
        	pushCommand("JZERO", -1, -1);
        	pushCommand("DEC", -1, -1);

		assignFlag = true;

	} commands ENDFOR {
	
	        Identifier iterator = forStack.at(forStack.size()-1);
	        //rejestr
	        pushCommand("INC it", -1, -1);
	        //rejestr

        	long long int jumpCount = jumpStack.size()-1;
        	long long int stack = jumpStack.at(jumpCount).placeInStack-1;
        
		pushCommand("JUMP", stack+100, -1);
        
		//addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
		codeStack.at(jumpStack.at(jumpCount).placeInStack) = codeStack.at(jumpStack.at(jumpCount).placeInStack) + " " + to_string(codeStack.size());
	        jumpStack.pop_back();

        	string name = "C" + to_string(depth);
        	removeIdentifier(name);
        	removeIdentifier(iterator.name);
        	forStack.pop_back();

        	depth--;
        	assignFlag = true;
    }

|	DOWNTO value DO {
 
	Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUMBER") {
            //rejestr
            removeIdentifier(a.name);
        }

        else if(a.type == "IDENTIFIER") {
            //rejestr
        }

        else {
		Identifier index = identifierStack.at(argumentsTabIndex[0]);
            
		if(index.type == "NUMBER") {
                
                	//rejestr
                	removeIdentifier(index.name);
            	}

		else {
                
			//rejestr
	                pushCommand("ADD mejbi", -1, -1);
	                pushCommand("STORE mejbi", -1, -1);
	                pushCommand("LOAD mejbi", -1, -1);
            }
        }
        
	//rejestr
        identifierStack.at(assignTarget.name).initialized = 1;

        if(a.type != "ARRAY" && b.type != "ARRAY"){
		//sub(a, b, 1, 1);
	}
        
	else {
	  	Identifier aI, bI;
            
		if(identifierStack.count(argumentsTabIndex[0]) > 0)
                	aI = identifierStack.at(argumentsTabIndex[0]);

		if(identifierStack.count(argumentsTabIndex[1]) > 0)
                	bI = identifierStack.at(argumentsTabIndex[1]);
            
		//subTab(a, b, aI, bI, 1, 1);
            	argumentsTabIndex[0] = "-1";
            	argumentsTabIndex[1] = "-1";
        }

        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";

        Identifier s;
        string name = "C" + to_string(depth);
        createIdentifier(&s, name, 1, 0, 0, "IDENTIFIER");
        insertIdentifier(name, s);

        //rejestr
        forStack.push_back(identifierStack.at(assignTarget.name));

        pushCommand("JZERO", codeStack.size()+102, -1);
        //rejestr
        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
        pushCommand("JZERO", -1, -1);
        pushCommand("DEC", -1, -1);
        //rejestr

        assignFlag = true;

	} commands ENDFOR {
        	
		Identifier iterator = forStack.at(forStack.size()-1);
        	//rejestr
        	pushCommand("DEC", -1, -1);
        	//rejestr

        	long long int jumpCount = jumpStack.size()-1;
        	long long int stack = jumpStack.at(jumpCount).placeInStack-1;

	        pushCommand("JUMP", stack+100, -1);
	        //addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
		codeStack.at(jumpStack.at(jumpCount).placeInStack) = codeStack.at(jumpStack.at(jumpCount).placeInStack) + " " + to_string(codeStack.size());
	        jumpStack.pop_back();

        	string name = "C" + to_string(depth);
        	removeIdentifier(name);
        	removeIdentifier(iterator.name);
        	forStack.pop_back();

        	depth--;
        	assignFlag = true;
	}	
;

expression:
	value {
		temp_ll = atoll($1);
		cout << "expression: value -> temp_ll = " << temp_ll << endl;

	}

|	value ADD value {

		dzialanie_przemienne = 1;

		//	num + num	ide + ide	num + ide	ide + num	
		if(num_ide == 80 || num_ide == 11 || num_ide == 81 || num_ide == 10){
            			
			long long int a;
			long long int b; 

			if (num_ide == 80){
				a = atoll($1);
				b = atoll($3);
			}

			else if (num_ide == 11){				
				int a_ind = findIndex($1);
				int b_ind = findIndex($3);
				cout << "vAv n_i=11 -> $1 = " << $1 << ", $3 = " << $3 << ", findIndex($1) = " << findIndex($1) << ", findIndex($3) = " << findIndex($3) << endl; 
				a = regis_value[a_ind];
				b = regis_value[b_ind];
				cout << "vAv n_i=11 -> regis_value[a_ind] = " << regis_value[a_ind] << ", regis_value[b_ind] = " << regis_value[b_ind] << endl;
			}

			else if (num_ide == 81){
				a = atoll($1);
				int b_ind = findIndex($3);
				b = regis_value[b_ind];
			}

			else if (num_ide == 10){
				int a_ind = findIndex($1);
				a = regis_value[a_ind];
				b = atoll($3);
			}  


			add_function(a, b);
		}
        
		else {
	            		/*Identifier aI, bI;
	
	            		if(identifierStack.count(argumentsTabIndex[0]) > 0)
	                		aI = identifierStack.at(argumentsTabIndex[0]);

	            		if(identifierStack.count(argumentsTabIndex[1]) > 0)
	                		bI = identifierStack.at(argumentsTabIndex[1]);

	            		addTab(a, b, aI, bI);

	            		argumentsTabIndex[0] = "-1";
	            		argumentsTabIndex[1] = "-1"; */
		}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";
	}
	
|	value SUB value {

		dzialanie_przemienne = 0;

		//	num - num	ide - ide	num - ide	ide - num	
		if(num_ide == 80 || num_ide == 11 || num_ide == 81 || num_ide == 10){
            			
			long long int a;
			long long int b; 

			if (num_ide == 80){
				a = atoll($1);
				b = atoll($3);
			}

			else if (num_ide == 11){				
				int a_ind = findIndex($1);
				int b_ind = findIndex($3);
				cout << "vSv n_i=11 -> $1 = " << $1 << ", $3 = " << $3 << ", findIndex($1) = " << findIndex($1) << ", findIndex($3) = " << findIndex($3) << endl; 
				a = regis_value[a_ind];
				b = regis_value[b_ind];
				cout << "vSv n_i=11 -> regis_value[a_ind] = " << regis_value[a_ind] << ", regis_value[b_ind] = " << regis_value[b_ind] << endl;
			}

			else if (num_ide == 81){
				a = atoll($1);
				int b_ind = findIndex($3);
				b = regis_value[b_ind];
			}

			else if (num_ide == 10){
				int a_ind = findIndex($1);
				a = regis_value[a_ind];
				b = atoll($3);
			}  


			sub_function(a, b);
		}
        
		else {
	            		/*Identifier aI, bI;
	
	            		if(identifierStack.count(argumentsTabIndex[0]) > 0)
	                		aI = identifierStack.at(argumentsTabIndex[0]);

	            		if(identifierStack.count(argumentsTabIndex[1]) > 0)
	                		bI = identifierStack.at(argumentsTabIndex[1]);

	            		addTab(a, b, aI, bI);

	            		argumentsTabIndex[0] = "-1";
	            		argumentsTabIndex[1] = "-1"; */
		}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";
	}
|	value MUL value {

		dzialanie_przemienne = 1;

		//	num * num	ide * ide	num * ide	ide * num	
		if(num_ide == 80 || num_ide == 11 || num_ide == 81 || num_ide == 10){
            			
			long long int a;
			long long int b; 

			if (num_ide == 80){
				a = atoll($1);
				b = atoll($3);
			}

			else if (num_ide == 11){				
				int a_ind = findIndex($1);
				int b_ind = findIndex($3);
				cout << "vMv n_i=11 -> $1 = " << $1 << ", $3 = " << $3 << ", findIndex($1) = " << findIndex($1) << ", findIndex($3) = " << findIndex($3) << endl; 
				a = regis_value[a_ind];
				b = regis_value[b_ind];
				cout << "vMv n_i=11 -> regis_value[a_ind] = " << regis_value[a_ind] << ", regis_value[b_ind] = " << regis_value[b_ind] << endl;
			}

			else if (num_ide == 81){
				a = atoll($1);
				int b_ind = findIndex($3);
				b = regis_value[b_ind];
			}

			else if (num_ide == 10){
				int a_ind = findIndex($1);
				a = regis_value[a_ind];
				b = atoll($3);
			}  


			mul_function(a, b);
		}
        
		else {
	            		/*Identifier aI, bI;
	
	            		if(identifierStack.count(argumentsTabIndex[0]) > 0)
	                		aI = identifierStack.at(argumentsTabIndex[0]);

	            		if(identifierStack.count(argumentsTabIndex[1]) > 0)
	                		bI = identifierStack.at(argumentsTabIndex[1]);

	            		addTab(a, b, aI, bI);

	            		argumentsTabIndex[0] = "-1";
	            		argumentsTabIndex[1] = "-1"; */
		}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";
	}
|	value DIV value {

		dzialanie_przemienne = 0;

		//	num / num	ide / ide	num / ide	ide / num	
		if(num_ide == 80 || num_ide == 11 || num_ide == 81 || num_ide == 10){
            			
			long long int a;
			long long int b; 

			if (num_ide == 80){
				a = atoll($1);
				b = atoll($3);
			}

			else if (num_ide == 11){				
				int a_ind = findIndex($1);
				int b_ind = findIndex($3);
				cout << "vDv n_i=11 -> $1 = " << $1 << ", $3 = " << $3 << ", findIndex($1) = " << findIndex($1) << ", findIndex($3) = " << findIndex($3) << endl; 
				a = regis_value[a_ind];
				b = regis_value[b_ind];
				cout << "vDv n_i=11 -> regis_value[a_ind] = " << regis_value[a_ind] << ", regis_value[b_ind] = " << regis_value[b_ind] << endl;
			}

			else if (num_ide == 81){
				a = atoll($1);
				int b_ind = findIndex($3);
				b = regis_value[b_ind];
			}

			else if (num_ide == 10){
				int a_ind = findIndex($1);
				a = regis_value[a_ind];
				b = atoll($3);
			}  


			div_function(a, b);
		}
        
		else {
	            		/*Identifier aI, bI;
	
	            		if(identifierStack.count(argumentsTabIndex[0]) > 0)
	                		aI = identifierStack.at(argumentsTabIndex[0]);

	            		if(identifierStack.count(argumentsTabIndex[1]) > 0)
	                		bI = identifierStack.at(argumentsTabIndex[1]);

	            		addTab(a, b, aI, bI);

	            		argumentsTabIndex[0] = "-1";
	            		argumentsTabIndex[1] = "-1"; */
		}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";
	}
|	value MOD value {

		dzialanie_przemienne = 0;

		//	num % num	ide % ide	num % ide	ide % num	
		if(num_ide == 80 || num_ide == 11 || num_ide == 81 || num_ide == 10){
            			
			long long int a;
			long long int b; 

			if (num_ide == 80){
				a = atoll($1);
				b = atoll($3);
			}

			else if (num_ide == 11){				
				int a_ind = findIndex($1);
				int b_ind = findIndex($3);
				cout << "v%v n_i=11 -> $1 = " << $1 << ", $3 = " << $3 << ", findIndex($1) = " << findIndex($1) << ", findIndex($3) = " << findIndex($3) << endl; 
				a = regis_value[a_ind];
				b = regis_value[b_ind];
				cout << "v%v n_i=11 -> regis_value[a_ind] = " << regis_value[a_ind] << ", regis_value[b_ind] = " << regis_value[b_ind] << endl;
			}

			else if (num_ide == 81){
				a = atoll($1);
				int b_ind = findIndex($3);
				b = regis_value[b_ind];
			}

			else if (num_ide == 10){
				int a_ind = findIndex($1);
				a = regis_value[a_ind];
				b = atoll($3);
			}  


			mod_function(a, b);
		}
        
		else {
	            		/*Identifier aI, bI;
	
	            		if(identifierStack.count(argumentsTabIndex[0]) > 0)
	                		aI = identifierStack.at(argumentsTabIndex[0]);

	            		if(identifierStack.count(argumentsTabIndex[1]) > 0)
	                		bI = identifierStack.at(argumentsTabIndex[1]);

	            		addTab(a, b, aI, bI);

	            		argumentsTabIndex[0] = "-1";
	            		argumentsTabIndex[1] = "-1"; */
		}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";
	}
;

condition:
	value EQUAL value {

		dzialanie_przemienne = 1;

		//	num + num	ide + ide	num + ide	ide + num	
		if(num_ide == 80 || num_ide == 11 || num_ide == 81 || num_ide == 10){
            			
			long long int a;
			long long int b; 

			if (num_ide == 80){
				a = atoll($1);
				b = atoll($3);
			}

			else if (num_ide == 11){				
				int a_ind = findIndex($1);
				int b_ind = findIndex($3);
				cout << "vAv n_i=11 -> $1 = " << $1 << ", $3 = " << $3 << ", findIndex($1) = " << findIndex($1) << ", findIndex($3) = " << findIndex($3) << endl; 
				a = regis_value[a_ind];
				b = regis_value[b_ind];
				cout << "vAv n_i=11 -> regis_value[a_ind] = " << regis_value[a_ind] << ", regis_value[b_ind] = " << regis_value[b_ind] << endl;
			}

			else if (num_ide == 81){
				a = atoll($1);
				int b_ind = findIndex($3);
				b = regis_value[b_ind];
			}

			else if (num_ide == 10){
				int a_ind = findIndex($1);
				a = regis_value[a_ind];
				b = atoll($3);
			}  


			add_function(a, b);
		}
        
		else {
	            		/*Identifier aI, bI;
	
	            		if(identifierStack.count(argumentsTabIndex[0]) > 0)
	                		aI = identifierStack.at(argumentsTabIndex[0]);

	            		if(identifierStack.count(argumentsTabIndex[1]) > 0)
	                		bI = identifierStack.at(argumentsTabIndex[1]);

	            		addTab(a, b, aI, bI);

	            		argumentsTabIndex[0] = "-1";
	            		argumentsTabIndex[1] = "-1"; */
		}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";
	}
|	value NOT_EQUAL value {
	
			Identifier a = identifierStack.at(expressionArguments[0]);
        		Identifier b = identifierStack.at(expressionArguments[1]);

        		if(a.type == "NUMBER" && b.type == "NUMBER") {
            
				if(stoll(a.name) != stoll(b.name))
 	               			cout << "PRAWDA" << endl;
            			else
                			cout << "FAŁSZ" << endl;
            
				removeIdentifier(a.name);
            			removeIdentifier(b.name);
        		}
        
			else {
	            		cout << "Porównywanie innych typów na razie za trudne" << endl;
        		}

        		Jump j;
        		createJump(&j, codeStack.size(), depth);
        		jumpStack.push_back(j);
        		pushCommand("JZERO", 100, -1);

        		expressionArguments[0] = "-1";
        		expressionArguments[1] = "-1";
			argumentsTabIndex[0] = "-1";
        		argumentsTabIndex[1] = "-1";
	}
|	value GT value { //dupa

		cout << "Jestem w value GT value" << endl;

		dzialanie_przemienne = 0;

		//	num > num	ide > ide	num > ide	ide > num	
		if(num_ide == 80 || num_ide == 11 || num_ide == 81 || num_ide == 10){
            			
			long long int a;
			long long int b; 

			if (num_ide == 80){
				a = atoll($1);
				b = atoll($3);
			}

			else if (num_ide == 11){				
				int a_ind = findIndex($1);
				int b_ind = findIndex($3);
				cout << "v>v n_i=11 -> $1 = " << $1 << ", $3 = " << $3 << ", findIndex($1) = " << findIndex($1) << ", findIndex($3) = " << findIndex($3) << endl; 
				a = regis_value[a_ind];
				b = regis_value[b_ind];
				cout << "v>v n_i=11 -> regis_value[a_ind] = " << regis_value[a_ind] << ", regis_value[b_ind] = " << regis_value[b_ind] << endl;
			}

			else if (num_ide == 81){
				a = atoll($1);
				int b_ind = findIndex($3);
				b = regis_value[b_ind];
			}

			else if (num_ide == 10){
				int a_ind = findIndex($1);
				a = regis_value[a_ind];
				b = atoll($3);
			}  


			gt_function(a, b);
		}
        
		else {
	            		/*Identifier aI, bI;
	
	            		if(identifierStack.count(argumentsTabIndex[0]) > 0)
	                		aI = identifierStack.at(argumentsTabIndex[0]);

	            		if(identifierStack.count(argumentsTabIndex[1]) > 0)
	                		bI = identifierStack.at(argumentsTabIndex[1]);

	            		addTab(a, b, aI, bI);

	            		argumentsTabIndex[0] = "-1";
	            		argumentsTabIndex[1] = "-1"; */
		}

		expressionArguments[0] = "-1";
		expressionArguments[1] = "-1";
	}
|	value LT value {
	
			Identifier a = identifierStack.at(expressionArguments[0]);
        		Identifier b = identifierStack.at(expressionArguments[1]);

        		if(a.type == "NUMBER" && b.type == "NUMBER") {
            
				if(stoll(a.name) > stoll(b.name))
 	               			cout << "PRAWDA" << endl;
            			else
                			cout << "FAŁSZ" << endl;
            
				removeIdentifier(a.name);
            			removeIdentifier(b.name);
        		}
        
			else {
	            		cout << "Porównywanie innych typów na razie za trudne" << endl;
        		}

        		Jump j;
        		createJump(&j, codeStack.size(), depth);
        		jumpStack.push_back(j);
        		pushCommand("JZERO", 100, -1);

        		expressionArguments[0] = "-1";
        		expressionArguments[1] = "-1";
	}
|	value LE value {
	
			Identifier a = identifierStack.at(expressionArguments[0]);
        		Identifier b = identifierStack.at(expressionArguments[1]);

        		if(a.type == "NUMBER" && b.type == "NUMBER") {
            
				if(stoll(a.name) <= stoll(b.name))
 	               			cout << "PRAWDA" << endl;
            			else
                			cout << "FAŁSZ" << endl;
            
				removeIdentifier(a.name);
            			removeIdentifier(b.name);
        		}
        
			else {
	            		cout << "Porównywanie innych typów na razie za trudne" << endl;
        		}

        		Jump j;
        		createJump(&j, codeStack.size(), depth);
        		jumpStack.push_back(j);
        		pushCommand("JZERO", 100, -1);

        		expressionArguments[0] = "-1";
        		expressionArguments[1] = "-1";
	}
|	value GE value {
	
			Identifier a = identifierStack.at(expressionArguments[0]);
        		Identifier b = identifierStack.at(expressionArguments[1]);

        		if(a.type == "NUMBER" && b.type == "NUMBER") {
            
				if(stoll(a.name) >= stoll(b.name))
 	               			cout << "PRAWDA" << endl;
            			else
                			cout << "FAŁSZ" << endl;
            
				removeIdentifier(a.name);
            			removeIdentifier(b.name);
        		}
        
			else {
	            		cout << "Porównywanie innych typów na razie za trudne" << endl;
        		}

        		Jump j;
        		createJump(&j, codeStack.size(), depth);
        		jumpStack.push_back(j);
        		pushCommand("JZERO", 100, -1);

        		expressionArguments[0] = "-1";
        		expressionArguments[1] = "-1";
	}
;

value:
	num {	cout << num_ide << " <- wartość num_ide na początku value: num" << endl;
		if (num_ide == 1){
			num_ide = 10;
			cout << "ide : num (num_ide=10)" <<endl; //test		
		}

		else if (num_ide == 0){
			num_ide = 80;
			cout << "num : num (num_ide=80)" <<endl; //test		
		}	
		
		else{
			num_ide = 0;
			cout << "num^^ (num_ide=0)" <<endl; //test
		}

		if (atoll($1) < 0){
			yyerror("Niewłaściwy znak '-'");		
		}
		
		if(assignFlag){
            		yyerror("Próba przypisania do stałej.");
      		}
        
		Identifier s;
	      	createIdentifier(&s, $1, 0, 0, 0, "NUMBER");
	        insertIdentifier($1, s);
	
	      	/*if (expressionArguments[0] == "-1"){
      			expressionArguments[0] = $1;
      		}
      		else{
      			expressionArguments[1] = $1;
      		}*/	
	}

|	identifier { if (num_ide == -1){ num_ide=1;  cout << "ide xD (num_ide=1;)" << endl; }
		else if (num_ide == 0) { num_ide=81; cout << "num : ide (num_ide=81;)" << endl; }
		else if (num_ide == 1) { num_ide=11; cout << "ide : ide (num_ide=11;)" << endl; }	 
	}

;

identifier:
	pidentifier {

		temp_str = $1;
		if(identifierStack.find($1) == identifierStack.end()) {
			string err = $1;
            		yyerror("Zmienna "+err+" nie została zadeklarowana.");
		}
		if(identifierStack.at($1).tableEnd == 0) {
			if(!assignFlag){
				if(identifierStack.at($1).initialized == 0) {
					string err = $1;			
					yyerror("Próba użycia niezadeklarowanej zmiennej "+err+".");
                		}

				if (expressionArguments[0] == "-1"){
                    			expressionArguments[0] = $1;
                		}
                		
				else{
	                    		expressionArguments[1] = $1;
	                	}
			}
			else{
				assignTarget = identifierStack.at($1);
			}
		}
		else{
			string err = $1;
			yyerror("Brak odwołania do elementu tablicy "+err+".");
        	}
        }
	
|	pidentifier LB pidentifier RB {
		if(identifierStack.find($1) == identifierStack.end()) {
			string err = $1;
			yyerror("Zmienna "+err+" nie została zadeklarowana.");
		}
	
		if(identifierStack.find($3) == identifierStack.end()) {
			string err = $3;
			yyerror("Zmienna "+err+" nie została zadeklarowana.");
		}

	        if(identifierStack.at($1).tableEnd == 0) {
            		string err = $1;
			yyerror("Zmienna "+err+" nie jest tablicą.");
		}
		else {
			if(identifierStack.at($3).initialized == 0) {
				string err = $3;
				yyerror("Próba użycia niezadeklarowanej zmiennej "+err+".");
			}

            		if(!assignFlag){
                
                		/*if (expressionArguments[0] == "-1"){
					expressionArguments[0] = $1;
					argumentsTabIndex[0] = $3;
                		}
                		else{
                    			expressionArguments[1] = $1;
                    			argumentsTabIndex[1] = $3;
                		}*/

            		}
            		else {
                		assignTarget = identifierStack.at($1);
                		tabAssignTargetIndex = $3;
            		}
        	}
	}

|	pidentifier LB num RB {
		if(identifierStack.find($1) == identifierStack.end()) {
			string err = $1;
			yyerror("Zmienna "+err+" nie została zadeklarowana.");
		}

        	if(identifierStack.at($1).tableEnd == 0) {
            		string err = $1;
			yyerror("Zmienna "+err+" nie jest tablicą.");
        	}
		else {
            		Identifier s;
            		createIdentifier(&s, $3, 0, 0, 0, "NUMBER");
            		insertIdentifier($3, s);

            		if(!assignFlag){
                
                		if (expressionArguments[0] == "-1"){
                    			expressionArguments[0] = $1;
                    			argumentsTabIndex[0] = $3;
                		}
                		else{
                    			expressionArguments[1] = $1;
                    			argumentsTabIndex[1] = $3;
                		}

            		}
            		else {
                		assignTarget = identifierStack.at($1);
                		tabAssignTargetIndex = $3;
            		}
        	}
	}
;

%% 

void pushCommand(string str, int r1, int r2){
	if (r2 == -1){
		if (r1 == -1){
			cout << krok++ << ": " << str << endl;
			//codeStack.push_back(str);
		}
		
		else{
			char r = 'A'+r1;
			cout << krok++ << ": " << str << " " << r << endl;
			//codeStack.push_back(str);
		}
	}
	else if (r2 > 100){
		char r = 'A'+r1;
			cout << krok++ << ": " << str << " " << r << " " << krok + r2 - 100 << endl;
			cout << "krok = " << krok << endl;
			cout << "r2 = " << r2 << endl;
			//codeStack.push_back(str);
	}	
	else{
		char a = 'A'+r1;
		char b = 'A'+r2;
		cout << krok++ << ": " << str << " " << a << " " << b << endl;
		//codeStack.push_back(str);	
	}
}

void createJump(Jump *j, long long int stack, long long int depth) {
    j->placeInStack = stack;
    j->depth = depth;
}

void createIdentifier(Identifier *s, string name, long long int isLocal,
    long long int tableStart, long long int tableEnd, string type){
    s->name = name;
//    s->mem = memCounter;
    s->type = type;
    s->reg = 0;	
    s->initialized = 0;
    if(isLocal){
    	s->local = 1;
    }
    else{
    	s->local = 0;
    }
    if(tableEnd){
	s->tableStart = tableStart;
	s->tableEnd = tableEnd;
    }
    else{
	s->tableStart = 0;
	s->tableEnd = 0;
    }
}

void insertIdentifier(string key, Identifier i){

	if(identifierStack.count(key) == 0){
		identifierStack.insert(make_pair(key, i));
		identifierStack.at(key).counter = 0;
		//memCounter++;
	}

	else {
        	identifierStack.at(key).counter = identifierStack.at(key).counter+1;
	}
    /*cout << "Add: " << key << " " << memCounter-1 << endl;*/
}

void removeIdentifier(string key) {
    if(identifierStack.count(key) > 0) {
        if(identifierStack.at(key).counter > 0) {
            identifierStack.at(key).counter = identifierStack.at(key).counter-1;
        }
        else {
            identifierStack.erase(key);
            //memCounter--;
        }
    }
    /*cout << "Remove: " << key << endl;*/
}

void genNum(long long int number, int rX){
	int kolejka[number];
	long long int index=0, size=number;
	while (number != 0){
		if (number > 11 && number%2 == 0){
		
			number = number/2;
			kolejka[index] = 11;
			index++;			
		}
		
		else{
			number--;
			kolejka[index] = 22;
			index++;		
		}
			
	}
	if (regis_value[rX] != 0)
		rozkazDoKolejki_expression(6, rX, rX);

	for (--size; size>=0; size--){
		if (kolejka[size]==11){
			rozkazDoKolejki_expression(5, rX, rX);
		}
		else if (kolejka[size]==22){
			rozkazDoKolejki_expression(8, rX, -1);
		}	
	}
}

void genNum_condition(long long int number, int rX){
	int kolejka[number];
	long long int index=0, size=number;
	while (number != 0){
		if (number > 11 && number%2 == 0){
		
			number = number/2;
			kolejka[index] = 11;
			index++;			
		}
		
		else{
			number--;
			kolejka[index] = 22;
			index++;		
		}
			
	}
	if (regis_value[rX] != 0)
		rozkazDoKolejki_condition(6, rX, rX);

	for (--size; size>=0; size--){
		if (kolejka[size]==11){
			rozkazDoKolejki_condition(5, rX, rX);
		}
		else if (kolejka[size]==22){
			rozkazDoKolejki_condition(8, rX, -1);
		}	
	}
}

void add_function(long long int a, long long int b) { //DONE 

	cout << "WEJŚCIE DO add_function: a = " << a << ", b = " << b << endl;		
	
	// num + num
	if ( num_ide == 80 ) { 
        	
		cout << "add_function PRZED (1) -> temp_ll = " << temp_ll << endl;
		temp_ll = a + b;
		cout << "add_function PO (1) -> temp_ll = " << temp_ll << endl;		
		if (a != b){
			if (a < b){
				long long int t = a;
				a = b;
				b = t;
			}
			if (b < 8){
				genNum(a, -2); 
				for(int i=0; i < b; i++) {
                			rozkazDoKolejki_expression(8, -2, -1);
				}
            		}

			else{
				if ((a - b) < 8){					
					genNum(b, -2);
					rozkazDoKolejki_expression(5, -2, -2);
					for(int i=0; i < (a - b); i++) {
                				rozkazDoKolejki_expression(8, -2, -1);		
					}
				}

				else{
					genNum(b, -2);
					addToReg(to_string(a), "-1", a);
					genNum(a, regisX_index);
					rozkazDoKolejki_expression(5, -2, regisX_index);
					rozkazDoKolejki_expression(6, regisX_index, regisX_index);
					//removeFromReg_index(regisX_index, "-1", -1);	
					temp_reg = regisX_index;			
				}					
			}
		}	
		else{
			if ( a < 8 ){
				for(int i=0; i < 2*a; i++) {
                			rozkazDoKolejki_expression(8, -2, -1);		
				}			
			}

			else{
				genNum(a, -2);
				rozkazDoKolejki_expression(5, -2, -2);
			}
		}
		
    	}
    
	// num + ide
	else if ( num_ide == 81 ) {

		cout << "add_function PRZED (2) -> temp_ll = " << temp_ll << endl;
		if (b<0)
		temp_ll = -81; // UWAGA przypisuję wartość -81 w C++ dla wczytanej zmiennej
		else
		temp_ll = a + b;
		cout << "add_function PO (2) -> temp_ll = " << temp_ll << endl;		

	        //trying to opt
	        if( a < 8) {
            		rozkazDoKolejki_expression(4, -2, -3);
			for(int i=0; i < a; i++) {
               			rozkazDoKolejki_expression(8, -2, -1);
	          	}	
        	}
        
		else {
			if (b < 8 && b >= 0){
				genNum(a, -2); 
				for(int i=0; i < a; i++) {
               				rozkazDoKolejki_expression(8, -2, -1);
	          		}
			}
			else{
				regisY_index = findIndex_value(b);				
				rozkazDoKolejki_expression(4, -2, regisY_index);
				addToReg(to_string(a), "-1", a);
				genNum(a, regisX_index); //genNum_withoutsub(a, regisX_index);
				rozkazDoKolejki_expression(5, -2, regisX_index);
				temp_reg=regisX_index;
				
			}
		}    	
	}
    
	// ide + num
	else if ( num_ide == 10 ) {

		cout << "add_function PO (3) -> temp_ll = " << temp_ll << endl;
		if (a<0)
		temp_ll = -10; // UWAGA przypisuję wartość -10 w C++ dla wczytanej zmiennej
		else
		temp_ll = a + b;		
		cout << "add_function PO (3) -> temp_ll = " << temp_ll << endl;

	        //trying to opt
	        if( b < 8) {
            		rozkazDoKolejki_expression(4, -2, -3);
			for(int i=0; i < b; i++) {
                		rozkazDoKolejki_expression(8, -2, -1);
            		}
        	}
        
		else {
			if (a < 8 && a >= 0){
				genNum(b, -2); 
				for(int i=0; i < b; i++) {
               				rozkazDoKolejki_expression(8, -2, -1);
	          		}
			}
			else{
				regisY_index = findIndex_value(a);				
				rozkazDoKolejki_expression(4, -2, regisY_index);
				addToReg(to_string(b), "-1", b);
				genNum(b, regisX_index); //genNum_withoutsub(a, regisX_index);
				rozkazDoKolejki_expression(5, -2, regisX_index);
				temp_reg=regisX_index;
				
			}
		}    	
    	}

	// ide + ide
	else if ( num_ide == 11 ) {
        
		cout << "add_function PRZED (4) -> temp_ll = " << temp_ll << endl;	
		if (a<0 || b<0)
		temp_ll = -11; // UWAGA przypisuję wartość -11 w C++ dla wczytanej zmiennej
		else
		temp_ll = a + b;		
		cout << "add_function PO (4) -> temp_ll = " << temp_ll << endl;

		if (a == b && a >= 0) {
			regisY_index = findIndex_value(a);
			rozkazDoKolejki_expression(4, -2, regisY_index);
			rozkazDoKolejki_expression(5, -2, -2);
        	}

	        else {
			regisY_index = findIndex_value(a);
			rozkazDoKolejki_expression(4, -2, regisY_index);
			regisY_index = findIndex_value(b);
			rozkazDoKolejki_expression(5, -2, regisY_index);
        	}
	}
}

void sub_function(long long int a, long long int b) {

	cout << "WEJŚCIE DO sub_function: a = " << a << ", b = " << b << endl;		
	
	// num - num
	if ( num_ide == 80 ) { 
        	
		cout << "sub_function PRZED (1) -> temp_ll = " << temp_ll << endl;
		if (a == 0 || a < b)		
			temp_ll = 0;
		else
			temp_ll = a - b;
		cout << "sub_function PO (1) -> temp_ll = " << temp_ll << endl;		
		if (a > b){
			
			if (b < 8){
				genNum(a, -2); 
				for(int i=0; i < b; i++) {
                			rozkazDoKolejki_expression(9, -2, -1);
				}
            		}

			else{
				genNum(a, -2);
				addToReg(to_string(b), "-1", b);
				genNum(b, regisX_index);
				rozkazDoKolejki_expression(6, -2, regisX_index);
				rozkazDoKolejki_expression(6, regisX_index, regisX_index);	
				temp_reg = regisX_index;			
									
			}
		}
		
		else{
                		rozkazDoKolejki_expression(6, -2, -2);
		}
		
    	}
    
	// num - ide
	else if ( num_ide == 81 ) {

		cout << "sub_function PRZED (2) -> temp_ll = " << temp_ll << endl;
		if (a == 0 || a < b)		
			temp_ll = 0;
		else if (b < 0)
			temp_ll = -81; // TODO gdy b jest z READ
		else
			temp_ll = a - b;
		cout << "sub_function PO (2) -> temp_ll = " << temp_ll << endl;	

		if (a <= b && b >= 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}
		else{	        
			genNum(a, -2);
			if (b < 8 && b >= 0){ 
				for(int i=0; i < b; i++) {
	                		rozkazDoKolejki_expression(9, -2, -1);
				}
            		}
			else{
				regisY_index = findIndex_value(b);
				rozkazDoKolejki_expression(6, -2, regisY_index);	
			}
	        }
	}    	
    
	// ide - num
	else if ( num_ide == 10 ) {

		cout << "sub_function PRZED (3) -> temp_ll = " << temp_ll << endl;
		if (a < 0)		
			temp_ll = -10;
		else if (a == 0 || a < b)
			temp_ll = 0;
		else
			temp_ll = a - b;
		cout << "sub_function PO (3) -> temp_ll = " << temp_ll << endl;	

		if (a <= b && a >= 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}
		else{
			regisY_index = findIndex_value(a);		
			rozkazDoKolejki_expression(4, -2, regisY_index);		

			if (b < 8){ 
				for(int i=0; i < b; i++) {
                			rozkazDoKolejki_expression(9, -2, -1);
				}
            		}
			else{
				addToReg(to_string(b), "-1", b);
				genNum(b, regisX_index);			
				rozkazDoKolejki_expression(6, -2, regisX_index);
				temp_reg = regisX_index;	
			}
	        }
    	}
    

	// ide - ide
	else if ( num_ide == 11 ) {
        
		cout << "sub_function PRZED (4) -> temp_ll = " << temp_ll << endl;
		if (a < 0 || b < 0)			
			temp_ll = -11;	
		else if (a == 0 || a < b)		
			temp_ll = 0;
		else
			temp_ll = a - b;
		cout << "sub_function PO (4) -> temp_ll = " << temp_ll << endl;

		if (a <= b && a >= 0) {
			regisY_index = findIndex_value(a);
			rozkazDoKolejki_expression(6, regisY_index, regisY_index);
        	}

	        else {
			addToReg(to_string(a), "-1", a);
			temp_reg = regisX_index;
			regisY_index = findIndex_value(a);
			rozkazDoKolejki_expression(4, temp_reg, regisY_index);
			regisX_index = findIndex_value(b);
			rozkazDoKolejki_expression(6, temp_reg, regisX_index);
			rozkazDoKolejki_expression(4, -2, temp_reg);
        	}
	}
}

void mul_function(long long int a, long long int b) { //TODO zrobić dla wartości pobranych z READ

	cout << "WEJŚCIE DO mul_function: a = " << a << ", b = " << b << endl;		
	
	// num * num
	if ( num_ide == 80 ) { 
        	
		cout << "mul_function PRZED (1) -> temp_ll = " << temp_ll << endl;
		temp_ll = a * b;
		cout << "mul_function PO (1) -> temp_ll = " << temp_ll << endl;		
		if (a == 2){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 2){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 1){
			genNum(b, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 4){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 4){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 8){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 8){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg(to_string(a), "-1", a);
			genNum(a, regisX_index);
			int tr;
			temp_reg = regisX_index;			
			cout << "Rejestr małego a: " << temp_reg << endl; //test
			addToReg(to_string(b), "-1", b);
			genNum(b, regisX_index);
			cout << "Rejestr małego b: " << regisX_index << endl; //test
			knownMultiplication(a, b);
			cout << "RegisX po knownMulti: " << regisX_index << endl;
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A, B wyzeruje się sam
			tr = regisX_index;
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++	
		}
		
    	}
    
	// num * ide
	else if ( num_ide == 81 ) {

		cout << "mul_function PRZED (2) -> temp_ll = " << temp_ll << endl;
		temp_ll = a * b;
		cout << "mul_function PO (2) -> temp_ll = " << temp_ll << endl;		

	        if (a == 2){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 2){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 1){
			genNum(b, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 4){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 4){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 8){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 8){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}			
		
		else{
			addToReg(to_string(a), "-1", a);
			genNum(a, regisX_index);
			int tr;
			temp_reg = regisX_index;
			regisY_index = findIndex_value(b);
			addToReg(to_string(b), "-1", b);
			tr = regisX_index;
			rozkazDoKolejki_expression(4, regisX_index, regisY_index);
			if (b >= 0)  
				knownMultiplication(a, b);
			else
				unknownMultiplication(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A, B wyzeruje się sam
			rozkazDoKolejki_expression(-2, tr, 0); // usunwam rejestr B w C++
			
		}
	}

	// ide * num
	else if ( num_ide == 10 ) {

		cout << "mul_function PRZED (3) -> temp_ll = " << temp_ll << endl;
		temp_ll = a * b;
		cout << "mul_function PO (3) -> temp_ll = " << temp_ll << endl;		

	        if (a == 2){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 2){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 1){
			genNum(b, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 4){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 4){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 8){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 8){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg(to_string(b), "-1", b);
			genNum(b, regisX_index);
			int tr;
			temp_reg = regisX_index;
			regisY_index = findIndex_value(a);
			addToReg(to_string(a), "-1", a);
			tr = regisX_index;
			rozkazDoKolejki_expression(4, regisX_index, regisY_index);
			if (a >= 0)  
				knownMultiplication(a, b);
			else
				unknownMultiplication(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A, B wyzeruje się sam
			rozkazDoKolejki_expression(-2, tr, 0);		
		}
	}

	// ide * ide
	else if ( num_ide == 11 ) {

		cout << "mul_function PRZED (4) -> temp_ll = " << temp_ll << endl;
		temp_ll = a * b;
		cout << "mul_function PO (4) -> temp_ll = " << temp_ll << endl;		

	        if (a == 2){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 2){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 1){
			genNum(b, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 4){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 4){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 8){
			genNum(b, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (b == 8){
			genNum(a, -2);
			rozkazDoKolejki_expression(5, -2, -2);
			rozkazDoKolejki_expression(5, -2, -2);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			int orginal_a, orginal_b, tr;			
			orginal_b = findIndex_value(b);				
			addToReg(to_string(b), "-1", b);
			genNum(b, regisX_index);
			temp_reg = regisX_index;
			orginal_a = findIndex_value(a);
			addToReg(to_string(a), "-1", a);
			tr = regisX_index;
			rozkazDoKolejki_expression(4, tr, orginal_a);
			rozkazDoKolejki_expression(4, temp_reg, orginal_b);
			if (a >= 0 && b >= 0)  
				knownMultiplication(a, b);
			else
				unknownMultiplication(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg);
			rozkazDoKolejki_expression(-2, tr, 0);	
		}
	}
}

void div_function(long long int a, long long int b) { //TODO

	cout << "WEJŚCIE DO div_function: a = " << a << ", b = " << b << endl;		
	
	// num / num
	if ( num_ide == 80 ) { 
        	
		cout << "div_function PRZED (1) -> temp_ll = " << temp_ll << endl; //test 
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a / b;
		cout << "div_function PO (1) -> temp_ll = " << temp_ll << endl;	//test	
		
		if (a < b && a >= 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}		
		else if (b == 2){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (b == 4){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 8){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 16){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 32){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg("div("+to_string(a)+")", "-1", a);
			genNum(a, regisX_index);
			int tr;
			temp_reg = regisX_index;			
			cout << "Rejestr małego a: " << tr << endl; //test
			addToReg("div("+to_string(b)+")", "-1", b);
			genNum(b, regisX_index);
			cout << "Rejestr małego b: " << regisX_index << endl; //test
			knownDivision(a, b);
			cout << "RegisX po knownDiv: " << regisX_index << endl;
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			tr = regisX_index;
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++			
		}
		
    	}
    
	// num / ide
	else if ( num_ide == 81 ) { 
        	
		cout << "div_function PRZED (2) -> temp_ll = " << temp_ll << endl;
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a / b;
		cout << "div_function PO (2) -> temp_ll = " << temp_ll << endl;		
		
		if (a < b && a >= 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}		
		else if (b == 2){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (b == 4){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 8){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 16){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 32){
			genNum(a, -2);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg("DIV(A)", "-1", a);
			genNum(a, regisX_index);
			int tr;
			temp_reg = regisX_index; //A
			regisY_index = findIndex_value(b);
			addToReg("DIV(B)", "-1", b);
			tr = regisX_index; //B
			rozkazDoKolejki_expression(4, tr, regisY_index);
			if (b >= 0)  
				knownDivision(a, b);
			else
				//unknownDivision(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++			
		}
		
    	}

	// ide / num
	else if ( num_ide == 10 ) { 
        	
		cout << "div_function PRZED (3) -> temp_ll = " << temp_ll << endl;
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a / b;
		cout << "div_function PO (3) -> temp_ll = " << temp_ll << endl;		
		
		if (a < b && a >= 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}
		else if (b == 2){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 1){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
		}

		else if (b == 4){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 8){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 16){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 32){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg("DIV(B)", "-1", b);
			genNum(b, regisX_index);
			int tr;
			temp_reg = regisX_index;
			regisY_index = findIndex_value(a);
			addToReg("DIV(A)", "-1", a);
			tr = regisX_index;
			rozkazDoKolejki_expression(4, regisX_index, regisY_index);
			if (a >= 0)  
				knownDivision(a, b);
			else
				//unknownDivision(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++			
		}
		
    	}

	// ide / ide
	else if ( num_ide == 11 ) { 
        	
		cout << "div_function PRZED (4) -> temp_ll = " << temp_ll << endl;
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a / b;
		cout << "div_function PO (4) -> temp_ll = " << temp_ll << endl;		
	
		if (a < b && a >= 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}				
		else if (b == 2){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 1){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
		}

		else if (b == 4){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 8){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 16){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (b == 32){
			rozkazDoKolejki_expression(4, -1, findIndex_value(a));
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
			rozkazDoKolejki_expression(7, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			int orginal_a, orginal_b, tr;			
			orginal_b = findIndex_value(b);				
			addToReg("DIV(B)", "-1", b);
			genNum(b, regisX_index);
			temp_reg = regisX_index;
			orginal_a = findIndex_value(a);
			addToReg("DIV(A)", "-1", a);
			tr = regisX_index;
			rozkazDoKolejki_expression(4, tr, orginal_a);
			rozkazDoKolejki_expression(4, temp_reg, orginal_b);
			if (a >= 0 && b >= 0)  
				knownDivision(a, b);
			else
				//unknownDivision(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++
		}
		
    	}
}

void mod_function(long long int a, long long int b) { //TODO

	cout << "WEJŚCIE DO mod_function: a = " << a << ", b = " << b << endl;		
	
	// num % num
	if ( num_ide == 80 ) { 
        	
		cout << "mod_function PRZED (1) -> temp_ll = " << temp_ll << endl;
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a % b;
		cout << "mod_function PO (1) -> temp_ll = " << temp_ll << endl;		
		
		if (a == b){
			rozkazDoKolejki_expression(6, -2, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 1){
			genNum(a, -2);
			rozkazDoKolejki_expression(6, -2, -2);
			rozkazDoKolejki_expression(8, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg("div("+to_string(a)+")", "-1", a);
			genNum(a, regisX_index);
			int tr;
			temp_reg = regisX_index;			
			cout << "Rejestr małego a: " << tr << endl; //test
			addToReg("div("+to_string(b)+")", "-1", b);
			genNum(b, regisX_index);
			cout << "Rejestr małego b: " << regisX_index << endl; //test
			knownModulo(a, b);
			cout << "RegisX po knownDiv: " << regisX_index << endl;
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			tr = regisX_index;
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++		
		}
		
    	}
    
	// num % ide
	else if ( num_ide == 81 ) { 
        	
		cout << "mod_function PRZED (2) -> temp_ll = " << temp_ll << endl;
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a % b;
		cout << "mod_function PO (2) -> temp_ll = " << temp_ll << endl;		
		
		if (a == b){
			rozkazDoKolejki_expression(6, -2, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 1){
			genNum(a, -2);
			rozkazDoKolejki_expression(6, -2, -2);
			rozkazDoKolejki_expression(8, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg("DIV(A)", "-1", a);
			genNum(a, regisX_index);
			int tr;
			temp_reg = regisX_index; //A
			regisY_index = findIndex_value(b);
			addToReg("DIV(B)", "-1", b);
			tr = regisX_index; //B
			rozkazDoKolejki_expression(4, tr, regisY_index);
			if (b >= 0)  
				knownModulo(a, b);
			else
				//unknownModulo(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++			
		}
		
    	}

	// ide % num
	else if ( num_ide == 10 ) { 
        	
		cout << "mod_function PRZED (3) -> temp_ll = " << temp_ll << endl;
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a % b;
		cout << "mod_function PO (3) -> temp_ll = " << temp_ll << endl;		
		
		if (a == b){
			rozkazDoKolejki_expression(6, -2, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 1){
			genNum(a, -2);
			rozkazDoKolejki_expression(6, -2, -2);
			rozkazDoKolejki_expression(8, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			addToReg("DIV(B)", "-1", b);
			genNum(b, regisX_index);
			int tr;
			temp_reg = regisX_index;
			regisY_index = findIndex_value(a);
			addToReg("DIV(A)", "-1", a);
			tr = regisX_index;
			rozkazDoKolejki_expression(4, regisX_index, regisY_index);
			if (a >= 0)  
				knownModulo(a, b);
			else
				//unknownModulo(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++			
		}
		
    	}

	// ide % ide
	else if ( num_ide == 10 ) { 
        	
		cout << "mod_function PRZED (4) -> temp_ll = " << temp_ll << endl;
		if (b == 0)
		temp_ll = 0;
		else		
		temp_ll = a % b;
		cout << "mod_function PO (4) -> temp_ll = " << temp_ll << endl;		
		
		if (a == b){
			rozkazDoKolejki_expression(6, -2, -2);
		}

		else if (b == 1){
			genNum(a, -2);
		}

		else if (a == 1){
			genNum(a, -2);
			rozkazDoKolejki_expression(6, -2, -2);
			rozkazDoKolejki_expression(8, -2, -1);
		}

		else if (a == 0 || b == 0){
			rozkazDoKolejki_expression(6, -2, -2);
		}	
			
		else{
			int orginal_a, orginal_b, tr;			
			orginal_b = findIndex_value(b);				
			addToReg("DIV(B)", "-1", b);
			genNum(b, regisX_index);
			temp_reg = regisX_index;
			orginal_a = findIndex_value(a);
			addToReg("DIV(A)", "-1", a);
			tr = regisX_index;
			rozkazDoKolejki_expression(4, tr, orginal_a);
			rozkazDoKolejki_expression(4, temp_reg, orginal_b);
			if (a >= 0 && b >= 0)  
				knownModulo(a, b);
			else
				//unknownModulo(a, b);
			rozkazDoKolejki_expression(6, temp_reg, temp_reg); //usuwam rejestr A
			rozkazDoKolejki_expression(6, tr, tr); //usuwam rejestr B
			rozkazDoKolejki_expression(-2, tr, 0); // usuwam rejestr B w C++		
		}
		
    	}
}

void gt_function(long long int a, long long int b) { //TODO

	cout << "WEJŚCIE DO gt_function: a = " << a << ", b = " << b << endl;		
	
	// num > num
	if ( num_ide == 80 ) { 
        	
		cout << "gt_function PRZED (1) -> temp_flag = " << temp_flag << endl;
		if (a > b)
			temp_flag = 1;
		else
			temp_flag = 0;
		cout << "gt_function PO (1) -> temp_flag = " << temp_flag << endl;		
		
		if (a > b){
			
			if (b < 8){
				addToReg("A>B", "-1", a);
				temp_reg = regisX_index;
				genNum_condition(a, temp_reg); 
				for(int i=0; i < b; i++) {
                			rozkazDoKolejki_condition(9, temp_reg, -1);
				}
            		}

			else{
				addToReg("A>B(A)", "-1", a);
				temp_reg = regisX_index;
				genNum_condition(a, temp_reg);
				addToReg("A>B(B)", "-1", b);
				genNum_condition(b, regisX_index);
				rozkazDoKolejki_condition(6, temp_reg, regisX_index);
				rozkazDoKolejki_condition(6, regisX_index, regisX_index);	
				rozkazDoKolejki_condition(-2, regisX_index, 0); // usuwam rejestr B w C++			
									
			}
		}
		
		else{
			if (a < 8){
				addToReg("A>B", "-1", a);
				temp_reg = regisX_index;
                		rozkazDoKolejki_condition(6, temp_reg, temp_reg);
            		}

			else{
				addToReg("A>B", "-1", a);
				temp_reg = regisX_index;
                		rozkazDoKolejki_condition(6, temp_reg, temp_reg);
									
			}
		}	
		
    	}
    
	// num > ide
	else if ( num_ide == 81 ) { 
        	
		cout << "gt_function PRZED (2) -> temp_flag = " << temp_flag << endl;
		if (b >= 0){
			if (a > b)
				temp_flag = 1;
			else
				temp_flag = 0;
		}
		else{
			temp_flag = -1;
		}
		cout << "gt_function PO (2) -> temp_flag = " << temp_flag << endl;		
		
		if (a <= b && b >= 0){
			addToReg("A>B", "-1", a);
			temp_reg = regisX_index;
			rozkazDoKolejki_condition(6, temp_reg, temp_reg);
		}
		else{	
			addToReg("A>B", "-1", a);
			temp_reg = regisX_index;       
			genNum_condition(a, temp_reg);
			if (b < 8 && b >= 0){ 
				for(int i=0; i < b; i++) {
	                		rozkazDoKolejki_condition(9, temp_reg, -1);
				}
            		}
			else{
				regisY_index = findIndex_value(b);
				rozkazDoKolejki_condition(6, temp_reg, regisY_index);	
			}
	        }
    	}

	// ide > num
	else if ( num_ide == 10 ) { 
        	
		cout << "mod_function PRZED (3) -> temp_flag = " << temp_flag << endl;
		if (a >= 0){
			if (a > b)
				temp_flag = 1;
			else
				temp_flag = 0;
		}
		else{
			temp_flag = -1;
		}
		cout << "mod_function PO (3) -> temp_flag = " << temp_flag << endl;

		if (a <= b && a >= 0){
			addToReg("A>B", "-1", a);
			temp_reg = regisX_index;
			rozkazDoKolejki_condition(6, temp_reg, temp_reg);
		}
		else{
			addToReg("A>B", "-1", a);
			temp_reg = regisX_index;
			regisY_index = findIndex_value(a);		
			rozkazDoKolejki_condition(4, temp_reg, regisY_index);		

			if (b < 8){ 
				for(int i=0; i < b; i++) {
                			rozkazDoKolejki_condition(9, temp_reg, -1);
				}
            		}
			else{
				addToReg("A>B(B)", "-1", b);
				genNum_condition(b, regisX_index);			
				rozkazDoKolejki_condition(6, temp_reg, regisX_index);
				rozkazDoKolejki_condition(-2, regisX_index, 0); // usuwam rejestr B w C++	
			}
	        }		
		
    	}

	// ide > ide
	else if ( num_ide == 10 ) { 
        	
		cout << "mod_function PRZED (4) -> temp_flag = " << temp_flag << endl;
		if (a >= 0 && b >= 0){
			if (a > b)
				temp_flag = 1;
			else
				temp_flag = 0;
		}
		else{
			temp_flag = -1;
		}
		cout << "mod_function PO (4) -> temp_flag = " << temp_flag << endl;

		if (a <= b && a >= 0) {
			addToReg("A>B", "-1", a);
			temp_reg = regisX_index;
			rozkazDoKolejki_condition(6, temp_reg, temp_reg);
        	}

	        else {
			addToReg("A>B", "-1", a);
			temp_reg = regisX_index;
			regisY_index = findIndex_value(a);
			rozkazDoKolejki_condition(4, temp_reg, regisY_index);
			regisX_index = findIndex_value(b);
			rozkazDoKolejki_condition(6, temp_reg, regisX_index);
        	}		
		
    	}
}

void unknownMultiplication(long long int a, long long int b) {
	//long long int wynik = 0;
	rozkazDoKolejki_expression(6, -2, -2); // SUB C C
	regisX_index = findIndex_value(b);
	regisY_index = findIndex_value(a);
	
	rozkazDoKolejki_expression(11, regisX_index, -1); // TODO obliczyć trzeci argument JZERO B j
      
	//while (b > 0) {
	rozkazDoKolejki_expression(8, regisX_index, -1); // INC B
	rozkazDoKolejki_expression(12, regisX_index, -1); // JODD B		
		//if (b%2 == 1){
			rozkazDoKolejki_expression(5, -2, regisY_index); // ADD C A
			//wynik += a;
		//}
	rozkazDoKolejki_expression(9, regisX_index, -1); // DEC B
	rozkazDoKolejki_expression(5, regisY_index, regisY_index); // ADD A A
        //a <<= 1;
	rozkazDoKolejki_expression(7, regisX_index, -1); // ADD A A
        //b >>= 1;
      //}
	rozkazDoKolejki_expression(10, -1, -1); // TODO JUMP j+7
	//return wynik;
    }

void knownMultiplication(long long int a, long long int b) {
	long long int wynik = 0;
	
	regisY_index = findIndex_value(a);
	regisX_index = findIndex_value(b);
	cout << "regisY_index: " << regisY_index << endl;
	rozkazDoKolejki_expression(6, -2, -2); // SUB C C
	
	while (b > 0) {		
		if (b%2 == 1){
			rozkazDoKolejki_expression(5, -2, regisY_index); // ADD C A
			wynik += a;
		}
	rozkazDoKolejki_expression(5, regisY_index, regisY_index); // ADD A A
        a <<= 1;
	rozkazDoKolejki_expression(7, regisX_index, -1); // HALF B
        b >>= 1;
      }
    }

void unknownDivision(long long a, long long b){ //TODO
	
	// X := A / B, X == D
	int regC_index;
	addToReg("div(C)", "-1", 1);
	regC_index = regisX_index;
	
	long long c = 1; // SUB C C, INC C
	rozkazDoKolejki_expression(6, regC_index, regC_index); // SUB C C
	rozkazDoKolejki_expression(8, regC_index, -1); // INC C

	
	long long d = 0; // SUB D D
	rozkazDoKolejki_expression(6, -2, -2); // SUB D D

	
	regisY_index = findIndex_value(a); // A
	regisX_index = findIndex_value(b); // B	
	

	while(a > b){ // JZERO E n+3, ale dla jakiegoś E = A - B
		b = b + b;	// ADD B B
		rozkazDoKolejki_expression(5, regisX_index, regisX_index); // ADD B B
		c = c + c;	// ADD C C
		rozkazDoKolejki_expression(5, regC_index, regC_index); // ADD C C
	}


	do {
		if (a >= b) {
			a = a - b; // SUB A B
			rozkazDoKolejki_expression(6, regisY_index, regisX_index); // SUB A B
			d = d + c; // ADD D C
			rozkazDoKolejki_expression(5, -2, regC_index); // ADD D C
		}
	
	b = b / 2; // HALF B
	rozkazDoKolejki_expression(7, regisX_index, -1); // HALF B
	c = c / 2; // HALF C
	rozkazDoKolejki_expression(7, regC_index, -1); // HALF B
	
	} while (c != 0);
		
	rozkazDoKolejki_expression(-2, regC_index, 0); // usuwam rejestr C w C++, ponieważ c==0	
	//return d; //dzielenie
	// return a; //modulo

}

void knownDivision(long long a, long long b){ 
	
	// X := A / B, X == D
	int regC_index;
	addToReg("div(C)", "-1", 1);
	regC_index = regisX_index;
	
	long long c = 1; // SUB C C, INC C
	rozkazDoKolejki_expression(6, regC_index, regC_index); // SUB C C
	rozkazDoKolejki_expression(8, regC_index, -1); // INC C

	
	long long d = 0; // SUB D D
	rozkazDoKolejki_expression(6, -2, -2); // SUB D D

	
	regisY_index = findIndex_value(a); // A
	regisX_index = findIndex_value(b); // B
	cout << "DUPA regisX_index: " << regisX_index << endl;	
	

	while(a > b){ 
		b = b + b;	// ADD B B
		rozkazDoKolejki_expression(5, regisX_index, regisX_index); // ADD B B
		c = c + c;	// ADD C C
		rozkazDoKolejki_expression(5, regC_index, regC_index); // ADD C C
	}


	do {
		if (a >= b) {
			a = a - b; // SUB A B
			rozkazDoKolejki_expression(6, regisY_index, regisX_index); // SUB A B
			d = d + c; // ADD D C
			rozkazDoKolejki_expression(5, -2, regC_index); // ADD D C
		}
	
	b = b / 2; // HALF B
	rozkazDoKolejki_expression(7, regisX_index, -1); // HALF B
	c = c / 2; // HALF C
	rozkazDoKolejki_expression(7, regC_index, -1); // HALF B
	
	} while (c != 0);
		
	rozkazDoKolejki_expression(-2, regC_index, 0); // usuwam rejestr C w C++, ponieważ c==0	
	//return d; //dzielenie
	// return a; //modulo

}

void unknownModulo(long long a, long long b){
	
	// X := A % B, X == A

	long long c = 1;
	long long d = 0;

	if (b == 0){
		//return 0;
	}

	while(a > b){
		b = b + b;
		c = c + c;
	}


	do {
		if (a >= b) {
			a = a - b;
			d = d + c;
		}
	
	b = b / 2;
	c = c / 2;
	
	} while (c != 0);
		
		
	//return a; //modulo

}

void knownModulo(long long a, long long b){ 
	
	int regC_index;
	addToReg("div(C)", "-1", 1);
	regC_index = regisX_index;
	
	long long c = 1; // SUB C C, INC C
	rozkazDoKolejki_expression(6, regC_index, regC_index); // SUB C C
	rozkazDoKolejki_expression(8, regC_index, -1); // INC C

	
	long long d = 0; // SUB D D
	rozkazDoKolejki_expression(6, -2, -2); // SUB D D

	
	regisY_index = findIndex_value(a); // A
	regisX_index = findIndex_value(b); // B
	cout << "DUPA regisX_index: " << regisX_index << endl;	
	

	while(a > b){ 
		b = b + b;	// ADD B B
		rozkazDoKolejki_expression(5, regisX_index, regisX_index); // ADD B B
		c = c + c;	// ADD C C
		rozkazDoKolejki_expression(5, regC_index, regC_index); // ADD C C
	}


	do {
		if (a >= b) {
			a = a - b; // SUB A B
			rozkazDoKolejki_expression(6, regisY_index, regisX_index); // SUB A B
			d = d + c; // ADD D C
			rozkazDoKolejki_expression(5, -2, regC_index); // ADD D C
		}
	
	b = b / 2; // HALF B
	rozkazDoKolejki_expression(7, regisX_index, -1); // HALF B
	c = c / 2; // HALF C
	rozkazDoKolejki_expression(7, regC_index, -1); // HALF B
	
	} while (c != 0);
	
	rozkazDoKolejki_expression(4, -2, regisY_index); // COPY D A 	
	rozkazDoKolejki_expression(-2, regC_index, 0); // usuwam rejestr C w C++, ponieważ c==0	
	//return d; //dzielenie
	// return a; //modulo

}

void pokazRejestr(){ //DO USUNIĘCIA W OSTATECZNEJ WERSJI
	for (int i=0; i<7; i++){
		cout << "Lierka " << i << ": nazwa - " << regis_name[i] << ", wartość - " << regis_value[i] << endl; 	
	}

	cout << "Lierka " << 7 << "(AKUM.): nazwa - " << regis_name[7] << ", wartość - " << regis_value[7] << endl;
}

int findIndex(string name){
	int ind;	
	for (int i=0; i<8; i++){
		ind=i;			
		if(!(regis_name[i].compare(name))){
			break;
		}
  	}
	return ind; 
}

int findIndex_value(long long int value){
	int ind, end;	
	for (int i=7; i>=0; i--){
		ind=i;			
		if(regis_value[i] == value){
			break;
		}
		end=i;
  	}
	
	if (ind != end)
		return ind;
	else
		return -1; 
}

void addToReg(string name, string empty_name, long long int value){
	bool end = false;	
	for (int i=0; i<8; i++){
		regisX_index=i;				
			
		if(!(regis_name[i].compare(name))){
			cout << name << " jest już w rejestrze (wszedł IF)" << endl;
			regis_value[i] = value;
			end = true;
			break;
		}
	}
	
	if (!end){
		for (int i=0; i<8; i++){
			regisX_index=i; 				
			if (!(regis_name[i].compare(empty_name))){
				cout << name << " nie jest w rejestrze -> dodawanie (wszedł ELSE IF)" << endl;
				regis_name[i] = name;
				regis_value[i] = value;
				end = true;
				break;
			}
		}
	}

	if (!end){
		cout << "REJESTR PEŁNY!!!" << endl;
	}
}

void removeFromReg_index(int index, string empty_name, long long int empty_value){
	regis_name[index] = empty_name;
	regis_value[index] = empty_value;
	cout << "Usuwam rejestr " << (char)('A'+index) << " (tylko w C++)" << endl;	
}

void rozkazDoKolejki_expression(int nr_rozkazu, int rX, int rY){
	rozkazy_expression[rozkazy_index_expression][0] = nr_rozkazu;
	rozkazy_expression[rozkazy_index_expression][1] = rX;
	rozkazy_expression[rozkazy_index_expression][2] = rY;
	rozkazy_index_expression++;
}

void rozkazDoKolejki_condition(int nr_rozkazu, int rX, int rY){
	rozkazy_condition[rozkazy_index_condition][0] = nr_rozkazu;
	rozkazy_condition[rozkazy_index_condition][1] = rX;
	rozkazy_condition[rozkazy_index_condition][2] = rY;
	rozkazy_index_condition++;
}

void rozkazDoKolejki(int nr_rozkazu, int rX, int rY){
	rozkazy[rozkazy_index][0] = nr_rozkazu;
	rozkazy[rozkazy_index][1] = rX;
	rozkazy[rozkazy_index][2] = rY;
	rozkazy_index++;
}

void wykonajRozkazy(){
	for (int i=0; i<rozkazy_index; i++){
		if (rozkazy[i][0]==-1)
			break;
		else if (rozkazy[i][0]==0){
			pushCommand("GET", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==1){
			pushCommand("PUT", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==2){
			pushCommand("LOAD", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==3){
			pushCommand("STORE", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==4){
			pushCommand("COPY", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==5){
			pushCommand("ADD", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==6){
			pushCommand("SUB", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==7){
			pushCommand("HALF", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==8){
			pushCommand("INC", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==9){
			pushCommand("DEC", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==10){
			pushCommand("JUMP", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==11){
			pushCommand("JZERO", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==12){
			pushCommand("JODD", rozkazy[i][1], rozkazy[i][2]);
		}
		else if (rozkazy[i][0]==-2){
			cout << "W tym miejscu USUWAM rejestr B z dzielenia, index = " << regisX_index << endl; // test
			removeFromReg_index(rozkazy[i][1], "-1", 0); //usuwam w C++ rejestr B
		}
	}

	for (int i=0; i<100; i++){
		rozkazy[i][0]=-1;
		rozkazy[i][1]=-1;
		rozkazy[i][2]=-1;
	}

	rozkazy_index=0;	
 
}

void wykonajRozkazy_expression(){
		
	for (int i=0; i<rozkazy_index_expression; i++){
		
		

		if (rozkazy_expression[i][0]==-1)
			break;
		else{
		
			if (rozkazy_expression[i][1] == -2)
				rozkazy_expression[i][1] = regisX_index;
			else if (rozkazy_expression[i][1] == -3)
				rozkazy_expression[i][1] = regisY_index;

			if (rozkazy_expression[i][2] == -2)
				rozkazy_expression[i][2] = regisX_index;
			else if (rozkazy_expression[i][2] == -3)
				rozkazy_expression[i][2] = regisY_index;
			
			rozkazDoKolejki(rozkazy_expression[i][0], rozkazy_expression[i][1], rozkazy_expression[i][2]);
			
		}
	}

	cout << "Wyjście z pętli" << endl;

	for (int i=0; i<100; i++){
		rozkazy_expression[i][0]=-1;
		rozkazy_expression[i][1]=-1;
		rozkazy_expression[i][2]=-1;
	}

	rozkazy_index_expression=0;
}

void wykonajRozkazy_condition(){	

	for (int i=0; i<rozkazy_index_condition; i++){
	
		if (rozkazy_condition[i][0]==-1)
			break;
		else{
		
			if (rozkazy_condition[i][1] == -2)
				rozkazy_condition[i][1] = regisX_index;
			else if (rozkazy_condition[i][1] == -3)
				rozkazy_condition[i][1] = regisY_index;

			if (rozkazy_condition[i][2] == -2)
				rozkazy_condition[i][2] = regisX_index;
			else if (rozkazy_condition[i][2] == -3)
				rozkazy_condition[i][2] = regisY_index;
			else if (rozkazy_condition[i][2] == -4){
				cout << "(i) = " << i << endl;
				rozkazy_condition[i][2] = rozkazy_index_condition - i + 100; 								
				jump = i;
			}
			rozkazDoKolejki(rozkazy_condition[i][0], rozkazy_condition[i][1], rozkazy_condition[i][2]);
			
		}
	}

	cout << "Wyjście z pętli" << endl;

	for (int i=0; i<100; i++){
		rozkazy_condition[i][0]=-1;
		rozkazy_condition[i][1]=-1;
		rozkazy_condition[i][2]=-1;
	}

	cout << "Końcowe rozkazy_index_condition = " << rozkazy_index_condition << endl;
	jump = rozkazy_index_condition - jump;
	rozkazy_index_condition=0;
}

int main(int argv, char* argc[]){
	assignFlag = true;
	yyparse();
	return 0;
}

int yyerror(string str){
    cout << "Błąd [okolice linii " << yylineno << "]: " << str << endl;
	/*return 1;*/
    exit(1);
}

