#include "console.h"

#define _1 qDebug() << "1";
#define _2 qDebug() << "2";
#define _3 qDebug() << "3";

Console::Console(QWidget *parent)
    : QPlainTextEdit(parent)
{    
    this->setWindowTitle("Console");
    this->resize(700, 400);

    this->setReadOnly(true);
}

Console::~Console()
{

}

void Console::write(QString text)
{
    QString Char = "";
    QString newLine;

    if(showTime){
        for(int i = 0; i < text.count(); i++){
            Char = text.at(i);

            if(Char == "\n"){
                if(textWithTime){
                    this->insertPlainText(newLine + "\n");
                }
                else{
                    this->insertPlainText("[" + QTime::currentTime().toString() + "]: " + newLine + "\n");
                    textWithTime = false;
                }

                newLine.clear();
                line.clear();
            }
            else{
                newLine += Char;
            }
        }



        if(textWithTime){
            this->insertPlainText(newLine);
        }
        else{
            this->insertPlainText("[" + QTime::currentTime().toString() + "]: " + newLine);
            textWithTime = true;
        }
    }

    else{
        for(int i = 0; i < text.count(); i++){
            Char = text.at(i);

            if(Char == "\n"){
                this->insertPlainText(newLine + "\n");
                newLine.clear();
                line.clear();
            }
            else{
                newLine += Char;
            }
        }

        this->insertPlainText(newLine);
        line += newLine;
    }
}

void Console::writeln(QString text)
{
    QString Char = "";
    QString newLine;

    if(showTime){
        if(text == ""){
            if(this->toPlainText().split(QChar('\n')).at(this->document()->lineCount() - 1) == ""){
                this->insertPlainText("[" + QTime::currentTime().toString() + "]: ");
                this->insertPlainText("\n");
                this->insertPlainText("[" + QTime::currentTime().toString() + "]: ");
                textWithTime = true;
            }
            else{
                this->insertPlainText("\n");
                this->insertPlainText("[" + QTime::currentTime().toString() + "]: ");
                textWithTime = true;
            }
        }
        else{
            for(int i = 0; i < text.count(); i++){
                Char = text.at(i);

                if(Char == "\n"){
                    if(textWithTime){
                        this->insertPlainText(newLine);
                    }
                    else{
                        this->insertPlainText("[" + QTime::currentTime().toString() + "]: " + newLine + "\n");
                        textWithTime = false;
                    }

                    newLine.clear();
                    line.clear();
                }
                else{
                    qDebug() << Char;
                    newLine += Char;
                }
            }

            qDebug() << textWithTime;

            if(textWithTime){
                this->insertPlainText(newLine + "\n");
                line += newLine;
            }
            else{
                this->insertPlainText("[" + QTime::currentTime().toString() + "]: " + newLine + "\n");
                line += "[" + QTime::currentTime().toString() + "]: " + newLine;

                textWithTime = false;
            }
        }
    }

    else{
        for(int i = 0; i < text.count(); i++){
            Char = text.at(i);

            if(Char == "\n"){
                this->insertPlainText(newLine + "\n");
                newLine.clear();
                line.clear();
            }
            else{
                newLine += Char;
            }
        }

        this->insertPlainText(newLine + "\n");
        line += newLine;

        textWithTime = false;
    }

    line.clear();
}

QString Console::read()
{

    return "";
}

void Console::setIntroduced(bool introducedBool)
{
    introduced = introducedBool;
    introduced ? (this->setReadOnly(false)) : (this->setReadOnly(true));
}

bool Console::getIntroduced()
{
    return introduced;
}

void Console::setShowTime(bool timeBool)
{
    showTime = timeBool;
}

bool Console::getShowTime()
{
    return showTime;
}

void Console::setNotChangableText(QString text)
{
    notChangableText = text;
    QString plainText = this->document()->toPlainText();
    this->clear();

    this->insertPlainText(notChangableText);
    this->insertPlainText(plainText);
}

void Console::clearNotChangableText()
{
    QString plainText = this->document()->toPlainText().mid(notChangableText.count());
    this->clear();
    this->insertPlainText(plainText);
    notChangableText.clear();
}

void Console::setSaveLogFile(bool SLF, QString path)
{
    saveLF = SLF;

    if(!saveLF == true){
        return;
    }
    else{

    }
}

bool Console::saveLogFile()
{
    return saveLF;
}

void Console::clearConsole()
{
    if(notChangableText.isEmpty()){
        this->clear();
    }
    else{
        this->clear();
        this->insertPlainText(notChangableText);
    }

    line.clear();
}

void Console::clearLastString()
{   
    QString plainText = this->document()->toPlainText().mid(0, (this->document()->toPlainText().count() - QString(this->toPlainText().split(QChar('\n')).at(this->document()->lineCount() - 1)).count()) - 1);
    (this->document()->lineCount() > 1) ? (line = this->toPlainText().split(QChar('\n')).at(this->document()->lineCount() - 2))
                                        : (line.clear());

    this->clear();
    this->insertPlainText(plainText);

    textCursor().movePosition(QTextCursor::Up);
}


void Console::onEnter()
{
    QString userText = this->document()->toPlainText().split(QChar('\n')).at(textCursor().blockNumber()).mid(line.count());
    addHistory(userText);

//    if(readingText == true){
//        readingText = false;
//        readLine = userText;
//    }
//    else{
        emit onEnterPressing(userText);
//    }
}

void Console::addHistory(QString text)
{
    history->append(text);
    historyPosition++;
}

void Console::clearHistory()
{
    history->clear();
    historyPosition = 0;
}

void Console::historyForward()
{
    if(historyPosition == history->count())
        return;

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(line + history->at(historyPosition - 1));
    setTextCursor(cursor);

    historyPosition++;
}

void Console::historyBack()
{
    if(historyPosition == 0)
        return;

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();

    if(historyPosition == history->count() - 1)
        cursor.insertText(line);
    else
        cursor.insertText(line + history->at(historyPosition + 1));

    setTextCursor(cursor);
    historyPosition--;
}

void Console::keyPressEvent(QKeyEvent *event)
{
    if(!introduced){
        return;
    }
    if(event->key() == Qt::Key_Return && event->modifiers() == Qt::NoModifier){
        onEnter();
    }
    if(event->key() >= 0x20 && event->key() <= 0x7e
            && (event->modifiers() == Qt::NoModifier || event->modifiers() == Qt::ShiftModifier)){
        QPlainTextEdit::keyPressEvent(event);
    }
    if(event->key() == Qt::Key_Backspace
            && event->modifiers() == Qt::NoModifier
            && textCursor().positionInBlock() > line.length()){
        QPlainTextEdit::keyPressEvent(event);
    }
    if(event->key() == Qt::Key_Up && event->modifiers() == Qt::NoModifier){
        historyForward();
    }
    if(event->key() == Qt::Key_Down && event->modifiers() == Qt::NoModifier){
        historyBack();
    }
}

void Console::mousePressEvent(QMouseEvent *)
{
    this->setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *)
{

}

void Console::contextMenuEvent(QContextMenuEvent *event)
{
    QPlainTextEdit::contextMenuEvent(event);
}
