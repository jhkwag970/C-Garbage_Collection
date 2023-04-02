#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "tree.h"

#include "scanner.h"
#include "parser.h"
#include "executor.h"

#include "memory.h"


void executeProcedure();
void executeDeclSeq(struct nodeDeclSeq *ds2);
void executeStmtSeq(struct nodeStmtSeq *ss2);
void executeDecl(struct nodeDecl *d2);
void executeDeclInteger(struct nodeDeclInteger *di2);
void executeDeclRecord(struct nodeDeclRecord *dr2);
void executeStmt(struct nodeStmt *s2);
void executeAssign(struct nodeAssign *ass2);
void executeIf(struct nodeIf *i2);
void executeLoop(struct nodeLoop *lp2);
void executeOut(struct nodeOut *out2);
int executeIndex(struct nodeIndex *idx2);
int executeExpr(struct nodeExpr *exp2);
int executeTerm(struct nodeTerm *tm2);
int executeFactor(struct nodeFactor *fac2);
int executeCond(struct nodeCond *c2);
int executeCmpr(struct nodeCmpr *cmp2);

void executeCall(struct nodeCall* call2);
void executeFunc(struct nodeFunc *func2, struct nodeParam* param2);
void executeParam(struct nodeParam *param2);


int findFunction(char* id);

extern struct nodeProcedure *p;
extern struct nodeFunc **funcArray; 
extern int funcIdx;
static int indentSize;

/*
*
* Helper functions
*
*/

static void indents(int indent) {
	for (int i=0; i<indent; i++) {
		printf("  ");
	}
}

/*
*
* Print functions go here
*
*/

void executeTree(char* inputFile){
	scanner_open(inputFile);
	initializeFP();
	initializeSize();
	executeProcedure();
	scanner_close();
}
void executeProcedure(){

	executeDeclSeq(p->ds);
	memory_init();
	executeStmtSeq(p->ss);
	// printIntValues();
	// printRecValues();
}


void executeDeclSeq(struct nodeDeclSeq *ds2){

	executeDecl(ds2->d);
	if(ds2->ds != NULL){
		executeDeclSeq(ds2->ds);
	}
}

void executeDecl(struct nodeDecl *d2){
	if(d2->di != NULL){
		executeDeclInteger(d2->di);
	}
	if(d2->dr != NULL){
		executeDeclRecord(d2->dr);
	}
}

void executeDeclInteger(struct nodeDeclInteger *di2){
	//printf("integer %s;\n",di2->id);
	declare(di2->id, INTEGER);
}

void executeDeclRecord(struct nodeDeclRecord *dr2){
	//printf("record %s;\n",dr2->id);
	declare(dr2->id, RECORD);
}

void executeStmtSeq(struct nodeStmtSeq *ss2){
	executeStmt(ss2->s);

	if(ss2->ss != NULL){
		executeStmtSeq(ss2->ss);
	}

	
}

void executeStmt(struct nodeStmt *s2){
	// only in() case in executeFactor()
	if(s2->ass != NULL){
		executeAssign(s2->ass);
	}
	if(s2->i != NULL){
		executeIf(s2->i);
	}
	if(s2->lp != NULL){
		executeLoop(s2->lp);
	}
	//(x)
	if(s2->out != NULL){
		executeOut(s2->out);
	}
	if(s2->call != NULL){
		executeCall(s2->call);
	}
}

void executeCall(struct nodeCall* call2){
	//check location is -1;
	int funcLocation = findFunction(call2->id);

	if(funcLocation == -1){
		printf("ExecuteCall Error: Undeclared Function\n");
		exit(0);
	}

	executeFunc(funcArray[funcLocation], call2->param);
}

void executeFunc(struct nodeFunc *func2, struct nodeParam* param2){
	initializeSize();
	executeParam(func2->param);
	executeDeclSeq(func2->ds);
	memory_init();

	initializeParam(param2->id1, param2->id2, func2->param->id1, func2->param->id2);
	
	executeStmtSeq(func2->ss);
	stackOutFP();
}

void executeParam(struct nodeParam *param2){
	declare(param2->id1, RECORD);
	if(param2->id2 != NULL){
		declare(param2->id2, RECORD);
	}
}

//(x)
void executeAssign(struct nodeAssign *ass2){
	//printf("%s", ass2->id);
	if(ass2->idx != NULL){
		int idx = executeIndex(ass2->idx);
		//printf(":=");
		int value = executeExpr(ass2->exp);
		if(idx == -1){  //(x)
			//id:=<expr>
			store(ass2->id, value);
		}else{ //(x)
			//id[idx]:=<expr>
			storeRec(ass2->id, idx, value);
		}
	}else if(ass2->exp != NULL){ //(x)
		//printf(":=new record[");
		int size = executeExpr(ass2->exp);
		//printf("]");
		allocateRecord(ass2->id, size);
	}else if(ass2->id2 != NULL){   //(x)
		//printf(":=record %s", ass2->id2);
		record(ass2->id, ass2->id2);
	}	
	//printf(";\n");

}

