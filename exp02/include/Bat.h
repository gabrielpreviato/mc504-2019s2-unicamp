// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#ifndef EXP01_INCLUDE_BAT_H_
#define EXP01_INCLUDE_BAT_H_
#include <pthread.h>
#include <iostream>


class Bat {
 public:
    int bat_number;
    char bat_line;      // Possible values are {n, e, s, w}

    Bat(int bat_number, char bat_line);
};

#endif  // EXP01_INCLUDE_BAT_H_
