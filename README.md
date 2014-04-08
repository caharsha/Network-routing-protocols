Network-routing-protocols
=========================

As part of the Analysis of Algorithms course, this project aims at evaluating the efficiency of different algorithms and data structures in designing routing protocols.

Introduction
The problem addressed here is called the maximum bandwidth path, also called the maximum width path problem or the bottleneck shortest path problem or the maximum capacity path problem. 

A formal definition of the maximum bandwidth path is presented as follows:

Let G be a weighted undirected graph, where the edge weight is interpreted as the “bandwidth” of the edge, i.e, the amount of flow allowed to go through the edge in unit time. The bandwidth of a path is defined, naturally, to be the minimum edge bandwidth over the edges on the path. The Max-Bandwidth-Path problem is for a given weighted undirected graph G and two vertices s and t in G, to find a path between s and t in G whose bandwidth is the maximum over all paths between s and t in G. 

It is also closely related to the min-max path problem which minimizes the maximum weight of any of the edges on a chosen path, which finds applications in the transport industry. Any algorithm for the widest path problem can be transformed into an algorithm for the minimax path problem, or vice versa, by reversing the sense of all the weight comparisons performed by the algorithm, or equivalently by replacing every edge weight by its negation.
Solution to the maximum bandwidth problem is an important component of the Schulze method for deciding the winner of a multi-way election, and has been applied to digital compositing, metabolic analysis, and the computation of maximum flows among many other applications.

The application in question here refers to the network routing protocol which if bluntly put can be described as follows, paying no importance to the communication networks aspect of the problem:

If the edges in the graph represents connections between routers in the Internet, and the weight of an edge represents the bandwidth of a connection between two routers, the widest path problem is the problem of finding an end-to-end path between two Internet nodes that has the maximum possible bandwidth.

The algorithms implemented to solve the maximum bandwidth path here are modifications of Dijkstra's algorithm to calculate the single source shortest path and Kruskal's algorithm to compute the maximum spanning tree.
The maximum bandwidth path between the source and the destination lies on the maximum spanning tree. This fact is exploited in the application of a modified Kruskal's algorithm to the same which computes a maximum spanning tree. The traversal along the tree is then done using Depth First Search to return the path between source s and destination t. DFS is preferred as the graph is sparse.

Design and Implementation


Random graph generation:

We generate sparse and dense graphs for testing the network routing protocol implementation, each with 5000 vertices and of degree 6 and ~1000 respectively. A vector of vectors is used to store the adjacency matrix in both cases to ensure uniformity. The choice of an edge existing between 2 vertices is chosen based on the output of a random number generation and the edge weight also determined by random number generation.

System time is used as a seed for randomizing on each execution.

A edge weight of -1 is used to indicate the absence of an edge between the two vertices in the adjacency matrix. Initially the entire vector of vectors is initialized to -1. Depending upon the degree of vertices, a probability function is implemented using rand() to determine by choice if an edge between vertex v and w should exist. Edge weights are generated using rand() and take values between 0 and 32766. (32767 is used as the source width for Dijkstra).
The number of edges for the sparse graph is exactly 15,000 while the number of edges for the dense graph is around 5,000,000.

The exact degree for each vertex for the sparse graph may not be 6 for all executions as sometimes there may not be a vertex for some vertices to connect to in this randomized generation and hence, it is rerun until the condition is satisfied. Fortunately only one out of six computations on average is rerun and hence  the randomization works fine.

Heap and operations:

A binary heap is used for implementing a priority queue. Operations such as maximum, insert and delete are implemented. Maximum returns the root, the insert operation appends the new element at the end of the heap and reorders as necessary and the delete operation removes the root and reorders as necessary. A vector of integers is used to store the heap element and the value of the heap element in itself is stored in another vector where the heap element functions as the index.

The insert and delete operations need reordering which is executed using a max-heapify process (different for each procedure). While the insertion pushes the inserted element up the heap, the delete pushes elements up the heap to take the place of the root and the element that was pushed up to the root and so on.

Modified Dijkstra's for computing the maximum bandwidth path:

