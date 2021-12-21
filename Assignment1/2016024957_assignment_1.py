import random
from collections import deque#to use queue in bfs

#1. BFS
def bfs(Size):
    print("******** Bfs ********")
    #bfs는 모든 경우의 수를 탐색하므로 board 랜덤초기화가 필요 없음.
    Board = fillZero(Size)
    BoardInfo = placeQueenRandomly(Board,Size)
    
    
    saveWays = deque()
    Board = createBoard(BoardInfo,Size)
    
    saveWays.append(BoardInfo) # queue에 현재 Board 정보 넣기
    
    filename = "{size}_bfs_output.txt".format(size = Size)
    resultFile = open(filename,'w')
    if (Size<4): # n이 3이하에서는 solution이 없고, 4이상은 모든 경우를 찾기떄문에 solution을 반드시 찾아냄
        resultFile.write("no solution")
        return
    cnt = 0
    while(saveWays): # queue에 값이 있을때 or optimal 찾으면 break
        
        BoardInfo = saveWays.popleft()
        Board = createBoard(BoardInfo, Size)
        #print("while문에서 현재 큐의 보드 출력")
        #printBoard(Board,Size)
        #print()
        neighborBoard = createBoard(BoardInfo, Size)
        neighborBoardInfo = BoardInfo.copy() # ref가 아닌 copy..

        for i in range(Size):
            for j in range(Size):
                if (j != BoardInfo[i]):
            
                    neighborBoard[i][neighborBoardInfo[i]] = 0 #기존의 queen이 있던 자리
                    neighborBoardInfo[i] = j # row i 의 새로운 queen 자리는 column j
                    neighborBoard[i][j] = 1 # place new queen -> change to 1
                
                    neighborHValue = heuristics(neighborBoard,Size)
                    if (neighborHValue == 0):
                        neighborBoardInfo = chagneRowColumn(neighborBoardInfo,Size)
                        resultFile.write(" ".join(map(str, neighborBoardInfo)))

                        print("Found solution!!")
                        printBoard(neighborBoard,Size)
                        print("result :",neighborBoardInfo)
                        print()

                        
                        return

                    else:
                        saveWays.append(neighborBoardInfo.copy())
                     

                    #다시 이웃 보드 원상복구 후

                    neighborBoard[i][neighborBoardInfo[i]] = 0
                    neighborBoardInfo[i] = BoardInfo[i]
                    neighborBoard[i][neighborBoardInfo[i]] = 1
        
        cnt += 1
        
        if (cnt>1000000):
            print("no solution")
            resultFile.write("no solution (time over)")
            return

#2. HillClimbing
def hc(Size):
    print("******** Hill Climbing ********")
    filename = "{size}_hc_output.txt".format(size = Size)
    resultFile = open(filename,'w')
    Board = fillZero(Size)
    BoardInfo = placeQueenRandomly(Board,Size)

    iterationNumber =0
    randomSettingCount = 1
    while(True):
        
        Board,BoardInfo = getOptimalNeighbor(Board,BoardInfo,Size)
        iterationNumber+=1
        result = heuristics(Board,Size)

        if(result == 0):
            BoardInfo = chagneRowColumn(BoardInfo,Size)
            resultFile.write(" ".join(map(str,BoardInfo)))
            print("Found Solution!!")
            printBoard(Board,Size)
            print("result :",BoardInfo)
            print("보드 초기화 횟수 :",randomSettingCount)
            print()
            break
        if iterationNumber>30:
            #if not found optimal board, set board randomly again, and repeat until find optimal board
            if result > 0:                
                Board = fillZero(Size)
                BoardInfo = placeQueenRandomly(Board,Size)
                iterationNumber = 0
                randomSettingCount += 1
                
                if randomSettingCount > 30:
                    print("no solution")
                    resultFile.write("no solution")
                    break

#3. Constraints Satisfaction Problem                    
def csp(Size):
    print("******** Constraint Satisfaction Problem ********")
    filename = "{size}_csp_output.txt".format(size = Size)
    resultFile = open(filename,'w')
    Board = fillZero(Size)
    BoardInfo = []

    for _ in range(Size):
        BoardInfo.append(0)
    
    if(placeQueen(Board,BoardInfo,0,Size) == False):
        print("no solution")
        resultFile.write("no solution")
        print()
    else:
        BoardInfo = chagneRowColumn(BoardInfo,Size)
        resultFile.write(" ".join(map(str,BoardInfo)))
        print("Found solution!!!!!!")
        printBoard(Board,Size)
        print("result :",BoardInfo)
        print()
        
