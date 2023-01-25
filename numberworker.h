#ifndef NUMBERWORKER_H
#define NUMBERWORKER_H

#include <QObject>

static const std::uint8_t cZero(0);

class NumberWorker : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief NumberWorker класс, работающий с цифрами на форме, кроме рандомно генерируемых цифр классом RandomNumGen
    ///
    NumberWorker();
    ///
    /// \brief SetCountersZero ф-ция обнуления счетчиков
    /// \param number передаваемое число
    ///
    void SetCountersZero();
    ///
    /// \brief SetGoalScore обновляет m_goal_score и обнуляет счетчик кликов
    ///
    void SetGoalScore(int32_t number);
    ///
    /// \brief ClickChecker срабатывает на каждый клик левой кнопки мыши, увеличивает m_counter_click
    ///
    void ClickIter();
    ///
    /// \brief GetCounterWin геттер переменной m_counter_win
    /// \return
    ///
    int32_t GetCounterWin();
    ///
    /// \brief GetCounterLose геттер переменной m_counter_lose
    /// \return
    ///
    int32_t GetCounterLose();
    ///
    /// \brief IsGoalClicked ф-ция сравнивает кол-во сделанных кликов с целью(кол-во нужных кликов для победы)
    ///
    void IsGoalClicked();
signals:
    Q_SIGNAL void clickCounterUpdate(uint16_t counter);
private:
    std::int32_t m_counter_win,
                 m_counter_lose,
                 m_goal_score,
                 m_counter_click;
};

#endif // NUMBERWORKER_H
