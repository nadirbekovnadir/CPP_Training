#include <boost/graph/named_function_params.hpp>
#include <boost/pending/property.hpp>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <stack>

#include <boost/array.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_utility.hpp>

struct Point {
    int x;
    int y;
};

typedef struct EdgeProperties
{
  int weight = 1;
} EdgeProperties;

void DoRandomStaff() {
    using namespace boost;
    // create a typedef for the Graph type
    using Graph = adjacency_list<vecS, vecS, bidirectionalS, no_property, EdgeProperties>;

    // Make convenient labels for the vertices
    enum { A, B, C, D, E, N };
    const int num_vertices = N;
    const std::string name = "ABCDE";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    std::vector<Edge> edges = 
    { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
      Edge(C,E), Edge(B,D), Edge(D,E) };

    // declare a graph object
    Graph g(edges.begin(), edges.end(), num_vertices);

    print_graph(g);

    auto weights = get(&EdgeProperties::weight, g);
    
    boost::array<int, N> paths;
    dijkstra_shortest_paths(
        g, A, 
        predecessor_map(paths.begin()).weight_map(weights));

    std::stack<int> st;
    int p; 
    for (p = E; p != A; p = paths[p]) {
        st.push(p);
    }
    st.push(p);

    while (!st.empty()) {
        std::cout << st.top() << ", ";
        st.pop();
    }
}

int main(int, char**) {
    std::vector<Point> points {{4, 1}, {2, 2}, {3, 5}, {1, 2}};

    std::sort(
        points.begin(), 
        points.end(),
        [](auto a, auto b) { return a.x > b.x; });

    std::ranges::sort(points, {}, &Point::x);

    // do {
    //     std::ranges::for_each(
    //         points, 
    //         [](const auto& p) { 
    //             std::cout << "x: " << p.x << "\t"; 
    //         }
    //     );
    //     std::cout << std::endl;
    // } while (std::ranges::next_permutation(
    //         points.begin(), 
    //         points.end(), 
    //         [](auto a, auto b) { return a < b; }, 
    //         &Point::x)
    //     .found
    // );

    DoRandomStaff();
}
