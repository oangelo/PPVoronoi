/*
* The author of this software is Shane O'Sullivan.  
* Permission to use, copy, modify, and distribute this software for any
* purpose without fee is hereby granted, provided that this entire notice
* is included in all copies of any software which is or includes a copy
* or modification of this software and in all copies of the supporting
* documentation for such software.
* THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
* WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR AT&T MAKE ANY
* REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
* OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
*/

#include <string>
#include <algorithm>

#include <stdio.h>
#include <search.h>
#include <malloc.h>

#include "VoronoiDiagramGenerator.h"
#include "SysUtilsPlus/utils.h"


int main(int argc,char **argv) 
{	

    auto data = ReadFile<double>(std::string(argv[1]));

	float xValues[data.size()];
	float yValues[data.size()];
    for(size_t i = 0; i < data.size(); ++i){
        xValues[i] = data[i][0];
        yValues[i] = data[i][1];
    }
	long count = data.size();

    float max_x = *std::max_element(xValues, xValues + count);
    float max_y = *std::max_element(yValues, yValues + count);
    float min_x = *std::min_element(xValues, xValues + count);
    float min_y = *std::min_element(yValues, yValues + count);

	VoronoiDiagramGenerator vdg;
	vdg.generateVoronoi(xValues,yValues,count, min_x, max_x, min_y, max_y, 0);

	vdg.resetIterator();

	float x1,y1,x2,y2;

	while(vdg.getNext(x1,y1,x2,y2))
	{
		printf("%f %f \n",x1,y1);
		printf("%f %f \n",x2, y2);
		printf("\n");
	}

	return 0;

	
}



