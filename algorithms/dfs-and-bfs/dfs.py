#!/usr/bin/env python

def dfs(graph, start_node):
    visited = set()
    stack = [start_node]

    while stack:
        curr = stack.pop()
        if curr not in visited:
            visited.add(curr)
            print(curr)

            for neighbor in graph[curr]:
                if neighbor not in visited:
                    stack.append(neighbor)


if __name__ == "__main__":
    graph = {
        "A": set(["B", "C"]),
        "B": set(["A", "D", "E"]),
        "C": set(["A", "D"]),
        "D": set(["B", "C"]),
        "E": set(["B"])
    }

    dfs(graph, "A")
