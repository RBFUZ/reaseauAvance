#fat topology file.
#Value of k = 4
#Total number of hosts = 16
Number of hosts under each switch = 2
#############################################################################
Hca		1		"Node(0)"
[1]  "Edge(0 0 1)"[2]
Hca		1		"Node(1)"
[1]  "Edge(0 0 1)"[4]
Hca		1		"Node(2)"
[1]  "Edge(0 1 1)"[2]
Hca		1		"Node(3)"
[1]  "Edge(0 1 1)"[4]
Hca		1		"Node(4)"
[1]  "Edge(1 0 1)"[2]
Hca		1		"Node(5)"
[1]  "Edge(1 0 1)"[4]
Hca		1		"Node(6)"
[1]  "Edge(1 1 1)"[2]
Hca		1		"Node(7)"
[1]  "Edge(1 1 1)"[4]
Hca		1		"Node(8)"
[1]  "Edge(2 0 1)"[2]
Hca		1		"Node(9)"
[1]  "Edge(2 0 1)"[4]
Hca		1		"Node(10)"
[1]  "Edge(2 1 1)"[2]
Hca		1		"Node(11)"
[1]  "Edge(2 1 1)"[4]
Hca		1		"Node(12)"
[1]  "Edge(3 0 1)"[2]
Hca		1		"Node(13)"
[1]  "Edge(3 0 1)"[4]
Hca		1		"Node(14)"
[1]  "Edge(3 1 1)"[2]
Hca		1		"Node(15)"
[1]  "Edge(3 1 1)"[4]


Switch		4		"Edge(0 0 1)"
Switch		4		"Edge(0 1 1)"
Switch		4		"Edge(1 0 1)"
Switch		4		"Edge(1 1 1)"
Switch		4		"Edge(2 0 1)"
Switch		4		"Edge(2 1 1)"
Switch		4		"Edge(3 0 1)"
Switch		4		"Edge(3 1 1)"
