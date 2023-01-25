#include "randomnumgen.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

RandomNumGen::RandomNumGen()
{

}

int RandomNumGen::RandomInt(uint32_t min, uint32_t max)
{
      // Установить генератор случайных чисел
      srand(time(NULL));

      // Получить случайное число - формула
      uint32_t num = min + rand() % (max - min + 1);

      return num;
}
