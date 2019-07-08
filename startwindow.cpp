#include "startwindow.h"
#include <QApplication>

StartWindow::StartWindow(QWidget* parent) : QWidget (parent)
{
    //游戏主窗口相关
    mainwindow = new MainWindow(this);
    connect(mainwindow, &MainWindow::GameClear, this, &StartWindow::slotsClearGame);

    //开始窗口相关
    setMaximumSize(STARTWINDOW_WIDTH, STARTWINDOW_HEIGHT);
    setMinimumSize(STARTWINDOW_WIDTH, STARTWINDOW_HEIGHT);
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle(WINDOW_TITLE);
    setWindowIcon(QIcon(WINDOW_ICON_PNG));

    //开始窗口背景设置
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(BACKGROUND_PNG)));
    setPalette(palette);

    //开始窗口按钮设置
    startButton = new QPushButton(this);
    quitButton = new QPushButton(this);
    settingsButton = new QPushButton(this);
    startButton->setIconSize(QSize(90, 45));
    quitButton->setIconSize(QSize(90, 45));
    settingsButton->setIconSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    startButton->setIcon(QIcon(STARTBUTTON_PNG));
    quitButton->setIcon(QIcon(QUITBUTTON_PNG));
    settingsButton->setIcon(QIcon(SETTINGSBUTTON_PNG));
    startButton->setGeometry(STARTBUTTON_X, STARTBUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    quitButton->setGeometry(QUITBUTTON_X, QUITBUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    settingsButton->setGeometry(SETTINGSBUTTON_X, SETTINGSBUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

    connect(startButton, &QPushButton::clicked, this, &StartWindow::slotsStartGame);
    connect(quitButton, &QPushButton::clicked, this, &StartWindow::slotsQuitGame);
    connect(settingsButton, &QPushButton::clicked, this, &StartWindow::slotsSettingsShow);

    //音乐音效设置
    BGM = new Sound(true, DEFAULT_BGM_WAV, this);
    startMusic = new Sound(false, STARTBUTTON_WAV, this);
    quitMusic = new Sound(false, QUITBUTTON_WAV, this);
    settingsMusic = new Sound{false, SETTINGSBUTTON_WAV, this};

    BGM->start();

    /*
     * 以下为设置窗口设置
    */
    settingsWindow = new QWidget{this};
    settingsWindow->setWindowTitle(tr("设置"));
    settingsWindow->setWindowFlags(Qt::Dialog);
    settingsWindow->setWindowModality(Qt::WindowModal);
    settingsWindow->setWindowIcon(QIcon(SETTINGS_WINDOW_PNG));
    settingsWindow->setMaximumSize(SETTINGS_WINDOW_WIDTH, SETTINGS_WINDOW_HEIGHT);
    settingsWindow->setMinimumSize(SETTINGS_WINDOW_WIDTH, SETTINGS_WINDOW_HEIGHT);

    void (QSpinBox::*spinboxSignal)(int) = &QSpinBox::valueChanged;

    BGMLabel = new QLabel{tr("背景音乐"), settingsWindow};

    BGMWidget = new QWidget{settingsWindow};
    BGMSpinBox = new QSpinBox{BGMWidget};
    BGMSpinBox->setRange(0, 100);
    BGMSlider = new QSlider{Qt::Horizontal, BGMWidget};
    BGMSlider->setRange(0, 100);
    connect(BGMSlider, &QSlider::valueChanged, BGMSpinBox, &QSpinBox::setValue);
    connect(BGMSpinBox, spinboxSignal, BGMSlider, &QSlider::setValue);
    BGMLayout = new QHBoxLayout{BGMWidget};
    BGMLayout->addWidget(BGMSpinBox);
    BGMLayout->addWidget(BGMSlider);
    BGMWidget->setLayout(BGMLayout);

    effectLabel = new QLabel{tr("游戏音效"), settingsWindow};

    effectWidget = new QWidget{settingsWindow};
    effectSpinBox = new QSpinBox{effectWidget};
    effectSpinBox->setRange(0, 100);
    effectSlider = new QSlider{Qt::Horizontal, effectWidget};
    effectSlider->setRange(0, 100);
    connect(effectSlider, &QSlider::valueChanged, effectSpinBox, &QSpinBox::setValue);
    connect(effectSpinBox, spinboxSignal, effectSlider, &QSlider::setValue);
    effectLayout = new QHBoxLayout{effectWidget};
    effectLayout->addWidget(effectSpinBox);
    effectLayout->addWidget(effectSlider);
    effectWidget->setLayout(effectLayout);

    buttonWidget = new QWidget{settingsWindow};
    confirmButton = new QPushButton{buttonWidget};
    confirmButton->setText(tr("确定"));
    cancelButton = new QPushButton{buttonWidget};
    cancelButton->setText(tr("取消"));
    ruleButton = new QPushButton{buttonWidget};
    ruleButton->setText(tr("游戏规则"));
    BGMSelectButton = new QPushButton{buttonWidget};
    BGMSelectButton->setText(tr("背景音乐选择"));
    connect(confirmButton, &QPushButton::clicked, this, &StartWindow::slotsSetBGMVolume);
    connect(confirmButton, &QPushButton::clicked, this, &StartWindow::slotsSetEffectVolume);
    connect(confirmButton, &QPushButton::clicked, settingsWindow, &QWidget::close);
    connect(cancelButton, &QPushButton::clicked, settingsWindow, &QWidget::close);
    connect(ruleButton, &QPushButton::clicked, this, &StartWindow::slotsGameRule);
    connect(BGMSelectButton, &QPushButton::clicked, this, &StartWindow::slotsBGMSelect);
    buttonLayout = new QHBoxLayout{buttonWidget};
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(ruleButton);
    buttonLayout->addWidget(BGMSelectButton);
    buttonWidget->setLayout(buttonLayout);

    settingsLayout = new QVBoxLayout{settingsWindow};
    settingsLayout->addWidget(BGMLabel);
    settingsLayout->addWidget(BGMWidget);
    settingsLayout->addWidget(effectLabel);
    settingsLayout->addWidget(effectWidget);
    settingsLayout->addWidget(buttonWidget);
    settingsWindow->setLayout(settingsLayout);

}

StartWindow::~StartWindow()
{
    BGM->terminate();
    BGM->wait();
    BGM->deleteLater();
    startMusic->terminate();
    startMusic->deleteLater();
    quitMusic->terminate();
    quitMusic->deleteLater();
    settingsMusic->terminate();
    settingsMusic->deleteLater();
    startButton->deleteLater();
    quitButton->deleteLater();
    settingsButton->deleteLater();
    confirmButton->deleteLater();
    ruleButton->deleteLater();
    BGMLabel->deleteLater();
    BGMSpinBox->deleteLater();
    BGMSlider->deleteLater();
    effectLabel->deleteLater();
    effectSpinBox->deleteLater();
    effectSlider->deleteLater();
    BGMLayout->deleteLater();
    effectLayout->deleteLater();
    BGMWidget->deleteLater();
    effectWidget->deleteLater();
    settingsLayout->deleteLater();
    settingsWindow->deleteLater();
}

void StartWindow::slotsStartGame()
{
    startMusic->start();
    startMusic->wait();
    mainwindow->slotsStartGame();
    mainwindow->show();
    hide();
}

void StartWindow::slotsQuitGame()
{
    quitMusic->start();
    quitMusic->wait();
    exit(EXIT_SUCCESS);
}

void StartWindow::slotsSettingsShow()       //弹出设置对话框
{
    settingsMusic->start();
    settingsMusic->wait();
    BGMSlider->setValue(static_cast<int>(BGM->BGMVolume * 100));
    effectSlider->setValue(static_cast<int>(BGM->effectVolume * 100));
    settingsWindow->show();
}


void StartWindow::slotsGameRule()           //弹出游戏规则对话框
{
    QMessageBox::about(settingsWindow, tr("游戏规则"),
                       tr("不同的轨道会掉落不同颜色的小球若干个,通过Q, W, E, R四个键分别控制轨道一, 二, 三, 四的障碍物, 控制障碍物, 只让同颜色的小球掉落!"));
}

void StartWindow::slotsClearGame()
{
    show();
    mainwindow->hide();
}

void StartWindow::slotsBGMSelect()          //弹出背景音乐选择对话框
{
    QStringList bgmitems;
    bgmitems << tr("Crazy Dave (Intro Theme)") << tr("Energy Drink") << tr("Back on Track");
    bool ok;
    QString bgmitem = QInputDialog::getItem(settingsWindow, tr("设置"), tr("背景音乐选择"), bgmitems, 0, false, &ok);
    if(ok)
        BGM->slotsChangeBGM(bgmitem);
}

void StartWindow::slotsSetBGMVolume()
{
    BGM->slotsSetBGMVolume(BGMSlider->value());
}

void StartWindow::slotsSetEffectVolume()
{
    startMusic->slotsSetEffectVolume(effectSlider->value());
}
