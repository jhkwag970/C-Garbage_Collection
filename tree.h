#ifndef TREE_H
#define TREE_H

/*
*
* Define structs to serve as you tree nodes
*
*/



struct nodeParam{ //call
    char* id1;
    char* id2;
};

struct nodeCall{ //call
    char* id;
    struct nodeParam* param;
};


struct nodeFunc{ //func
    char* id;
    struct nodeParam* param;
    struct nodeDeclSeq* ds;
    struct nodeStmtSeq* ss;
};


struct nodeFuncSeq{ //fs
    struct nodeFunc* func;
    struct nodeFuncSeq* fs;
};


struct nodeExpr{ //exp
    struct nodeTerm *tm;
    char* math;
    struct nodeExpr *exp;
};


struct nodeFactor{ //fac
    char *id;
    int cnt;
    struct nodeExpr *exp;
};


struct nodeTerm{ //tm
    struct nodeFactor *fac;
    char* math;
    struct nodeTerm *tm;
};


struct nodeCmpr{ //cmp
    struct nodeExpr *exp;
    char *sign;
    struct nodeExpr *exp2;
};


struct nodeCond{ //c
    struct nodeCmpr *cmp;
    char *sign;
    struct nodeCond *c;
};


struct nodeLoop{ //lp
    struct nodeCond *c;
    struct nodeStmtSeq *ss;
};


struct nodeIf{ //i
    struct nodeCond *c;
    struct nodeStmtSeq *ss;
    struct nodeStmtSeq *ss2;
};

struct nodeOut{ //out
    struct nodeExpr *exp;
};

struct nodeIndex{ //idx
    struct nodeExpr *exp;
};


struct nodeAssign{ //ass
    char *id;
    struct nodeIndex *idx;
    struct nodeExpr *exp;
    char *id2;
};


struct nodeStmt{ //s
    struct nodeAssign *ass;
    struct nodeIf *i;
    struct nodeLoop * lp; //**
    struct nodeOut *out;
    struct nodeCall* call;
};

struct nodeDeclRecord{ //dr
    char *id;
};

struct nodeDeclInteger{ //di
    char *id;
};

struct nodeDecl{ //d
    struct nodeDeclInteger *di;
    struct nodeDeclRecord *dr;
};

struct nodeStmtSeq{ //ss
    struct nodeStmt *s;
    struct nodeStmtSeq *ss;
};

struct nodeDeclSeq{ //ds
    struct nodeDecl* d;
    struct nodeDeclSeq* ds;
};


struct nodeProcedure {
  char* id;
  struct nodeFuncSeq* fs;
  struct nodeDeclSeq* ds;
  struct nodeStmtSeq* ss;
};

#endif