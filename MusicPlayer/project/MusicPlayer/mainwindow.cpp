#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QSlider>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QImage>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置软件标题
    setWindowTitle("MusicPlayer");

    //设置软件图标
    setWindowIcon(QIcon(":/images/01.jpg"));

    //初始化播放模式
    m_mode = ORDER_PLAY;

    //创建定时器对象
    m_timer = new QTimer(this);
    m_timer->setInterval(100); //间隔100ms

    //设置按钮图片
    ui->prevBtn->setIcon(QIcon(":/images/previous.png"));
    ui->playBtn->setIcon(QIcon(":/images/play.png"));
    ui->nextBtn->setIcon(QIcon(":/images/next.png"));
    ui->modeBtn->setIcon(QIcon(":/images/order.png"));
    ui->lowVolumnBtn->setIcon(QIcon(":/images/volumnLow.png"));
    ui->highVolumnBtn->setIcon(QIcon(":/images/volumnHigh.png"));

    ui->prevBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->nextBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->modeBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->playBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->lowVolumnBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->highVolumnBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");


    //创建音乐播放器对象
    m_player = new QMediaPlayer(this);

    //歌曲文件夹
    m_songDir = "F:\\Qt\\music";
    //加载歌曲文件夹
    loadSongDir(m_songDir);

    //加载默认歌曲
    m_player->setMedia(QUrl::fromLocalFile("F:\\Qt\\music\\七里香.mp3"));
    QString defalutfile = "F:\\Qt\\music\\七里香.lrc";
    loadLyricInfo(defalutfile);
    //默认专辑封面
    QPixmap pic("F:\\Qt\\music\\七里香.jpg");
    ui->albumPicture->setPixmap(pic.scaled(ui->albumPicture->width(),ui->albumPicture->height()));

    //设置默认播放第一首歌曲
    ui->songList->setCurrentRow(0);
    //设置音量范围
    ui->volumnBar->setRange(0,100);
    //设置初始音量
    ui->volumnBar->setValue(50);
    m_player->setVolume(50);

    /*信号和槽*/
    connect(ui->prevBtn,&QPushButton::clicked,this,&MainWindow::handlePrevSongSlot);
    connect(ui->playBtn,&QPushButton::clicked,this,&MainWindow::handleSuspendSongSlot);
    connect(ui->nextBtn,&QPushButton::clicked,this,&MainWindow::handleNextSongSlot);
    connect(ui->modeBtn,&QPushButton::clicked,this,&MainWindow::handlePlayModeSongSlot);

    connect(m_player,&QMediaPlayer::durationChanged,this,&MainWindow::handleDurationSlot);

    //音乐状态改变
    connect(m_player,&QMediaPlayer::positionChanged,this,&MainWindow::handlePositioSlot);

    //进度条
    connect(ui->progressBar,&QSlider::sliderMoved,this,&MainWindow::handleSliderSlot);
    //音量条
    connect(ui->volumnBar,&QSlider::sliderMoved,this,&MainWindow::handleVolumnSlot);
    //定时器时间到达
    connect(m_timer,&QTimer::timeout,this,&MainWindow::handleTimeoutSlot);
    //双击列表中的音乐
    connect(ui->songList,&QListWidget::doubleClicked,this,&MainWindow::playAppointSong);
    //
    connect(m_player,&QMediaPlayer::positionChanged,this,&MainWindow::handleStateChangedSlot);

    //当前播放状态
    m_playerState = false;

//    //启动定时器
//    m_timer->start();
}

void MainWindow::handlePrevSongSlot()
{
    qDebug()<<"播放上一首";

    //当前播放的歌曲是哪一首
    int currentSong = ui->songList->currentRow();    // 当前歌曲所在音乐列表的行数

    int prevSong = 0;
    if(m_mode == ORDER_PLAY){
        prevSong = (currentSong-1+ui->songList->count())%ui->songList->count();

    }else if (m_mode==RANDOM_PLAY) {
        do{
            prevSong = (rand()%10)%ui->songList->count();
        }while(prevSong==currentSong);

    }else if(m_mode == CIRCLE_PLAY){
        prevSong = currentSong;
    }

    ui->songList->setCurrentRow(prevSong);
}

void MainWindow::handleNextSongSlot()
{
    qDebug()<<"播放下一首";

    //当前播放的歌曲是哪一首
    int currentSong = ui->songList->currentRow();    // 当前歌曲所在音乐列表的行数

    int nextSong = 0;
    if(m_mode == ORDER_PLAY){
        nextSong = (currentSong + 1)%ui->songList->count();
    }else if (m_mode==RANDOM_PLAY) {
        do{
            nextSong = (rand()%10)%ui->songList->count();
        }while(nextSong==currentSong);

    }else if(m_mode == CIRCLE_PLAY){
        nextSong = currentSong;
    }

    ui->songList->setCurrentRow(nextSong);

    playAppointSong();  //播放指定音乐
}

