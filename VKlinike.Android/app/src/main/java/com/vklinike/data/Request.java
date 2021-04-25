package com.vklinike.data;

import com.google.gson.JsonObject;


public class Request
{
    public Request(String _header)
    {
        header = _header;
        body = new JsonObject();
    }

    public Request(JsonObject request)
    {
        header = request.get("header").getAsString();
        body = request.get("body").getAsJsonObject();
    }

    public String header;
    public JsonObject body;
}
