package com.vklinike.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import java.util.ArrayList;
import java.util.List;


public class PackageData
{
    public PackageData() {
        tariffs = new ArrayList<TariffData>();
    }
    public PackageData(int _duration, List <TariffData> _tariffs)
    {
        duration = _duration;
        tariffs = _tariffs;
    }

    public static PackageData createFromJson(JsonObject object)
    {
        PackageData pack = new PackageData();
        pack.load(object);
        return pack;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("id");
        if(element != null)
            id = element.getAsInt();

        element = object.get("duration");
        if(element != null)
            duration = element.getAsInt();

        element = object.get("tariffs");
        if(element != null){
            JsonArray array = element.getAsJsonArray();
            for(int i = 0; i < array.size(); i++)
                tariffs.add(TariffData.createFromJson(array.get(i).getAsJsonObject()));
        }
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        object.addProperty("duration", duration);
        JsonArray array = new JsonArray();
        for(int i = 0; i < tariffs.size(); i++)
            array.add(tariffs.get(i).toJson());
        object.add("packages", array);
        return object;
    }

    public int id;
    public int duration;
    public List <TariffData> tariffs;
}
