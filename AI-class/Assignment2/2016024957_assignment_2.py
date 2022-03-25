import random

#current location에서 direction 정보가 왓을때, next location Return
def move(currentLocation, directionInfo):
    print("move 함수 들어옴")
    nextLocation = currentLocation.copy()

    print("이동전 location : ",nextLocation)
    if directionInfo == 0: # up 
        nextLocation[0] -= 1
    elif directionInfo == 1: # right
        nextLocation = list(currentLocation)
        nextLocation[1] += 1
    elif directionInfo == 2: # down
        nextLocation = list(currentLocation)
        nextLocation[0] += 1
    elif directionInfo == 3: #left
        nextLocation = list(currentLocation)
        nextLocation[1] -= 1
    print("이동한 new location: ",nextLocation)
    print("이동 방향 : ",directionInfo)
    return nextLocation
    

#function that writes best way to file
def findway(mineMap,start,Goal,file):
    currentLocation = start.copy()
    file.write(str(currentLocation[0]*5 + currentLocation[1]) +" ")
    
    while(currentLocation != Goal):
        direction = selectMaxEdge(mineMap,currentLocation)
        currentLocation = move(currentLocation,direction)
        file.write(str(currentLocation[0]*5 + currentLocation[1]) + " ")
    

#function that returns max Q value
def findMaxEdge(mineMap, currentLocation):
    
    currentLocation_x = currentLocation[1]
    currentLocation_y = currentLocation[0]

    edgeInfo = mineMap[currentLocation_y][currentLocation_x]
    print(currentLocation,edgeInfo)

    directionIndex = -1 #  0 : up  1 : right   2 : down    3 : left 
    edgeValue = -200
    
    for i in range(len(edgeInfo)):    
        if (edgeInfo[i] > edgeValue):
            directionIndex = i
            edgeValue = edgeInfo[i]
    if (directionIndex == -1):
        print("findMaxEdge Error")
        quit()
    return edgeValue

#function returns index(direction) of max Q value 
def selectMaxEdge(mineMap, currentLocation): 
    

    currentLocation_x = currentLocation[1]
    currentLocation_y = currentLocation[0]

    edgeInfo = mineMap[currentLocation_y][currentLocation_x]
    print(currentLocation,edgeInfo)

    directionIndex = -1 #  0 : up  1 : right   2 : down    3 : left 
    edgeValue = -200
       
    for i in range(len(edgeInfo)):        
        if (edgeInfo[i] > edgeValue):
            directionIndex = i
            edgeValue = edgeInfo[i]
    if (directionIndex == -1):
        print("findMaxEdge Error")
        quit()
    return directionIndex

#function that selects edge Randomly. If selected edge is "Bomb edge" or unexist edge, It selects again
def selectEdgeRandomly(mineMap,reward, currentLocation,Goal):


    currentLocation_x = currentLocation[1]
    currentLocation_y = currentLocation[0]

    directionIndex = random.randint(0,3)
    nextLocation = move(currentLocation,directionIndex)
    print("move 함수 완료")
    nextLocation_y = nextLocation[0]
    nextLocation_x = nextLocation[1]

    #print(nextLocation)

    if (nextLocation_y < 0 or nextLocation_x < 0 or nextLocation_x > 4 or nextLocation_y > 4):
        #map을 벗어난 경우 아무것도 update 하지 않고 다시 select
        print("out of range.. 다시 탐색")
        return selectEdgeRandomly(mineMap,reward,currentLocation,Goal)

    elif reward[nextLocation_y][nextLocation_x] == -100: # bomb
        print("bomb 만났어용")
        mineMap[currentLocation_y][currentLocation_x][directionIndex] = -100 # 어차피 bomb가 나오면 다시 시작지점으로 가므로 r Max Q 는 생략
        return "Bomb" #it means it should start from beginning

    
    else:
        #정상 동작이므로 일단 Q table update
        #new value 가 기존 값보다 더 큰 경우에만 update
        newValue = reward[nextLocation_y][nextLocation_x] + 0.9 * findMaxEdge(mineMap,nextLocation)
        if newValue > findMaxEdge(mineMap,currentLocation) :
            mineMap[currentLocation_y][currentLocation_x][directionIndex] = newValue
        
        if nextLocation == Goal:
            print("line 107 : Goal")
            return "Goal" 
        else:
            print("정상적으로 nextLocation으로 이동.. reward 값 : ",reward[nextLocation_y][nextLocation_x])
            return selectEdgeRandomly(mineMap,reward,nextLocation,Goal)
            
#Q Table을 update하는 함수     
def updateQTable(mineMap,reward,start,Goal):
    #처음엔 시작지점에서 select를 해서
    GoalCount = 0
    
    
    while(GoalCount<50):
        Result = selectEdgeRandomly(mineMap,reward,start,Goal)
        if Result == "Goal":
            print("Goal")
            GoalCount += 1


if __name__ == "__main__":
    
    f = open("input.txt",'r')

    mineMap = [[[0 for direction in range(4)] for row in range(5)] for col in range(5)]
    reward = [[0 for row in range(5)] for col in range(5)]
    
    lineCount = 0
    start = [-1,-1]
    Goal = [-1,-1]
    
    while(lineCount<5):
        line = f.readline()
        if not line:
            print("file error")
            break
        seperateLine = list(line)
        print(seperateLine)
        for i in range(5):
            #Start Point
            if seperateLine[i] == 'S':
                start = [lineCount,i]
                reward[lineCount][i] = 0
            
            #Normal point
            elif seperateLine[i] == 'P':
                reward[lineCount][i] = 0
            
            #Bonus Point
            elif seperateLine[i] == 'T':
                reward[lineCount][i] = 1
            
            #Bomb Point
            elif seperateLine[i] == 'B':
                reward[lineCount][i] = -100

            #Goal Point
            elif seperateLine[i] == 'G':
                reward[lineCount][i] = 100
                Goal = [lineCount,i]
                  

        lineCount += 1
    
    if (start == [-1,-1] or Goal == [-1,-1]):
        print("No Start point or Goal point")
        quit()
                
    file = open("output.txt",'w') #output file
    updateQTable(mineMap,reward,start,Goal)  
    for i in range(5):
        for j in range(5):
            print(mineMap[i][j],end="     ")
        print()

    findway(mineMap,start,Goal,file)

    answer = findMaxEdge(mineMap,start)
    
    file.write("\n" + str(answer))
    f.close()
    file.close()
    
#94.73684210526312