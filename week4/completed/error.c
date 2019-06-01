/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorCode err, int lineNo, int colNo) {
  switch (err) {
  case ERR_ENDOFCOMMENT:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_ENDOFCOMMENT);
    break;
  case ERR_IDENTTOOLONG:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_IDENTTOOLONG);
    break;
  case ERR_INVALIDCHARCONSTANT:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCHARCONSTANT);
    break;
  case ERR_INVALIDSYMBOL:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSYMBOL);
    break;
  case ERR_INVALIDCONSTANT:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCONSTANT);
    break;
  case ERR_INVALIDTYPE:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDTYPE);
    break;
  case ERR_INVALIDBASICTYPE:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDBASICTYPE);
    break;
  case ERR_INVALIDPARAM:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDPARAM);
    break;
  case ERR_INVALIDSTATEMENT:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSTATEMENT);
    break;
  case ERR_INVALIDARGUMENTS:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDARGUMENTS);
    break;
  case ERR_INVALIDCOMPARATOR:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCOMPARATOR);
    break;
  case ERR_INVALIDEXPRESSION:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDEXPRESSION);
    break;
  case ERR_INVALIDTERM:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDTERM);
    break;
  case ERR_INVALIDFACTOR:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDFACTOR);
    break;
  case ERR_INVALIDCONSTDECL:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCONSTDECL);
    break;
  case ERR_INVALIDTYPEDECL:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDTYPEDECL);
    break;
  case ERR_INVALIDVARDECL:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDVARDECL);
    break;
  case ERR_INVALIDSUBDECL:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSUBDECL);
    break;
  case ERR_INVALIDINDEX:
    printf("\n%d-%d:%s\n", lineNo, colNo, ERM_INVALIDINDEX);
    break;
  }
  exit(0);
}

void missingToken(TokenType tokenType, int lineNo, int colNo) {
  printf("\n%d-%d:Missing %s\n", lineNo, colNo, tokenToString(tokenType));
  exit(0);
}

void assert(char *msg) {
  printf("%s\n", msg);
}
