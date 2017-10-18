/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);

//FUNCTION WHICH FINDS THE COORDINATES OF THE MARKER CHARACTER "ch"
//IN THE 2D ARRAY "maze" OF DIMENSION "height" x "width". "row" AND
//"column" ARE SET TO THE COORDIATES OF THE MARKER, AND FUNCTION
//RETURNS TRUE IF "ch" EXISTS. OTHERWISE "row" AND "column" ARE SET
//TO -1 AND FUNCTION RETURNS FALSE.
bool find_marker(const char ch, char** maze, const int height,
		 const int width, int& row, int& column);

//FUNCTION WHICH DETERMINES IF A GIVEN PATH "path" THROUGH A
//"height" x "width" MAZE "maze" LEADS FROM THE ENTRANCE MARKER '<'
//TO THE EXIT MARKER "X" WITHOUT MOVING OUTSIDE THE BOUNDARIES OF THE
//MAZE OR PASSING THROUGH A HEDGE.
bool valid_solution(const char* path, char** maze, int height,
		    int width);

//FUNCTION WHICH FINDS A VALID SOLUTION PATH THROUGH A MAZE "maze"
//OF DIMENSION "height" x "width", BEGINNING AT THE MARKER "start"
//AND FINISHING AT THE MARKER "end". THE PATH IS RETURNED AND IT IS
//MARKED ON THE "maze". IF THERE IS NO PATH, FUNCTION RETURNS
//"no solution".
char* find_path(char** maze, int height, int width,
		const char start, const char end);
