#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgameitem.h"
#include "scene/creditscene.h"
#include "scene/logoscene.h"
#include "scene/mainscene.h"
#include "scene/readyscene.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMediaPlayer>


class CustomItem : public QGraphicsPixmapItem
{
private:
    QApplication *app;
    MainWindow *window;
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        qDebug() << "Custom item clicked.";
        setPixmap(QPixmap(":images/button_ok_click.png"));

        window->switchToMain();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        setPixmap(QPixmap(":images/button_ok.png"));
    }

    void setApplication(QApplication* app)
    {
        this->app = app;
    }

    void setMainWindow(MainWindow *window)
    {
        this->window = window;
    }
};


// Constructor & Destructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScenes();
    ui->graphicsView->setScene(logo);
}


MainWindow::~MainWindow()
{
    delete ui;
}


// Methods
// Utility Functions
void MainWindow::switchScene(int scenetype)
{
    using namespace SceneType;
    QGraphicsScene* scene;

    switch(scenetype) {
        case LOGO:
            scene = logo;
            break;
        case MAIN:
            scene = menu;
            break;
        case READY:
            scene = ready;
            break;
        case INGAME:
            scene = ingame;
            break;
        case CREDIT:
            scene = credit;
            break;
    }

    ui->graphicsView->setScene(scene);
}


void MainWindow::setApplication(QApplication* app)
{
    this->app = app;
}


void MainWindow::setupScenes()
{
    logo = new LogoScene(0, 0, 1280, 720, this);
    menu = new MainScene(0, 0, 1280, 720, this);
    ready = new QGraphicsScene(0, 0, 1280, 720, this);
    ingame = new QGraphicsScene(0, 0, 1280, 720, this);
    credit = new QGraphicsScene(0,0,1280,720,this);


    // setup for ready
    QGraphicsPixmapItem *ready_logo = ready->addPixmap(QPixmap(":images/logo/logo_background.png"));
    ready_logo->setPos(0, 0);

    // setup for ingame
    QGraphicsPixmapItem *game_board = ingame->addPixmap(QPixmap(":images/ingame/background.png"));
    game_board->setPos(0,0);




}
