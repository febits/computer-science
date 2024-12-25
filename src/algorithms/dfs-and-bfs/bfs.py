#!/usr/bin/env python

def bfs(graph, start_node):
    visited = set([start_node])
    queue = [start_node]

    while queue:
        curr = queue.pop(0)
        print(curr)
        
        for neighbor in graph[curr]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)


if __name__ == "__main__":
    graph = {
        "A": set(["B", "C"]),
        "B": set(["A", "D", "E"]),
        "C": set(["A", "D"]),
        "D": set(["B", "C"]),
        "E": set(["B"])
    }

    bfs(graph, "A")
