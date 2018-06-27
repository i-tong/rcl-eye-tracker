#ifndef UTIL_H
#define UTIL_H
#define BOOST_UBLAS_NDEBUG 1

#include <boost/math/constants/constants.hpp>
#include <stdio.h>
enum eyeSide {
    RIGHT_EYE,
    LEFT_EYE,
    BOTH_EYES
};

enum calibType {
  CALIB_2D,
  CALIB_3D
};

const float pi = boost::math::constants::pi<float>();

#endif

