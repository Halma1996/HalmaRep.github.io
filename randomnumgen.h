#ifndef RANDOMNUMGEM_H
#define RANDOMNUMGEM_H

#include <QObject>
///
/// \brief The RandomNumGem class класс, отвечающий за генерацию случайных чисел , пока что для 1 функции, но предусмотрен для потанециального расширения программы
///
class RandomNumGen
{
public:
    RandomNumGen();
    ///
    /// \brief RandomInt ф-ция генерирует случайно число типа "int" в заданном диапазоне
    /// \param min минимальное значение
    /// \param max максимальное значение
    /// \return
    ///
    int RandomInt(std::uint32_t min, std::uint32_t max);
};

#endif // RANDOMNUMGEM_H
