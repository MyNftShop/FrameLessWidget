#include "FramelessWindow.h"
#include "ui_framelesswindow.h"
#include "titlebar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QCursor>
#include <QStyle>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>
#include "frameless_helper.h"


FramelessWindow::FramelessWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramelessWindow),
    m_bPressed(false),
    m_nBorder(5)//drag edge
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 背景透明
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowOpacity(1);

    pTitleBar = new TitleBar(this);

    installEventFilter(pTitleBar);

    resize(400, 300);

    setWindowTitle("Custom Window");
    setWindowIcon(QIcon(":/images/logo"));

    //添加标题栏
    ui->contentLayout->insertWidget(0,pTitleBar);

    //设置窗口样式
    pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(pTitleBar->height());  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
    pHelper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放

//    //shadow under window title text
//    QGraphicsDropShadowEffect *textShadow = new QGraphicsDropShadowEffect;
//    textShadow->setBlurRadius(4.0);
//    textShadow->setColor(QColor("#eee"));
//    textShadow->setOffset(0.0);
//    pTitleBar->m_pTitleLabel->setGraphicsEffect(textShadow);

    //window shadow
//    QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
//    windowShadow->setBlurRadius(9.0);
//    windowShadow->setColor(palette().color(QPalette::Highlight));
//    windowShadow->setOffset(0.0);
//    ui->windowFrame->setGraphicsEffect(windowShadow);

    this->loadStyleSheet("MyTitle");
}



FramelessWindow::~FramelessWindow()
{
    delete ui;
}

void FramelessWindow::paintEvent(QPaintEvent*)

{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FramelessWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/Resources/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }

}
void FramelessWindow::setContent(QWidget *w)
{
    ui->contentLayout->setMargin(0);
//    ui->contentLayout->addWidget(w);
    ui->mainLayout->addWidget(w);
    ui->scrollArea->widget()->setMinimumSize(w->size());
    resize(w->size().width()+2,w->size().height()+2+pTitleBar->height() );
}

void FramelessWindow::setMinimizeVisible(bool visible){
    this->pTitleBar->mMinimizeable=visible;
    this->pTitleBar->m_pMinimizeButton->setVisible(visible);
}

void FramelessWindow::setMaximizeVisible(bool visible){
    this->pTitleBar->mMaximizeable=visible;
    this->pTitleBar->m_pMaximizeButton->setVisible(visible);
    this->pTitleBar->m_pButtonRestore->setVisible(!visible);

}

void FramelessWindow::setWidgetResizable(bool resizable){
    this->pHelper->setWidgetResizable(resizable);
}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void FramelessWindow::mousePressEvent(QMouseEvent *event)
{

    //#ifdef Q_OS_WIN
    //  if (ReleaseCapture())
    //    SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    //  event->ignore();
    //#else

    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
    //#endif
}

// 若鼠标左键被按下，移动窗体位置
void FramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

// 设置鼠标未被按下
void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}


