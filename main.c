#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "parser.h"
#include "executor.h"
#include "tree.h"

int main(int argc, char *argv[]) {  
  // scanner(argv[1]);
  // executeTree(argv[2]);

  scanner("Correct/test.code");
  executeTree("Correct/1.data");

  return 0;
}