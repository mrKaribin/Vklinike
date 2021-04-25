package com.vklinike.data;


import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import java.util.ArrayList;
import java.util.List;


public class ProfilePatientData
{
    public ProfilePatientData()
    {
        subscriptions = new ArrayList<PatientSubscriptionData>();
    }

    public ProfilePatientData(List <PatientSubscriptionData> _subscriptions)
    {
        subscriptions = _subscriptions;
    }

    public static ProfilePatientData createFromJson(JsonObject object)
    {
        ProfilePatientData patient = new ProfilePatientData();
        patient.load(object);
        return patient;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("id");
        if(element != null)
            id = element.getAsInt();
    }

    public void loadSubscriptions(JsonArray array)
    {
        if(subscriptions == null)
            subscriptions = new ArrayList<PatientSubscriptionData>();

        subscriptions.clear();
        for(int i = 0; i < array.size(); i++)
            subscriptions.add(PatientSubscriptionData.createFromJson(array.get(i).getAsJsonObject()));
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        return object;
    }

    public int id;
    public List <PatientSubscriptionData> subscriptions;
}
