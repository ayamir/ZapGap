#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new Scene{this};
    view = new QGraphicsView(scene, this);
    game = new GameController{scene};

    connect(scene, &Scene::GameClear, this, &MainWindow::slotsClearGame);

    //窗口设置
    setMaximumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    scene->setSceneRect(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
    view->setMaximumSize(WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2);
    view->setMinimumSize(WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2);
    view->show();
    setCentralWidget(view);
    resize(WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2);
    setWindowTitle(WINDOW_TITLE);
    setWindowIcon(QIcon(WINDOW_ICON_PNG));
}

MainWindow::~MainWindow()
{
    game->deleteLater();
    view->deleteLater();
    scene->deleteLater();
}

void MainWindow::slotsStartGame()
{
    scene->setLevel(1);
    scene->slotsStartGame();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    exit(EXIT_SUCCESS);
}

void MainWindow::slotsClearGame()
{
    emit GameClear();
}
