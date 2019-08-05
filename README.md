# kruskals-algorithm
Solution of a minimum-spanning-tree problem with Kruskal in C++
---
Kruskal's algorithm is a minimum-spanning-tree algorithm which finds an edge of the least possible weight that connects any two trees in the forest.

![alt text](https://upload.wikimedia.org/wikipedia/commons/b/bb/KruskalDemo.gif)

# Pseudocode

KRUSKAL(G):
A = ∅
foreach v ∈ G.V:
   MAKE-SET(v)
foreach (u, v) in G.E ordered by weight(u, v), increasing:
   if FIND-SET(u) ≠ FIND-SET(v):
      A = A ∪ {(u, v)}
      UNION(FIND-SET(u), FIND-SET(v))
return A
