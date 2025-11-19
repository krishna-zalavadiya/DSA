#include <stdio.h>
#include <stdbool.h>

#define MAX 100   // Maximum number of vertices supported



// ======================================================================
//                           GRAPH STRUCTURE
// ======================================================================
// The graph is stored using an adjacency matrix.
// If adjMatrix[i][j] = 1 → there is an edge between vertex i and j.
// If adjMatrix[i][j] = 0 → there is NO edge.
// We use 1-based indexing for clarity.
// ======================================================================
typedef struct {
    int vertex;                    // Total number of vertices in the graph
    int adjMatrix[MAX][MAX];       // The adjacency matrix
} GRAPH;



// ======================================================================
//            FUNCTION: CREATE & INITIALIZE THE ADJACENCY MATRIX
// ======================================================================
// - Takes input from the user for number of vertices and edges.
// - Initializes all matrix entries to 0.
// - For every edge (u, v), marks:
//        adjMatrix[u][v] = 1
//        adjMatrix[v][u] = 1      (UNDIRECTED graph) remove this line for directed graph
// ======================================================================
void create_adjMatrix(GRAPH *g) {
    int edges, v1, v2;

    printf("Enter number of vertices: ");
    scanf("%d", &g->vertex);

    // Initialize all cells to 0
    for (int i = 0; i <= g->vertex; i++)
        for (int j = 0; j <= g->vertex; j++)
            g->adjMatrix[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (vertex1 vertex2):\n");

    // Input each edge and fill symmetric matrix entries
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &v1, &v2);

        // Insert the edge into the matrix (undirected)
        g->adjMatrix[v1][v2] = 1;
        g->adjMatrix[v2][v1] = 1;   // Remove this line for directed graph
    }

    printf("\nGraph created successfully!\n");
}



// ======================================================================
//               FUNCTION: DISPLAY THE ADJACENCY MATRIX
// ======================================================================
// Prints the graph structure visually in matrix form.
// Very useful for understanding the graph you have entered.
// ======================================================================
void display_adjMatrix(GRAPH *g) {

    printf("\nAdjacency Matrix:\n\n  ");

    // Print column header
    for (int i = 1; i <= g->vertex; i++)
        printf("%3d", i);

    printf("\n");

    // Print matrix row by row
    for (int i = 1; i <= g->vertex; i++) {
        printf("%3d", i);   // Row label
        for (int j = 1; j <= g->vertex; j++)
            printf("%3d", g->adjMatrix[i][j]);
        printf("\n");
    }
}



// ======================================================================
//                   DFS CONNECTIVITY CHECK (Helper Function)
// ======================================================================
// dfs_visit() is a recursive DFS that:
// - Marks a node as visited
// - Recursively visits all unvisited neighbors
// - Counts how many nodes we are able to reach
// If we reach ALL nodes → graph is connected.
// ======================================================================
void dfs_visit(int vertex, GRAPH *g, int *visited, int *count) {
    visited[vertex] = 1;  // Mark current vertex as visited
    (*count)++;           // Increase reachable count

    // Explore all vertices to check if they are connected to this vertex
    for (int i = 1; i <= g->vertex; i++) {

        // If an edge exists AND the vertex has not been visited → DFS deeper
        if (g->adjMatrix[vertex][i] && !visited[i]) {
            dfs_visit(i, g, visited, count);
        }
    }
}



// ======================================================================
//                FUNCTION: CHECK IF GRAPH IS CONNECTED (DFS)
// ======================================================================
// Logic:
// - Start DFS from vertex 1.
// - Count how many nodes are visited.
// - If visited count == total vertices → graph is connected.
// ======================================================================
bool dfs_is_connected(GRAPH *g) {
    int visited[MAX] = {0};  // initially all unvisited
    int count = 0;

    dfs_visit(1, g, visited, &count);

    // If DFS visited all vertices → graph is connected
    return count == g->vertex;
}


