#include<bits/stdc++.h>

struct Edge
{
	int Source;
	int Destination;
	int Weight;
};

struct Graph
{
	int VerticesCount;
	int EdgesCount;
	struct Edge* edge;
};

 struct Graph* CreateGraph(int verticesCount, int edgesCount)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->VerticesCount = verticesCount;
	graph->EdgesCount = edgesCount;
	graph->edge = (struct Edge*)malloc(graph->EdgesCount * sizeof(struct Edge));

	return graph;
}

 void Print(int distance[], int count)
{
	printf("Vertex   Distance from source\n");

	for (int i = 0; i < count; ++i)
		printf("%d\t %d\n", i, distance[i]);
}

 void BellmanFord(struct Graph* graph, int source)
{
	int verticesCount = graph->VerticesCount;
	int edgesCount = graph->EdgesCount;
	int* distance = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++)
		distance[i] = INT_MAX;

	distance[source] = 0;

	for (int i = 1; i <= verticesCount - 1; ++i)
	{
		for (int j = 0; j < edgesCount; ++j)
		{
			int u = graph->edge[j].Source;
			int v = graph->edge[j].Destination;
			int weight = graph->edge[j].Weight;

			if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
				distance[v] = distance[u] + weight;
		}
	}

	for (int i = 0; i < edgesCount; ++i)
	{
		int u = graph->edge[i].Source;
		int v = graph->edge[i].Destination;
		int weight = graph->edge[i].Weight;

		if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
			printf("Graph contains negative weight cycle.");
	}

	Print(distance, verticesCount);
}

int main(){
	int verticesCount = 5;
int edgesCount = 8;
struct Graph* graph = CreateGraph(verticesCount, edgesCount);

// Edge 0-1
graph->edge[0].Source = 0;
graph->edge[0].Destination = 1;
graph->edge[0].Weight = -1;

// Edge 0-2
graph->edge[1].Source = 0;
graph->edge[1].Destination = 2;
graph->edge[1].Weight = 4;

// Edge 1-2
graph->edge[2].Source = 1;
graph->edge[2].Destination = 2;
graph->edge[2].Weight = 3;

// Edge 1-3
graph->edge[3].Source = 1;
graph->edge[3].Destination = 3;
graph->edge[3].Weight = 2;

// Edge 1-4
graph->edge[4].Source = 1;
graph->edge[4].Destination = 4;
graph->edge[4].Weight = 2;

// Edge 3-2
graph->edge[5].Source = 3;
graph->edge[5].Destination = 2;
graph->edge[5].Weight = 5;

// Edge 3-1
graph->edge[6].Source = 3;
graph->edge[6].Destination = 1;
graph->edge[6].Weight = 1;

// Edge 4-3
graph->edge[7].Source = 4;
graph->edge[7].Destination = 3;
graph->edge[7].Weight = -3;

BellmanFord(graph, 0);

}
