#include "mainwidget.h"
#include "updater.h"

#include <QApplication>
#include <QMessageBox>
#include <QtWebView>


int main(int argc, char *argv[])
{
    using namespace GlobalData;
    QApplication a(argc, argv);
    QtWebView::initialize();

    initialize();
    database_Open();
    database_Check();
    database_Read();
    connectToServer();
    Updater *updater = new Updater();
    updater->checkContent();

    MainWidget* main_widget = new MainWidget();
    return a.exec();
}
