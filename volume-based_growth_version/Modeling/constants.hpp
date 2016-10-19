#ifndef __CONSTANTS__
#define __CONSTANTS__

const float MEDIAN_CELL_VOLUME= 0.4; //median cell volume at growth rate = 0, Bacsim reference
const float MINIMAL_CELL_VOLUME= 0.1; //Bacsim reference
const float VOLUME_AT_DIVISION= 0.5; //Bacsim reference (5 times the minimal cell volume)
const float INIT_DRY_MASS= 290; //Bacsim
const float INIT_VOLUME= 0.4; //Bacsim
const float umax = 0.0205; 
const float Ymax = 0.4444; 
const float Vmax = umax/Ymax;
const float Km = 2.34*pow(10,3);
const float m = 6*pow(10,-4);


#endif