// ======================================================================
//                     DFS CYCLE DETECTION (Helper Function)
// ======================================================================
// dfs_cycle_helper():
// - We explore recursively like DFS.
// - A cycle exists if:
//       We reach a vertex that is already visited AND it is NOT the parent.
// Explanation:
// For UNDIRECTED graphs, edges go both ways. The "parent" check avoids
// counting the reverse edge as a cycle.
// ======================================================================
bool dfs_cycle_helper(int vertex, int parent, GRAPH *g, int *visited) {

    visited[vertex] = 1;

    for (int i = 1; i <= g->vertex; i++) {

        if (g->adjMatrix[vertex][i] && !visited[i]) {

            if (dfs_cycle_helper(i, vertex, g, visited))
                return true;

        } else if (g->adjMatrix[vertex][i] && i != parent) {
            return true;
        }
    }

    return false;
}



// ======================================================================
//                    FUNCTION: DETECT CYCLE IN GRAPH (DFS)
// ======================================================================
// - Graph may be disconnected, so we run DFS cycle check for each component.
// - As soon as any DFS finds a cycle → return true.
// ======================================================================
bool dfs_contains_cycle(GRAPH *g) {

    int visited[MAX] = {0};

    // We check every vertex because graph may have multiple components
    for (int i = 1; i <= g->vertex; i++) {

        if (!visited[i]) {  // If this node is unvisited, start DFS

            if (dfs_cycle_helper(i, -1, g, visited))
                return true;   // Cycle detected
        }
    }

    return false;  // No cycles anywhere
}



// ======================================================================
//                       DFS PATH FINDING (IMPORTANT)
// ======================================================================
// dfs_find_paths():
// - Finds ANY path (not all paths) from start to destination using DFS.
// - Uses backtracking:
//       - Mark node as visited
//       - Add it to path[]
//       - If destination is reached → print path
//       - Else explore neighbors
//       - Before returning, unmark node to allow other paths
// ======================================================================
int dfs_find_paths(int start, int destination, GRAPH *g,int *visited, int *path, int path_index)
{
    visited[start] = 1;            // Mark node visited
    path[path_index] = start;      // Add node to current path
    path_index++;                  // Move to next path position

    // BASE CASE: Destination reached
    if (start == destination) {
        printf("Path found: ");
        for (int i = 0; i < path_index; i++)
            printf("%d ", path[i]);
        printf("\n");
        return 1;   // Path exists
    }

    // EXPLORE NEIGHBORS
    for (int i = 1; i <= g->vertex; i++) {
        if (g->adjMatrix[start][i] && !visited[i]) {
            // Explore deeper
            if (dfs_find_paths(i, destination, g, visited, path, path_index))
                return 1;  // If path found, stop DFS
        }
    }

    visited[start] = 0;  // BACKTRACK: unmark for other possible paths
    return 0;            // No path found from this branch
}


// ======================================================================
//                             MAIN MENU
// ======================================================================
int main() {

    GRAPH g;
    int choice, start, destination;
    int visited[MAX] = {0};
    int path[MAX];

    create_adjMatrix(&g);   // Build graph once at the beginning

    while (1) {
        printf("\n========== ADJACENCY MATRIX - DFS OPERATIONS ==========\n");
        printf("1. Check Connectivity (DFS)\n");
        printf("2. Detect Cycle (DFS)\n");
        printf("3. Find Path (DFS)\n");
        printf("4. Display Adjacency Matrix\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            if (dfs_is_connected(&g))
                printf("The graph is CONNECTED.\n");
            else
                printf("The graph is NOT connected.\n");
            break;

        case 2:
            if (dfs_contains_cycle(&g))
                printf("The graph CONTAINS a cycle.\n");
            else
                printf("The graph does NOT contain any cycles.\n");
            break;

        case 3:
            printf("Enter start and destination vertices: ");
            scanf("%d %d", &start, &destination);

            // Clear visited array before each new DFS search
            for (int i = 0; i < MAX; i++)
                visited[i] = 0;

            if (!dfs_find_paths(start, destination, &g, visited, path, 0))
                printf("No path found between %d and %d.\n",
                       start, destination);

            break;

        case 4:
            display_adjMatrix(&g);
            break;

        case 5:
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}
