#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include "titlebar.h"
#include <QDebug>
#include <QStyle>
#include <QPainter>
#include <QStyleOption>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
    , m_windowBorderWidth(0)
{
    setFixedHeight(30);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pButtonRestore= new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinimizeButton->setFixedSize(27, 22);
    m_pMaximizeButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27, 22);
    m_pButtonRestore->setFixedSize(27, 22);

    setObjectName("titleBar");
    m_pTitleLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");
    m_pButtonRestore->setObjectName("restoreButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");
    m_pButtonRestore->setToolTip("Restore");

    m_pMinimizeButton->setFocusPolicy(Qt::TabFocus);
    m_pMaximizeButton->setFocusPolicy(Qt::TabFocus);
    m_pCloseButton->setFocusPolicy(Qt::TabFocus);
    m_pButtonRestore->setFocusPolicy(Qt::TabFocus);

    m_pButtonRestore->hide();


    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel,1);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pButtonRestore);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5, 0, 5, 0);

    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pButtonRestore, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    // 加载本地样式 MyTitle.css文件;

}

TitleBar::~TitleBar()
{

}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if(mMaximizeable&&mMinimizeable){
            if( pWindow->isMaximized()){
                emit m_pButtonRestore->clicked();
            }else{
                emit m_pMaximizeButton->clicked();
            }
        }

    }
}

// 绘制标题栏背景色;
//void TitleBar::paintEvent(QPaintEvent *event)
//{
//    //设置背景色;
//    QPainter painter(this);
//    QPainterPath pathBack;
//    pathBack.setFillRule(Qt::WindingFill);
//    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
//    painter.fillPath(pathBack, QBrush(m_barColor));

//    // 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变;
//    // 这里减去m_windowBorderWidth ，是因为窗口可能设置了不同宽度的边框;
//    // 如果窗口有边框则需要设置m_windowBorderWidth的值，否则m_windowBorderWidth默认为0;
//    if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth))
//    {
//        this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
//    }
//    QWidget::paintEvent(event);
//}

void TitleBar::paintEvent(QPaintEvent*)

{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


//void TitleBar::mousePressEvent(QMouseEvent *event)
//{
//#ifdef Q_OS_WIN
//    if (ReleaseCapture())
//    {
//        QWidget *pWindow = this->window();
//        if (pWindow->isTopLevel())
//        {
//           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
//        }
//    }
//    event->ignore();
//#else
//#endif
//}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            //显示还原
            m_pMaximizeButton->setVisible(false);
            m_pButtonRestore->setVisible(true);
            pWindow->showMaximized();
        }
        else if (pButton == m_pButtonRestore)
        {
            //显示最大化
            m_pMaximizeButton->setVisible(true);
            m_pButtonRestore->setVisible(false);
            pWindow->showNormal();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            if(mMaximizeable){
                //显示还原
                m_pMaximizeButton->setVisible(false);
                m_pButtonRestore->setVisible(true);
//                m_pMaximizeButton->hide();
//                m_pButtonRestore->show();
            }

            //            m_pMaximizeButtm_pMaximizeButton->setToolTip(tr("Restore"));
            //            m_pMaximizeButtm_pMaximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            if(mMaximizeable){
                //显示最大化
                m_pMaximizeButton->setVisible(true);
                m_pButtonRestore->setVisible(false);
            }
            //            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            //            m_pMaximizeButton->setToolTip(tr("Maximize"));
        }


    }
}
