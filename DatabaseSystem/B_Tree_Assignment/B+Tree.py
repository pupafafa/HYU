import bisect
import math #소수점 올림함수 ceil 사용을 위해서
import sys #command line input 쓰려고
import csv # csv파일 불러오기 / 저장하기 
import pickle
# tree단위 insert-> find position -> 노드단위 insert -> overflow check -> split
# overflow check.... split ... 


class node():

    def __init__(self,tree,order):
        self.tree=tree #노드의 트리를 참조하기 위해서 저장해두기 (상위 메모리 참조(?))
        self.keys=[]
        self.data=[] # store data if leaf// else store node
        self.next = None
        self.is_leaf=True
        self.order=order
        

    def insert(self,index,key,data,parents): #node 단위 insert->simply insert
        self.keys.insert(index,key)
        self.data.insert(index,data)
        if len(self.keys)>=self.order:
            self.overflow(parents)

    def split(self): #self(left) / right
        mid=self.order//2 # right biased tree
        right=node(self.tree,self.order)
        push_key=self.keys[mid]
        if self.is_leaf:
            right.keys=self.keys[mid:]
            right.data=self.data[mid:]
            self.data=self.data[:mid]   ##리프일때는 자신의 데이터값을 유지
        else: #리프가 아니면 미드값을 올려보내고 다시 내릴필요 없음
            right.keys=self.keys[mid+1:]
            right.data=self.data[mid+1:]
            self.data=self.data[:mid+1] # mid값만 올라가기때문에 왼쪽에서 자식노드 하나를 더 가지고 가야됨

        right.is_leaf=self.is_leaf    # self(left)와 right는 서로 같은 레벨에 위치하므로 
        right.next=self.next
        self.next=right
        self.keys=self.keys[:mid]
        
        self.next=right
        return right,push_key 
        #left -> stay at same position right.keys[0] goes to parent key
        # right -> parent.data[index+1] (append)

    def overflow(self,parents): #grow up
        right_sibling,new_key=self.split()
        if parents: # if parents exist -> 값 올리기
            parent,parent_index=parents.pop()
            parent.keys.insert(parent_index,new_key)
            parent.data.insert(parent_index+1,right_sibling)
            if len(parent.keys)>=self.order: #since parent size up, check overflow again
                parent.overflow(parents)
            #부모에서 overflow난거랑 리프에서 난거랑 구분해야됨

        else: # no parent -> create new node as parent
            new_node=node(self.tree,self.order)
            new_node.keys.append(new_key)
            new_node.data.append(self)
            new_node.data.append(right_sibling)
            new_node.is_leaf=False
            new_node.tree.root=new_node

    #underflow -> check sibling exist-> check sibling size-> can lend?lend func:merge
    def lend(self,parent,parent_index,borrower,borrower_parent_index):
        #try begging left node first
        #size check은 호출 전에 underflow에서 하자.
        if parent_index<borrower_parent_index: 
            # borrow from right / self=left sibling
            borrower.keys.insert(0,self.keys.pop())
            borrower.data.insert(0,self.data.pop())
            parent.keys[parent_index]=borrower.keys[0]
        
        else:
            #borrow from left
            borrower.keys.append(self.keys.pop(0))
            borrower.data.append(self.data.pop(0))
            
            parent.keys[borrower_parent_index]=self.keys[0]

    def underflow(self,parents): #if underflow after remove, borrow or merge
        minimum=math.ceil(self.order/2)-1
        parent,parent_index=parents.pop() 
        #after line86, there are only parents in parents (since self is extracted by pop())
        #if right_sib>min borrow
        left_sibling=None
        right_sibling=None
        if parent_index+1<len(parent.data):
            right_sibling=parent.data[parent_index+1]
        if parent_index:
            left_sibling=parent.data[parent_index-1]        
        

        if self.is_leaf: 
            #borrow <from> sibling 
            if right_sibling:
                if len(right_sibling.keys)>minimum:
                    right_sibling.lend(parent,parent_index+1,self,parent_index)
                    return
                #borrow from left
            if left_sibling:
                if len(left_sibling.keys)>minimum:
                    left_sibling.lend(parent,parent_index-1,self,parent_index)
                    return

            #merge
            #merge with left
            if left_sibling:
                left_sibling.keys.extend(self.keys)
                left_sibling.data.extend(self.data)
                left_sibling.next=self.next
                #delete split key
                parent.delete(parent_index-1,parents)
                return
            #merge with right
            if right_sibling:
                self.keys.extend(right_sibling.keys)
                self.data.extend(right_sibling.data)
                self.next=right_sibling.next
                #delete split key
                parent.delete(parent_index,parents)

        elif not self.is_leaf: #borrow from parent or merge with sibling, parent(split value)
            #internal node 에서의 underflow는 parent에서 값을 borrow 하거나 self + sibing + parent 세개를 merge한다 이떄 parent는 key값만 내려옴
            print("line129")

            #borrow from parent            
            if left_sibling:
                print("line133")
                if len(left_sibling.keys)>minimum:
                    self.keys.insert(0,parent.keys.pop(parent_index-1))
                    self.data.insert(0,left_sibling.data.pop())
                    parent.keys.insert(parent_index-1,left_sibling.keys.pop())
                    return
            if right_sibling:
                print("line140")
                if len(right_sibling.keys)>minimum:
                    self.keys.append(parent.keys.pop(parent_index))
                    self.data.append(right_sibling.data.pop(0))
                    parent.keys.insert(parent_index,right_sibling.keys.pop(0))
                    return

            #merge self + parent,sib
            #case1 : merge with left
            if left_sibling:
                left_sibling.keys.append(parent.keys.pop(parent_index-1)) #split 키를 가져옴
                parents.data.pop(parent_index-1)
                left_sibling.keys.extend(self.keys)
                left_sibling.data.extend(self.data)
                left_sibling.next=self.next
                if parent==self.tree.root:
                    if len(parent.keys) > 1:
                        parent.delete(parent_index-1,parents)
                    else:
                        self.tree.root=self  
                return

            #case2 : merge with right
            if right_sibling:
                print(parent.keys[parent_index])
                self.keys.append(parent.keys.pop(parent_index))
               # print(parent.keys)
                print(len(parent.keys))
                parent.data.pop(parent_index)
                self.keys.extend(right_sibling.keys)
                self.data.extend(right_sibling.data)
                self.next=right_sibling.next
                if parent==self.tree.root:
                    if len(parent.keys) > 1:
                        parent.delete(parent_index,parents)
                    else:
                        self.tree.root=self
                return
            



    def delete(self,index,parents):

        # tree단위 delete에서 find_path를 통해 노드와 인덱스 부모를 미리 find해놓고
        # leaf인지 아닌지 케이스 나누기
        minimum=math.ceil(self.order/2) - 1
        key=self.keys[index]
        if self.is_leaf:
            self.data.pop(index)
            self.keys.pop(index)

            if index==0:                   
                if len(self.keys)>0:                  
                   smallest=self.keys[0]
                else:
                    smallest=self.next.keys[0]
                for i,parent in enumerate(parents):
                    _Node=parent[0]
                    Index=parent[1]
                    if _Node==parents[-1][0]:
                        if len(self.keys)<minimum:
                            break
                    #여기서 i는 enumerate쓰는데 헷갈려서 인덱스 인자로 넣었습니다. 파이썬이 처음이어서 적응이 안되서요..
                    #인덱스있는 노드를 찾았는데 바로 윗 부모라면 -> 해당 노드의 인덱스가 오른쪽 값이 있으면,  1개뿐인 값이라면
                    if key in _Node.keys:
                        _Node.keys[Index-1]=smallest
                        break


        else: 
        #leaf 노드가 아닌 internal_node 일때
            self.keys.pop(index)
            self.data.pop(index+1)
        
        if len(self.keys)<minimum:
            self.underflow(parents) #merge or borrow


