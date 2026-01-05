#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define MAX_CONNECTIONS 10

typedef struct GraphNode {
  int process_id;
  char process_name[50];
  int tcp_port;
  int udp_port;
  int is_listening;
} GraphNode;

typedef struct GraphEdge {
  int from_node;
  int to_node;
  int socket_fd;
  char protocol[4];
  int is_active;
} GraphEdge;

typedef struct Graph {
  GraphNode nodes[MAX_NODES];
  int adjacency_matrix[MAX_NODES][MAX_NODES];
  GraphEdge edges[MAX_NODES * MAX_CONNECTIONS];
  int node_count;
  int edge_count;
} Graph;

Graph *init_graph();
int add_node(Graph *graph, int id, const char *name, int tcp, int udp);
int add_edge(Graph *g, int from, int to, int socket_fd, const char *protocol);
void print_nodes(const Graph *g);
void print_edges(const Graph *g);
void print_matrix(const Graph *g);
void inspect_process(const Graph *g, int node_idx);

int main() {
  Graph *graph = init_graph();

  printf("=== Graph ===\n\n");

  int web_server = add_node(graph, 1234, "nginx", 80, 0);
  int db_server = add_node(graph, 1235, "postgres", 5432, 0);
  int cache_server = add_node(graph, 1236, "redis", 6379, 0);
  int client = add_node(graph, 1237, "browser", 0, 0);

  add_edge(graph, client, web_server, 15, "TCP");
  add_edge(graph, web_server, db_server, 16, "TCP");
  add_edge(graph, web_server, cache_server, 17, "TCP");

  printf("Total Processes: %d\n", graph->node_count);
  printf("Total Connections: %d\n\n", graph->edge_count);

  print_nodes(graph);
  print_edges(graph);
  print_matrix(graph);

  inspect_process(graph, web_server);

  free(graph);
  return 0;
}

Graph *init_graph() {
  Graph *graph = (Graph *)malloc(sizeof(Graph));

  if (graph == NULL) {
    fprintf(stderr, "Error: Fallo crítico al asignar memoria para el sistema.\n");
    return NULL;
  }

  graph->node_count = 0;
  graph->edge_count = 0;

  for (size_t i = 0; i < MAX_NODES; i++) {
    for (size_t j = 0; j < MAX_NODES; j++) {
      graph->adjacency_matrix[i][j] = 0;
    }
  }

  return graph;
}

int add_node(Graph *graph, int id, const char *name, int tcp, int udp) {
  if (graph->node_count >= MAX_NODES)
    return -1;

  int index = graph->node_count;

  graph->nodes[index].process_id = id;
  strncpy(graph->nodes[index].process_name, name, 49);
  graph->nodes[index].process_name[49] = '\0';
  graph->nodes[index].tcp_port = tcp;
  graph->nodes[index].udp_port = udp;
  graph->nodes[index].is_listening = (tcp > 0) ? 1 : 0;

  return graph->node_count++;
}

int add_edge(Graph *graph, int from, int to, int socket_fd, const char *protocol) {
  if (from < 0 || from >= graph->node_count || to < 0 || to >= graph->node_count)
    return -1;

  int index = graph->edge_count;

  graph->adjacency_matrix[from][to] = 1;

  graph->edges[index].from_node = from;
  graph->edges[index].to_node = to;
  graph->edges[index].socket_fd = socket_fd;
  strncpy(graph->edges[index].protocol, protocol, 3);
  graph->edges[index].protocol[3] = '\0';
  graph->edges[index].is_active = 1;

  return graph->edge_count++;
}

void print_nodes(const Graph *g) {
  printf("Processes (Nodes): \n");
  printf("%-4s %-6s %-12s %-6s %-4s %-12s\n", "ID", "PID", "Name", "TCP", "UDP", "Listening");
  printf("----------------------------------------------\n");
  for (int i = 0; i < g->node_count; i++) {
    printf("%-4d %-6d %-12s %-6d %-4d %-12s\n", i, g->nodes[i].process_id, g->nodes[i].process_name,
           g->nodes[i].tcp_port, g->nodes[i].udp_port, (g->nodes[i].is_listening) ? "YES" : "NO");
  }
}

void print_edges(const Graph *g) {
  printf("\nActive Connections (Edges): \n");
  printf("%-8s %-12s %-6s %-10s %-12s\n", "From", "To", "Socket", "Protocol", "Status");
  printf("----------------------------------------------\n");
  for (int i = 0; i < g->edge_count; i++) {
    printf("%-8s %-12s %-6d %-10s %-12s\n", g->nodes[g->edges[i].from_node].process_name,
           g->nodes[g->edges[i].to_node].process_name, g->edges[i].socket_fd, g->edges[i].protocol,
           (g->edges[i].is_active) ? "ACTIVE" : "INACTIVE");
  }
}

void print_matrix(const Graph *g) {
  printf("\nAdjacency Matrix: \n");

  printf("  ");
  for (int i = 0; i < g->node_count; i++) {
    printf("%d ", i);
  }
  printf("\n");

  for (int i = 0; i < g->node_count; i++) {
    printf("%d ", i);
    for (int j = 0; j < g->node_count; j++) {
      printf("%d ", g->adjacency_matrix[i][j]);
    }
    printf("\n");
  }
}

void inspect_process(const Graph *g, int node_index) {
  printf("\nConnections for process '%s' (PID: %d):\n", g->nodes[node_index].process_name,
         g->nodes[node_index].process_id);

  printf("Outgoing connections: \n");
  for (int i = 0; i < g->edge_count; i++) {
    if (g->edges[i].from_node == node_index && g->edges[i].is_active == 1) {
      printf("  -> %s (Socket: %d, Protocol: %s) \n", g->nodes[g->edges[i].to_node].process_name,
             g->edges[i].socket_fd, g->edges[i].protocol);
    }
  }

  printf("Incoming connections: \n");
  for (int i = 0; i < g->edge_count; i++) {
    if (g->edges[i].to_node == node_index && g->edges[i].is_active == 1) {
      printf("  <- %s (Socket: %d, Protocol: %s) \n", g->nodes[g->edges[i].from_node].process_name,
             g->edges[i].socket_fd, g->edges[i].protocol);
    }
  }
}
