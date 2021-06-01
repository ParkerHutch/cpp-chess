# Don't forget to change the project name on the below line
include_directories(${CPPChess_SOURCE_DIR}/include)

set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")



find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
# add all the source files so they are linked to library and header files
#add_executable(CPPong main.cpp movingshape.cpp ball.cpp paddle.cpp computerpaddle.cpp userpaddle.cpp) 
add_executable(CPPChess main.cpp piece.cpp tile.cpp)
#add_subdirectory(paddles)
target_link_libraries(CPPChess sfml-graphics sfml-audio)