#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include "randomnumgen.h"
#include "numberworker.h"

static const std::uint16_t cTwoSec(2000),
                           cOneSec(1000),
                           cMinNumber(1),
                           cMaxNumber(11);

static const QString cPurpose("Цель:%1"),
                     cWin("Побед:%1"),
                     cLose("Поражений:%1"),
                     cClickDone("Сделано кликов:%1"),
                     cDash("-"),
                     cNewGoal("НОВАЯ ЦЕЛЬ!");

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ///
    /// \brief ConnectorSignalSlot ф-ция коннекта сигнал слотов (вынесена отдельно из конструктора для удобства)
    ///
    void ConnectorSignalSlot();
    ///
    /// \brief StartGame ф-ция вызывает другие методы, необходимые для старта игры
    ///
    void StartGame();
    ///
    /// \brief StopGame ф-ция вызывает другие методы, необходимые для остановки игрры игры
    ///
    void StopGame();
    ///
    /// \brief EnableDisableButt ф-ция делает активной или неактивной кнопку Butt_Start/Butt_Stop , в зависимости от того, кто ее вызвал
    ///
    void EnableDisableButt();
    ///
    /// \brief StartStopTimer ф-ция стартует или останавливает таймер, в зависимости от того, кто её вызвал
    ///
    void StartStopTimer();
    ///
    /// \brief RefrestNumbers обновляет цифры на форме
    ///
    void RefreshNumbers();
    ///
    /// \brief Blinking ф-ция морагния, чтоб было видно что цель обновилась
    ///
    void Blinking();
    ///
    /// \brief SetNormalColor красит в стандартный цвет Label_GoalScore
    ///
    void SetNormalColor();
    void SetClickDone(uint16_t num);
    ///
    /// \brief mousePressEvent ф-ция сообщающая классу NumberWorker о нажатии на левую кнопку мыши
    /// \param event
    ///
    void mousePressEvent(QMouseEvent* event) override;
    void closeEvent(QCloseEvent *event) override;

    const QScopedPointer<QTimer> m_p_Timer;
    const QScopedPointer<NumberWorker> m_p_NumberWorker;
    RandomNumGen m_p_RandomNumGen;
    ///
    /// \brief firstNumber переменная отвечает за первый проход (когда кол-во нужных кликов = 0)
    ///

    bool m_not_first_try;

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
