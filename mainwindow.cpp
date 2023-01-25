#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) //иницилизация
    : QMainWindow(parent),
      m_p_Timer(new QTimer),
      m_p_NumberWorker(new NumberWorker),
      m_not_first_try(false),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_p_Timer->setInterval(cTwoSec);
    this->setStyleSheet(QString("font-size: %1px").arg(32));//!!!!!!!!TO DO для всех, только по-нормальному

    ConnectorSignalSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectorSignalSlot()
{
    //start
    connect(ui->Butt_Start,&QPushButton::clicked,this,&MainWindow::StartStopTimer); //коннектим кнопку Butt_Start к функции StartStopTimer
    connect(ui->Butt_Start,&QPushButton::clicked,this,&MainWindow::EnableDisableButt); //коннектим кнопку Butt_Start к функции EnableDisabeButt
    //stop
    connect(ui->Butt_Stop,&QPushButton::clicked,this,&MainWindow::StartStopTimer); //коннектим кнопку Butt_Stop к функции StartStopTimer
    connect(ui->Butt_Stop,&QPushButton::clicked,this,&MainWindow::EnableDisableButt); //коннектим кнопку Butt_Stop к функции EnableDisabeButt
    //timer
    connect(m_p_Timer.data(),&QTimer::timeout,this,&MainWindow::RefreshNumbers); //коннектим сигнал таймаута к ф-ции RefreshNumbers
    //m_p_NumberWorker
    connect(m_p_NumberWorker.data(),&NumberWorker::clickCounterUpdate,this,&MainWindow::SetClickDone); // коннектим сигнал clickCounterUpdate класса NumberWorker к ф-ции SetClickDone
}

void MainWindow::StartGame()
{
    ui->Label_GoalScore->setText(QString(cPurpose).arg(cDash)); // Ставим начальные значения лейблам
    ui->Label_WinScore->setText(QString(cWin).arg(cDash));
    ui->Label_LoseScore->setText(QString(cLose).arg(cDash));
    ui->Label_ClickDone->setText(QString(cClickDone).arg(cDash));

    m_p_NumberWorker.data()->SetCountersZero(); //Вызываем ф-цию SetCountersZero(обнуляет значения переменных) класса NumberWorker

    m_p_Timer->start(); //запускаем таймер
    m_not_first_try = false; // присваиваем значение переменной false, чтобы знать что идет 1ая проходка
}

void MainWindow::StopGame()
{
    m_p_Timer->stop(); //стопаем таймер
    ui->Label_GoalScore->setText(QString(cPurpose).arg(cDash)); // Устанавливаем значение "-" лейблу GoalScore
}

void MainWindow::EnableDisableButt()
{
    bool ButtState(true); // иницилизируем переменную
    QObject::sender() == ui->Butt_Start ? ButtState = false : ButtState = true; /* в зависимости от того, от какой кнопки
                                                                                вызвалась данная функция, выставляем значение переменной ButtState/ отдельно от ф-ции Start/StopTimer
                                                                                для удобства и меньше кода xD*/

    ui->Butt_Start->setEnabled(ButtState); // делаем активной/неактивной кнопку, в зависимости от того кто вызвал ф-цию
    ui->Butt_Stop->setEnabled(!ButtState); // делаем активной/неактивной кнопку, в зависимости от того кто вызвал ф-цию
}

void MainWindow::StartStopTimer()
{
    QObject::sender() == ui->Butt_Start ? StartGame() : StopGame(); //В зависимости от того кто вызвал ф-цию начинаем или заканчиваем игру
}

void MainWindow::RefreshNumbers()
{
    if (m_not_first_try) //Если не первая проходка (проверка нужна чтобы при первом обновлении не засчитывалась победа/поражение)
    {
        m_p_NumberWorker.data()->IsGoalClicked(); // Запускаем проверку "набрал ли игрок нужное кол-во кликов"
        ui->Label_WinScore->setText(QString(cWin.arg(m_p_NumberWorker.data()->GetCounterWin()))); //гетаем значение в лейбл WinScore
        ui->Label_LoseScore->setText(QString(cLose.arg(m_p_NumberWorker.data()->GetCounterLose()))); //гетаем значение в лейбл LoseScore
        ui->Label_ClickDone->setText(QString(cClickDone).arg(cZero)); // обнуляем значение сделанных кликов
    }
    else
    {
        m_not_first_try = true; // меняем значения флага, после первого обновления
        ui->Label_ClickDone->setText(QString(cClickDone).arg(cZero)); // обнуляем значение сделанных кликов
    }

    int32_t newNumber= m_p_RandomNumGen.RandomInt(cMinNumber,cMaxNumber); // переменная чтобы сгенерированное число было одинаковое для поля Цели и для аргумента в ф-ции SetGoalScore
    ui->Label_GoalScore->setText(QString(cPurpose).arg(newNumber)); // сетаем сгенерированное значение на лейбл GoalScore
    Blinking(); // вызываем ф-цию моргания
    m_p_NumberWorker.data()->SetGoalScore(newNumber); //вызываем ф-цию SetGoalScore класса NumberWorker
}

void MainWindow::Blinking()
{
    ui->Label_GoalScore->setStyleSheet("QLabel { color : green; }"); //красим лейбл GoalScore в зеленый, для очевидного смены числа
    QTimer::singleShot(cOneSec, this, &MainWindow::SetNormalColor); // вызываем ф-цию смены цвета на стандартный через небольшую задержку
}

void MainWindow::SetNormalColor()
{
    ui->Label_GoalScore->setStyleSheet("QLabel { color : black; }"); // красим лейбл GoalScore в черный цвет
}

void MainWindow::SetClickDone(uint16_t num)
{
    ui->Label_ClickDone->setText(QString(cClickDone).arg(num)); //ф-ция выставляет в лейбл ClickDone новое значение
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton ) // если нажали левой кнопкой мыши внутри окна приложения
        m_p_NumberWorker.data()->ClickIter(); // вызываем ф-цию ClickIter класса NumberWorker
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore(); //игнориуем событие (в данной случае закрытие приложения)
    QMessageBox msgBox;
    msgBox.setWindowTitle("Пока!");
    msgBox.setText("Приходите еще");
    msgBox.setButtonText(QMessageBox::Ok,"Обязательно приду");
    bool isPressed = msgBox.exec(); // переменная для отслеживания "нажата ли кнопка"
    if (isPressed)
        event->accept(); //выполняем событие (в данном случае закрытие приложения)
}
