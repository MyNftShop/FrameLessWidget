#ifndef FramelessWindow_H
#define FramelessWindow_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include "titlebar.h"
#include "frameless_helper.h"
#include <QVBoxLayout>

namespace Ui {
  class FramelessWindow;
}

class FramelessWindow : public QWidget
{
  Q_OBJECT

public:
  explicit FramelessWindow(QWidget *parent = 0);
  ~FramelessWindow();

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void mouseMoveEvent(QMouseEvent *event);

  void setMinimizeVisible(bool);
  void setMaximizeVisible(bool);
  void setWidgetResizable(bool);
protected:

  void paintEvent(QPaintEvent *);
public:
  QVBoxLayout *m_pLayout;
  void setContent(QWidget *w);
  void loadStyleSheet(const QString &sheetName);
private slots:

private:

  Ui::FramelessWindow *ui;
  bool m_bPressed;
  QPoint m_point;
  int m_nBorder;
  TitleBar *pTitleBar;
  FramelessHelper *pHelper;
};

#endif // FramelessWindow_H
