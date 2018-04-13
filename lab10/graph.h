#include <stdlib.h> 

typedef struct graph_mat graph_mat ;
typedef struct graph_adj graph_adj ;
typedef struct vertex vertex ;

struct vertex {
    int visited , depth , label ; 
    list* neighbours ;
};

struct graph_mat {
    int vertices , edges ;
    int **mat ; 
};

struct graph_adj {
    int vertices , edges ; 

};
