
def dfs( grid, i, j):
    if i<0 or j<0 or i>=len(grid) or j>=len(grid[0]) or grid[i][j] != 1:
        return
    grid[i][j] = '#'
    #print(grid)
    dfs(grid, i+1, j)
    dfs(grid, i-1, j)
    dfs(grid, i, j+1)
    dfs(grid, i, j-1)
    dfs(grid, i+1, j+1)
    dfs(grid, i-1, j-1)
    dfs(grid, i+1, j-1)
    dfs(grid, i-1, j+1)


import sys

if __name__ == "__main__":

    m, n = sys.stdin.readline().strip().split()
    m = int(m)
    n = int(n)
    ans = 0
    grid = [list() for _ in range(m)]
    for i in range(m):
        line = sys.stdin.readline().strip()
        values = list(map(int, line.split()))

        grid[i] = values
        #print(grad)

    if not grid:
        print(0)
    count = 0  
    #print(grid)
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 1:
                dfs(grid, i, j)
                count += 1
   #print(grid)
    print(count)    
