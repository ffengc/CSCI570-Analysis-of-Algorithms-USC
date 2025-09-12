
## Graph Theory

> [!NOTE]
> Using an adjacency matrix to store graphs


**Partial explanation of the code:**

```cpp
template <class vertex_type, class weight_type, weight_type __max_weight = INT_MAX, bool direction = false>
class graph
{
private:
    typedef graph<vertex_type, weight_type, __max_weight, direction> self;
    std::vector<vertex_type> __vertexs;             // collection of vertices
    std::map<vertex_type, int> __index_map;         // Vertex map index
    std::vector<std::vector<weight_type>> __matrix; // Adjacency Matrix
public:
        ...
}
```

In the template parameters,

- `vertex_type` represents the node type. In my example, the node type is `char`.
- `weight_type` represents the edge weight type. In my example, both are `int`.
- `__max_weight` specifies: If nodes are not connected, the weight is set to the maximum.
- `direction` specifies whether the graph is directed or undirected. The default value is `false`, indicating an undirected graph.

Among the member variables:

- `__vertexs` represents the set of all vertices.
- `__index_map` represents the mapping between vertices and vertex indices. Use the `size_t get_vertex_index(const vertex_type &v)` member function to get the index of a node given its name.
- `__matrix` represents the graph's adjacency matrix.


**Implemented algorithms:**

- [x] Graph Creation
- [x] Add an edge to the graph: `void add_edge(const vertex_type &src, const vertex_type &dest, const weight_type &weight)`
- [x] DFS: `std::vector<std::pair<vertex_type, std::size_t>> dfs(const vertex_type &src)`
- [x] BFS: `std::vector<std::vector<std::pair<vertex_type, std::size_t>>> bfs(const vertex_type &src)`
- [x] check whether a graph is bipartite: `bool isBipartite(const vertex_type &input_src = vertex_type())`
- [x] check whether a graph is a strongly connected graph: `bool isStronglyConnected()`
- [x] check whether an edge is a bridge in a graph: `bool edge_in_cycle(const vertex_type &src, const vertex_type &dst)`
- [x] print the graph for debug: `void print()`
- [ ] Get the topological sort of the graph (DAG only)