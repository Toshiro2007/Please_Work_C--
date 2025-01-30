#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.hpp"



// path file name is "example.txt".
// "." is replaced with "_" to overcome c++ limitations
ASSET(path1_txt);
ASSET(example2_txt)

void autonomous() {
    // set chassis pose
    chassis.setPose(0, 0, 0);
    // lookahead distance: 15 inches
    // timeout: 2000 ms
    chassis.follow(path1_txt, 15, 2000, false);
    
};






