#ifndef PROGRAM_H
#define PROGRAM_H

#include "console.h"

#include <QObject>

class Program : public Console
{
    Q_OBJECT
public:
    explicit Program(QWidget *parent = nullptr);
private:


private slots:
//    void OnEnter(QString userText);
};

#endif // PROGRAM_H
