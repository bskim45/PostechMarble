#pragma once
#include <QGraphicsScene>
#include "../mainwindow.h"
#include "../qgameitem.h"

class GameoverScene : public QGraphicsScene
{
    Q_OBJECT
private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *credit_button;

    void setupGameover();

public:
    GameoverScene(qreal x=0, qreal y=0, qreal width=1280,
                  qreal height=720,
                  QObject* parent = 0);
    ~GameoverScene();

};
<<<<<<< HEAD



#endif // GAMEOVERSCENE_H
=======
>>>>>>> 55a54d1cb7458164f2c93e00d2f939c4049102ea
