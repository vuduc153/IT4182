#include <ctype.h>
#include <string.h>
#include "stringhandle.h"

int isValidWord(char *word, int length) {
	int i;
	for(i = 0; i < length; i ++) {
		if(!isalpha(word[i]))
			return 0;
	}
	return 1;
}

int standardizeWord(char *word, int length) {
	int i;
	// remove quotation marks, dots and commas // 
	if(word[length - 1] == '.' || word[length - 1] == ',' || word[length - 1] == ')' || word[length - 1] == '>' || word[length - 1] == '\'' || word[length - 1] == '\"') {
		word[length - 1] = '\0';
		length --;
	}
	if(word[0] == '(' || word[0] == '<' || word[0] == '\'' || word[0] == '\"') {
		memmove(word, word + 1, length);
		length --;
	}
	// transform all letters to lower case //
	for(i = 0; i < length; i ++) {
		if(isalpha(word[i]))
			word[i] = tolower(word[i]);
	}
	return length;
}

int isWordinList(char *word, char **list, int lengthList) {
	int i;
	for(i = 0; i < lengthList; i ++) {
		if(strcmp(word, list[i]) == 0)
			return 1;
	}
	return 0;
}
