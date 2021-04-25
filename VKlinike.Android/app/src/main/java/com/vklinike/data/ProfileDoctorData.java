package com.vklinike.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;


public class ProfileDoctorData
{
    public ProfileDoctorData()
    {
        workTime_begin = new GregorianCalendar(0,0,0,0,0,0);
        workTime_end = new GregorianCalendar(0,0,0,0,0,0);
        achievements = new ArrayList<AchievementData>();
        subscriptions = new ArrayList<SubscriptionData>();
        comments = new ArrayList<CommentData>();
    }

    public ProfileDoctorData (String _education, String _job, Calendar _workTime_begin, Calendar _workTime_end, int _replyInterval, List <AchievementData> _achievements, List <SubscriptionData> _subscriptions, List <CommentData> _comments)
    {
        education = _education;
        job = _job;
        workTime_begin = _workTime_begin;
        workTime_end = _workTime_end;
        replyInterval = _replyInterval;
        achievements = _achievements;
        subscriptions = _subscriptions;
        comments = _comments;
    }

    public static ProfileDoctorData createFromJson(JsonObject object)
    {
        ProfileDoctorData doctor = new ProfileDoctorData();
        doctor.load(object);
        return doctor;
    }

    public void load(JsonObject object)
    {
        JsonElement element;
        element = object.get("id");
        if(element != null)
            id = element.getAsInt();

        element = object.get("user_id");
        if(element != null)
            user_id = element.getAsInt();

        element = object.get("education");
        if(element != null)
            education = element.getAsString();

        element = object.get("job");
        if(element != null)
            job = element.getAsString();

        element = object.get("replyInterval");
        if(element != null)
            replyInterval = element.getAsInt();

        element = object.get("workTime_begin");
        if(element != null)
            workTime_begin = new Timepoint(element.getAsJsonObject()).toCalendar();

        element = object.get("workTime_end");
        if(element != null)
            workTime_end = new Timepoint(element.getAsJsonObject()).toCalendar();
    }

    public void loadSubscriptions(JsonArray array)
    {
        if(subscriptions == null)
            subscriptions = new ArrayList<SubscriptionData>();

        subscriptions.clear();
        for(int i = 0; i < array.size(); i++){
            JsonObject object = array.get(i).getAsJsonObject();
            if(object != null)
                subscriptions.add(SubscriptionData.createFromJson(object));
        }
    }

    public void loadComments(JsonArray array)
    {
        if(comments == null)
            comments = new ArrayList<CommentData>();

        comments.clear();
        for(int i = 0; i < array.size(); i++){
            JsonObject object = array.get(i).getAsJsonObject();
            if(object != null)
                comments.add(CommentData.createFromJson(object));
        }
    }

    public JsonObject toJson()
    {
        JsonObject object = new JsonObject();
        object.addProperty("id", id);
        object.addProperty("user_id", user_id);
        object.addProperty("education", education);
        object.addProperty("job", job);
        object.addProperty("replyInterval", replyInterval);
        object.add("workTime_begin", new Timepoint(workTime_begin).toJson());
        object.add("workTime_end", new Timepoint(workTime_end).toJson());
        return object;
    }

    public int id = -1;
    public int user_id = -1;
    public String education;
    public String job;
    public Calendar workTime_begin;
    public Calendar workTime_end;
    public int replyInterval;
    public List <AchievementData> achievements;
    public List <SubscriptionData> subscriptions;
    public List <CommentData> comments;
}
