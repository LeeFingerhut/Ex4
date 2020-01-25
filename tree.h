/*
 * include guard
 */
#pragma once

/*
 * defines
 */
#define NUM_LETTERS ((int)26)
#define null NULL

/*
 * macros
 */
#define log_err(p) printf("(%s.%d) ERR: " p, __func__, __LINE__)

/*
 * enums
 */
typedef enum {
    FALSE = 0,
    TRUE  = 1
} boolean;

typedef enum {
    TREE_OK   = 0,
    TREE_FAIL = 1,
} tree_status ;

typedef enum {
    REGULAR = 0,
    REVERSE = 1,
} tree_mode ;

/*
 * structs
 */
typedef struct node {
    //char              letter;
    long unsigned int count;
    struct node*      children[NUM_LETTERS];
} node_t;

/*
 * interface routines
 */
tree_status push_tree   (node_t* n, char* str) ;
tree_status print_tree  (node_t* n, char* str, int ind, tree_mode mode) ;
tree_status free_tree   (node_t* n) ;