The original relax subroutine is modified as follows:
For an edge (u,v), if min {d[u], w(u,v)} > d[v], then we update d[v] to be the min {d[u], w(u,v). This is done as the path from the source to u and then the path from u to v has bandwidth min {d[u],w(u, v)}, which is more than the one we have currently in d[v].

The implementation uses an unordered array for storing the fringes. The random graph generated in step 1 is passed as an argument input with the adjacency matrix to the Dijkstra_max_w procedure. All widths are initialized to -1 and all vertices (widths) are then added to a standard template library's priority queue implementation. The source is then given a width of 32767 (integer max) and popped from the queue. For each vertex v popped from the queue, all edges (v,w) are sequentially scanned and added to the fringe structure. The relax function as defined above is run for each of the edges and then the next vertex is popped from the queue and the process repeated until the queue is empty. The values stored in d[v] then correspond to the maximum bandwidth for the path between s and v.

The implementation was relatively easy as opposed to incorporating a heap structure for fringes as in the next procedure. 

Modified Dijkstra's for computing the maximum bandwidth path using heap structure to store fringes:
The heap structure removes the task of recomputing the extraction of the fringe at every instance and instead we extract the root with heap operation minimum and then delete the root and reorder as needed.  The insertion procedure is slightly more costly however as we may need to reorder certain elements to maintain the heap structure. This essentially speeds up the extraction of the max d[v] at the cost of log n insert and delete operation. This is advantageous for the dense graph while guaranteeing about the same performance for the sparse graph.

Once again, an array is used to store the fringes.

To find the max bandwidth path between a different source and destination we have to run the procedure again from scratch in both implementations of the modified Dijkstra.

The heap structure implementation for the fringe structure needed a number of redundancies to ensure smooth operation.
Kruskal's algorithm to compute the maximum spanning tree:

The graph G(V,E) is first passed as an argument (Adjacency matrix) to the heap sort function which returns the edges sorted in the ascending order of weights. The sorted edges are returned as a vector of structures where each of the structures consists of the edge weight and the constituent vertices of the given edge.

The sorted edges are then passed to the Kruskal function. The maximum spanning tree which is returned by the function is another adjacency matrix. The adjacency matrix is again initialized with all edge weights set to -1 to indicate the absence of the edge. Then the makeset procedure is invoked which initializes dad[v] and rank[v] for all vertices in the graph. Then scanning each edge from the sorted edge procedure, we check if the vertices are already part of the tree using the find function. The find function takes in the argument as vertex and then returns the root of the tree structure, the optimization procedure implemented assigns the root of every sub structure as dad[v]. After returning the root of each sub structure in the max spanning tree for the given vertices of the edge, the edge is added to the tree if the roots of the substructure are different. Additionally the union procedure combines the two substructures together for the next iteration. The procedure for Kruskal's is halted when we have added 4999 edges (tree has n-1 edges, given that we have 5000 vertices). Every time the union procedure is invoked a counter is incremented to keep count of the number of the edges in the tree.

The adjacency matrix is updated every time we add an edge with the vertices used as indices and the edge weight being the value contained. Now that we have the maximum spanning tree, we can compute the max bandwidth path between any two vertices as opposed to having to run the Dijkstra's procedure all over again to change the source for a different computation.

Depth first search to return maximum bandwidth path:
The depth first search returns the path and the minimum of the edge weights along the path gives us the maximum bandwidth path. The depth first search is implemented iteratively. Because of the addition of the extra path between the source and the destination, we do not run the risk of a non-existent path between source s and t.

Testing and Run-time Statistics

Test Machine:
All the tests were carried out on a Lenovo y510p ideapad with a Intel i7-4700M Haswell Quad core processor with each core clocked at 2.4GHz (up to 3.4GHz on turbo performance), 8GB RAM, 1 TB 500RPM Hard disk drive, Nvidia Geforce 750M GPU running on Ubuntu 13.10 Stable platform. The GNU open source g++ compiler and the Geany IDE complete the test machine specifications.

Run-time Statistics and Analysis:
For the graph generation, one dense graph was generated in 0.37 seconds which is roughly the same time as for the sparse graph but in cases where the sparse graph was not generated to specification on the first time, the time roughly doubled.

The Dijkstra's algorithm implementation ran in 0.72 – 0.89 seconds for the sparse and dense graphs respectively while using a heap structure for the fringes.
The Dijkstra's algorithm implementation ran in 0.68 – 1.35 seconds for the sparse and dense graphs respectively.
Kruskal's algorithm to find the maximum spanning tree ran in 0.1-0.2 seconds for the Sparse graph whereas it took around 0.97 – 1.1 seconds for the dense graph.
The DFS method ran in 0 – 0.1 seconds for the best and worst case respectively.
For finding about 5 source to destination max bandwidth paths, Dijkstra's implements took roughly 5 times the original implementation time, while for a given graph, Kruskal's added no significant addition of time. 
Conclusions

The test times are fairly indicative of the expected results. As expected, the modified Kruskal's algorithm is fastest for a sparse graph, as both the procedures for sorting the edges according to the edge weights, the construction of the maximum spanning tree are strongly dependent on the number of edges.
Modified Dijkstra's using a heap structure for fringes is the fastest for one iteration of source to destination max bandwidth computation for dense graphs. This beats the unordered array implementation as the quickest way to get retrieve the maximum from the unordered array requires one iteration of bubble sort (O(n) time) as opposed to O(1) retrieval from the heap. On the other hand, the comparison for the insert and delete times are O(log n) and O(1) respectively for the heap structure and the unordered array implementations and hence as expected, the unordered array implementation does marginally better for the sparse graphs.
As stated earlier, Dijkstra's works only for a single source to all destinations, hence finding the maximum bandwidth path from different sources take n times the time for one implementation. Whereas, the Kruskal's implementation returns the maximum spanning tree which can be used to compute the max bandwidth path from any vertex to any other vertex without any additional time as time taken for DFS is insignificant as compared to the computation of he maximum spanning tree. 

Suggested improvements
If the edges are sorted by their weights, then a modified version of Dijkstra's algorithm can compute the bottlenecks between a designated start vertex and every other vertex in the graph, in linear time. The key idea behind the speedup over a conventional version of Dijkstra's algorithm is that the sequence of bottleneck distances to each vertex, in the order that the vertices are considered by this algorithm, is a monotonic subsequence of the sorted sequence of edge weights; therefore, the priority queue of Dijkstra's algorithm can be replaced by an array indexed by the numbers from 1 to m (the number of edges in the graph), where array cell i contains the vertices whose bottleneck distance is the weight of the edge with position i in the sorted order. This method allows the widest path problem to be solved as quickly as sorting; for instance, if the edge weights are represented as integers, then the time bounds for integer sorting a list of m integers would apply also to this problem. This is much more efficient as compared to the current implementation which runs in the same time as the Dijkstra's implementation.
I have used an adjacency matrix for uniform and easy implementation for both sparse and dense matrices even though theory advocates the use of adjacency lists for sparse matrices for both an effective access time and space utilization.
The Standard template sort function gave a much better time as compared to my heap sort function which needs more optimization.
The maximum spanning tree is definitely a sparse matrix and edges should be represented as an adjacency list for much better overall performance.
