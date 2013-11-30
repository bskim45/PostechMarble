#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgameitem.h"
#include "scene/creditscene.h"
#include "scene/logoscene.h"
#include "scene/mainscene.h"
#include "scene/ingamescene.h"
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

        window->switchScene(SceneType::MAIN);
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
    switchScene(SceneType::LOGO);

    // animate logo
    dynamic_cast<LogoScene*>(logo)->animateLogo();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete logo;
    delete menu;
    delete ready;
    delete ingame;
    delete credit;
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
    ready = new ReadyScene(0, 0, 1280, 720, this);
    ingame = new IngameScene(0,0,1280,720,this);
    credit = new CreditScene(0,0,1280,720,this);
}


void MainWindow::animateScene(int scenetype)
{
    using namespace SceneType;

    switch(scenetype) {
        case LOGO:
            dynamic_cast<LogoScene*>(logo)->animateLogo();
            break;
        case MAIN:
            dynamic_cast<MainScene*>(menu)->animateMain();
            break;
        case READY:
            dynamic_cast<ReadyScene*>(ready)->animateReady();
            break;
        case INGAME:
            //dynamic_cast<IngameScene*>(ingame)->animateIngame();
            break;
        case CREDIT:
            dynamic_cast<CreditScene*>(credit)->animateCredit();
            break;
    }
}
