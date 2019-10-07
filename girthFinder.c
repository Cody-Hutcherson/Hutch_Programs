#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

//written by Cody Hutcherson and Ashwin Murali

double **djkistra(double **graph, int origin, int num_vertices);

double girth(double **graph, int nodes){
	int node_1 = 0;
	int node_2 = 0;
	double deleted_edge = 0;
	double shortestCycle = DBL_MAX;
	double cycle = 0;
	double **table;
	for(int i = 0; i < nodes; i++){
		for(int j = 0; j < nodes; j++){
			if(graph[i][j] > 0){
				deleted_edge = graph[i][j];
				node_1 = i;
				node_2 = j;
				graph[i][j] = 0;
			
				table = djkistra(graph, j, nodes);
				//if(table[j][0]!=0){
					//cycle = (deleted_edge + table[j][0]);
					cycle = (deleted_edge + table[0][i]);
					if(cycle < shortestCycle){
						shortestCycle = cycle;
					//}
				}
				graph[node_1][node_2] = deleted_edge;
			}
			//graph[node_1][node_2] = deleted_edge;
		}
	}
	
	if(shortestCycle==DBL_MAX){
		return -1;
	}

	return shortestCycle;
}

double** djkistra(double **graph, int origin, int num_vertices)
{
    double **djkistra_table = (double **) malloc(sizeof(double *) * 2);
    *(djkistra_table) = (double *) malloc(num_vertices * sizeof(double));
    *(djkistra_table + 1) = (double *) malloc(num_vertices * sizeof(double));
    _Bool visited[num_vertices];
    for (int k = 0; k < num_vertices; ++k)
        visited[k] = 0;
    for (int i = 0; i < num_vertices; ++i)
        djkistra_table[0][i] = DBL_MAX;

    djkistra_table[0][origin] = 0;
    for(int j = 0; j < num_vertices; ++j) {
        visited[origin] = 1;
        for(int i = 0; i < num_vertices; ++i) {
            if(graph[origin][i])
            {
                if(djkistra_table[0][i] > (djkistra_table[0][origin] + graph[origin][i])) {
                    djkistra_table[0][i] = djkistra_table[0][origin] + graph[origin][i];
                    djkistra_table[1][i] = origin;
                }
            }
        }
        double curr_min = DBL_MAX, index = 0;
        for (int k = 0; k < num_vertices; ++k) {
            if(!visited[k])
            {
                if(djkistra_table[0][k] < curr_min) {
                    curr_min = djkistra_table[0][k];
                    index = k;
                }
            }
        }
        origin = (int) index;
    }
    return djkistra_table;
}
