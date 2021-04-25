package com.vklinike.data;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

public class ValutaData
{
    public ValutaData() {}

    public ValutaData(String _name, String _abbreviation, String _symbol)
    {
        name = _name;
        abbreviation = _abbreviation;
        symbol = _symbol;
    }

    public static ValutaData createFromJson(JsonObject object)
    {
        ValutaData valuta = new ValutaData();
        valuta.load(object);
        return valuta;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("name");
        if(element != null)
            name = element.getAsString();

        element = object.get("abbreviation");
        if(element != null)
            abbreviation = element.getAsString();

        element = object.get("symbol");
        if(element != null)
            symbol = element.getAsString();
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("name", name);
        object.addProperty("abbreviation", abbreviation);
        object.addProperty("symbol", symbol);
        return object;
    }

    public String name = "";
    public String abbreviation = "";
    public String symbol = "";
}
