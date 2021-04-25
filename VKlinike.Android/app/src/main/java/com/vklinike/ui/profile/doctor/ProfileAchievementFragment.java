package com.vklinike.ui.profile.doctor;

import android.graphics.drawable.Drawable;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.vklinike.R;


public class ProfileAchievementFragment extends Fragment {

    private Drawable fld_icon;
    private String fld_text;

    private ImageView obj_icon;
    private TextView obj_text;

    public ProfileAchievementFragment(Drawable _icon, String _text)
    {
        fld_icon = _icon;
        fld_text = _text;
    }

    public static ProfileAchievementFragment newInstance(Drawable _icon, String _text) {
        return new ProfileAchievementFragment(_icon, _text);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_achievement, container, false);
        obj_icon = view.findViewById(R.id.profile_achievement_icon);
        obj_text = view.findViewById(R.id.profile_achievement_text);
        setIcon(fld_icon);
        setText(fld_text);
        return view;
    }

    public void setIcon(Drawable _icon)
    {
        obj_icon.setImageDrawable(_icon);
    }

    public void setText(String _text)
    {
        obj_text.setText(_text);
    }
}
