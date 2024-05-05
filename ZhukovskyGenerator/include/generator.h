#pragma once

#include "profile.h"

class ZhukovskyGenerator {
    value_type x0, y0;
    
public:
    ZhukovskyGenerator(value_type newX0, value_type newY0) {
        x0 = newX0;
        y0 = newY0;
    }

    Profile generateProfile(segment_number_type numberOfSegments);
};