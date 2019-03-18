#!/usr/bin/env python3

import rospy
from sudoku_pkg2.srv import service_file1

def sudoku_server_fun():
    rospy.wait_for_service('sudoku_server')
    sudoku_server=rospy.ServiceProxy('sudoku_server', service_file1 )
    a=sudoku_server(l)
    return(a)


l=[]
rospy.init_node("client_node")
for i in range(81):
    l.append(0)
l=sudoku_server_fun()