#4. calculate heuristic value of current state and return hvalue 
def heuristics(graph , Size):
    #왼쪽대각선 / 아래 / 오른쪽 대각선
    hvalue = 0
    for i in range(Size):
        for j in range(Size): 
            if graph[i][j] == 1:
               # print("i :",i,"j :",j)
                for k in range(i+1,Size): # 다음줄에 있는것부터 비교해야함
                    if graph[k][j] == 1: #아래
                        hvalue += 1
                    elif j-(k-i)>=0 and graph[k][j-(k-i)] == 1: # 왼쪽 아래
                        hvalue += 1
                    elif j+(k-i)<Size and graph[k][j+(k-i)] == 1: # 오른쪽 아래
                        hvalue += 1

    return hvalue

#5. Place queen at row 'row'. function for Backtracking ( 불가능하면 False 반환)
def placeQueen(Board,BoardInfo, row, Size):

    if row >= Size:
        #print("마지막 row로 왔어요")
        return True
    
    for i in range(Size): 
        # 현재 rowo에서 column i를 순회하며 queen을 놔도 안전한지 확인해야함
        Board[row][i] = 1
        if (heuristics(Board,Size) == 0):
               # print("safe한 보드임")
            #queen 을 둘 수 있으므로 
                BoardInfo[row] = i # 행 row 는 i 에 queen이 있음
                if placeQueen(Board,BoardInfo,row+1,Size) == True:
                    return True
                else:
                    Board[row][i] = 0
        else: 
          #  printBoard(Board,Size)
           # print()
            Board[row][i] = 0 # i column 에는 돌을 둘 수 없으므로 원상복구
            

    return False

#6. Make a board with size 'Size x Size' filled with zero and return the Board
def fillZero(Size):
    result = []
    for i in range(Size):
        tmpList = []
        for j in range(Size):
            tmpList.append(0)
        result.append(tmpList)
    return result

#7. Place queens randomly and return location information of queens
def placeQueenRandomly(graph,Size):
    locationInfo = []
    
    for i in range(Size):
        randomNumber = random.randint(0,Size-1)
        #print("random number :",randomNumber) 
        locationInfo.append(randomNumber)
        graph[i][randomNumber] = 1

    return locationInfo

#8. Function that create board with given location information and return Board
def createBoard(locationInfo,Size):
    newBoard = []
    newBoard = fillZero(Size)
    for i in range(Size):
        newBoard[i][locationInfo[i]] = 1

    return newBoard

#9. Fucntion that finds out optimal neighbor of graph of state "locationInfo". it returns Board, location info
def getOptimalNeighbor(graph, locationInfo ,Size):

    Board = createBoard(locationInfo,Size)
    BoardInfo = locationInfo.copy() # 참조가 안되고 복사 시키려면 이렇게 해야함
    hvalue = heuristics(Board,Size)
    
    neighborBoard = createBoard(locationInfo, Size)
    neighborBoardInfo = locationInfo.copy() # ref가 아닌 copy..


    for i in range(Size):
        for j in range(Size):
            if (j != locationInfo[i]):
                neighborBoard[i][neighborBoardInfo[i]] = 0 #기존의 queen이 있던 자리
                neighborBoardInfo[i] = j # 새로운 queen 자리
                neighborBoard[i][j] = 1 # place new queen -> change to 1

                neighborHValue = heuristics(neighborBoard,Size)

                if (neighborHValue <= hvalue): # found new op value
                    hvalue = neighborHValue # change to new op value
                    BoardInfo = neighborBoardInfo.copy()
                    Board = createBoard(BoardInfo,Size) # now Board is new board with new boardInfo

                #다시 이웃 보드 원상복구

                neighborBoard[i][neighborBoardInfo[i]] = 0

                neighborBoardInfo[i] = locationInfo[i]
                neighborBoard[i][neighborBoardInfo[i]] = 1
                
    return Board,BoardInfo

#10. Function that just prints out Board                 
def printBoard(graph, Size):
    for i in range(Size):
        for j in range(Size):
            print(graph[i][j],end=' ')
        print()

#11. function for formatting result (row -> column / start location 0 -> 1)
def chagneRowColumn(List,Size):
    def addOne(x):
        return x+1

    resultList = List.copy()
    for i in range(Size):
        resultList[List[i]] = i
    
    return list(map(addOne,resultList))


if __name__ == "__main__":
    
    f = open("input.txt",'r')
    while True:
 
        line = f.readline()
        if not line:
            break
        seperateLine = line.split() 
        tmpSize = int(seperateLine[0])
        method = seperateLine[1]
        
        if(method == "bfs"):
            bfs(tmpSize)
        elif(method == "hc"):
            hc(tmpSize)
        elif(method == "csp"):
            csp(tmpSize)
        else:
            print("지원하지않는 method 입니다.")
        
        
    
        
        
      






    f.close()