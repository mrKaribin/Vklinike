package com.vklinike.ui;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.vklinike.R;


public class EmptyFragment extends Fragment {

    private String field_text;

    private TextView widget_text;

    public EmptyFragment(String _text){
        field_text = _text;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view =  inflater.inflate(R.layout.fragment_empty, container, false);

        widget_text = view.findViewById(R.id.empty_text);

        widget_text.setText(field_text);

        return view;
    }
}
