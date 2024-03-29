#include "../inc/pathfinder.h"

void floyd_warshall(Graph *graph, int ***shortest_paths) {
    int num_vertices = graph->num_vertices;

    *shortest_paths = (int **)malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; ++i) {
        (*shortest_paths)[i] = (int *)malloc(num_vertices * sizeof(int));

        for (int j = 0; j < num_vertices; ++j) {
            (*shortest_paths)[i][j] = graph->adj_matrix[i][j];
        }
    }

    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                if ((*shortest_paths)[i][k] != INF && (*shortest_paths)[k][j] != INF) {
                    int new_dist = (*shortest_paths)[i][k] + (*shortest_paths)[k][j];
                    if ((*shortest_paths)[i][j] == INF || new_dist < (*shortest_paths)[i][j]) {
                        (*shortest_paths)[i][j] = new_dist;
                    }

                    if (i == j) {
                        (*shortest_paths)[i][j] = 0;
                    }
                }
            }
        }
    }
}


int main(int argc, char* argv[]) {
	errors(argc, argv);

    char *file = mx_file_to_str(argv[1]);

	char *line = mx_strtok((char*)file, "\n");
	int verticies = mx_atoi(line);

	Island* islands = (Island*)malloc(verticies * sizeof(Island));
	int num_islands = 0;

	Graph* graph = create_graph(verticies);

	while ((line = mx_strtok(NULL, "\n")) != NULL) {
		char start[100];
		char end[100];
		int weight;

		int r = mx_sscanf(line, "%s-%s,%d", start, end, &weight);

		if (r != 3) {
			continue;
		}

		Edge edge;

		edge.start = mx_strdup(start);
		edge.end = mx_strdup(end);
		edge.weight = weight;


		// ------ Get start index
		int start_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, edge.start) == 0) {
                start_index = i;
                break;
            }
		}

		if (start_index == -1) {
			islands[num_islands].name = mx_strdup(edge.start);
			start_index = num_islands;
			islands[num_islands].index = start_index;
			num_islands++;
		}

		// ------ Get end index
		int end_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, edge.end) == 0) {
                end_index = i;
                break;
            }
		}

		if (end_index == -1) {
			islands[num_islands].name = mx_strdup(edge.end);
			end_index = num_islands;
			islands[num_islands].index = end_index;
			num_islands++;
		}



		graph->adj_matrix[start_index][end_index] = edge.weight;
		graph->adj_matrix[end_index][start_index] = edge.weight;
	}

	int **shortest_paths;

	floyd_warshall(graph, &shortest_paths);

	output(graph->adj_matrix, shortest_paths, graph->num_vertices, islands);

	free(graph);
    free(islands);

    return 0;
}
