## Project 1 - Solving A Maze
## Student Information
Name: Jaime Yah-Perez 
Student ID: 008856387
git: https://github.com/JaimeYahPerez/CS315-Project1

## Collaboration and Resources
included libraries were done so out of expectation and assumption based on requirements and previous experience.

Struct Pos:
-The idea for this came from previous programming classes which also included data structures, which led to using previous works
for references, such as making a vertex class or usage of sets

loadFromFile():
-Significant research was done to fully remember proper implementation of file reading and writing with ifsream and ofstream with
w3schools and chatgpt to aid understanding of file streaming, and later for debugging of the function

print():
-simple and was written from experience

findEntrances():
-Idea to check only outer walls came from assumption that the maze would always have one entrance and exit on the outer layer, 
but also anywhere on the outer layer
-Implementation of that search came from prior experience with 2d vectors

inbounds():
-idea for this safety check as a helper function came during writing of neighbors(), and stemmed from a previous project involving
a chess board

neighbors():
-The idea of checking adjacencies through a table stemmed from two places, the lab we did practicing the backtracking algorithm,
and a previous programming project involving a game of chess, requring movements to be planned in classes
-output was based on the existence of the struct Pos object

solve():
-implementation is based on the algorithm we were shown in lab 3, this time utilzing the infrastructure that was setup
in prior steps based on the project 1 page
-The tracker for visited points comes from aid with chatgpt, specifically with its structure to avoid total reusage of the already 
present vector grid
-debugging and testing was done with the help of chatgpt

main()
-setup of main with its arguments and loadfromfile check was done with the aid of chatgpt as the use of argc and argv for terminal running 
is relatively new to me
- rest of the main setup was done based on my own experience


##Implementation Details
Struct Pos :
-This was made to provide easy access to a variable that stores info in the format of a coordinate (row, col), for later usage

Class Maze Private:
-2d vector named grid is made for storage of the given maze and maze solution
-R and C are used to record max length and width of the given maze
-Pos start and finish are used to record the coordinates of the entrance and exit of the maze


loadFromFile():
-reads the directly given file path and writes the maze into the 2d vector grid
-also records the max length and width of the maze into R and C
-also checks prior to writing the validity of the given file path

print():
-outputs the maze in grid row by row

findEntrance():
-prepares an output vector with Pos as its input variable,
-searches the left and right outer wall first for an entrance/exit of char '0'
-follows up with a check on the top and bottom wall
-outputs the first input into start, and the second into exit
-returns true for debugging

inbounds():
-checks if the current coordinate is within the bounds of the rectangular maze

neighbors():
-utilizes two tables that determines the movement check in order of up, right, down, and left, utilizng an integer to add/subtract from the current coordinate
-prepares a Pos vector to record available moves named moves
-runs through the table in reference to the currently given coordinate, and determines if the adjacent points are an open path
-if an open path '0' is available and within bounds, push it into vector moves
-return moves

solve():
-create a 2d vector named visited structured with chars as the input, and is made of the lengths R and C, and 0 as the default values
-the stack used for the backtracking algorithm is named search with the inputs being in the form of Pos
-since start is known, it is automatically pushed into search and the coordinate is marked onto visited
-bool found is used as a tracker if a solution is found

-the actual algorithm is structured similarly to what we were shown in class, with Pos curr being used to remember our current location and comparing it finish for the solution
-neighbors is used in every iteration of the algorithm to search for moves and is ran through in an internal for loop
-if no moves can be made a check with advanced is marked as false and backtracking is done

-the finishing stack of search is used for validation of a solution and for recording onto our grid

main()
grid is read and printed initially, then outputed once more if a solution is found

## Testing & status
So far with the three present mazes in the files, the current program correctly reads, navigates, and outputs a solution to the maze, if a solution is present.
In terms of debugging, outputs are only available if an incorrect filename is given, or if the maze is unsolvable. The maze class is written with a rectangular, two opening maze in mind




