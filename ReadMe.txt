========================================================================
    STATIC LIBRARY : Skyfire Project Overview
========================================================================

To Use:
#include "skyfire.h"

Universe:
-Update Thread
	-Updates all Regions and Objects within Universe
-Camera
	-Scene object that draws objects in Camera "view" within ActiveRegion
-Region
	-Set of Objects that interact with each other
	-Object
		-Location
		-Direction
		-Shape

Window:
-Event Thread
	-Input object updated with user input
-Render Thread
	-Renders all active scenes
