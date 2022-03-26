#include "mainwindow.h"

#include <QApplication>
#include <QMediaContent>
#include <QtMultimediaWidgets>
#include <iostream>
class ImageButton: public QPushButton
{
Q_OBJECT

public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void mousePressEvent(QMouseEvent *e) override;
    void sound();
    QMediaPlayer *myPlayer = nullptr;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    QString pathToAudioFile;
    QString filePath = R"(C:\Users\bagi3\Pictures\Click.mp3)";
    bool isDown = false;
};
ImageButton::ImageButton(QWidget *parent)
{
    setParent(parent);
    setToolTip("stop");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap(R"(C:\Users\bagi3\Pictures\up_1.png)");
    mButtonDownPixmap = QPixmap(R"(C:\Users\bagi3\Pictures\down_1.png)");
    pathToAudioFile = R"(C:\Users\bagi3\Pictures\Click.MP3)";
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mButtonUpPixmap.rect());
    //connect(this, &QPushButton::clicked, this, &QPushButton::setDown);
    myPlayer = new QMediaPlayer(this);
    myPlayer->setMedia(QUrl::fromLocalFile(filePath));
    myPlayer->setVolume(90);
}

void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}
QSize ImageButton::sizeHint() const
{
    return QSize(100,100);
}
QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}
void ImageButton::sound(){

}
void ImageButton::mousePressEvent(QMouseEvent *e)
{
    std::cout << "click mouse\n";
    myPlayer->play();
    setDown();
}
void ImageButton::setDown()
{
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(200, this, &ImageButton::setUp);
}
void ImageButton::setUp()
{
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageButton myButton(nullptr);
    myButton.setFixedSize(160,160);
    myButton.move(800, 500);
    myButton.show();

    return a.exec();
}
#include <main.moc>
