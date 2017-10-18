/* 

The required predicates and argument positions are:
a.	lines(+Station, ?Lines)
b.	disjointed_lines(-Lines)
c.	direct(+S1, +S2, ?Line, ?Route)
d.	changes(?C, +PR)
e.	noReps(+PR)
f.	jp(+S1, +S2, -PR)   --- optional

*/

/* useful predicates on lists that are used below */

%  rev(+L1, -L2) means L2 is the list L1 reversed.
rev(L, R) :-
	tr_rev(L, [], R).
tr_rev([], R, R).
tr_rev([H|T], Acc, R) :-
	tr_rev(T, [H|Acc], R).

%  L1 is a list of 2-tuples, then L2 is the list L1 with repeats removed,
%  where (X1,X2) and (X2,X1) occuring in L1 counts as a repeat as well.
remove_repeats([], []).
remove_repeats([(X1,X2)|T], L) :- 
	remove_repeats(T, L1),
	((member((X1,X2), L1) ; member((X2,X1), L1)) -> 
	  L = L1 ; append([(X1,X2)], L1, L)).

%  start_list_end(S,L,E) means the list L starts with S and ends with E. 
start_list_end(S,[S|T],E) :- append(_,[E],T).

%  disjointed_list(L1, L2) means L1 and L2 hve no elements in common.
disjointed_list([], L2).
disjointed_list([H|T], L2) :-
	\+member(H, L2),
	disjointed_list(T, L2).


/****************** Question a) *******************/

%	 line_station(Line, Station) means Line goes through Station.
line_station(Line, Station) :- 
	route(Line, LS), 
	member(Station, LS).

%  Lines is the list of all lines that go through Station.
%  If no such lines exists, Lines = [].
lines(Station, Lines) :- 
	(line_station(_, Station) -> 
		setof(Line, line_station(Line, Station), Lines) ; Lines = []).


/****************** Question b) *******************/
	     
%  disjointed_lines(Line1,Line2) means Line1 and Line 2
%  have no stations in common.
disjointed_lines(Line1, Line2) :-
	route(Line1, LS1), 
	route(Line2, LS2),
	disjointed_list(LS1, LS2).

%  identify paris of disjointed lines and remove repeats.	     
disjointed_lines(Lines) :- 
	setof((Line1, Line2), disjointed_lines(Line1, Line2), L), 
	remove_repeats(L, Lines).
 

/****************** Question c) *******************/

%  look for LS of the form LS = [...,S1,...,S2,...],
%  Route = [S1,...,S2].
direct(S1, S2, Line, Route) :-
	route(Line, LS),
	append(L1, [S2|_], LS),
	append(_, [S1|Middle], L1),
	append([S1|Middle], [S2], Route).

%  look for LS of the from LS = [...,S2,...,S1,...],
%  Route = reverse of [S2,...,S1]. 
direct(S1, S2, Line, Route) :-
	route(Line, LS),
	append(L1, [S1|_], LS),
	append(_, [S2|Middle], L1),
	append([S2|Middle], [S1], RevRoute),
	rev(RevRoute, Route).
	  

/****************** Question d) *******************/

%  base case: PR is a singleton, then C = [].
%  recursive case: PR = [H1,H2|T], list of changes for [H2|T] is C1.
%    append [(X,Y,S)] to C1 if H1 = (X,_), H2 = (Y,[S|_]) and X \= Y.
changes([], [_]).
changes(C, [H1,H2|T]) :- 
	changes(C1, [H2|T]),
	((H1 = (X,_), H2 = (Y,[S|_]), X\=Y) -> append([(X,Y,S)], C1, C) ; C = C1).
					
   
/****************** Question e) *******************/

%  noReps(PR): if PR = [(X,_)|T] check (X,_) is not a member of T, 
%  and call noReps(T).
noReps([]).
noReps([(X,_)|T]) :- \+member((X,_), T), noReps(T).


/****************** Question f) *******************/

jp(S1, S2, [(X,L)]) :- 
	route(X, L1), 
	append(_, L2, L1),
	append(L, _, L2),
	start_list_end(S1, L, S2).
	    
jp(S1, S2, [(X,L)|PR]) :- 
	route(X, L1),
	append(_, L2, L1),
	append(L, _, L2),
	start_list_end(S1 ,L, S3),
	jp(S3, S2, PR),
	noReps([(X,L)|PR]).



