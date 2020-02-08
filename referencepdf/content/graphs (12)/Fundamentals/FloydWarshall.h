/**
 * Description: Floyd Warshall's algorithm for all pairs shortest path
 * Time: O(V^3)
 * Source: lmao
 * Verification: lmao imagine verifying
 */

/*
 let dist be a |V| * |V| array of minimum distances initialized to inf
 for each edge (u, v) do
    dist[u][v] <- w(u, v)  // The weight of the edge (u, v)
 for each vertex v do
    dist[v][v] <- 0
 for k from 1 to |V|
    for i from 1 to |V|
        for j from 1 to |V|
            if dist[i][j] > dist[i][k] + dist[k][j]
                dist[i][j] <- dist[i][k] + dist[k][j]
            end if
*/
