// Include our custom library
#include "PPM.h"

int main(){

    PPM myPPM("../textures/test2.ppm");
    myPPM.darken();
    myPPM.savePPM("../textures/test1_darken.ppm");

    return 0;
}
