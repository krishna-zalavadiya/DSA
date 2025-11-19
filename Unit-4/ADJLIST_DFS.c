#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// ============================================================================
// NODE STRUCTURE FOR ADJACENCY LIST
// Each vertex has a linked list of neighbors.
// Example: 1 → 2 → 5 → NULL
// ============================================================================
typedef struct Node {
    int vertex;           // Adjacent vertex number
    struct Node* next;    // Pointer to next neighbor
} Node;

// ============================================================================
// GRAPH STRUCTURE
// Uses an array of linked list heads.
// adjList[i] = head of linked list of neighbors of vertex i
// ============================================================================
typedef struct {
    int numVertices;
    Node* adjList[MAX];   // Array of pointers (one list for each vertex)
} GRAPH;

// ============================================================================
// CREATE A NEW LINKED LIST NODE (for adjacency list)
// ============================================================================
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// ============================================================================
// CREATE ADJACENCY LIST
// 1. Read number of vertices
// 2. Initialize all adjacency list heads to NULL
// 3. Read edges and build linked lists
// ============================================================================
void create_adjList(GRAPH* g) {
    int edges, v1, v2;

    printf("Enter number of vertices: ");
    scanf("%d", &g->numVertices);

    // Initialize all adjacency list heads to NULL
    for (int i = 1; i <= g->numVertices; i++)
        g->adjList[i] = NULL;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (v1 v2):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &v1, &v2);

        // --------------------------
        // Add v2 to v1's adjacency list
        // --------------------------
        Node* newNode = createNode(v2);
        newNode->next = g->adjList[v1];   // Insert at front
        g->adjList[v1] = newNode;

        // --------------------------
        // Add v1 to v2's adjacency list (UNDIRECTED graph)
        // --------------------------
        newNode = createNode(v1);
        newNode->next = g->adjList[v2];
        g->adjList[v2] = newNode;
    }

    printf("\nGraph created successfully!\n");
}

// ============================================================================
// DISPLAY ADJACENCY LIST
// Shows each vertex and its neighbors:
// Example:
// 1 → 2 → 5 → NULL
// 2 → 1 → 3 → NULL
// ============================================================================

void display_adjList(GRAPH* g) {
    printf("\nAdjacency List Representation:\n");

    for (int i = 1; i <= g->numVertices; i++) {
        printf("Vertex %d → ", i);

        Node* temp = g->adjList[i];
        while (temp != NULL) {
            printf("%d → ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// ============================================================================
// DFS FOR CONNECTIVITY CHECK
// Visits all reachable vertices using DFS.
// ============================================================================
void dfs_visit(int vertex, GRAPH* g, int* visited, int* count) {
    visited[vertex] = 1;    // Mark vertex as visited
    (*count)++;             // Increase visited vertex count

    // Traverse all neighbors
    Node* temp = g->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;

        if (!visited[adjVertex]) {
            dfs_visit(adjVertex, g, visited, count);
        }

        temp = temp->next;
    }
}

// ============================================================================
// CHECK IF GRAPH IS CONNECTED
// Graph is connected if ONE DFS visit reaches ALL vertices.
// ============================================================================
bool dfs_is_connected(GRAPH* g) {
    int visited[MAX] = {0};
    int count = 0;

    // Start DFS from vertex 1
    dfs_visit(1, g, visited, &count);

    // If DFS visited all vertices → connected graph
    return count == g->numVertices;
}

// ============================================================================
// DFS CYCLE DETECTION
// Cycle exists if:
//   While visiting neighbors, we find a visited neighbor
//   that is NOT the parent → back edge → cycle!
// ============================================================================
bool dfs_cycle_helper(int vertex, int parent, GRAPH* g, int* visited) {

    visited[vertex] = 1;

    Node* temp = g->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;

        // Case 1: Visit unvisited neighbor
        if (!visited[adjVertex]) {

            if (dfs_cycle_helper(adjVertex, vertex, g, visited))
                return true;
        }
        // Case 2: Found visited neighbor that is NOT parent → cycle!
        else if (adjVertex != parent) {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

// Wrapper function
bool dfs_contains_cycle(GRAPH* g) {
    int visited[MAX] = {0};

    // Important: graph may be disconnected, so check all components
    for (int i = 1; i <= g->numVertices; i++) {

        if (!visited[i]) {
            if (dfs_cycle_helper(i, -1, g, visited))
                return true;
        }
    }
    return false;
}

// ============================================================================
// DFS PATH FINDING (Backtracking Algorithm)
// Finds ONE path from 'start' to 'destination'
// Uses:
//   - Path array to store current route
//   - Backtracking:
//         visited[start] = 1
//         explore deeper
//         visited[start] = 0 (undo for future paths)
// ============================================================================
int dfs_find_paths(int start, int destination, GRAPH* g,int* visited, int* path, int path_index) {

    visited[start] = 1;             // Mark current vertex visited
    path[path_index] = start;       // Store in path
    path_index++;                   // Move to next position

    // BASE CASE: Found destination
    if (start == destination) {
        printf("Path found: ");
        for (int i = 0; i < path_index; i++)
            printf("%d ", path[i]);
        printf("\n");
        return 1;
    }

    // EXPLORE NEIGHBORS
    Node* temp = g->adjList[start];
    while (temp != NULL) {
        int adjVertex = temp->vertex;

        if (!visited[adjVertex]) {
            // Recur deeper
            if (dfs_find_paths(adjVertex, destination, g,visited, path, path_index))
                return 1;   // Stop after finding first valid path
        }

        temp = temp->next;
    }

    // BACKTRACK: unmark before returning
    visited[start] = 0;

    return 0;   // No path found from current branch
}

// ============================================================================
// MAIN MENU
// ============================================================================
int main() {
    GRAPH g;
    int visited[MAX], path[MAX];
    int choice, start, destination;

    create_adjList(&g);

    while (1) {
        printf("\n=========== ADJACENCY LIST - DFS OPERATIONS ===========\n");
        printf("1. Check Connectivity (DFS)\n");
        printf("2. Detect Cycle (DFS)\n");
        printf("3. Find Path (DFS)\n");
        printf("4. Display Adjacency List\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            if (dfs_is_connected(&g))
                printf("Graph is connected.\n");
            else
                printf("Graph is NOT connected.\n");
            break;

        case 2:
            if (dfs_contains_cycle(&g))
                printf("Graph contains a cycle.\n");
            else
                printf("Graph does NOT contain a cycle.\n");
            break;

        case 3:
            printf("Enter start and destination: ");
            scanf("%d %d", &start, &destination);

            // Reset visited array
            for (int i = 0; i < MAX; i++)
                visited[i] = 0;

            if (!dfs_find_paths(start, destination, &g, visited, path, 0))
                printf("No path found.\n");
            break;

        case 4:
            display_adjList(&g);
            break;

        case 5:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }
}
