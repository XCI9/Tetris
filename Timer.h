#pragma once

#include <QTimer>

class Timer : public QTimer {
    int m_interval;
    bool m_isBeforePause;
    QMetaObject::Connection m_connect;

public:
    Timer(QObject *parent = nullptr)
      : QTimer{ parent }
      , m_interval{ 0 }
      , m_isBeforePause{ false }
    {}

    void pause(){
        //save original interval
        if(!m_isBeforePause)
            m_interval = interval();
        else
            QObject::disconnect(m_connect);

        //set current remain time as next interval
        auto remainTime{ remainingTime() };
        stop();
        setInterval(remainTime);
        setSingleShot(true);

        //after run out last remain time, reset to original interval
        m_connect = QObject::connect(this, &QTimer::timeout, this ,
                                     [&]{setInterval(m_interval);
                                         setSingleShot(false);
                                         QObject::disconnect(m_connect);
                                         m_isBeforePause = false;
                                         start();});
        m_isBeforePause = true;
    }

    void resume() {
        start();
    }
};
