#include "dialogwidget.h"
#include "dialog.h"


DW_Message::DW_Message(Widget *_parent, MessageData _data) : Widget(_parent)
{
    using namespace GlobalData;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        message_data = _data;
        margin = interface::indent;
        spacing = interface::indent;
        bar_height = 50;
        bar_text_size = interface::text_size * 0.6;
        message_max_width = screen::geometry.width() * 0.7;
        message_text_size = interface::text_size * 0.9;

        message = new QLabel();
        time = new QLabel();
        status = new QLabel();
        loader = new Widget();
        loader_icon = new Button();
        loader_header = new QLabel();
        loader_type = new QLabel();
        attachment = new Widget();
        layout_bar = new QBoxLayout((GlobalData::currentLogin == message_data.sender_email) ? (QBoxLayout::RightToLeft) : (QBoxLayout::LeftToRight));
        layout_loader = new QGridLayout();
        layout_attachment = new QVBoxLayout();
        layout = new QVBoxLayout();

    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        setTextSize(time, bar_text_size);
        setTextSize(status, bar_text_size);
        message->setWordWrap(true);
        message->setMaximumWidth(message_max_width);
        loader->setMaximumWidth(message_max_width);
        loader->setFrame(true, GlobalData::Frame_Rectangle, 2, GlobalData::interface::color::blue);
        loader_icon->setFixedSize(interface::row_size * 2, interface::row_size * 2);
        loader_header->setFixedHeight(interface::row_size);
        Widget::setTextSize(loader_header, interface::text_size);
        loader_type->setFixedHeight(interface::row_size);
        Widget::setTextSize(loader_type, interface::text_size * 0.8);
        attachment->setMaximumWidth(message_max_width);
        time->setFixedHeight(bar_height);
        status->setFixedSize(bar_height, bar_height);
        setMaximumWidth(message_max_width + margin * 2);
        setFrame(true, Frame_Rounded, 1, interface::color::blue);
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        if(message_data.message.isEmpty())
            message->setVisible(false);
        loader_icon->setPixmap(QPixmap(directory::icon + directory::icons::document).scaled(interface::row_size * 2, interface::row_size * 2));
        loader_header->setText("Загрузить вложение");
        setAttachment(message_data.attachment);
        messageChange(_data.message);
        timeReload();
        statusChange(message_data.recd, message_data.readed);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_bar->addWidget(time);
        layout_bar->addStretch(0);
        layout_bar->addWidget(status);
        layout_bar->setMargin(0);
        layout_bar->setSpacing(0);
        layout_loader->addWidget(loader_icon, 0, 0, 2, 1);
        layout_loader->addWidget(loader_header, 0, 1, 1, 3);
        layout_loader->addWidget(loader_icon, 1, 1, 1, 3);
        layout_loader->setMargin(0);
        layout_loader->setSpacing(0);
        layout_attachment->setMargin(0);
        layout_attachment->setSpacing(0);
        loader->setLayout(layout_loader);
        attachment->setLayout(layout_attachment);
        layout->addWidget(message);
        layout->addWidget(loader);
        layout->addWidget(attachment);
        layout->addLayout(layout_bar);
        layout->setMargin(margin);
        layout->setSpacing(spacing);
        setLayout(layout);
    //------------------------
    connect(loader_icon, &Button::clicked, this, &DW_Message::loadAttachment);
}

void DW_Message::loadAttachment()
{
    emit load_attachment(message_data.attachment.name);
}

