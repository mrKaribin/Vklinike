import QtQuick 2.11
import QtQuick.Controls 2.4
import QtWebView 1.1

Page {
    property alias webView: webView
    WebView {
        id: webView
        url: "https://www.google.com"
        anchors.fill: parent
    }
}