class BplusTree(node):
    def __init__(self,order):
        self.order=order
        self.root = node(self,order)
        self.root.tree=self


    def find_path(self,key): #경로찾기
        cur_node=self.root
        parents=[]

        while not cur_node.is_leaf:
            
            for i,item in enumerate(cur_node.keys):
                if key<item:
                    index=i
                    break
                elif key==item:
                    index=i+1
                    break
                elif i == len(cur_node.keys)-1: #data가 key보다 1개 더 많으므로
                    index=i+1
           
            parents.append((cur_node,index))
            cur_node=cur_node.data[index]

        
        index=bisect.bisect_left(cur_node.keys,key)


        parents.append((cur_node,index))
        return parents #앞에서부터 차례대로 부모와 인덱스정보가 들어있음


    def insert(self,key,data):
        parents=self.find_path(key)
        node,index = parents.pop()
        node.insert(index, key,data,parents)


    def delete(self,key):
        parents=self.find_path(key)
        node,index=parents.pop()
        if node.keys[index]!=key:
            return
        node.delete(index,parents)


    def single_search(self,key):
        parents = self.find_path(key)
        
        Size=len(parents)
        i=0
        check_node,check_index=parents.pop()
        if(check_node.keys==[]  or check_index>=len(check_node.keys) or check_node.keys[check_index]!=key ): # empty 트리일때도 못찾음
            print("NOT FOUND\n")
            return

        while i<Size-1:
            cur=parents[i][0]
            print(cur.keys,"\n")
            i+=1        
        
        print(check_node.data[check_index],'\n')

    def range_search(self,key1,key2):
        parents=self.find_path(key1)

        check_node,check_index=parents[-1]
        i=check_index
        cur=check_node
        while True:
            if cur.keys[i]>=key1:
                if cur.keys[i]> key2:
                    break
                elif cur.keys[i]<=key2:
                    print(cur.keys[i],cur.data[i])
                    i+=1
                    if i>=len(cur.keys):
                        if cur.next:
                            cur=cur.next
                            i=0
                        else:
                            break



