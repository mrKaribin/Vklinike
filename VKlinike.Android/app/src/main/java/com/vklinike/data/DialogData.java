package com.vklinike.data;

import android.content.res.Resources;
import android.graphics.drawable.Drawable;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import java.io.ByteArrayInputStream;
import java.util.ArrayList;
import java.util.List;

public class DialogData
{
    public DialogData()
    {
        messages = new ArrayList<MessageData>();
    }

    public DialogData(ProfileBaseData _companion, SpecializationData _specialization)
    {
        companion = _companion;
        specialization = _specialization;
    }

    public static DialogData createFromJson(JsonObject object){
        DialogData dialog = new DialogData();
        dialog.load(object);
        return dialog;
    }

    public void load(JsonObject json)
    {
        JsonElement element;
        element = json.get("id");
        if(element != null)
            id = element.getAsInt();

        element = json.get("companion");
        if(element != null)
            companion = ProfileBaseData.createFromJson(element.getAsJsonObject());

        element = json.get("specialization");
        if(element != null)
            specialization = SpecializationData.createFromJson(element.getAsJsonObject());

        element = json.get("opponent_mode");
        if(element != null)
            opponent_mode = element.getAsInt();

        element = json.get("muted");
        if(element != null)
            muted = element.getAsBoolean();

        element = json.get("opponent_muted");
        if(element != null)
            opponent_muted = element.getAsBoolean();
    }

    public void loadMessages(JsonArray array){
        if(messages == null)
            messages = new ArrayList<MessageData>();

        messages.clear();
        for(int i = 0; i < array.size(); i++){
            JsonObject object = array.get(i).getAsJsonObject();
            if(object != null)
                messages.add(MessageData.createFromJson(object));
        }
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        object.add("specialization", specialization.toJson());
        object.addProperty("opponent_mode", opponent_mode);
        object.addProperty("muted", muted);
        object.addProperty("opponent_muted", opponent_muted);
        return object;
    }

    public int id = 0;
    public boolean muted;
    public int opponent_mode;
    public boolean opponent_muted;
    public ProfileBaseData companion;
    public SpecializationData specialization;
    public List <MessageData> messages;
}
