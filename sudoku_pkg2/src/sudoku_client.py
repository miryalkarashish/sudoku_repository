#!/usr/bin/env python3

import rospy
from sudoku_pkg2.srv import service_file1
from sudoku_pkg2.srv import service_file2

def sudoku_server_fun():
    rospy.wait_for_service('sudoku_server')
    sudoku_server=rospy.ServiceProxy('sudoku_server', service_file1 )
    a=sudoku_server(l)
    return(a.res)

def sudoku_placing_fun():
    s=l1
    rospy.wait_for_service('sudoku_placing_server')
    sudoku_server=rospy.ServiceProxy('sudoku_placing_server',service_file2)
    a=sudoku_server(l,s)
    return(a.res)


rospy.init_node("client_node")
l=[5,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
l1=sudoku_server_fun()
print(l1)
rospy.sleep(2)
l2=sudoku_placing_fun()
print(l2)