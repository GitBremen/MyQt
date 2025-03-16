#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <map>
#include <QString>
using namespace std;

//播放模式
enum PLAYMODE{
    ORDER_PLAY=1,
    RANDOM_PLAY,
    CIRCLE_PLAY,
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void loadLyricInfo(QString &filename);  //加载歌词信息
    int parseTime2Millsec(QString &time);   //解析时间
    void loadSongDir(QString &filepath);    //加载文件夹
    void loadAlbumPic(QString &filepath);   //加载专辑图片
    void playAppointSong();                 //播放指定音乐
public slots:
    void handlePrevSongSlot();
    void handleNextSongSlot();
    void handleSuspendSongSlot();
    void handlePlayModeSongSlot();
    //音乐总时长
    void handleDurationSlot();
    void handlePositioSlot();
    void handleSliderSlot();    //进度条

    void handleVolumnSlot();

    void handleTimeoutSlot();   //定时时间到

    void handleStateChangedSlot();
private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_player;

    //当前播放状态
    bool m_playerState;
    //hash table-lyric
    std::map<int,QString> m_lyric;
    //定时器
    QTimer *m_timer;
    //歌曲文件夹
    QString m_songDir;

    enum PLAYMODE m_mode;
};

#endif // MAINWINDOW_H
