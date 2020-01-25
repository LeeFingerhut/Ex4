#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

/*
 * name: char_to_ind
 *
 * description: translate a letter to the corresponding index in node's children array
 *
 * input:
 *  c - char
 *
 * return:
 *  index in range (0, NUM_LETTERS-1)
 */
static int char_to_ind (char c) {
    return (int) (c - 'a') ;
}

/*
 * name: push_tree
 *
 * description: pushed the word to the words tree
 *
 * note: functions as a recursive routine
 *
 * input:
 *  n - reference node
 *  str - word to push
 *
 * return:
 *  TREE_OK, TREE_FAIL
 */
tree_status push_tree (node_t* n,
                       char* str) {
    /* this is a guard for entering a blank word */
    if ( !str ) { /* when word is empty - do nothing */
        /* we are all good :) */
        return TREE_OK ;
    }
    /* take the first letter and convert is to lowercase */
    char c = *str ;
    c = tolower(c) ;
    /* translate the first letter to a numerical index in the node's children array  */
    int ind = char_to_ind(c) ;
    if ( !n->children[ind] ) { /* if relevant child is not initialized yet */
        /* memory allocation */
        n->children[ind] = (node_t*) malloc(sizeof(node_t)) ;
        /* verify allocation */
        if ( !n->children[ind] ) {
            log_err("memory allocation failed ! \n") ;
            return TREE_FAIL ;
        }
        /* set memory to zeros */
        memset(n->children[ind], 0, sizeof(node_t)) ;
    }
    if ( strlen(str) == 1 ) { /* if we left with the last letter */
        /* update letter and count */
        n->children[ind]->count++ ;
        /* we are all good :) */
        return TREE_OK ;
    }
    /* if there is still more letters to push */
    /* continue pushing word from next letter to relevant child */
    str = str + 1;
    return push_tree(n->children[ind], str) ;
}

/*
 * name: ind_to_char
 *
 * description: translate index in node's children array to the corresponding letter
 *
 * input:
 *  ind - index in range (0, NUM_LETTERS-1)
 *
 * return:
 *  lowercase letter (char)
 */
static char ind_to_char (int ind) {
    return (char) (ind + 'a') ;
}

/*
 * name: print_tree
 *
 * description: prints the words in lexicographic or reverse lexicographic order
 *
 * note: functions as a recursive routine
 *
 * input:
 *  n - reference node
 *  str - string to use for printing
 *  mode - print mode (regular/reverse)
 *
 * return:
 *  TREE_OK
 */
tree_status print_tree (node_t* n,
                        char* str,
                        int ind,
                        tree_mode mode) {
    if (n->count) {
        printf("%s\t%lu\n", str, n->count) ;
    }
    for (int i = 0; i < NUM_LETTERS ; i++) {
        int j ;
        if (mode == REVERSE) {
            j = NUM_LETTERS - (i + 1) ;
        } else { /* mode == REGULAR */
            j = i ;
        }
        if ( n->children[j] )
        {
            *(str + ind) = ind_to_char(j) ;
            print_tree(n->children[j], str, ind + 1, mode) ;
        }
    }
    *(str + ind) = '\0' ;
    /* we are all good :) */
    return TREE_OK ;
}

/*
 * name: free_tree
 *
 * description: free all allocated memory in tree
 *
 * note: functions as a recursive routine
 *
 * input:
 *  n - reference node, should be tree head
 *
 * return:
 *  TREE_OK
 */
tree_status free_tree (node_t* n) {
    for (int i = 0; i < NUM_LETTERS ; i++) {
        if ( n->children[i] )
        {
            free_tree(n->children[i]) ;
            free(n->children[i]) ;
        }
    }
    /* we are all good :) */
    return TREE_OK ;
}
