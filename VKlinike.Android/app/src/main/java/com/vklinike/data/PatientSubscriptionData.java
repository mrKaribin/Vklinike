package com.vklinike.data;


import android.graphics.drawable.GradientDrawable;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.GlobalData;
import com.vklinike.ui.profile.ProfileInformationBase;

import java.util.Calendar;
import java.util.GregorianCalendar;


public class PatientSubscriptionData
{
    public PatientSubscriptionData()
    {
        specialization = new SpecializationData();
        package_id = -1;
        tariff_id = -1;
        doctor = new ProfileBaseData();
        start_time = new GregorianCalendar();
        finish_time = new GregorianCalendar();
    }

    public PatientSubscriptionData(ProfileBaseData _doctor, Calendar _start_time, Calendar _finish_time, String _specialization_name, int _duration, int _cost, ValutaData _valuta, int _time)
    {
        doctor = _doctor;
        start_time = _start_time;
        finish_time = _finish_time;
        specialization = new SpecializationData();
        specialization.name = _specialization_name;
        duration = _duration;
        cost = _cost;
        valuta = _valuta;
        time = _time;
    }

    public PatientSubscriptionData(ProfileBaseData _doctor, SpecializationData _specialization, PackageData _package, TariffData _tariff)
    {
        doctor = _doctor;
        start_time = Calendar.getInstance();
        finish_time = new GregorianCalendar();
        finish_time.setTimeInMillis(start_time.getTimeInMillis() + _package.duration * 60 * 60 * 1000);
        specialization = new SpecializationData();
        specialization.name = _specialization.name;
        duration = _package.duration;
        cost = _tariff.cost;
        valuta = _tariff.valuta;
        time = _tariff.time;
    }

    public static PatientSubscriptionData createFromJson(JsonObject object)
    {
        PatientSubscriptionData subscription = new PatientSubscriptionData();
        subscription.load(object);
        return subscription;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("id");
        if(element != null)
            id = element.getAsInt();

        element = object.get("doctor");
        if(element != null)
            doctor = ProfileBaseData.createFromJson(element.getAsJsonObject());

        element = object.get("timepoint_begin");
        if(element != null)
            start_time = new Timepoint(element.getAsJsonObject()).toCalendar();

        element = object.get("timepoint_end");
        if(element != null)
            finish_time = new Timepoint(element.getAsJsonObject()).toCalendar();

        element = object.get("specialization");
        if(element != null)
            specialization = SpecializationData.createFromJson(element.getAsJsonObject());

        element = object.get("package_id");
        if(element != null)
            package_id = element.getAsInt();

        element = object.get("duration");
        if(element != null)
            duration = element.getAsInt();

        element = object.get("tariff_id");
        if(element != null)
            tariff_id = element.getAsInt();

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
        object.add("doctor", doctor.toJson());
        object.add("timepoint_begin", new Timepoint(start_time).toJson());
        object.add("education", new Timepoint(finish_time).toJson());
        object.add("education", specialization.toJson());
        object.addProperty("package_id", package_id);
        object.addProperty("duration", duration);
        object.addProperty("tariff_id", tariff_id);
        object.addProperty("cost", cost);
        object.add("valuta", valuta.toJson());
        object.addProperty("time", time);
        return object;
    }

    public int id = -1;
    public ProfileBaseData doctor;
    public Calendar start_time;
    public Calendar finish_time;
    public SpecializationData specialization;
    public int package_id = -1;
    public int duration;
    public int tariff_id = -1;
    public int cost;
    public ValutaData valuta;
    public int time;
}