//(x)
int executeIndex(struct nodeIndex *idx2){
	int idx = -1;
	if(idx2->exp != NULL){
		//printf("[");
		idx = executeExpr(idx2->exp);
		//printf("]");
	}
	return idx;
}

//(X)
void executeIf(struct nodeIf *i2){
	//if executeCond 
	//	executeStmtSeq

	//printf("if ");
	//printf(" then\n");
	int cond = executeCond(i2->c);
	if (cond){
		executeStmtSeq(i2->ss);
	}

	
	if(i2->ss2 != NULL){
		//printf("else\n");

		//if (!executeCond)
		//	executeStmtSeq
		if(!cond){
			executeStmtSeq(i2->ss2);
		}
	}
	//printf("end\n");

}

//(x)
int executeCond(struct nodeCond *c2){
	int boolean = 0;
	if(c2->cmp !=NULL){
		boolean = executeCmpr(c2->cmp);
		if(c2->c != NULL){
			int rBoolean2 = executeCond(c2->c);
			if(!strcmp(c2->sign, "OR")){
				
				if(boolean || rBoolean2){
					boolean = 1;
				}
			}else if(!strcmp(c2->sign, "AND")){

				if(boolean && rBoolean2){
					boolean = 1;
				}
			}
		}
	}else{
		//printf("not ");
		boolean = executeCond(c2->c);
		if(boolean){
			boolean = 0;
		}else{
			boolean = 1;
		}
	}
	return boolean;
}

//(x)
int executeCmpr(struct nodeCmpr *cmp2){
	int boolean = 0;
	int lValue = executeExpr(cmp2->exp);
	int rValue = executeExpr(cmp2->exp2);
	if(!strcmp(cmp2->sign, "=")){
		//printf("=");
		if(lValue == rValue){
			boolean = 1;
		}
	}else if(!strcmp(cmp2->sign, "<")){
		//printf("<");
		if(lValue < rValue){
			boolean = 1;
		}
	}
	return boolean;
}

void executeLoop(struct nodeLoop *lp2){
	//while (executeCond)
	//	executeStmtSeq


	//printf("while ");
	while(executeCond(lp2->c)){
		executeStmtSeq(lp2->ss);
	}
	//printf(" do\n");
	
	//printf("end\n");
}


//(x)
void executeOut(struct nodeOut *out2){
	//printf("out(");
	int value = executeExpr(out2->exp);
	printf("%d\n", value);
	//printf(");\n");
}

//(x)
int executeExpr(struct nodeExpr *exp2){
	int value = executeTerm(exp2->tm);

	if(exp2->math != NULL){
		int nextValue = executeExpr(exp2->exp);
		if(!strcmp(exp2->math, "+")){
			//printf("+");
			value = value + nextValue;
		}else if(!strcmp(exp2->math, "-")){
			//printf("-");
			value = value - nextValue;
		}
		
	}
	return value;
}

//(x)
int executeTerm(struct nodeTerm *tm2){
	int value = executeFactor(tm2->fac);
	
	if(tm2->math != NULL){
		int nextValue = executeTerm(tm2->tm);
		if(!strcmp(tm2->math, "*")){
			//printf("*");
			value = value * nextValue;
		}else if(!strcmp(tm2->math, "/")){
			//printf("/");
			if(nextValue == 0){
				printf("Error: Cannot divisible by 0\n");
				exit(0);
			}
			value = value / nextValue;
		}
	}
	return value;
}

//(x)
int executeFactor(struct nodeFactor *fac2){
	int value;
	if(fac2->id != NULL){
		//printf("%s", fac2->id);
		if(fac2->exp != NULL){ //(x)
			// id[expr]
			//printf("[");
			int idx = executeExpr(fac2->exp);
			//printf("]");
			value = recallRec(fac2->id, idx);
		}else{            //(x)
			// id 
			value = recall(fac2->id);
		}
	}else if(fac2->cnt != -1){  //(x)
		//printf("%d", fac2->cnt); 
		value=fac2->cnt;
	}else if(fac2->exp != NULL){   //(x)
		//printf("("); 
		value = executeExpr(fac2->exp);
		//printf(")");
	}else{
		//printf("in()");
		int token = currentToken();
		if(token == EOS){
			printf("Error: Input File reached at the end of the line\n");
			exit(0);
		}
		value = getConst();
		nextToken();
	}
	return value;
}


//find the location of function in the struct array of function
int findFunction(char* id){
	int i;
	for(i=0; i<funcIdx;i++){
		if(!strcmp(funcArray[i]->id, id)){
			return i;
		}
	}
	return -1;
}
