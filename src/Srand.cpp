#include "Srand.hpp"



void Srand::SetTimeSeed() {
  srand(time(NULL));
}

int Srand::GetInt(int from, int to) {
  if (to < from)
    return rand() % RAND_MAX;
  
  int range = to - from;
  int result = rand() % (range + 1) + from;
  return result;
}
