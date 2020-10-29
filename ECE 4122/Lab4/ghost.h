//#include <utility>
#include "players.h"

class Ghost : public players {

private:

public:
	// general ghost info:
	int index;
	bool frightened;
	bool chase;
	bool scatter;
	Ghost(float r, float g, float b, int x, int y, float z);

	// scattering functionality:
	int scatterTileX;
	int scatterTileY;

	// targeting functionality:
	int targetTileX;
	int targetTileY;
	int TargetPythagoras(int agle); 

	//  visual appearance:
	float r;
	float g;
	float b;
	void Draw(float phi); // unique ghost look

	// map location and inference mechanisms:	
	void onTileChange() override;
	void onTileCenter() override;
	bool WallForCheck(int angle);
	

};
