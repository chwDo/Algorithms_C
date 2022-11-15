cmake_minimum_required(VERSION 3.15)
project(9024_C_project C)

set(CMAKE_C_STANDARD 99)

add_executable(9024_C_project palindrome.c
        Stack.c Stack.h
        IntStack.c IntStack.h
        IntQueue.c IntQueue.h
        llsplit.c
        graphAndConnectedComponent.c
        GraphWithCC.c GraphWithCC.h
        Graph.c Graph.h
        popularityRank.c
        adjacentRepresentationGraph.c adjacentRepresentationGraph.h
        list.c list.h
        WGraph.c WGraph.h
        goNSW.c
        queue.c queue.h
        BST.c BST.h)
add_executable(test2 RBTree.c RBTree.h list.c list.h)
add_executable(week9 rootFinding.c)
add_executable(dijkstra dijkstra.c  PQueue.c PQueue.h  WGraph.c WGraph.h)