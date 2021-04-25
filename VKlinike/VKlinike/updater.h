#ifndef UPDATER_H
#define UPDATER_H

#include "object.h"
#include "globaldata.h"

#include <QDir>
#include <QFile>
#include <QThread>


class Updater : public Object
{
    Q_OBJECT
public:
    Updater();

private:


public slots:
    void                    server_reply(QString header, QByteArray body) override;

    bool                    checkFile(QString type, QString name, bool loading = false);
    void                    checkContent();

    void                    loadData_File(QByteArray array);

signals:

};

#endif // UPDATER_H
