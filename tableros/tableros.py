from random import randint
from collections import deque

# Check if the move is within board boundaries and the cell is valid (not '#')
def is_valid_move(board, visited, row, col):
    return 0 <= row < len(board) and 0 <= col < len(board[0]) and board[row][col] == '.' and not visited[row][col]

# Looks for a valid path from (i1,j1) to (i2,j2)
def bfs(board, i1, j1, i2, j2):
    # Directions for moving: up, down, left, right
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    # Mark the start position as visited
    visited = [[False] * len(board[0]) for _ in range(len(board))]
    visited[i1][j1] = True
    
    # Queue for BFS
    queue = deque([(i1, j1)])
    
    while queue:
        x, y = queue.popleft()
        
        # If we reach the destination
        if x == i2 and y == j2:
            return True
        
        # Explore neighbors
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            
            if is_valid_move(board, visited, nx, ny):
                visited[nx][ny] = True
                queue.append((nx, ny))
    
    # If no path found
    return False

# Transforms the board dict into a writeable string
def stringify(tablero):
    string = ""
    string+= f'{tablero["N"]} {tablero["M"]} {tablero["D"]}\n'
    string+= f'{tablero["i1"]} {tablero["j1"]}\n'
    string+= f'{tablero["i2"]} {tablero["j2"]}\n'
    for row in tablero["T"]:
        for char in row:
            string+=f"{char}"
        string+="\n"
    return string

# Checks if the board is valid
def checkTablero(tablero):
    if(tablero["T"][tablero["i1"]][tablero["j1"]] == "#" or
       tablero["T"][tablero["i2"]][tablero["j2"]] == "#"):
        return False
    return bfs(tablero["T"], tablero["i1"], tablero["j1"], tablero["i2"], tablero["j2"])

# Genereates a Random Board of given dimensions
def generarTablero(N:int,M:int,D:int):
    tablero={}
    tablero["N"] = N
    tablero["M"] = M
    tablero["D"] = D
    tablero["i1"] = randint(0,N-1)
    tablero["i2"] = randint(0,N-1)
    tablero["j1"] = randint(0,M-1)
    tablero["j2"] = randint(0,M-1)
    tablero["T"]=[]
    for i in range(0,N):
        tablero["T"].append([])
        for j in range(0,M):
            chance = randint(1,50)
            char = "."
            if randint(1,100)<chance: 
                char = "#"
            tablero["T"][i].append(char)
    print(tablero)
    return tablero

# Generates various boards up to dimension N*M 
# and writes each one in one file if the board is valid
#N>8, M>8
def generarNM_Tableros(N:int, M: int):
    for i in range(8,N):
        for j in range(8,M,3):
            for d in range(1,randint(1,max(N,M))):
                tablero = generarTablero(i,j,d)
                if checkTablero(tablero):
                    archivo = open(f"./tableros/tablero{i}-{j}-{d}.txt", "w")
                    archivo.write(stringify(tablero))
                    archivo.close()

def main():
    generarNM_Tableros(50,50)

if __name__=="__main__":
    main()