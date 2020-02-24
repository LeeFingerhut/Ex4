#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAX_WORD 10000

static tree_mode get_mode_from_stdin(int argc, char* argv[]) {
    if (argc > 1 && strlen(argv[1]) == 1 && *argv[1] == 'r') {
        return REVERSE ;
    }
    return REGULAR ;
}

static int is_letter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 1 ;
    }
    return 0 ;
}

static tree_status get_word(char* word) {
    char str[MAX_WORD] ;
    memset(word, 0, MAX_WORD) ;
    memset(str, 0, MAX_WORD) ;
    if ((scanf("%s", str)) == EOF) {
        return TREE_FAIL ;
    }
    int ind = 0 ;
    for (int i = 0; i < strlen(str); i++) {
        if (is_letter(str[i])) {
            word[ind++] = str[i] ;
        }
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
        if (!strlen(word)) {
            continue ;
        }

        if (push_tree(&head, word)) {
            free_tree(&head) ;
            return TREE_FAIL ;
        }
    }

    memset(word, 0, MAX_WORD) ;
    print_tree(&head, word, 0, mode) ;

    free_tree(&head) ;

    return TREE_OK ;
}