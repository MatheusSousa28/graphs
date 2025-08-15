**Main Content**

Hello! This repository contains an implementation of directed and undirected graphs in the C programming language, using the adjacency list method.

**What are adjacency lists?**

A graph is a data structure that represents relationships between objects, in this case, vertices.
These vertices are connected by “paths” (edges) that link one to another.

An adjacency list stores, for each vertex, all the vertices it is connected to.
This structure allows us to implement search algorithms based on the graph’s connections.

**Advantages and Disadvantages of using adjacency lists**

**Advantages:**

- Using structs makes the code more readable.

- Easier to maintain and understand.

- Relatively simple to implement.

**Disadvantages:**

- Higher memory usage compared to an adjacency matrix.

- May require more processing in certain cases.

*Alternative:* An adjacency matrix can be lighter and faster in some scenarios, but is more complex to maintain and implement.

**Search algorithms implemented**

Graphs can use different search algorithms to find the shortest path between two vertices or check reachability (which vertices can be accessed
from another). In this implementation, the directed graph uses the DFS (Depth-First Search) algorithm, which goes as deep as possible
along a path before backtracking and exploring others, making it great for checking connections and detecting cycles. The undirected 
graph uses the BFS (Breadth-First Search) algorithm, which visits all neighbors of a vertex before going deeper, allowing us to 
determine the shortest path between vertices. DFS and BFS are not exclusive to directed or undirected graphs and work on both types, 
the choice depends on the search’s purpose.

[Read this in Brazilian Portuguese](README.pt.md)
