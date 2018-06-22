#include "program.h"

Program::Program(QWidget *parent) : Console(parent)
{
//    connect(this, SIGNAL(onEnterPressing(QString)), this, SLOT(OnEnter(QString)));

    this->setShowTime(true);

    this->write("Hello world!");


}

//void Program::OnEnter(QString userText)
//{
//    qDebug() << "OnEnter";
//}
