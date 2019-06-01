#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stringhandle.h"
#define wordLength 20

typedef struct Nodes{
  char word[wordLength];
  int times;
  struct Indices *head;
  struct Nodes *next;
} node;

typedef struct Indices{
  int line;
  struct Indices *next;
} word_index;

node *lindex_head = NULL;

// list of all capitalized words //
typedef struct CapWords {
  char word[wordLength];
  int line;
  struct CapWords *next;
} cap; 

cap *lname_head = NULL; // list of people or places' names 
cap *lwait_head = NULL; // list of words with capitalized first letters that need revalidating 


// functions for lists that hold capitalized words //
void insert(char *word, int line, cap **head) {
  cap *new = (cap *) malloc(sizeof(cap));
  strcpy(new->word, word);
  new->line = line;
  new->next = *head;
  *head = new;
}

int search(char *word, cap *head) {
  cap *current = head;
  if(head == NULL)
    return 0;
  while(strcmp(current->word, word) != 0) {
    if(current->next == NULL) // last node //
      return 0;
    else current = current->next;
  }
  return 1;
}

// functions for lists that hold words with indexes //
int index_search(int line, word_index *head) {
	word_index *current = head;
	if(head == NULL)
	  return 0;
	while(current->line != line) {
	  if(current->next == NULL) // last node //
	      return 0;
	  else current = current->next;
	}
  	return 1;
}

void insertIndex(int line, word_index **head) {
	word_index *new = (word_index *) malloc(sizeof(word_index));
	new->line = line;
	if(*head == NULL || (*head)->line > line) {
		new->next = *head;
		*head = new;
	}
	else {
		word_index *current = *head;
		while(current->next != NULL && current->next->line < line) {
			current = current->next;
		}
		new->next = current->next;
		current->next = new;
	}
}

node* word_search(char *word, node *head) {
	node *current = head;
	if(head == NULL)
		return NULL;
	while(strcmp(current->word, word) != 0) {
		if(current->next == NULL)
			return NULL;
		else current = current->next;
	}
	return current;
}


void insertWord(char *word, int line, node **head) {
	node *result = word_search(word, *head);
	// if word alr existed //
	if(result != NULL) {
		result->times ++;
		// if this word hasn't been indexed in the same line //
		if(index_search(line, result->head) == 0) {
			// insert to index list in order //
			insertIndex(line, &result->head);
		}
	}
	// if word not existed //
	else {
		node *new = (node *) malloc(sizeof(node));
		strcpy(new->word, word);
		new->times = 1;
		new->head = NULL;
		insertIndex(line, &new->head);
		// insert to word list in order //
		if(*head == NULL || strcmp((*head)->word, word) > 0) {
			new->next = *head;
			*head = new;
		}
		else {
			node *current = *head;
			while(current->next != NULL && strcmp(current->next->word, word) < 0) {
				current = current->next;
			}
			new->next = current->next;
			current->next = new;
		}
	}
}

int main() {
  // get a word list from stopw.txt //
  char **wordlist;
  FILE *w_fptr;
  // terminate if could not open file //
  if((w_fptr = fopen("stopw.txt", "r")) == NULL) {
    exit(1);
  }
  int line_count = 0;
  char c;
  // get the number of words //
  while((c = fgetc(w_fptr)) != EOF) {
    if(c == '\n')
      line_count ++;
  }
  
  // initialize array with line_count elements //
  wordlist = (char **) malloc(line_count * sizeof(char *));
  int i;
  rewind(w_fptr);
  for(i = 0; i < line_count; i ++) {
    wordlist[i] = (char *) malloc(wordLength * sizeof(char));
    fscanf(w_fptr, "%s", wordlist[i]);
  }
  
  fclose(w_fptr);

  
  FILE *fptr;
  if((fptr = fopen("vanban.txt", "r")) == NULL) {
    exit(1);
  }

  int begin_of_sentence_flag = 1;
  int seen_a_dot_flag = 1; 
  char word[wordLength];
  int pos = 0;
  int line = 1;
  int actual_length;
  int cap_word = 0;
  while((c = fgetc(fptr)) != EOF) {
    // get a complete word -> standardize -> validate -> add to list in alphabet order //
    if(c == '\n' || c == ' ' || c == '\r') {
      word[pos] = '\0';
      
      // handle the word //
      if(strlen(word) != 0) {
	      if(word[pos - 1] == '.') {
	       seen_a_dot_flag = 1;
	      }
	      else seen_a_dot_flag = 0;
	      
	      if(isupper(word[0]))
	      	cap_word = 1;
	      else cap_word = 0;

	      actual_length = standardizeWord(word, strlen(word)); // length of the word without quotation marks, dots or commas //

	      if(isValidWord(word, strlen(word)) && !isWordinList(word, wordlist, line_count) && cap_word == 0) {
	      	insertWord(word, line, &lindex_head);
	      }
	      else if(isValidWord(word, strlen(word)) && !isWordinList(word, wordlist, line_count) && begin_of_sentence_flag == 0 && cap_word == 1) { // capitalized words not at the beginning of a sentence //
	        // add to name list //
	        insert(word, line, &lname_head);
	      }
	      else if(isValidWord(word, strlen(word)) && !isWordinList(word, wordlist, line_count) && begin_of_sentence_flag == 1 && cap_word == 1) { // capitalized words at the beginning of a sentence //
	        insert(word, line, &lwait_head);
	      }
	       
      }
      if(c == '\n')
      	line ++;
	  // if theres a dot in the end of this word, raise the flag for the next word //
	  begin_of_sentence_flag = seen_a_dot_flag;
	  // reset position to store the next word //
	  pos = 0;
	  word[pos] = '\0';
      
    }
    else {
      word[pos] = c;
      pos ++;
    }
  }
  
  // check if words in wait list are names //
  cap *temp = lwait_head;
  while(temp != NULL) {
  	// if the word is not in name list, add it to index list //
  	if(search(temp->word, lname_head) == 0) {
  		insertWord(temp->word, temp->line, &lindex_head);
  	}
  	temp = temp->next;
  }
  
  node *current;
  word_index *index_current;
  current = lindex_head;
  while(current != NULL) {
  	printf("%s %d ", current->word, current->times);
  	index_current = current->head;
  	while(index_current != NULL) {
  		if(index_current->next != NULL) 
  			printf("%d,", index_current->line);
  		else printf("%d\n", index_current->line);
  		index_current = index_current->next;
  	}
  	current = current->next;
  }
  
  fclose(fptr);
  
  
  return 0;
}
