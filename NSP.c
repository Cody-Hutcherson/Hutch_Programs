#include <stdlib.h>
#include <float.h>

//written by Aswhin Murali

typedef struct node{

    int index;
    double weight;
    int* num_shortestPath;
    _Bool explored;
} node;

int all_paths(double **graph, int num_vertices, int origin, int destination)
{
    node *vertices = (node*) malloc(num_vertices * sizeof(node));
    for (int i = 0; i < num_vertices; ++i){
        vertices[i].index = i;
        vertices[i].explored = 0;
        vertices[i].num_shortestPath = (int*) calloc(num_vertices, sizeof(int));
        vertices[i].weight = DBL_MAX;
    }
    vertices[origin].weight = 0;
    vertices[destination].explored = 1;
    vertices[origin].num_shortestPath[origin] = 1;
    for (;;){
        vertices[origin].explored = 1;
        for(int k = 0; k < num_vertices; ++k){
            if(graph[origin][k]){
                if((vertices[origin].weight + graph[origin][k]) < vertices[k].weight){
                    vertices[k].weight = graph[origin][k] + vertices[origin].weight;

                    if (k != destination)
                        vertices[k].explored = 0;

                    for(int i = 0; i < num_vertices; ++i)
                        vertices[k].num_shortestPath[i] = 0;

                    int points = 0;

                    for(int j = 0; j < num_vertices; j++)
                        points += vertices[origin].num_shortestPath[j];

                    vertices[k].num_shortestPath[origin] = points;

                    for (int l = 0; l < num_vertices; ++l)
                        vertices[l].num_shortestPath[k] = 0;

                }
                else if((vertices[origin].weight + graph[origin][k]) == vertices[k].weight){
                    for (int i = 0; i < num_vertices; ++i) {
                        int points = 0;

                        for(int j = 0; j < num_vertices; j++)
                            points += vertices[origin].num_shortestPath[j];

                        vertices[k].num_shortestPath[origin] = points;
                    }
                }
            }
        }
        origin = -1;
        for (int j = 0; j < num_vertices; ++j) {
            if(!vertices[j].explored) {
                origin = j;
                break;
            }
        }
        if(origin == -1){
            int paths = 0;
            for (int i = 0; i < num_vertices; ++i)
                paths += vertices[destination].num_shortestPath[i];
            return paths;
            }
        }
    }