//播放/暂停音乐
void MainWindow::handleSuspendSongSlot()
{
    qDebug()<<"暂停/播放";

    if(m_player->state()==QMediaPlayer::PlayingState){
        m_timer->stop();
        m_player->pause();

        ui->playBtn->setIcon(QIcon(":/images/play.png"));
        m_playerState = false;

    }
    //当前状态播放
    else {
        m_timer->start();
        m_player->play();
//        m_player->state()==QMediaPlayer::PausedState
        ui->playBtn->setIcon(QIcon(":/images/pause.png"));
        m_playerState = true;
    }

}
void MainWindow::handlePlayModeSongSlot()
{
    qDebug()<<"播放模式切换";

    if(m_mode==ORDER_PLAY){
        m_mode = RANDOM_PLAY;
        ui->modeBtn->setIcon(QIcon(":/images/random.png"));
    }else if(m_mode==RANDOM_PLAY){
        m_mode = CIRCLE_PLAY;
        ui->modeBtn->setIcon(QIcon(":/images/circle.png"));
    }else if(m_mode==CIRCLE_PLAY){
        m_mode = ORDER_PLAY;
        ui->modeBtn->setIcon(QIcon(":/images/order.png"));
    }
}

void MainWindow::handleDurationSlot()
{
    //qDebug()<<"duration:"<<m_player->duration();
    int totalMillSecs = m_player->duration();

    int minutes = totalMillSecs / 1000 / 60;
    int seconds = (totalMillSecs % (1000 * 60)) / 1000;

    QString time = QString("%1:%2").arg(minutes).arg(seconds);
    ui->totalTime->setText(time);

    //进度条范围
    ui->progressBar->setRange(0,m_player->duration());
}

//音乐状态改变
void MainWindow::handlePositioSlot()
{
    int position = m_player->position();

    //当前进度时间
    QString time = QString("%1:%2").arg(position /1000 / 60).arg(position /1000 % 60);
    ui->currentTime->setText(time);

    //进度条
    ui->progressBar->setValue(position);
}

void MainWindow::handleSliderSlot()
{
    int progressPos = ui->progressBar->value();
    m_player->setPosition(progressPos);
}

void MainWindow::handleVolumnSlot()
{
    int volumnValue = ui->volumnBar->value();

    //设置音量
    m_player->setVolume(volumnValue);
}

//加载歌词信息
void MainWindow::loadLyricInfo(QString &filename)
{
    // 清空hash table
    m_lyric.clear();

    QFile file(filename);

    file.open(QIODevice::ReadOnly);

    if(file.isOpen()==false){
        QMessageBox::warning(this,"文件","文件打开失败");
        return;
    }
//    QMessageBox::information(this,"文件","文件打开成功");
    char buffer[128] = {0};

    while(1){
        int readBytes = file.readLine(buffer,sizeof(buffer));
        if(readBytes<=0)
            break;
//        qDebug()<<buffer<<endl;

        QString lineDate(buffer);
        QStringList lists = lineDate.split("]");

        int millSec = parseTime2Millsec(lists[0]);
  //      qDebug()<<"millSec"<<millSec<<"lists[1]"<<lists[1];

        m_lyric[millSec] = lists[1];    //插入hash table
    }

}

int MainWindow::parseTime2Millsec(QString &time)
{
    //time 传过来的时间为"[00:00.00"
    int minutes = time.split("[")[1].split(":")[0].toInt();
    int seconds = time.split("[")[1].split(":")[1].split(".")[0].toInt();
    int millSec = time.split(".")[1].toInt();

    int totalMillSec = (minutes*60 + seconds)*1000 + millSec;

    return totalMillSec;

}//解析时间

 void MainWindow::handleTimeoutSlot()
 {
    //显示歌词
    int currentPlayPos = m_player->position();

    //判断currentPlayPos在哪个位置之间
    for (auto iter = m_lyric.begin();iter != m_lyric.end();){
        auto prev = iter;
        auto next = ++iter;

        if(prev->first<=currentPlayPos && currentPlayPos<next->first){
            ui->lyric->setText(prev->second);
        }
    }
 }

 //加载文件夹
 void MainWindow::loadSongDir(QString &filepath)
 {
    QDir dir(filepath); //文件夹对象
    if(dir.exists()==false){
        QMessageBox::warning(this,"文件夹","文件夹打开失败");
        return ;
    }

    QFileInfoList fileInfo = dir.entryInfoList();

    for (auto iter = fileInfo.begin();iter !=fileInfo.end();++iter){

        if(iter->suffix()=="mp3"){
            qDebug()<<"basename:"<<iter->baseName()<<endl;
            //将歌曲名添加到歌曲列表
            ui->songList->addItem(iter->baseName());
        }
    }
 }

 //播放指定音乐
void MainWindow::playAppointSong()
{
   /*
    *1.音乐名
    *2.音乐的歌词
    *3.音乐的专辑
    */
    QString musicName = ui->songList->currentItem()->text();

    QString comingPlaySong = m_songDir + "\\" +musicName+ ".mp3";
    m_player->setMedia(QUrl::fromLocalFile(comingPlaySong));

    QString comingPlayLyric = m_songDir + "\\" +musicName+ ".lrc";
    loadLyricInfo(comingPlayLyric);

    QString comingPlayAlbumn = m_songDir + "\\" +musicName+ ".jpg";
    loadAlbumPic(comingPlayAlbumn);

    handleSuspendSongSlot();    //播放音乐
}

//加载专辑图片
void MainWindow::loadAlbumPic(QString &filepath)
{
    QPixmap pic(filepath);
    ui->albumPicture->setPixmap(pic.scaled(ui->albumPicture->width(),ui->albumPicture->height()));
}

void MainWindow::handleStateChangedSlot()
{
    qDebug()<<"State:"<<m_player->state()<<endl;

    if(m_player->state()==QMediaPlayer::StoppedState && m_player->position()!=0){
        handleNextSongSlot();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
