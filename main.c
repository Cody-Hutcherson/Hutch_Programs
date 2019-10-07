#include<stdio.h>
#include<stdlib.h>

//written by Cody Hutcherson and Ashwin Murali 10-7-2019

double** getArray(FILE *f);
double** djkistra(double** graph, int origin, int num_vertices);
double girth(double **graph, int nodes);
int all_paths(double **graph, int num_vertices, int origin, int NSP_origin);
int main(int argc, char *argv[]){
	if(argc < 3){
		fprintf(stderr, "Not enough command line arguments. Usage: FILE, starting node, NSP starting node\n");
	  exit(1);
	}
	FILE *f = fopen(argv[1], "r");
	double **graph;
	int nodes;
	int numShortestPaths;
	double **table;
	double shortest_cycle;
	double **table_NSP;
	graph = getArray(f);
	fseek(f, 0, SEEK_SET);
	fscanf(f, "%d", &nodes);
	int origin = atoi(argv[2]);
	shortest_cycle = girth(graph, nodes);
	if(shortest_cycle > -1){
		printf("\nTHE SHORTEST CYCLE IS: %lf\n\n", shortest_cycle);
	} else{
			printf("\nGIRTH: NO CYCLE EXISTS\n\n");
		}
	table = djkistra(graph, origin, nodes);
	printf("Dijkstra table\n\n");
	printf("Node     ");
	printf("Distance from %d     ", origin);
	printf("Parent\n\n");
	for(int i = 0; i < nodes; i++){
		printf("%d", i);
		for(int j = 0; j < 2; j++){
			printf("        %.5lf     ", table[j][i]);
		}
		printf("\n");
	}
	printf("\n");

	fclose(f);

	for(int z = 0; z < nodes; z++){

		numShortestPaths = all_paths(graph, nodes, atoi(argv[3]), z);

		printf("Number of shortest paths to %d: %d\n", z,  numShortestPaths);

	}
  
	printf("\n");

	return 0;
}

double** getArray(FILE *f){
	double nodes, arcs;
	double c;
	int i = 0;
	int I1 = 0;
	int I2 = 0;
	while(fscanf(f, "%lf", &c)!=EOF){
		if(i == 0){
			nodes = c;
		} else{
			arcs = c;
			break;
		}
		i++;
	}
	double **graph = (double**)malloc(sizeof(double*)*nodes);
	for(i = 0; i < nodes; i++){
		graph[i] = (double*)malloc(sizeof(double)*nodes);
	}
	i = 0;
	while(fscanf(f, "%lf", &c)!=EOF){
		i++;
		if(i == 1){
			I1 = (int)c;
		}
		if(i == 2){
			I2 = (int)c;
		} else if(i == 3){
			graph[I1][I2] = c;
			i = 0;
		}
	}
	return graph;
}
