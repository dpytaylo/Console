#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <future>
#include <QtGui>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QFile>

class Console : public QPlainTextEdit
{
    Q_OBJECT

public:
    Console(QWidget *parent = 0);
    ~Console();

    void write(QString text);
    void writeln(QString text = "");

    QString read();

    void setIntroduced(bool inputBool);
    bool getIntroduced();

    void setShowTime(bool timeBool);
    bool getShowTime();

    void setNotChangableText(QString text);
    void clearNotChangableText();

    void setSaveLogFile(bool SLF = true, QString path = "");
    bool saveLogFile();

    void clearConsole();
    void clearLastString();

private:
    bool introduced = false;
    bool showTime = false;
    bool textWithTime = false;
    bool saveLF = false;
    bool readingText = false;

    QString line = "";
    QString notChangableText;
    QString pathToSaveLogFile;
    QString readLine;

    QStringList *history;
    int historyPosition = 0;

    void onEnter();

    void addHistory(QString text);
    void clearHistory();
    void historyForward();
    void historyBack();

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void contextMenuEvent(QContextMenuEvent *event);

signals:
    void onEnterPressing(QString);
};

#endif // MAINWINDOW_H
