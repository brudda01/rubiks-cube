cmake_minimum_required(VERSION 3.28)
project(rubiks_cube)

set(CMAKE_CXX_STANDARD 17)

add_executable(rubiks_cube main.cpp
        models/generic_cube.cpp
        models/generic_cube.h
        models/1Dmodel.cpp
        models/3Dmodel.cpp
        models/bitsModel.cpp
        bfs_solver.h
        dfs_solver.h
        iddfs_solver.h
        idastar_solver.h
        patternDB/reqmath.cpp
        patternDB/reqmath.h
        patternDB/perm_indexer.h
        patternDB/nibble_array.cpp
        patternDB/nibble_array.h
        patternDB/patternDBstructure.cpp
        patternDB/patternDBstructure.h
        patternDB/corner_patternDB.cpp
        patternDB/corner_patternDB.h
        patternDB/corner_patternDB_maker.cpp
        patternDB/corner_patternDB_maker.h
)
