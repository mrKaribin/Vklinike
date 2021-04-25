package com.vklinike.ui.profile.doctor;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import com.vklinike.R;


public class ProfileSubscriptionAddFragment extends Fragment {
    private int field_width;
    private int field_height;
    private int margins;
    private FrameLayout.OnClickListener field_clickListener;

    private FrameLayout widget_layout;

    public ProfileSubscriptionAddFragment(FrameLayout.OnClickListener _listener, int _width, int _height, int _margins)
    {
        field_width = _width;
        field_height = _height;
        margins = _margins;
        field_clickListener = _listener;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_subscription_add, container, false);

        widget_layout = view.findViewById(R.id.profile_subscription_add);
        resize(field_width, field_height);
        widget_layout.setOnClickListener(field_clickListener);

        return view;
    }

    void resize(int width, int height)
    {
        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(width, height);
        if(margins != 0) {
            if (width == ViewGroup.LayoutParams.MATCH_PARENT)
                params.setMargins(margins, margins, margins, 0);
            else if (height == ViewGroup.LayoutParams.MATCH_PARENT)
                params.setMargins(margins, margins, 0, margins);
        }
        widget_layout.setLayoutParams(params);
    }
}
