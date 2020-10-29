#ifndef GAMEBOARD_H
#define GAMEBOARD_H

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Pacman.rc
//
#define ID_1                            103
#define IDB_BITMAP1                     104
#define ID_2                            104

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        105
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

class board {

public:
	// general map information:
	static const int DIM_X = 30;
	static const int DIM_Y = 15;
	static const int CENTER_X = DIM_X / 2;
	static const int CENTER_Y = (DIM_Y + 1) / 2;
	static const int CENTER_Z = 0;

	int coinsCount;

	// static map references:
	static int initial_map[DIM_Y][DIM_X];
	static bool isWall(int x, int y);

	void GameBoard();

	// map visual appearance:
	void Draw();
	void DrawWall(int x, int y, int z);
	void DrawWalls(int j, int i);

	void TextureLoad(int id);
};

#endif