#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QApplication>
#include "message_box.h"

MessageBox::MessageBox(QWidget *parent, const QString &title, const QString &text,
                       QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
    : CustomWindow(parent)
{
    resize(300, 130);
    setWindowIcon(QIcon(":/images/logo"));
    setWindowTitle(title);
    this->setMinimumSize(300, 130);

    setMinimizeVisible(false);
    setMaximizeVisible(false);

    setWidgetResizable(false);

    m_pButtonBox = new QDialogButtonBox(this);
    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    setDefaultButton(defaultButton);

    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
    if (pYesButton != NULL)
    {
        pYesButton->setObjectName("blueButton");
        pYesButton->setStyle(QApplication::style());
    }

    m_pIconLabel = new QLabel(this);
    m_pLabel = new QLabel(this);

//    QPixmap pixmap();
    m_pIconLabel->setPixmap(style()->standardPixmap(QStyle::SP_MessageBoxInformation));
    m_pIconLabel->setFixedSize(35, 35);
    m_pIconLabel->setScaledContents(true);

    m_pLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabel->setObjectName("whiteLabel");
    m_pLabel->setOpenExternalLinks(true);
    m_pLabel->setText(text);

    m_pGridLayout = new QGridLayout();
    m_pGridLayout->addWidget(m_pIconLabel, 0, 0, 2, 1, Qt::AlignTop);
    m_pGridLayout->addWidget(m_pLabel, 0, 1, 2, 1);
    m_pGridLayout->addWidget(m_pButtonBox, m_pGridLayout->rowCount(), 0, 1, m_pGridLayout->columnCount());
    m_pGridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    m_pGridLayout->setHorizontalSpacing(10);
    m_pGridLayout->setVerticalSpacing(10);
    m_pGridLayout->setContentsMargins(10, 10, 10, 10);
    m_pLayout->addLayout(m_pGridLayout);

    translateUI();

    connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

}

MessageBox::~MessageBox()
{

}

void MessageBox::setStandardButtons(QDialogButtonBox::StandardButtons buttons){
m_pButtonBox->setStandardButtons(buttons);
}

void MessageBox::changeEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::LanguageChange:
        translateUI();
        break;
    default:
        CustomWindow::changeEvent(event);
    }
}

void MessageBox::translateUI()
{
    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
    if (pYesButton != NULL)
        pYesButton->setText(tr("Yes"));

    QPushButton *pNoButton = m_pButtonBox->button(QDialogButtonBox::No);
    if (pNoButton != NULL)
        pNoButton->setText(tr("No"));

    QPushButton *pOkButton = m_pButtonBox->button(QDialogButtonBox::Ok);
    if (pOkButton != NULL)
        pOkButton->setText(tr("Ok"));

    QPushButton *pCancelButton = m_pButtonBox->button(QDialogButtonBox::Cancel);
    if (pCancelButton != NULL)
        pCancelButton->setText(tr("Cancel"));
}

QMessageBox::StandardButton MessageBox::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)m_pButtonBox->standardButton(button);
}

QAbstractButton *MessageBox::clickedButton() const
{
    return m_pClickedButton;
}

int MessageBox::exec(QAbstractButton *button)
{
    int nResult = m_pButtonBox->standardButton(button);
    return nResult;
}

void MessageBox::onButtonClicked(QAbstractButton *button)
{
    m_pClickedButton = button;
    (exec(button));
}

void MessageBox::setDefaultButton(QPushButton *button)
{
    if (!m_pButtonBox->buttons().contains(button))
        return;
    m_pDefaultButton = button;
    button->setDefault(true);
    button->setFocus();
}

void MessageBox::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(button)));
}

void MessageBox::setTitle(const QString &title)
{
    setWindowTitle(title);
}

void MessageBox::setText(const QString &text)
{
    m_pLabel->setText(text);
}

void MessageBox::setIcon(const QString &icon)
{
    m_pIconLabel->setPixmap(QPixmap(icon));
}

void MessageBox::setIcon(const QPixmap &icon)
{
    m_pIconLabel->setPixmap((icon));
}


void MessageBox::addWidget(QWidget *pWidget)
{
    m_pLabel->hide();
    m_pGridLayout->addWidget(pWidget, 0, 1, 2, 1);
}


QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
                                            const QString &text, QMessageBox::StandardButtons buttons,
                                            QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(msgBox.style()->standardPixmap(QStyle::SP_MessageBoxInformation));
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showError(QWidget *parent, const QString &title,
                                      const QString &text, QMessageBox::StandardButtons buttons,
                                      QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(msgBox.style()->standardPixmap(QStyle::SP_MessageBoxCritical));
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showSuccess(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons,
                                        QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(msgBox.style()->standardPixmap(QStyle::SP_MessageBoxInformation));
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showQuestion(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons,
                                         QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(msgBox.style()->standardPixmap(QStyle::SP_MessageBoxQuestion));
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons,
                                        QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(msgBox.style()->standardPixmap(QStyle::SP_MessageBoxWarning));
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showCritical(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons,
                                         QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(msgBox.style()->standardPixmap(QStyle::SP_MessageBoxCritical));
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showCheckBoxQuestion(QWidget *parent, const QString &title,
                                                 const QString &text, QMessageBox::StandardButtons buttons,
                                                 QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(msgBox.style()->standardPixmap(QStyle::SP_MessageBoxQuestion));

    QCheckBox *pCheckBox = new QCheckBox(&msgBox);
    pCheckBox->setText(text);
    msgBox.addWidget(pCheckBox);
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;

    QMessageBox::StandardButton standardButton = msgBox.standardButton(msgBox.clickedButton());
    if (standardButton == QMessageBox::Yes)
    {
        return pCheckBox->isChecked() ? QMessageBox::Yes : QMessageBox::No;
    }
    return QMessageBox::Cancel;
}

