#ifndef BROWSER_H
#define BROWSER_H

#include "globaldata.h"
#include "widget.h"
#include "viewer.h"

#include <QTextEdit>
#include <QQuickWidget>


class Browser : public Widget
{
    Q_OBJECT
public:
    Browser(QString url);

private:
    QTextEdit* wgt_text;
    QQuickWidget *item;
    QQmlEngine *engine;

public slots:
    void open();
    void close();
};

#endif // BROWSER_H
