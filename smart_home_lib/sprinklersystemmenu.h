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

    void run(SprinklerSystemProxy* sprinklerProxy);

    QTimer *timer;
    
signals:

public slots:
    void update();
        
private:
  QTextStream &_display;
  QTextStream &_input;

  SprinklerSystemProxy* _sprinklerProxy;
};

#endif // SPRINKLERSYSTEMMENU_H
