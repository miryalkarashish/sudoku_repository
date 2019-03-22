#!/usr/bin/env python3

import rospy
from sudoku_pkg2.srv import service_file2,service_file2Response

def handle_sudoku_algo2(req):
    l=req.l
    s=req.s
    for i in range(9):
        for j in range(9):
            if(l[i*9+j]==0):
                a=s[i*9+j]
                for k in range(9):
                    if(res_l[(a-1)*9+k]==0):
                        res_l[(a-1)*9+k] = i*9+j
                        break
    return service_file2Response(res_l)

def sudoku_server_fun():
    rospy.init_node('server_node2')
    s=rospy.Service('sudoku_placing_server', service_file2 ,handle_sudoku_algo2)
    print('ready to place accordingly')
    rospy.spin()

res_l=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
sudoku_server_fun()