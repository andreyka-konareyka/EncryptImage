#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPixmap>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *_parent) :
    QMainWindow(_parent),
    m_ui(new Ui::MainWindow)
{
    prepareUi();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::encryptSlot()
{
    int currentBigPixel = 0;
    m_encryptImage = QImage(m_bigImage);

    for (int i = 0; i < m_smallImage.height(); ++i)
    {
        for (int j = 0; j < m_smallImage.width(); ++j)
        {
            QColor color = m_smallImage.pixelColor(j, i);

            for (int t = 0; t < 8; ++t)
            {
                int x = (currentBigPixel + t) % m_encryptImage.width();
                int y = (currentBigPixel + t) / m_encryptImage.height();
                QColor tmpColor = m_encryptImage.pixelColor(x, y);

                int mask = (1 << t);

                if ((color.red() & mask) == mask)
                {
                    tmpColor.setRed(tmpColor.red() | 0x1);
                }
                else
                {
                    tmpColor.setRed(tmpColor.red() & 0xfe);
                }

                if ((color.green() & mask) == mask)
                {
                    tmpColor.setGreen(tmpColor.green() | 0x1);
                }
                else
                {
                    tmpColor.setGreen(tmpColor.green() & 0xfe);
                }

                if ((color.blue() & mask) == mask)
                {
                    tmpColor.setBlue(tmpColor.blue() | 0x1);
                }
                else
                {
                    tmpColor.setBlue(tmpColor.blue() & 0xfe);
                }

                m_encryptImage.setPixelColor(x, y, tmpColor);
            }

            currentBigPixel += 8;
        }
    }

    m_ui->encryptImage->setScaledContents(true);
    m_ui->encryptImage->setPixmap(QPixmap::fromImage(m_encryptImage));

    m_ui->statusbar->showMessage(QString::fromUtf8("Зашифровано"));
}

void MainWindow::decryptSlot()
{
    int currentBigPixel = 0;
    m_decryptImage = QImage(m_smallImage.width(),m_smallImage.height(), QImage::Format_RGB32);

    for (int i = 0; i < m_decryptImage.height(); ++i)
    {
        for (int j = 0; j < m_decryptImage.width(); ++j)
        {
            QColor color(0, 0, 0);

            for (int t = 0; t < 8; ++t)
            {
                int x = (currentBigPixel + t) % m_encryptImage.width();
                int y = (currentBigPixel + t) / m_encryptImage.height();
                QColor tmpColor = m_encryptImage.pixelColor(x, y);

                int mask = (1 << t);

                if ((tmpColor.red() & 0x1) == 0x1)
                {
                    color.setRed(color.red() | mask);
                }

                if ((tmpColor.green() & 0x1) == 0x1)
                {
                    color.setGreen(color.green() | mask);
                }

                if ((tmpColor.blue() & 0x1) == 0x1)
                {
                    color.setBlue(color.blue() | mask);
                }
            }

            currentBigPixel += 8;
            m_decryptImage.setPixelColor(j, i, color);
        }
    }

    m_ui->decryptImage->setScaledContents(true);
    m_ui->decryptImage->setPixmap(QPixmap::fromImage(m_decryptImage));

    m_ui->statusbar->showMessage(QString::fromUtf8("Дешифровано"));
}

void MainWindow::swapImage1Slot()
{
    m_smallImage = QImage(":/images/small");
    m_ui->smallImage->setPixmap(QPixmap::fromImage(m_smallImage));

    m_ui->statusbar->showMessage(QString::fromUtf8("Установлена первая картинка"));
}

void MainWindow::swapImage2Slot()
{
    m_smallImage = QImage(":/images/small2");
    m_ui->smallImage->setPixmap(QPixmap::fromImage(m_smallImage));

    m_ui->statusbar->showMessage(QString::fromUtf8("Установлена вторая картинка"));
}

void MainWindow::prepareUi()
{
    m_ui->setupUi(this);
    initConnections();

    m_bigImage = QImage(":/images/big");
    m_ui->bigImage->setScaledContents(true);
    m_ui->bigImage->setPixmap(QPixmap::fromImage(m_bigImage));

    m_smallImage = QImage(":/images/small");
    m_ui->smallImage->setScaledContents(true);
    m_ui->smallImage->setPixmap(QPixmap::fromImage(m_smallImage));
}

void MainWindow::initConnections()
{
    connect(m_ui->pbEncrypt, &QPushButton::clicked,
            this,            &MainWindow::encryptSlot);
    connect(m_ui->pbDecrypt, &QPushButton::clicked,
            this,            &MainWindow::decryptSlot);

    connect(m_ui->pbImage1,   &QPushButton::clicked,
            this,            &MainWindow::swapImage1Slot);
    connect(m_ui->pbImage2,   &QPushButton::clicked,
            this,            &MainWindow::swapImage2Slot);
}