void DW_Message::setAttachment(Attachment _attachment)
{
    while(QLayoutItem* item = layout_attachment->itemAt(0))
    {
        layout_attachment->removeItem(item);
        layout_attachment->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    message_data.attachment = _attachment;
    if(message_data.attachment.name.isEmpty())
    {
        loader->setVisible(false);
        attachment->setVisible(false);
    }
    if(!message_data.attachment.name.isEmpty() && message_data.attachment.data.isEmpty())
    {
        loader->setVisible(true);
        attachment->setVisible(false);
        if(message_data.attachment.group == Attachment::Image)
            loader_type->setText("Изображение");
        if(message_data.attachment.group == Attachment::Video)
            loader_type->setText("Видео");
        if(message_data.attachment.group == Attachment::Document)
            loader_type->setText("Документ");
    }
    if(!message_data.attachment.name.isEmpty() && !message_data.attachment.data.isEmpty())
    {
        loader->setVisible(false);
        attachment->setVisible(true);
        if(message_data.attachment.group == Attachment::Image)
        {
            QLabel *new_label = new QLabel();
            QPixmap pixmap;
            pixmap.loadFromData(message_data.attachment.data);
            if(pixmap.size().width() > message_max_width)
                pixmap = pixmap.scaled(message_max_width, ((double)message_max_width / (double)pixmap.size().width()) * pixmap.size().height(), Qt::KeepAspectRatioByExpanding);
            attachment->setFixedSize(pixmap.size());
            new_label->setPixmap(pixmap);
            layout_attachment->addWidget(new_label);
            layout_attachment->update();
        }
    }
    layout->update();
}

void DW_Message::timeReload()
{
    QString result = "";
    if(message_data.send_time.date() != QDate::currentDate())
    {
        result += message_data.send_time.date().toString();
    }
    result += message_data.send_time.time().toString().mid(0, 5);
    time->setText(result);
}

void DW_Message::messageChange(QString _message)
{
    QFontMetrics fm(message->font());
    message_data.message = _message;
    if(fm.horizontalAdvance(_message) < message_max_width)
        message->setFixedWidth(fm.horizontalAdvance(_message));
    else
        message->setFixedWidth(message_max_width);
    message->setText(_message);
    message->setFixedHeight(message->sizeHint().height());
}

void DW_Message::statusChange(bool rect, bool readed)
{
    using namespace GlobalData::directory;
    if(message_data.sender_email == GlobalData::currentLogin)
    {
        if(!rect)
            status->setPixmap(QPixmap(icon + icons::loading).scaled(bar_height, bar_height));
        if(rect && !readed)
            status->setPixmap(QPixmap(icon + icons::check).scaled(bar_height, bar_height));
        if(rect && readed)
            status->setPixmap(QPixmap(icon + icons::check_double).scaled(bar_height, bar_height));
    }
    else
    {
        status->setPixmap(QPixmap());
    }
}


DialogWidget::DialogWidget(Dialog *_object, DialogData _data) : Widget((QWidget*)GlobalData::widget_main)
{
    using namespace GlobalData;
    using namespace GlobalData::interface;
    using namespace GlobalData::directory;
    my_object = _object;
    my_data = _data;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        spacing = 0;
        margin = indent;
        size_header = QSize(screen::geometry.width() - margin * 2, screen::geometry.height() * 0.09);
        size_editor = QSize(screen::geometry.width() - margin * 2, screen::geometry.height() * 0.065);
        size_body = QSize(screen::geometry.width() - margin * 2, screen::geometry.height() - size_header.height() - size_editor.height() - indent * 4);
        header_pix_size = size_header.height() * 0.4;
        header_row_size = size_header.height() * 0.3;
        header_margin = size_header.height() * 0.1;
        header_spacing = interface::spacing;
        body_margin = indent;
        body_spacing = indent;
        editor_frame_thick = 4;
        editor_margin = editor_frame_thick;
        editor_spacing = indent;
        editor_pix_size = size_editor.height() - editor_spacing * 2;

        header = new Widget(this);
        header_back = new Button(header);
        header_name = new QLabel(header);
        header_status = new QLabel(header);
        header_call_audio = new Button(header);
        header_call_video = new Button(header);
        header_options = new Button(this);
        header_options_menu = new QMenu();
        body = new Widget(this);
        body_area = new Widget(body);
        editor = new Widget(this);
        editor_text = new QTextEdit(editor);
        editor_affix = new Button(editor);
        editor_affix_menu = new QMenu();
        editor_send = new Button(editor);

        layout = new QVBoxLayout();
        layout_header = new QHBoxLayout();
        layout_body_area = new QBoxLayout(QBoxLayout::TopToBottom);
        layout_editor = new QHBoxLayout();
        QVBoxLayout* layout_header_text = new QVBoxLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        header_name->setText(_data.copanion_name);
        header_status->setText(_data.status);
        header_back->setPixmap(QPixmap(icon + icons::back).scaled(header_pix_size, header_pix_size));
        header_call_audio->setPixmap(QPixmap(icon + icons::call_audio).scaled(header_pix_size, header_pix_size));
        header_call_video->setPixmap(QPixmap(icon + icons::call_video).scaled(header_pix_size, header_pix_size));
        header_options->setPixmap(QPixmap(icon + icons::preferences).scaled(header_pix_size, header_pix_size));
        editor_affix->setPixmap(QPixmap(icon + icons::affix).scaled(editor_pix_size, editor_pix_size));
        editor_send->setPixmap(QPixmap(icon + icons::send).scaled(editor_pix_size, editor_pix_size));

        header_options_menu->addAction("Поиск");
        header_options_menu->addAction("Удалить историю");
        header_options_menu->addAction("В черный список");

        editor_affix_menu->addAction(QPixmap(icon + icons::photo), "Фотография");
        editor_affix_menu->addAction(QPixmap(icon + icons::document), "Документ");
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        setTextSize(header_name, header_row_size);
        setTextSize(header_status, header_row_size * 0.7);
        header->setFixedSize(size_header);
        header->setFrame(true, Frame_Rectangle, editor_frame_thick, color::blue);
        header_back->setFixedSize(header_pix_size, header_pix_size);
        header_call_audio->setFixedSize(header_pix_size, header_pix_size);
        header_call_video->setFixedSize(header_pix_size, header_pix_size);
        header_options->setFixedSize(header_pix_size, header_pix_size);
        body->setFixedSize(size_body);
        body_area->move(0, 0);
        body_area->setMoveableBorder(0, 0, size_body.width(), size_body.height());
        body_area->setMovable_vertical(true);
        editor->setFrame(true, Frame_Rectangle, editor_frame_thick, color::blue);
        editor->setFixedWidth(size_header.width());
        editor->setMinimumHeight(size_editor.height());
        editor->setMaximumHeight(screen::geometry.height() / 4);
        editor->setFixedSize(size_editor);
        editor_affix->setFixedSize(editor_pix_size, editor_pix_size);
        setFixedSize(screen::geometry.size());
        move(0, 0);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_header_text->addWidget(header_name);
        layout_header_text->addWidget(header_status);
        layout_header_text->setMargin(header_margin / 2);
        layout_header_text->setSpacing(indent);
        layout_header->addWidget(header_back);
        layout_header->addLayout(layout_header_text);
        layout_header->addStretch(0);
        layout_header->addWidget(header_call_audio);
        layout_header->addWidget(header_call_video);
        layout_header->addWidget(header_options);
        layout_header->setContentsMargins(header_spacing, header_margin, header_spacing, header_margin);
        layout_header->setSpacing(header_spacing);
        header->setLayout(layout_header);
        layout_body_area->setMargin(body_margin);
        layout_body_area->setSpacing(body_spacing);
        layout_body_area->setSizeConstraint(QLayout::SetMinAndMaxSize);
        body_area->setLayout(layout_body_area);
        layout_editor->addWidget(editor_text);
        layout_editor->addWidget(editor_affix);
        layout_editor->addWidget(editor_send);
        layout_editor->setContentsMargins(editor_margin, editor_margin, editor_spacing, editor_margin);
        layout_editor->setSpacing(editor_spacing);
        editor->setLayout(layout_editor);
        layout->addWidget(header);
        layout->addWidget(body);
        layout->addWidget(editor);
        layout->setMargin(margin);
        layout->setSpacing(spacing);
        setLayout(layout);
    //------------------------
    connect(header_back, &Button::clicked, this, &DialogWidget::exit);
    connect(editor_send, &Button::clicked, this, &DialogWidget::sendMessage);
    connect(header_options, &Button::clicked, this, &DialogWidget::openOptionsMenu);
    connect(header_options_menu, &QMenu::triggered, this, &DialogWidget::optionsMenuChanged);
    connect(editor_affix, &Button::clicked, this, &DialogWidget::openAffixMenu);
    connect(editor_affix_menu, &QMenu::triggered, this, &DialogWidget::affixMenuChanged);
    show();
    body_area->setFixedWidth(size_header.width());
    body_area->setMinimumWidth(size_header.width());
    setData(_data);
}

void DialogWidget::setData(DialogData _data)
{
    my_data = _data;

    header_name->setText(my_data.copanion_name);
    header_status->setText(my_data.status);

    while(QLayoutItem* item = layout_body_area->itemAt(0))
    {
        layout_body_area->removeItem(item);
        layout_body_area->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete(item);
    }

    for(int i = 0; i < my_data.messages.size(); i++)
    {
        DW_Message *new_message = new DW_Message(body_area, my_data.messages[i]);
        layout_body_area->addWidget(new_message);
        if(my_data.messages[i].sender_email == GlobalData::currentLogin)
            layout_body_area->setAlignment(new_message, Qt::AlignRight);
        else
            layout_body_area->setAlignment(new_message, Qt::AlignLeft);
        connect(new_message, &DW_Message::load_attachment, my_object, &Dialog::message_attachment_load);
    }
}

void DialogWidget::sendMessage()
{
    MessageData new_message;
    new_message.send_time = QDateTime::currentDateTime();
    new_message.message = editor_text->toPlainText();
    new_message.sender_name = GlobalData::currentName;
    new_message.sender_email = GlobalData::currentLogin;
    if(!my_attachments.isEmpty()){
        new_message.attachment = my_attachments[0];
        my_attachments.clear();
    }
    my_data << new_message;
    editor_text->setText("");
    setData(my_data);
    emit message_send(new_message);
}

void DialogWidget::openOptionsMenu()
{
    header_options_menu->exec(QPoint(header_options->x(), size_header.height()));
}

void DialogWidget::optionsMenuChanged(QAction* action)
{
    if(action->text() == "Поиск")
    {

    }
    if(action->text() == "Удалить историю")
    {
        my_data.messages.clear();
        setData(my_data);
        emit remove_story();
    }
    if(action->text() == "В черный список")
    {
        editor_text->setText("Этот пользователь в черном списке");
        editor_text->setReadOnly(true);
        emit block_user();
    }
}

void DialogWidget::openAffixMenu()
{
    editor_affix_menu->exec(QPoint(editor_affix->x(), editor->y() - editor_affix_menu->sizeHint().height()));
}

void DialogWidget::affixMenuChanged(QAction *action)
{
    QString adress;
    if(action->text() == "Фотография")
    {
        adress = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "/storage/emulated/0/DCIM/Camera", tr("Images (*.png *.xpm *.jpg)"));
    }
    if(action->text() == "Документ")
    {
        adress = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "/storage/emulated/0", tr("Documents (*.docx *.pdf)"));
    }

    QFile file(adress);
    if(!file.open(QIODevice::ReadOnly))
        GlobalData::error_Show("Прикрепление вложений", "Не удалось открыть файл");
    Attachment new_attachment(adress, file.readAll(), false);
    my_attachments << new_attachment;
}

void DialogWidget::exit()
{
    emit returning();
}
