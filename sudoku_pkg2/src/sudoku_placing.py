import rospy
from sudoku_pkg2.srv import service_file2


def sudoku_server_fun():
    rospy.init_node('server_node1')
    s=rospy.Service('sudoku_server', service_file2 ,handle_sudoku_algo2)
    print('ready to place accordingly')
    rospy.spin()

res_l=[[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0]]
sudoku_server_fun()