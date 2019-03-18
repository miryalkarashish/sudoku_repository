#!/usr/bin/env python3

import rospy
from sudoku_pkg2.srv import service_file1,service_file1Response

def returnarray():
    a=[0]*81
    for i in range(9):
        for j in range(9):
            a[i*9+j]=l[i][j]
    print(a)
    return service_file1Response(a)


def check(r,c,k):
    for i in range(9):
        if(l[i][c]==k or l[r][i]==k):
            return 0
        rr=(r//3)*3
        cc=(c//3)*3
    for i in range(rr,rr+3):
        for j in range(cc,cc+3):
            if(l[i][j]==k):
                return 0


def assign(i,j):
    if(l[i][j]!=0):
        if(i==8 and j==8):
            print(l)
            returnarray()
        if(j==8):
            return(assign(i+1,0))
        return(assign(i,j+1))
    k=1
    while(k<=9):
        if(check(i,j,k)==0):
            k+=1
            continue
        l[i][j]=k
        if(i==8 and j==8):
            print(l)
            returnarray()
        if(j==8):
            k+=assign(i+1,0)
            continue
        if(i<=8):
            k+=assign(i,j+1)
    l[i][j]=0
    return(1)


def handle_sudoku_algo(req):
    print(req.data)
    for i in range(9):
        for j in range(9):
            l[i][j]=req.data[i*9+j]
    r=assign(0,0)
    returnarray()



def sudoku_server_fun():
    rospy.init_node('server_node1')
    rospy.Service('sudoku_server', service_file1 ,handle_sudoku_algo)
    print("ready to solve puzzel")
    rospy.spin()

l=[[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0]]
sudoku_server_fun()