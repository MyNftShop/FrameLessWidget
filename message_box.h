#ifndef MESSAGE_BOX
#define MESSAGE_BOX

/**


showInformation(this, QStringLiteral("提示"), QStringLiteral("这是一个普通的提示框-Information！"));
showQuestion(this, QStringLiteral("提示"), QStringLiteral("这是一个普通的提示框-Question！"));
showSuccess(this, QStringLiteral("提示"), QStringLiteral("这是一个普通的提示框-Success！"));
showError(this, QStringLiteral("提示"), QStringLiteral("这是一个普通的提示框-Error！"));


  */

#include <QMessageBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QCheckBox>
#include "customwindow.h"

class QLabel;

class MessageBox : public CustomWindow
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = 0, const QString &title = tr("Tip"), const QString &text = tr("This is Infomation!"),
                        QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
    ~MessageBox();
    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;

    // 设置默认按钮
    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);
    void setStandardButtons(QDialogButtonBox::StandardButtons);
    // 设置窗体标题
    void setTitle(const QString &title);
    // 设置提示信息
    void setText(const QString &text);
    // 设置窗体图标
    void setIcon(const QString &icon);
    void  setIcon(const QPixmap &icon);
    // 添加控件-替换提示信息所在的QLabel
    void addWidget(QWidget *pWidget);

    int exec(QAbstractButton *button=NULL);

protected:
    // 多语言翻译
    void changeEvent(QEvent *event);

private slots:
    void onButtonClicked(QAbstractButton *button);

private:
    void translateUI();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pLabel;
    QGridLayout *m_pGridLayout;
    QDialogButtonBox *m_pButtonBox;
    QAbstractButton *m_pClickedButton;
    QAbstractButton *m_pDefaultButton;
};

QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
                                            const QString &text, QMessageBox::StandardButtons buttons=QMessageBox::Cancel,
                                            QMessageBox::StandardButton defaultButton=QMessageBox::Cancel);



#endif // MESSAGEBOX_H
