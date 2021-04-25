#ifndef SEARCH_H
#define SEARCH_H

#include "object.h"
#include "Search/patientsearchwidget.h"
#include "Search/searchdata.h"


class Search : public Object
{
    Q_OBJECT
public:
    Search(QThread *_thread = nullptr);

    static Widget*              create_widget_search(Search *object);

private:
    SearchData                  my_data;

public slots:
    void                        load();
    void                        search(QString text, int specialization_id);
    void                        update();

    void                        server_reply(QString header, QByteArray body) override;
    void                        readFromBytes_Specializations(QByteArray array);
    void                        readFromBytes_SearchResult(QByteArray array);

signals:
    void update_all_widgets(SearchData);

};

#endif // SEARCH_H
