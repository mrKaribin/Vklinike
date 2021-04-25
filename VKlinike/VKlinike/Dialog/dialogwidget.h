#ifndef DIALOGWIDGET_H
#define DIALOGWIDGET_H

#include "Dialog/dialogdata.h"
#include "widget.h"
#include "button.h"

#include <QLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QMenu>

class Dialog;
class DialogWidget;


class DW_Message : public Widget
{
    Q_OBJECT
public:
    DW_Message(Widget *_parent, MessageData _data);

    MessageData                 message_data;

private:

    QBoxLayout                 *layout_bar;
    QGridLayout                *layout_loader;
    QVBoxLayout                *layout_attachment;
    QVBoxLayout                *layout;
    QLabel                     *message;
    QLabel                     *time;
    QLabel                     *status;
    Widget                     *loader;
    QLabel                     *loader_header;
    QLabel                     *loader_type;
    Button                     *loader_icon;
    Widget                     *attachment;

    int                         margin;
    int                         spacing;
    int                         bar_height;
    int                         bar_text_size;
    int                         message_height;
    int                         message_max_width;
    int                         message_text_size;

public slots:
    void                        setAttachment(Attachment attachment);
    void                        loadAttachment();
    void                        messageChange(QString _message);
    void                        statusChange(bool rect, bool readed);
    void                        timeReload();

signals:
    void                        load_attachment(QString name);

};


class DialogWidget : public Widget
{
    Q_OBJECT
public:
    DialogWidget(Dialog *my_object, DialogData _data);

private:
    Dialog                     *my_object;
    DialogData                  my_data;

    Widget                     *header;
    Button                     *header_back;
    QLabel                     *header_name;
    QLabel                     *header_status;
    Button                     *header_call_audio;
    Button                     *header_call_video;
    Button                     *header_options;
    Widget                     *body;
    Widget                     *body_area;
    Widget                     *editor;
    QTextEdit                  *editor_text;
    Button                     *editor_affix;
    Button                     *editor_send;
    QMenu                      *header_options_menu;
    QMenu                      *editor_affix_menu;

    QVBoxLayout                *layout;
    QHBoxLayout                *layout_header;
    QBoxLayout                 *layout_body_area;
    QHBoxLayout                *layout_editor;

    QSize                       size_header;
    QSize                       size_body;
    QSize                       size_editor;
    int                         margin;
    int                         spacing;
    int                         header_margin;
    int                         header_spacing;
    int                         header_pix_size;
    int                         header_row_size;
    int                         body_margin;
    int                         body_spacing;
    int                         editor_margin;
    int                         editor_spacing;
    int                         editor_pix_size;
    int                         editor_frame_thick;

    QString                     my_name;
    QList <Attachment>          my_attachments;

public slots:
    void                        setData(DialogData _data);

    void                        sendMessage();

    void                        openOptionsMenu();
    void                        optionsMenuChanged(QAction* action);

    void                        openAffixMenu();
    void                        affixMenuChanged(QAction* action);

    void                        exit();

signals:
    void message_send(MessageData);

    void remove_story();
    void block_user();

    void returning();

};

#endif // DIALOGWIDGET_H
