package com.vklinike.data;

import com.google.gson.JsonObject;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class Timepoint
{
    private Calendar field_timepoint;

    public Timepoint(Calendar _timepoint)
    {
        field_timepoint = _timepoint;
    }

    public Timepoint(JsonObject _timepoint)
    {
        int year = _timepoint.get("year").getAsInt();
        int month = _timepoint.get("month").getAsInt();
        int day = _timepoint.get("day").getAsInt();
        int hour = _timepoint.get("hour").getAsInt();
        int minute = _timepoint.get("minute").getAsInt();
        int second = _timepoint.get("second").getAsInt();
        field_timepoint = new GregorianCalendar(year, month, day, hour, minute, second);
    }

    public JsonObject toJson()
    {
        JsonObject json = new JsonObject();
        json.addProperty("year", field_timepoint.get(Calendar.YEAR));
        json.addProperty("month", field_timepoint.get(Calendar.MONTH));
        json.addProperty("day", field_timepoint.get(Calendar.DAY_OF_MONTH));
        json.addProperty("hour", field_timepoint.get(Calendar.HOUR_OF_DAY));
        json.addProperty("minute", field_timepoint.get(Calendar.MINUTE));
        json.addProperty("second", field_timepoint.get(Calendar.SECOND));
        return json;
    }

    public Calendar toCalendar()
    {
        return field_timepoint;
    }
}
