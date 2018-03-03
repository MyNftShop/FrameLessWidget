#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();
//    void loadStyleSheet(const QString &sheetName);

protected:


    // 双击标题栏进行界面的最大化/还原
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    // 进行鼠界面的拖动
    //    virtual void mousePressEvent(QMouseEvent *event);

    // 设置界面标题与图标
    virtual bool eventFilter(QObject *obj, QEvent *event);

    //void paintEvent(QPaintEvent *event);

    void paintEvent(QPaintEvent *);
private slots:

    // 进行最小化、最大化/还原、关闭操作
    void onClicked();

private:

    // 最大化/还原
    void updateMaximize();

public:
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton* m_pButtonRestore;      // 最大化还原按钮;
    QPushButton *m_pCloseButton;

    bool mMaximizeable=true;
    bool mMinimizeable=true;
private:
    // 窗口边框宽度;
    int m_windowBorderWidth;


};

#endif // TITLE_BAR
