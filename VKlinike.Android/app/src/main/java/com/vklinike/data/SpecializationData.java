package com.vklinike.data;


import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

public class SpecializationData
{
    public SpecializationData() {}
    public SpecializationData(String _name, String _info)
    {
        name = _name;
        info = _info;
    }

    public static SpecializationData createFromJson(JsonObject object)
    {
        SpecializationData specialization = new SpecializationData();
        specialization.load(object);
        return specialization;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("id");
        if(element != null)
            id = element.getAsInt();

        element = object.get("name");
        if(element != null)
            name = element.getAsString();

        /*
        element = object.get("information");
        if(element != null)
            info = element.getAsString();

         */
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        object.addProperty("name", name);
        //object.addProperty("information", info);
        return object;
    }

    public int id = 0;
    public String name;
    public String info;
}
