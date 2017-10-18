#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(const char ch, char** maze, const int height,
		 const int width, int& row, int& column)
{
  for (int r = 0; r < height; r++) //rows
  {
    for (int c = 0; c < width; c++) //columns
    {
      if (maze[r][c] == ch)
      {
	row = r; column = c;
	return true;
      }
    }
  }
  row = -1; column = -1;
  return false;
}

//helper function
bool valid_position(int r, int c, int height, int width)
{
  return (r >= 0 && r < height && c >= 0 && c < width);
}

void make_move(char direction, int& r, int& c)
{
  if (direction == 'N')
    r--;
  else if (direction == 'S')
    r++;
  else if (direction == 'W')
    c--;
  else //direction == 'E'
    c++;
}

bool valid_solution(const char* path, char** maze, int height,
		    int width)
{
  int r,c;
  find_marker('>', maze, height, width, r, c);

  for (unsigned int i = 0; i < strlen(path); i++)
  {
    make_move(path[i], r, c);
   
    //check inside boundaries
    if (!valid_position(r, c, height, width))
      return false;

    //check not passing through hedge
    if (maze[r][c] == '+' || maze[r][c] == '-' || maze[r][c] == '|')
      return false;
  }
  
  //reached 'X'?
  if (maze[r][c] != 'X')
    return false;

  return true;
}

//helper function
//valid to go in "direction" from (r,c)?
bool valid_move(char** maze, int height, int width, char direction,
		int r, int c)
{
  make_move(direction, r, c);
   
  //check inside boundaries
  if (!valid_position(r, c, height, width))
    return false;

  //check not passing through hedge
  if (maze[r][c] == '+' || maze[r][c] == '-' || maze[r][c] == '|'
      || maze[r][c] == '#')
    return false;

  return true;
}

//helper function
bool search_path(char** maze, int height, int width, int r, int c,
	     const char end, char* path)
{
  //reached the end
  if (maze[r][c] == end)
  {
    maze[r][c] = '#';
    return true;
  }
  
  maze[r][c] = '#';
  
  //see if moving N S W E is possible
  if (valid_move(maze, height, width, 'N', r, c))
  {
    make_move('N',r,c);
    strcat(path, "N");
    if (search_path(maze, height, width, r, c, end, path))
      return true;
    r++;
  }
  if (valid_move(maze, height, width, 'S', r, c))
  {
    make_move('S',r,c);
    strcat(path, "S");
    if (search_path(maze, height, width, r, c, end, path))
      return true;
    r--;
  }
  if (valid_move(maze, height, width, 'W', r, c))
  {
    make_move('W',r,c);
    strcat(path, "W");
    if (search_path(maze, height, width, r, c, end, path))
      return true;
    c++;
  }
  if (valid_move(maze, height, width, 'E', r, c))
  {
    make_move('E',r,c);
    strcat(path, "E");
    if (search_path(maze, height, width, r, c, end, path))
      return true;
    c--;
  }
  
  //nowhere to go
  path[strlen(path)-1] = '\0';
  maze[r][c] = ' ';
  return false;
}

char* find_path(char** maze, int height, int width,
		const char start, const char end)
{
  char* path; int MAX_LENGTH = height * width;
  path = new char[MAX_LENGTH]; 
  strcpy(path, "");

  int r,c;
  find_marker(start, maze, height, width, r, c);
  
  if (search_path(maze, height, width, r, c, end, path))
    return path;
  else
  {
    strcpy(path, "no solution");
    return path;
  }
}
