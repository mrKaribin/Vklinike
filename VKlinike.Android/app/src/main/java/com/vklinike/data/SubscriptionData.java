package com.vklinike.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import java.util.ArrayList;
import java.util.List;


public class SubscriptionData
{
    public SubscriptionData() {
        packages = new ArrayList<PackageData>();
        specialization = new SpecializationData();
    }
    public SubscriptionData(SpecializationData _specialization, List  <PackageData> _packages)
    {
        specialization = _specialization;
        packages = _packages;
    }

    public static SubscriptionData createFromJson(JsonObject object)
    {
        SubscriptionData subscription = new SubscriptionData();
        subscription.load(object);
        return subscription;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("specialization");
        if(element != null)
            specialization = SpecializationData.createFromJson(element.getAsJsonObject());

        element = object.get("packages");
        if(element != null){
            JsonArray array = element.getAsJsonArray();
            for(int i = 0; i < array.size(); i++)
                packages.add(PackageData.createFromJson(array.get(i).getAsJsonObject()));
        }
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.add("specialization", specialization.toJson());
        JsonArray array = new JsonArray();
        for(int i = 0; i < packages.size(); i++)
            array.add(packages.get(i).toJson());
        object.add("packages", array);
        return object;
    }

    public SpecializationData specialization;
    public List <PackageData> packages;
}
