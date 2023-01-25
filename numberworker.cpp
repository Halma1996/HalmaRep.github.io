#include "numberworker.h"

NumberWorker::NumberWorker() : //иницилизация
    m_counter_win(0),
    m_counter_lose(0),
    m_goal_score(0),
    m_counter_click(0)
{
}

void NumberWorker::SetCountersZero()
{
    m_counter_win = cZero; //нулим переменную (счетчик побед)
    m_counter_lose = cZero; //нулим переменную (счетчик поражений)
}

void NumberWorker::SetGoalScore(int32_t number)
{
    m_goal_score = number; // запомнимаем значение "Цели"
    m_counter_click = cZero; // обнуляем переменную (счетчик кликов)
}

void NumberWorker::ClickIter()
{
    m_counter_click++;
    emit clickCounterUpdate(m_counter_click); // эмитим сигнал (который передааст значение m_counter_click) в класс MainWindow
}

int32_t NumberWorker::GetCounterWin()
{
    return m_counter_win;
}

int32_t NumberWorker::GetCounterLose()
{
    return m_counter_lose;
}

void NumberWorker::IsGoalClicked()
{
    if (m_counter_click == m_goal_score) // если кол-во кликов равно нужному кол-ву для победы
        m_counter_win++; // увеличиваем счетчик побед
    else
        m_counter_lose++; // увеличиваем счетчик поражений
}
