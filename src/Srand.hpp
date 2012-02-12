#ifndef SRAND_HPP
#define SRAND_HPP

#include <stdlib.h>
#include <time.h>

class Srand {
public:
  static void SetSeed(int seed);
  static void SetTimeSeed();

  static int GetInt(int from, int to);  
};



#endif
