#ifndef CONSTANT_H
#define CONSTANT_H

#include <vector>
#include <QGraphicsScene>
#include <utility>
#include <QtDebug>

using std::make_pair;

#define STARTWINDOW_WIDTH 800                       //开始窗口宽度
#define STARTWINDOW_HEIGHT 640                      //开始窗口高度
#define BUTTON_WIDTH 90                             //按钮宽度
#define BUTTON_HEIGHT 45                            //按钮高度
#define BACKGROUND_PNG ":/image/background.png"     //背景图片地址
#define WINDOW_ICON_PNG ":/image/icon.png"          //窗口图标地址
#define WINDOW_TITLE "勿越雷池"                      //窗口标题
#define DEFAULT_BGM_WAV ":/music/Crazy Dave (Intro Theme).wav" //默认背景音乐

#define STARTBUTTON_X 400                           //开始游戏按钮横坐标
#define STARTBUTTON_Y 360                           //开始游戏按钮纵坐标
#define STARTBUTTON_PNG ":/image/Start.png"         //开始游戏按钮图标
#define STARTBUTTON_WAV ":/music/startmusic.wav"    //开始游戏按钮音效

#define QUITBUTTON_X 400                            //退出游戏按钮横坐标
#define QUITBUTTON_Y 480                            //退出游戏按钮纵坐标
#define QUITBUTTON_PNG ":/image/Quit.png"           //退出游戏按钮图标
#define QUITBUTTON_WAV ":/music/quitmusic.wav"      //退出游戏按钮音效

#define SETTINGSBUTTON_X 400                        //设置按钮横坐标
#define SETTINGSBUTTON_Y 420                        //设置按钮纵坐标
#define SETTINGSBUTTON_PNG ":/image/Settings.png"      //设置按钮图标
#define SETTINGSBUTTON_WAV ":/music/settingsmusic.wav" //设置按钮音效

#define SETTINGS_WINDOW_WIDTH 600                   //设置窗口宽度
#define SETTINGS_WINDOW_HEIGHT 400                  //设置窗口高度
#define SETTINGS_WINDOW_PNG ":/image/settingswindowicon.png"  //设置窗口图标

#define WINDOW_WIDTH 1024                           //游戏窗口宽度
#define WINDOW_HEIGHT 768                           //游戏窗口高度
#define TIME_PER_FRAME 1000 / 60                    //帧
#define RAIL_WIDTH 200                              //轨道宽度
#define LINE_HEIGHT 234                             //线高度
#define BALL_RADIUS 25                              //小球半径
#define BALL_SPEED 0.165 * TIME_PER_FRAME           //小球速度
#define MAX_CUR_OF_BALL 15                          //同屏最大小球数量
#define CORRECT_SCORE 25                            //正确消球得分
#define INCORRECT_SCORE -30                         //错误消球得分
#define RAIL_SPEED 2.5 * TIME_PER_FRAME             //轨道移动速度
#define LEVEL_TIME 30000                            //每关时间(ms)
#define WORD_SIZE 30                                //得分字体字号
#define CORRECT_WAV ":/music/correct.wav"           //正确消球音效
#define INCORRECT_WAV ":/music/incorrect.wav"       //错误消球音效
#define MAX_LEVEL 5                                 //关卡数量

const std::vector<int> BALL_OF_LEVEL {25, 30, 40, 60, 100};                           //每关小球数量
const std::vector<int> FREQUENCY_OF_BALL {
    LEVEL_TIME / BALL_OF_LEVEL[0],
    LEVEL_TIME / BALL_OF_LEVEL[1],
    LEVEL_TIME / BALL_OF_LEVEL[2],
    LEVEL_TIME / BALL_OF_LEVEL[3],
    LEVEL_TIME / BALL_OF_LEVEL[4]
};                                                                                    //小球产生时间
const std::vector<std::vector<int>> STARTX_OF_RAIL {                                  //轨道左边界横坐标
    std::vector<int>{-RAIL_WIDTH, 0}, std::vector<int>{-RAIL_WIDTH, 0},
    std::vector<int>{-3 * RAIL_WIDTH / 2, -RAIL_WIDTH / 2, RAIL_WIDTH / 2},
    std::vector<int>{-3 * RAIL_WIDTH / 2, -RAIL_WIDTH / 2, RAIL_WIDTH / 2},
    std::vector<int>{-2 * RAIL_WIDTH, -RAIL_WIDTH, 0, RAIL_WIDTH}
};
const std::vector<int> KEY {Qt::Key_Q, Qt::Key_W, Qt::Key_E, Qt::Key_R};                //轨道按键
const std::vector<int> PASS_SCORE {514, 529, 724, 1224, 1949};                           //每关过关最少得分
const std::vector<std::vector<std::pair<int, QString>>> EVALUATION_SCORE {              //得分对应评价
    {make_pair(514, "小有所成"), make_pair(569, "技冠群雄"), make_pair(624, "一代宗师")},
    {make_pair(529, "小有所成"), make_pair(639, "技冠群雄"), make_pair(749, "一代宗师")},
    {make_pair(724, "小有所成"), make_pair(889, "技冠群雄"), make_pair(999, "一代宗师")},
    {make_pair(1224, "小有所成"), make_pair(1389, "技冠群雄"), make_pair(1499, "一代宗师")},
    {make_pair(1949, "小有所成"), make_pair(2224, "技冠群雄"), make_pair(2499, "一代宗师")}
};

enum class ObjectType {Rail, Ball, Line};                                               //Object类类型
const std::vector<QColor> COLOR {Qt::red, Qt::blue, Qt::cyan, Qt::green};               //颜色

#endif // CONSTANT_H
