
#ifndef __FENGCHENGYU_GRAPH_HPP__
#define __FENGCHENGYU_GRAPH_HPP__

#include <vector>
#include <map>
#include <set>
#include <limits.h>
#include <iostream>
#include <queue>
#include <assert.h>
#include <algorithm>
#include "union_find_disjoint_set.hpp"

namespace fengcheng_yu_graph_algorithm
{
    template <class vertex_type, class weight_type, weight_type __max_weight = INT_MAX, bool direction = false>
    class graph
    {
    private:
        typedef graph<vertex_type, weight_type, __max_weight, direction> self;
        std::vector<vertex_type> __vertexs;             // collection of vertices
        std::map<vertex_type, int> __index_map;         // Vertex map index
        std::vector<std::vector<weight_type>> __matrix; // Adjacency Matrix
    public:
        // Graph creation
        /*
            Three methods for creating a graph:
            1. IO input -- inconvenient for testing, OJ is more suitable
            2. Writing graph structure relationships to and reading from files
            3. Manually adding edges (prefer this one)
        */
        graph() = default;
        graph(const vertex_type *a, size_t n)
        {
            __vertexs.reserve(n);
            for (size_t i = 0; i < n; i++)
            {
                __vertexs.push_back(a[i]); // Each vertex is stored in
                __index_map[a[i]] = i;     // The subscript of the vertex map is which index in __vertexs this vertex is on
            }
            __matrix.resize(n);
            for (size_t i = 0; i < __matrix.size(); ++i)
            {
                __matrix[i].resize(n, __max_weight);
            }
        }
        size_t get_vertex_index(const vertex_type &v)
        {
            // Determine the index of the vertex
            auto it = __index_map.find(v);
            if (it != __index_map.end())
                return it->second;
            else
            {
                throw std::invalid_argument("vertex not exists");
                return -1;
            }
        }
        void add_edge(const vertex_type &src, const vertex_type &dest, const weight_type &weight)
        {
            size_t srci = get_vertex_index(src);
            size_t desti = get_vertex_index(dest);
            __add_edge(srci, desti, weight);
        }
        void __add_edge(size_t srci, size_t dsti, const weight_type &weight)
        {
            // Add a version using subscript. This function is generally used internally.
            __matrix[srci][dsti] = weight;
            // If it is an undirected graph
            if (direction == false)
                __matrix[dsti][srci] = weight;
        } //
    private:
        void __dfs(size_t srci, std::vector<bool> &visited, std::vector<std::pair<vertex_type, std::size_t>> &result)
        {
            result.push_back({__vertexs[srci], srci});
            visited[srci] = true; // Mark visited
            // Find a point adjacent to srci that has not been visited and go to the depth traversal
            for (size_t i = 0; i < __vertexs.size(); ++i)
                if (__matrix[srci][i] != __max_weight && visited[i] == false) // Just traverse the connected points in the matrix
                    __dfs(i, visited, result);
        } //
    public:
        // traversal
        std::vector<std::vector<std::pair<vertex_type, std::size_t>>> bfs(const vertex_type &src)
        {
            // Output collection: bfs layered output
            std::vector<std::vector<std::pair<vertex_type, std::size_t>>> result;
            int layerIdx = 0;
            // Need a starting point
            size_t srci = get_vertex_index(src); // Find the starting point index
            std::queue<int> q;
            std::vector<bool> visited(__vertexs.size(), false); // All vertices are initially marked as false
            q.push(srci);                                       // Start queue
            visited[srci] = true;                               // Mark the starting point because it has been queued.
            int levelSize = 1;
            while (!q.empty())
            {
                // Control one layer at a time
                // one layer
                result.push_back(std::vector<std::pair<vertex_type, std::size_t>>());
                for (size_t i = 0; i < levelSize; i++)
                {
                    // If the queue is not empty, continue traversing
                    int front = q.front();
                    // std::cout << __vertexs[front] << "[" << front << "]"
                    //           << " ";
                    result[layerIdx].push_back({__vertexs[front], front});
                    q.pop();
                    // Enqueue the vertices connected to the front
                    for (size_t i = 0; i < __vertexs.size(); ++i)
                    {
                        if (__matrix[front][i] != __max_weight && visited[i] == false)
                        {
                            q.push(i);         // Nodes connected to the current vertex
                            visited[i] = true; // mark
                        }
                    }
                }
                // std::cout << std::endl;
                layerIdx++;           // next layer
                levelSize = q.size(); // At this time, levelSize is the number of the next layer, that is, the number of elements in the current queue, because we have finished the current layer, and the rest are the next layer.
            }
            std::cout << "bfs done!" << std::endl;
            return result;
        }
        std::vector<std::pair<vertex_type, std::size_t>> dfs(const vertex_type &src)
        {
            std::vector<std::pair<vertex_type, std::size_t>> result;
            size_t srci = get_vertex_index(src);
            std::vector<bool> visited(__vertexs.size(), false);
            __dfs(srci, visited, result);
            std::cout << std::endl
                      << "dfs done" << std::endl;
            return result;
        } //
    public:
        bool isBipartite(const vertex_type &input_src = vertex_type())
        {
            if (__vertexs.size() == 0)
            {
                std::cerr << "empty graph called is_bipartite" << std::endl;
                return false;
            }
            vertex_type src = vertex_type();
            if (input_src == vertex_type())
                src = __vertexs[0];
            else
                src = input_src;
            // Use the existing bfs function to get the layered results
            // std::vector<std::vector<std::pair<vertex_type, std::size_t>>>
            auto layers = bfs(src);
            size_t n = __vertexs.size();
            std::vector<int> color(n, -1);
            // Assign colors to each layer of nodes
            for (size_t layer = 0; layer < layers.size(); ++layer)
            {
                for (auto &p : layers[layer])
                {
                    size_t idx = p.second;
                    color[idx] = (layer % 2 == 0 ? 0 : 1);
                }
            }
            // Iterate over all edges and check endpoint colors
            for (size_t u = 0; u < n; ++u)
            {
                for (size_t v = u + 1; v < n; ++v)
                {
                    if (__matrix[u][v] != __max_weight)
                    {
                        if (color[u] == color[v])
                            return false;
                    }
                }
            }
            return true;
        }
        bool isStronglyConnected()
        {
            size_t n = __vertexs.size();
            if (n == 0)
                return true;

            // run bfs/dfs
            std::vector<bool> visited(n, false);
            __dfs(0, visited, *(new std::vector<std::pair<vertex_type, std::size_t>>()));
            for (bool v : visited)
                if (!v)
                    return false;

            // Determine whether it is a directed graph. If it is an undirected graph, it returns true.
            if constexpr (direction == false)
                return true;

            // get G^T
            graph<vertex_type, weight_type, __max_weight, direction> gT;
            gT = *this; // deep copy
            for (size_t i = 0; i < n; i++)
                for (size_t j = 0; j < n; j++)
                    gT.__matrix[i][j] = __max_weight;
            for (size_t i = 0; i < n; i++)
                for (size_t j = 0; j < n; j++)
                    if (__matrix[i][j] != __max_weight)
                        gT.__matrix[j][i] = __matrix[i][j]; // 反向边
            // run bfs/dfs on G^T
            std::vector<bool> visitedT(n, false);
            gT.__dfs(0, visitedT, *(new std::vector<std::pair<vertex_type, std::size_t>>()));
            for (bool v : visitedT)
                if (!v)
                    return false;
            return true;
        }
        void dagTopologicalOrdering() {} //
        bool edge_in_cycle(const vertex_type &src, const vertex_type &dst)
        {
            size_t srci = get_vertex_index(src);
            size_t dsti = get_vertex_index(dst);

            // Temporarily "delete" this edge (srci, dsti)
            weight_type backup = __matrix[srci][dsti];
            __matrix[srci][dsti] = __max_weight;
            if (direction == false) // undirected
                __matrix[dsti][srci] = __max_weight;
            // call bfs
            auto layers = bfs(src);
            // Restore Edge
            __matrix[srci][dsti] = backup;
            if (direction == false)
                __matrix[dsti][srci] = backup;
            // Check whether the target vertex dst appears in the traversal result
            for (auto &layer : layers)
                for (auto &p : layer)
                    if (p.second == dsti)
                        return true;
            return false;
        } //
    public:
        void print()
        {
            // Print out the vertices
            for (size_t i = 0; i < __vertexs.size(); i++)
                std::cout << "[" << i << "]"
                          << "->" << __vertexs[i] << std::endl;
            std::cout << std::endl;
            // Print the matrix
            // Print the subscript first
            std::cout << "  ";
            for (size_t i = 0; i < __vertexs.size(); ++i)
                std::cout << i << " ";
            std::cout << std::endl;
            for (size_t i = 0; i < __matrix.size(); ++i)
            {
                // Print the subscript first
                std::cout << i << " ";
                for (size_t j = 0; j < __matrix[i].size(); ++j)
                    if (__matrix[i][j] == __max_weight)
                        std::cout << "* ";
                    else
                        std::cout << __matrix[i][j] << " ";
                std::cout << std::endl;
            }
        }
    };
}

#endif