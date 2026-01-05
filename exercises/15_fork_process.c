/*
 ===============================================================================
 Graph: Network Connections Graph
 Description: Represents network connections between processes
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_CONNECTIONS 10

typedef struct GraphNode {
  int process_id;
  char process_name[50];
  int tcp_port;
  int udp_port;
  int is_listening; // 1 = listening socket, 0 = client socket
} GraphNode;

typedef struct GraphEdge {
  int from_node;
  int to_node;
  int socket_fd;
  char protocol[4]; // "TCP" o "UDP"
  int is_active;    // 1 = conexión activa
} GraphEdge;

typedef struct Graph {
  GraphNode nodes[MAX_NODES];
  int adjacency_matrix[MAX_NODES][MAX_NODES]; // 1 = conexión, 0 = no conexión
  GraphEdge edges[MAX_NODES * MAX_CONNECTIONS];
  int node_count;
  int edge_count;
} Graph;

// Crear un nuevo grafo
Graph *create_graph() {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  if (!g)
    return NULL;

  g->node_count = 0;
  g->edge_count = 0;

  // Inicializar matriz de adyacencia
  for (int i = 0; i < MAX_NODES; i++) {
    for (int j = 0; j < MAX_NODES; j++) {
      g->adjacency_matrix[i][j] = 0;
    }
  }

  return g;
}

// Añadir un nodo (proceso) al grafo
int add_node(Graph *g, int pid, const char *name, int tcp_port, int udp_port) {
  if (g->node_count >= MAX_NODES)
    return -1;

  g->nodes[g->node_count].process_id = pid;
  strncpy(g->nodes[g->node_count].process_name, name, 49);
  g->nodes[g->node_count].tcp_port = tcp_port;
  g->nodes[g->node_count].udp_port = udp_port;
  g->nodes[g->node_count].is_listening = (tcp_port > 0) ? 1 : 0;

  return g->node_count++;
}

// Añadir una arista (conexión) entre nodos
int add_edge(Graph *g, int from, int to, int socket_fd, const char *protocol) {
  if (from >= g->node_count || to >= g->node_count)
    return -1;

  // Actualizar matriz de adyacencia
  g->adjacency_matrix[from][to] = 1;

  // Añadir arista a la lista
  g->edges[g->edge_count].from_node = from;
  g->edges[g->edge_count].to_node = to;
  g->edges[g->edge_count].socket_fd = socket_fd;
  strncpy(g->edges[g->edge_count].protocol, protocol, 3);
  g->edges[g->edge_count].is_active = 1;

  return g->edge_count++;
}

// Mostrar el grafo en consola
void print_graph(const Graph *g) {
  printf("\n=== Network Connection Graph ===\n\n");
  printf("Total Processes: %d\n", g->node_count);
  printf("Total Connections: %d\n\n", g->edge_count);

  // Mostrar nodos
  printf("Processes (Nodes):\n");
  printf("ID  PID  Name                  TCP  UDP  Listening\n");
  printf("---------------------------------------------------\n");
  for (int i = 0; i < g->node_count; i++) {
    printf("%-3d %-4d %-20s %-4d %-4d %-9s\n", i, g->nodes[i].process_id, g->nodes[i].process_name,
           g->nodes[i].tcp_port, g->nodes[i].udp_port, g->nodes[i].is_listening ? "Yes" : "No");
  }

  // Mostrar conexiones
  printf("\nActive Connections (Edges):\n");
  printf("From  To    Socket  Protocol  Status\n");
  printf("------------------------------------\n");
  for (int i = 0; i < g->edge_count; i++) {
    if (g->edges[i].is_active) {
      printf("%-5s -> %-5s %-6d %-8s %-6s\n", g->nodes[g->edges[i].from_node].process_name,
             g->nodes[g->edges[i].to_node].process_name, g->edges[i].socket_fd,
             g->edges[i].protocol, "ACTIVE");
    }
  }

  // Mostrar matriz de adyacencia
  printf("\nAdjacency Matrix:\n   ");
  for (int i = 0; i < g->node_count; i++) {
    printf("%-3d", i);
  }
  printf("\n");

  for (int i = 0; i < g->node_count; i++) {
    printf("%-3d", i);
    for (int j = 0; j < g->node_count; j++) {
      printf("%-3d", g->adjacency_matrix[i][j]);
    }
    printf("\n");
  }
}

// Encontrar todas las conexiones de un proceso
void find_connections(const Graph *g, int node_index) {
  printf("\nConnections for process '%s' (PID: %d):\n", g->nodes[node_index].process_name,
         g->nodes[node_index].process_id);

  printf("Outgoing connections:\n");
  for (int i = 0; i < g->edge_count; i++) {
    if (g->edges[i].from_node == node_index && g->edges[i].is_active) {
      printf("  -> %s (Socket: %d, Protocol: %s)\n", g->nodes[g->edges[i].to_node].process_name,
             g->edges[i].socket_fd, g->edges[i].protocol);
    }
  }

  printf("Incoming connections:\n");
  for (int i = 0; i < g->edge_count; i++) {
    if (g->edges[i].to_node == node_index && g->edges[i].is_active) {
      printf("  <- %s (Socket: %d, Protocol: %s)\n", g->nodes[g->edges[i].from_node].process_name,
             g->edges[i].socket_fd, g->edges[i].protocol);
    }
  }
}

// Liberar memoria del grafo
void free_graph(Graph *g) {
  if (g) {
    free(g);
  }
}

// Ejemplo de uso
int main() {
  // Crear grafo de conexiones de red
  Graph *network = create_graph();

  // Añadir procesos/nodos
  int web_server = add_node(network, 1234, "nginx", 80, 0);
  int db_server = add_node(network, 1235, "postgres", 5432, 0);
  int cache_server = add_node(network, 1236, "redis", 6379, 0);
  int client = add_node(network, 1237, "browser", 0, 0);

  // Añadir conexiones/aristas
  add_edge(network, client, web_server, 15, "TCP");
  add_edge(network, web_server, db_server, 16, "TCP");
  add_edge(network, web_server, cache_server, 17, "TCP");

  // Mostrar información
  print_graph(network);

  // Buscar conexiones específicas
  find_connections(network, web_server);

  // Liberar memoria
  free_graph(network);

  return 0;
}
