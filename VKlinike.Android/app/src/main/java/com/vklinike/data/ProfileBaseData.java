package com.vklinike.data;


import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.DrawableContainer;
import android.media.Image;
import android.util.TypedValue;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.GlobalData;
import com.vklinike.ui.socket.ClientSocket;

import org.json.JSONArray;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Calendar;
import java.util.GregorianCalendar;


public class ProfileBaseData
{
    public ProfileBaseData() {
        birthday = new GregorianCalendar();
    }

    public static ProfileBaseData createFromJson(JsonObject object){
        ProfileBaseData profile = new ProfileBaseData();
        profile.load(object);
        return profile;
    }

    public void load(JsonObject json)
    {
        JsonElement element;
        element = json.get("id");
        if(element != null)
            id = element.getAsInt();

        element = json.get("miniature");
        if(element != null) {
            miniature_name = element.getAsString();
            GlobalData.socket.addExpectedEnclosure(miniature_name, new ClientSocket.OnEnclosureReceived() {
                @Override
                public void received(byte[] body) {
                    miniature = BitmapFactory.decodeByteArray(body, 0, body.length);
                }
            });
        }

        element = json.get("name");
        if(element != null)
            name = element.getAsString();

        element = json.get("surname");
        if(element != null)
            surname = element.getAsString();

        element = json.get("patronymic");
        if(element != null)
            patronymic = element.getAsString();

        element = json.get("sex");
        if(element != null)
            sex = element.getAsInt();

        element = json.get("birthday");
        if(element != null)
            birthday = new Timepoint(element.getAsJsonObject()).toCalendar();

        element = json.get("email");
        if(element != null)
            email = element.getAsString();

        element = json.get("phone");
        if(element != null)
            phone = element.getAsString();

        element = json.get("password");
        if(element != null)
            password = element.getAsString();
    }

    public JsonObject toJson()
    {
        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        avatar.compress(Bitmap.CompressFormat.PNG, 100, stream);
        String avatar_name = "profile_avatar_" + String.valueOf(id);
        GlobalData.socket.sendEnclosure(avatar_name, stream.toByteArray());

        stream = new ByteArrayOutputStream();
        miniature.compress(Bitmap.CompressFormat.PNG, 100, stream);
        String miniature_name = "profile_miniature_" + String.valueOf(id);
        GlobalData.socket.sendEnclosure(miniature_name, stream.toByteArray());

        JsonObject object = new JsonObject();
        object.addProperty("avatar", avatar_name);
        object.addProperty("miniature", miniature_name);
        object.addProperty("name", name);
        object.addProperty("surname", surname);
        object.addProperty("patronymic", patronymic);
        object.addProperty("sex", sex);
        object.add("birthday", new Timepoint(birthday).toJson());
        object.addProperty("email", email);
        object.addProperty("phone", phone);
        object.addProperty("password", password);
        return object;
    }

    public int id = 0;
    public Bitmap avatar;
    public Bitmap miniature;
    public String miniature_name = "";
    public String name = "";
    public String surname = "";
    public String patronymic = "";
    public int sex = 0;
    public Calendar birthday;
    public String email = "";
    public String phone = "";
    public String password = "";
}