#test
if __name__ == '__main__':    
    if sys.argv[1]=='-c':
        with open(sys.argv[2],'wb') as File:
            My_Tree=BplusTree(int(sys.argv[3])) # create tree with order argv[3]
            pickle.dump(My_Tree,File)

    elif sys.argv[1]=='-i':
        with open(sys.argv[2],'rb') as File:
            My_Tree=pickle.load(File)
        with open(sys.argv[2],'wb') as File:
            with open(sys.argv[3],'r') as Insert_File:
                lines=csv.reader(Insert_File,delimiter=',')
                for line in lines:
                    My_Tree.insert(int(line[0]),int(line[1]))
                pickle.dump(My_Tree,File)
    
    elif sys.argv[1]=='-d':
        with open(sys.argv[2],'rb') as File:
            My_Tree=pickle.load(File)
        with open(sys.argv[2],'wb') as File:
            with open(sys.argv[3],'r') as Delete_File:
                lines=csv.reader(Delete_File,delimiter=',')
                for line in lines:
                    My_Tree.delete(int(line[0]))
                pickle.dump(My_Tree,File)
        

    elif sys.argv[1] =='-s':
        with open(sys.argv[2],'rb') as File:
            My_Tree=pickle.load(File)
            My_Tree.single_search(int(sys.argv[3]))
            
    elif sys.argv[1] =='-r':
        with open(sys.argv[2],'rb') as File:
            My_Tree=pickle.load(File)
            My_Tree.range_search(int(sys.argv[3]),int(sys.argv[4]))

    elif sys.argv[1] =='-check':
        with open(sys.argv[2],'rb') as File:
            My_Tree=pickle.load(File)   
        cur=My_Tree.root
        while True:
            leftmost=cur.data[0]
            while cur.next:
                print(cur.keys,end='     ')
                cur=cur.next
            print(cur.keys)
            if cur.is_leaf==True:
                break
            cur=leftmost            
                