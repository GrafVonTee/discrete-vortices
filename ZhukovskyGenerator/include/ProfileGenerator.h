#pragma once

#include "Profile.h"

class ProfileGenerator {
    value_type m_x0, m_y0;
    
public:
    ProfileGenerator(value_type x0, value_type y0) {
        m_x0 = x0;
        m_y0 = y0;
    }

    Profile generateProfile(segment_number_type numberOfSegments = 1000);
};