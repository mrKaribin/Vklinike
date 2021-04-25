#ifndef MESSAGESWIDGET_H
#define MESSAGESWIDGET_H

#include "widget.h"
#include "button.h"
#include "messagesdata.h"

#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>

class MW_Filter;
class MessagesWidget;
class Messages;


class MW_Message : public Button
{
    Q_OBJECT
public:
    MW_Message(MessagesWidget* parent, DialogPreviewData _data);

    Button                         *image;
    QLabel                         *header,
                                   *specialization,
                                   *lastMessage;

private:
    DialogPreviewData               my_data;

public slots:
    void                            profileOpen();
    void                            dialogOpen();

signals:
    void profile_open();
    void diialog_open();

};


struct Filter
{
    bool forChild = false;
    bool forAdult = false;
    QList <QString> custom;
};


class MW_Filter : public Widget
{
    Q_OBJECT
public:
    MW_Filter(MessagesWidget* parent);

    void configurateBox(QCheckBox* box);

private:
    QLabel                         *header_icon;
    QLabel                         *header_text;
    Button                         *header;
    QCheckBox                      *box_children;
    QCheckBox                      *box_adult;
    Widget                         *body;
    QGridLayout                    *layout_body_editable;
    QThread                        *service_thread;
    QVector <QCheckBox*>            checkBoxes;

    QSize                           size_opened;
    QSize                           size_closed;

    int                             margin;
    int                             spasing;
    int                             header_height;
    int                             header_text_size;
    int                             body_box_height;
    int                             body_text_size;
    int                             body_margin;
    int                             body_spasing;

public slots:
    void                            updateFilters(QVector <QString> _filters);
    void                            filterChanged(int i);
    void                            open();
    void                            close();

signals:
    void changed(Filter);

};


class MessagesWidget : public Widget
{
    Q_OBJECT
public:
    MessagesWidget(Messages* _object, DialogsData _data, Widget* parent = nullptr);


private:
    QVBoxLayout                    *layout;
    MW_Filter                      *filter;
    QVector <MW_Message*>           messages;

    DialogsData                    my_data;
    Filter                          my_filter;
    bool                            filters_opened = false;

public slots:
    void setData(DialogsData);
    void messagesChange(QVector <DialogPreviewData> _data);
    void filtersChanged(Filter _filter);
    void reloadLayout();

};

#endif // MESSAGESWIDGET_H
