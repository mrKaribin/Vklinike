package com.vklinike.data;

import android.graphics.drawable.Drawable;


public class AchievementData
{
    public AchievementData() {}
    public AchievementData(Drawable _icon, String _text)
    {
        icon = _icon;
        text = _text;
    }

    public int id;
    public Drawable icon;
    public String text;
}
