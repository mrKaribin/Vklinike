#include "cardslist.h"
#include "Cards/cards.h"
#include "Cards/cardeditor.h"
#include "viewer.h"


CardWidget::CardWidget(CardData _data)
{
    using namespace GlobalData::interface;
    using namespace GlobalData::directory;
    my_data = _data;

    QHBoxLayout *layout = new QHBoxLayout();
    wgt_check = new QCheckBox();
    wgt_remove = new Button();
    wgt_edit = new Button();

    wgt_edit->setFixedSize(row_size, row_size);
    wgt_remove->setFixedSize(row_size, row_size);
    setFixedSize(GlobalData::screen::geometry.width() - indent * 2, row_size + indent * 2);

    wgt_check->setText(my_data.number.mid(0, 4) + " **** **** " + my_data.number.mid(12, 4));
    wgt_edit->setPixmap(QPixmap(icon + icons::settings).scaled(row_size, row_size));
    wgt_remove->setPixmap(QPixmap(icon + icons::cross).scaled(row_size, row_size));

    layout->addWidget(wgt_check);
    layout->addStretch(0);
    layout->addWidget(wgt_edit);
    layout->addWidget(wgt_remove);
    layout->setSpacing(indent);
    layout->setMargin(indent);
    setLayout(layout);

    connect(wgt_check, &QCheckBox::toggled, this, &CardWidget::check);
    connect(wgt_remove, &Button::clicked, this, &CardWidget::remove);
    connect(wgt_edit, &Button::clicked, this, &CardWidget::edit);
}

void CardWidget::uncheckAllAlso(int id)
{
    if(my_data.id != id)
        wgt_check->setChecked(false);
}

void CardWidget::check(bool state)
{
    if(state)
        emit checked(my_data.id);
}

void CardWidget::edit()
{
    emit edited(my_data.id);
}

void CardWidget::remove()
{
    emit removed(my_data.id);
}


CardsList::CardsList(Cards *_object, Widget *parent) : Widget(parent)
{
    using namespace GlobalData;
    my_object = _object;

    QVBoxLayout *layout = new QVBoxLayout();
    layout_cards = new QVBoxLayout();
    wgt_create = new Button("Добавить карту");

    wgt_create->setFixedSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 1.5);
    wgt_create->setFrame(true, Frame_Rounded, 2, interface::color::blue);
    setFixedWidth(screen::geometry.width() - interface::indent * 2);
    setFixedHeight(300);

    layout_cards->setSpacing(interface::spacing);
    layout_cards->setMargin(0);
    layout->addLayout(layout_cards);
    layout->addWidget(wgt_create);
    layout->setSpacing(interface::spacing);
    layout->setMargin(0);
    setLayout(layout);

    connect(_object, &Cards::update_all_widgets, this, &CardsList::setData);
    connect(this, &CardsList::update, _object, &Cards::update);
    connect(wgt_create, &Button::clicked, this, &CardsList::card_create);
    emit update();
}

void CardsList::setData(QList <CardData> _data)
{
    using namespace GlobalData::interface;
    my_data = _data;

    while(QLayoutItem *item = layout_cards->itemAt(0))
    {
        layout_cards->removeItem(item);
        layout_cards->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    for(int i = 0; i < _data.size(); i++)
    {
        CardWidget *new_card = new CardWidget(_data[i]);
        connect(new_card, &CardWidget::checked, this, &CardsList::card_checked);
        connect(new_card, &CardWidget::edited, this, &CardsList::card_edit);
        connect(this, &CardsList::checked_card_id, new_card, &CardWidget::uncheckAllAlso);
        connect(new_card, &CardWidget::removed, my_object, &Cards::card_remove);
        layout_cards->addWidget(new_card);
    }
    //setFixedHeight((row_size + indent * 2) * _data.size() + indent * (_data.size() - 1) + row_size * 1.5);
    layout_cards->update();
}

CardData CardsList::currentCard()
{
    foreach(auto card, my_data)
        if(card.id == checked)
            return card;
    return CardData();
}

void CardsList::card_checked(int id)
{
    checked = id;
    emit checked_card_id(id);
}

void CardsList::card_edit(int id)
{
    foreach (auto card, my_data)
    {
        if(card.id == id)
        {
            CardEditor *editor = new CardEditor(my_object, card);
        }
    }
}

void CardsList::card_create()
{
    CardEditor *editor = new CardEditor(my_object);
}
