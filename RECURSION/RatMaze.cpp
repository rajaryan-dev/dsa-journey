#include <bits/stdc++.h>
using namespace std;

// DFS function to explore all valid paths in the maze
void explorePaths(vector<vector<int>>& maze, int row, int col,
                  string currentPath, vector<string>& allPaths,
                  vector<vector<bool>>& visited) {
  int n = maze.size();

  // Out of bounds / blocked / already visited
  if (row < 0 || col < 0 || row >= n || col >= n || maze[row][col] == 0 ||
      visited[row][col])
    return;

  // If destination reached (bottom-right corner), store the path
  if (row == n - 1 && col == n - 1) {
    allPaths.push_back(currentPath);
    return;
  }

  // Mark the current cell as visited
  visited[row][col] = true;

  // Move Down
  explorePaths(maze, row + 1, col, currentPath + "D", allPaths, visited);

  // Move Up
  explorePaths(maze, row - 1, col, currentPath + "U", allPaths, visited);

  // Move Left
  explorePaths(maze, row, col - 1, currentPath + "L", allPaths, visited);

  // Move Right
  explorePaths(maze, row, col + 1, currentPath + "R", allPaths, visited);

  // Backtrack — unmark visit so other paths can use this cell
  visited[row][col] = false;
}

// Function to return all possible paths if the rat can reach the destination
vector<string> findAllPaths(vector<vector<int>>& maze) {
  int n = maze.size();
  vector<string> allPaths;

  // If starting position is blocked → no path possible
  if (maze[0][0] == 0) return allPaths;

  vector<vector<bool>> visited(n, vector<bool>(n, false));
  explorePaths(maze, 0, 0, "", allPaths, visited);

  return allPaths;
}

int main() {
  vector<vector<int>> maze = {
      {1, 0, 0, 0},
      {1, 1, 0, 1},
      {1, 1, 0, 0},
      {0, 1, 1, 1},
  };

  vector<string> paths = findAllPaths(maze);

  if (paths.empty())
    cout << "No path exists" << endl;
  else
    for (string path : paths) cout << path << endl;

  return 0;
}
