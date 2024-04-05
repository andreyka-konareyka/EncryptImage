#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QImage>

namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* _parent = nullptr);
    ~MainWindow();

private slots:
    void encryptSlot();
    void decryptSlot();
    void swapImage1Slot();
    void swapImage2Slot();

private:
    void prepareUi();
    void initConnections();

private:
    Ui::MainWindow *m_ui;

    QImage m_bigImage;
    QImage m_smallImage;
    QImage m_encryptImage;
    QImage m_decryptImage;
};

#endif // MAINWINDOW
