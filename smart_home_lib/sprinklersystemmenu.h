#ifndef SPRINKLERSYSTEMMENU_H
#define SPRINKLERSYSTEMMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <sprinklersystemproxy.h>

class SprinklerSystemMenu : public QObject
{
    Q_OBJECT
public:
    explicit SprinklerSystemMenu(QTextStream &display, QTextStream &input, QObject *parent = nullptr);
    virtual ~SprinklerSystemMenu() = default;

    void run();

signals:

public slots:
    void showRegisterDevice(SprinklerSystemProxy* sprinklerSystemProxy);

private:
  QTextStream &_display;
  QTextStream &_input;

};

#endif // SPRINKLERSYSTEMMENU_H
