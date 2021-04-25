package com.vklinike.data;


import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.GlobalData;

public class TariffData
{
    public TariffData()
    {
        valuta = new ValutaData("Рубли", "руб", "Р");
    }

    public TariffData(int _cost, ValutaData _valuta, int _consultationTime)
    {
        cost = _cost;
        valuta = _valuta;
        time = _consultationTime;
    }

    public static TariffData createFromJson(JsonObject object)
    {
        TariffData tariff = new TariffData();
        tariff.load(object);
        return tariff;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("id");
        if(element != null)
            id = element.getAsInt();

        element = object.get("package_id");
        if(element != null)
            package_id = element.getAsInt();

        element = object.get("cost");
        if(element != null)
            cost = element.getAsInt();

        element = object.get("valuta");
        if(element != null){
            String valuta_abbreviation = element.getAsString();
            for(int i = 0; i < GlobalData.availableValutes.size(); i++){
                if(GlobalData.availableValutes.get(i).abbreviation == valuta_abbreviation)
                    valuta = GlobalData.availableValutes.get(i);
            }
        }

        element = object.get("time");
        if(element != null)
            time = element.getAsInt();
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        object.addProperty("package_id", package_id);
        object.addProperty("cost", cost);
        object.addProperty("valuta", valuta.abbreviation);
        object.addProperty("time", time);
        return object;
    }

    public int id = -1;
    public int package_id = -1;
    public int cost;
    public ValutaData valuta;
    public int time;
}
