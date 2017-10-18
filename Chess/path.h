#include <string>
#include <map>

using namespace std;

// "from" AND "to" REPRESENT SQUARES ON A CHESSBOARD.
//PATH MEANS THE PATH "from" -> "to"

//FUNCTION WHICH RETURNS 'true' IFF "from" AND "to" are the same.
bool same(const string& from, const string& to);

//FUNCTION WHICH RETURNS 'true' IFF THE PATH
//IS VERTICAL OR HORIZONTAL.
bool str_path(const string& from, const string& to);

//FUNCTION WHICH RETURNS 'true' IFF THE PATH
//IS DIAGONAL.
bool diag_path(const string& from, const string& to);

//FUNCTION WHICH RETURNS 'true' IFF THE PATH
//IS AN "L" SHAPE.
bool l_path(const string& from, const string& to);

//FUNCTION WHICH RETURNS 'true' IFF "from" AND "to"
//ARE ADJACENT (INCLUDES DIAGONALLY ADJACENT AND "from" == "to").
bool adj(const string& from, const string& to);
