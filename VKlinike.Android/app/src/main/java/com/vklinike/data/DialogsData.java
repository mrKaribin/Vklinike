package com.vklinike.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

import java.util.ArrayList;
import java.util.List;

public class DialogsData
{
    public DialogsData() {
        dialogs = new ArrayList <DialogData>();
    }

    public DialogsData(List <DialogData> _dialogs)
    {
        dialogs = _dialogs;
    }

    public void load(JsonArray array) {
        if(dialogs == null)
            dialogs = new ArrayList <DialogData>();

        dialogs.clear();
        for(int i = 0; i < array.size(); i++){
            JsonObject object = array.get(i).getAsJsonObject();
            if(object != null)
                dialogs.add(DialogData.createFromJson(object));
        }
    }

    public List<DialogData> dialogs;
}
