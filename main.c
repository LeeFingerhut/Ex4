#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAX_WORD 100

static tree_mode get_mode_from_stdin(int argc, char* argv[]) {
    if (argc > 1 && strlen(argv[1]) == 1 && *argv[1] == 'r') {
        return REVERSE ;
    }
    return REGULAR ;
}

static tree_status get_word(char* word) {
    char c = 0;
    if ((c = getchar()) == EOF) {
            return TREE_FAIL ;
    }
    while (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '.') {
        if ((c = getchar()) == EOF) {
            return TREE_FAIL ;
        }
    }
    while (c != ' ' && c != '\t' && c != '\n' && c != ',' && c != '.') {
        *word = c ;
        word += 1 ;
        c = getchar() ;
    }
    return TREE_OK ;
}

int main(int argc, char* argv[]) {
    char word[MAX_WORD] ;
    tree_mode mode = get_mode_from_stdin(argc, argv) ;

    node_t head ;
    memset(&head, 0, sizeof(node_t)) ;

    while (1) {
        if (get_word(word)) {
            break ;
        }

        if (push_tree(&head, word)) {
            free_tree(&head) ;
            return TREE_FAIL ;
        }

        memset(word, 0, MAX_WORD) ;
    }

    memset(word, 0, MAX_WORD) ;
    print_tree(&head, word, 0, mode) ;

    free_tree(&head) ;

    return TREE_OK ;
}