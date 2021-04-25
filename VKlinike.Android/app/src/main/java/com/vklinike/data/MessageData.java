package com.vklinike.data;

import android.content.res.Resources;
import android.graphics.drawable.Drawable;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import java.io.ByteArrayInputStream;
import java.sql.Time;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;

public class MessageData
{
    public MessageData(){
        timepoint = Calendar.getInstance();
        attachment_data = new byte[1];
        deleted = new ArrayList<String>();
    }

    public static MessageData createFromJson(JsonObject object){
        MessageData message = new MessageData();
        message.load(object);
        return message;
    }

    public void load(JsonObject json)
    {
        JsonElement element;
        element = json.get("id");
        if(element != null)
            id = element.getAsInt();

        element = json.get("dialog_id");
        if(element != null)
            dialog_id = element.getAsInt();

        element = json.get("sender_id");
        if(element != null)
            sender_id = element.getAsInt();

        element = json.get("timepoint");
        if(element != null)
            timepoint = new Timepoint(element.getAsJsonObject()).toCalendar();

        element = json.get("message");
        if(element != null)
            message = element.getAsString();

        element = json.get("recd");
        if(element != null)
            recd = element.getAsBoolean();

        element = json.get("readed");
        if(element != null)
            readed = element.getAsBoolean();

        element = json.get("deleted");
        if(element != null){
            JsonArray array = element.getAsJsonArray();
            for(int i = 0; i < array.size(); i++) {
                element = array.get(i);
                if(element != null)
                deleted.add(element.getAsString());
            }
        }

        element = json.get("attachment_type");
        if(element != null)
            attachment_type = element.getAsString();

        element = json.get("attachment_name");
        if(element != null)
            attachment_name = element.getAsString();
    }

    public JsonObject toJson()
    {
        JsonArray array = new JsonArray();
        for(int i = 0; i < deleted.size(); i++)
            array.add(deleted.get(i));

        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        object.addProperty("dialog_id", dialog_id);
        object.addProperty("sender_id", sender_id);
        object.add("timepoint", new Timepoint(timepoint).toJson());
        object.addProperty("message", message);
        object.addProperty("recd", recd);
        object.add("deleted", array);
        object.addProperty("attachment_type", attachment_type);
        object.addProperty("attachment_name", attachment_name);
        return object;
    }

    public int id = -1;
    public int dialog_id = -1;
    public int sender_id = -1;
    public Calendar timepoint;
    public String message;
    public boolean readed = false;
    public boolean recd = false;
    public List<String> deleted;
    public String attachment_type = "empty";
    public String attachment_name = "empty";
    public byte[] attachment_data;
}
