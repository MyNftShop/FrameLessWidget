#include <QApplication>
#include "framelesswindow.h"
#include "mainwindow.h"
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  FramelessWindow framelessWindow;

  // create our mainwindow instance
  MainWindow *mainWindow = new MainWindow;
  framelessWindow.setContent(mainWindow);


  framelessWindow.show();

  return a.exec();
}
