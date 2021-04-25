#include "browser.h"
#include <QBoxLayout>
#include <QClipboard>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickView>
#include <QUrl>


//
//QString qmlcode = "import QtQuick 2.11\nimport QtQuick.Controls 2.4\nPage {\nText { text: \"Hello world!\" }}";

Browser::Browser(QString url) : Widget()
{
    QString qmlcode = "import QtQuick 2.11\nimport QtQuick.Controls 2.4\nimport QtWebView 1.1\nPage {\nproperty alias webView: webView\nWebView {\nid: webView\nurl: \"%1\"\nanchors.fill: parent}}";
    QFile qmlfile(GlobalData::directory::image + "webview.qml");
    qmlfile.open(QIODevice::WriteOnly);
    qmlfile.write(qmlcode.arg(url).toUtf8());
    qmlfile.close();
    Viewer* viewer = new Viewer(this);
    connect(viewer, &Viewer::returned, this, &Browser::close);
    QTimer::singleShot(GlobalData::interface::animation_duration, this, &Browser::open);
}

void Browser::open()
{
    using namespace GlobalData::interface;
    /*
    QQuickView* view = new QQuickView(QUrl::fromLocalFile(GlobalData::directory::image + "webview.qml"));
    QWidget* wgt = QWidget::createWindowContainer(view, this);
    wgt->setFixedSize(GlobalData::screen::geometry.width() - indent * 2, GlobalData::screen::geometry.height() * 0.9);
    */
    engine = new QQmlEngine();
    item = new QQuickWidget(engine, this);
    item->setSource(QUrl::fromLocalFile(GlobalData::directory::image + "webview.qml"));
    item->setResizeMode(QQuickWidget::SizeRootObjectToView);
    item->setFixedSize(GlobalData::screen::geometry.width() - indent * 2, GlobalData::screen::geometry.height() * 0.9);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(item, 0, 0);
    //layout->addWidget(wgt);
    layout->setMargin(indent);
    layout->setSpacing(indent);
    setLayout(layout);
}

void Browser::close()
{
    hide();
    item->rootObject()->window()->hide();
    item->rootObject()->childItems()[0]->deleteLater();
    item->deleteLater();
    engine->deleteLater();
    deleteLater();
}
