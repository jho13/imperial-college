OBJ = ChessMain.o ChessBoard.o ChessPiece.o King.o Queen.o Rook.o Knight.o Bishop.o Pawn.o path.o enum.o
EXE = chess
CXX = g++
CXXFLAGS = -Wall -g -MMD

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)

.PHONY: clean
