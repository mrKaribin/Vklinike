package com.vklinike.data;


import android.content.res.Resources;
import android.graphics.drawable.Drawable;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import java.io.ByteArrayInputStream;

public class CommentData
{
    public CommentData()
    {
        sender = new ProfileBaseData();
    }

    public CommentData(ProfileBaseData _sender, int _rating, String _text)
    {
        sender = _sender;
        rating = _rating;
        text = _text;
    }

    public static CommentData createFromJson(JsonObject object){
        CommentData comment = new CommentData();
        comment.load(object);
        return comment;
    }

    public void load(JsonObject json)
    {
        JsonElement element;
        element = json.get("id");
        if(element != null)
            id = element.getAsInt();

        element = json.get("sender");
        if(element != null)
            sender = ProfileBaseData.createFromJson(element.getAsJsonObject());

        element = json.get("rating");
        if(element != null)
            rating = element.getAsInt();

        element = json.get("message");
        if(element != null)
            text = element.getAsString();
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        object.addProperty("sender_id", sender.id);
        object.addProperty("rating", rating);
        object.addProperty("message", text);
        return object;
    }

    public int id = 0;
    public ProfileBaseData sender;
    public int rating = 0;
    public String text = "";
}
