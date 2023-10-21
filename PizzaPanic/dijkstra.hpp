
#ifndef DIJKSTRA
#define DIJKSTRA

/////////////////////////////////////////////////////
// TIPO DE DATO PARA GRAFICAS DIRIGIDAS PONDERADAS //
/////////////////////////////////////////////////////

typedef float graph;

graph* empty_graph(int n);
int index_of(int n, int row, int col);
void free_graph(graph* g);
int graph_vertices(graph* g);
void connect(graph* g, int u, int v, float weight);
void biconnect(graph* g, int u, int v, float weight);
float weight(graph* g, int u, int v);
bool adjacent(graph* g, int u, int v);
int nearest_vertex(int n, bool* frontier, float* distances);
int* find_path(graph* g, int beg, int end);
void initialize_graph(graph* g, int**matriz, int**adyacencia);


#endif 
