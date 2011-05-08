========================================================================
    STATIC LIBRARY : Skyfire Project Overview
========================================================================

To Use:
#include "skyfire.h"

Universe:
-Update Thread
	-Updates all Regions and Objects within Universe (60x per second)
-Camera
	-Scene object that draws objects in Camera "view" within ActiveRegion
-Region
	-Set of Objects that interact with each other
	-Object
		-Location
		-Direction
		-Shape

Window:
-Render Thread
	-Renders all active scenes (60x per second) + gets user input

TODO:
-Collision Detection
    --Finish AABB
    --Add sphere
    --Add fine grained detection
    --Add cache system (first AABB, then more accurate)
-Speed up .obj loading
-Fix jpeg loading
-Add .3ds model loading
-Seperate Cameras
    --Make Camera a base class
    --Add FPS Camera
    --Add third person Camera
-Seperate Vector out into Vector + Vector3 classes