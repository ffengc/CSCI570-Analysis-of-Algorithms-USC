

#include "Graph.hpp"
#include <string.h>

template <class graph_type>
void make_graph(graph_type &g)
{
    // 后面就用这个图来测试了
    g.add_edge('A', 'B', 1);
    g.add_edge('B', 'C', 1);
    g.add_edge('C', 'A', 1);
    g.add_edge('A', 'D', 1);
    g.add_edge('D', 'F', 1);
    g.add_edge('C', 'F', 1);
    g.add_edge('F', 'H', 1);
    g.add_edge('H', 'I', 1);
    g.add_edge('B', 'E', 1);
    g.add_edge('G', 'E', 1);
}
void test_bfs()
{
    // 测试bfs
    fengcheng_yu_graph_algorithm::graph<char, int, false> g("ABCDEFGHI", 9); // 无向图
    make_graph(g);
    g.print();
    std::cout << std::endl;
    auto res = g.bfs('A');
    for (int i = 0; i < res.size(); ++i)
    {
        for (int j = 0; j < res[i].size(); ++j)
        {
            std::cout << res[i][j].first << "[" << res[i][j].second << "]" << " ";
        }
        std::cout << std::endl;
    }
}
void test_dfs()
{
    // 测试dfs
    fengcheng_yu_graph_algorithm::graph<char, int, false> g("ABCDEFGHI", 9); // 无向图
    make_graph(g);
    g.print();
    std::cout << std::endl;
    auto res = g.dfs('A');
    for(int i = 0; i < res.size(); ++i)
        std::cout << res[i].first << "[" << res[i].second << "]" << " ";
    std::cout << std::endl;
}


// 测试1：带有三角形的图（非二分图）
void test_is_bipartite_case1()
{
    typedef fengcheng_yu_graph_algorithm::graph<char,int> graph_type;
    graph_type g({"ABC"}, 3);
    g.add_edge('A', 'B', 1);
    g.add_edge('B', 'C', 1);
    g.add_edge('C', 'A', 1);
    std::cout << "Test 1 (triangle graph): "
              << (g.isBipartite() ? "Bipartite" : "Not bipartite") 
              << std::endl;
}
// 测试2：简单链式图（肯定是二分图）
void test_is_bipartite_case2()
{
    typedef fengcheng_yu_graph_algorithm::graph<char,int> graph_type;
    graph_type g({"ABCD"}, 4);
    g.add_edge('A','B',1);
    g.add_edge('B','C',1);
    g.add_edge('C','D',1);
    std::cout << "Test 2 (path graph A-B-C-D): "
              << (g.isBipartite() ? "Bipartite" : "Not bipartite") 
              << std::endl;
}
// 测试3：偶数环（比如四边形，二分图）
void test_is_bipartite_case3()
{
    typedef fengcheng_yu_graph_algorithm::graph<char,int> graph_type;
    graph_type g({"ABCD"}, 4);
    g.add_edge('A','B',1);
    g.add_edge('B','C',1);
    g.add_edge('C','D',1);
    g.add_edge('D','A',1);
    std::cout << "Test 3 (square cycle A-B-C-D-A): "
              << (g.isBipartite() ? "Bipartite" : "Not bipartite") 
              << std::endl;
}
// 测试4：奇数环（五边形，非二分图）
void test_is_bipartite_case4()
{
    typedef fengcheng_yu_graph_algorithm::graph<char,int> graph_type;
    graph_type g({"ABCDE"}, 5);
    g.add_edge('A','B',1);
    g.add_edge('B','C',1);
    g.add_edge('C','D',1);
    g.add_edge('D','E',1);
    g.add_edge('E','A',1);
    std::cout << "Test 4 (pentagon A-B-C-D-E-A): "
              << (g.isBipartite() ? "Bipartite" : "Not bipartite") 
              << std::endl;
}
void test_is_bipartite() {
    test_is_bipartite_case1();
    test_is_bipartite_case2();
    test_is_bipartite_case3();
    test_is_bipartite_case4();
}

void test_strongly_connected()
{
    // Example 1: 强连通图 (A->B->C->A)
    typedef fengcheng_yu_graph_algorithm::graph<char,int,INT_MAX,true> digraph_type;
    digraph_type g1({"ABC"}, 3);
    g1.add_edge('A','B',1);
    g1.add_edge('B','C',1);
    g1.add_edge('C','A',1);
    std::cout << "Graph1 (triangle cycle): "
              << (g1.isStronglyConnected() ? "Strongly connected" : "Not strongly connected")
              << std::endl;

    // Example 2: 非强连通图 (A->B->C, no edge back)
    digraph_type g2({"ABC"}, 3);
    g2.add_edge('A','B',1);
    g2.add_edge('B','C',1);
    std::cout << "Graph2 (A->B->C only): "
              << (g2.isStronglyConnected() ? "Strongly connected" : "Not strongly connected")
              << std::endl;

    // Example 3: 全部互通 (A<->B, B<->C, C<->A)
    digraph_type g3({"ABC"}, 3);
    g3.add_edge('A','B',1);
    g3.add_edge('B','A',1);
    g3.add_edge('B','C',1);
    g3.add_edge('C','B',1);
    g3.add_edge('C','A',1);
    g3.add_edge('A','C',1);
    std::cout << "Graph3 (complete digraph): "
              << (g3.isStronglyConnected() ? "Strongly connected" : "Not strongly connected")
              << std::endl;
}


void test_edge_in_cycle()
{
    typedef fengcheng_yu_graph_algorithm::graph<char,int> graph_type;

    // 测试1：三角形 A-B-C-A (每条边都在环上)
    graph_type g1({"ABC"}, 3);
    g1.add_edge('A','B',1);
    g1.add_edge('B','C',1);
    g1.add_edge('C','A',1);

    std::cout << "Test1 A-B: "
              << (g1.edge_in_cycle('A','B') ? "in cycle" : "not in cycle") << std::endl;

    // 测试2：链式图 A-B-C (中间边是桥，不在任何环)
    graph_type g2({"ABC"}, 3);
    g2.add_edge('A','B',1);
    g2.add_edge('B','C',1);

    std::cout << "Test2 A-B: "
              << (g2.edge_in_cycle('A','B') ? "in cycle" : "not in cycle") << std::endl;
    std::cout << "Test2 B-C: "
              << (g2.edge_in_cycle('B','C') ? "in cycle" : "not in cycle") << std::endl;

    // 测试3：正方形 A-B-C-D-A (偶数环，每条边都在环上)
    graph_type g3({"ABCDE"}, 5);
    g3.add_edge('A','B',1);
    g3.add_edge('B','C',1);
    g3.add_edge('C','D',1);
    g3.add_edge('D','A',1);

    std::cout << "Test3 A-B: "
              << (g3.edge_in_cycle('A','B') ? "in cycle" : "not in cycle") << std::endl;

    // 测试4：加一个叶子结点 (D-E)，边 D-E 是桥
    g3.add_edge('D','E', 1);
    std::cout << "Test4 D-E: "
              << (g3.edge_in_cycle('D','E') ? "in cycle" : "not in cycle") << std::endl;
}

int main()
{
    // test4();
    test_edge_in_cycle();
    return 0;
}