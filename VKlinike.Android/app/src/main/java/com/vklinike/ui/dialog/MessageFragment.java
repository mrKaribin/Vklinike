package com.vklinike.ui.dialog;

import android.graphics.BitmapFactory;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.text.format.DateFormat;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.vklinike.R;
import com.vklinike.data.MessageData;

import java.util.Calendar;


public class MessageFragment extends Fragment {

    public enum Type {Input, Output};

    private Type field_type;
    private MessageData field_data;

    private LinearLayout layout_enclosure;

    private TextView widget_text;
    private TextView widget_time;
    private ImageView widget_status;

    public MessageFragment(Type _type, MessageData _data){
        field_type = _type;
        field_data = _data;
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view;
        if(field_type == Type.Input)
            view = inflater.inflate(R.layout.fragment_message_input, container, false);
        else if(field_type == Type.Output)
            view = inflater.inflate(R.layout.fragment_message_output, container, false);
        else
            view = inflater.inflate(R.layout.fragment_message_output, container, false);

        layout_enclosure = view.findViewById(R.id.layout_message_enclosure);
        widget_text = view.findViewById(R.id.message_text);
        widget_status = view.findViewById(R.id.message_status);
        widget_time = view.findViewById(R.id.message_timepoint);

        layout_enclosure.setId(View.generateViewId());
        reload();

        return view;
    }

    public void reload(){
        widget_text.setText(field_data.message);
        setDate(field_data.timepoint);
        if(field_data.attachment_type.equals("jpg")){
            FragmentManager manager = getActivity().getSupportFragmentManager();
            FragmentTransaction transaction = manager.beginTransaction();
            transaction.replace(
                    layout_enclosure.getId(),
                    (field_data.attachment_data.length < 2)
                            ? new MessageEnclosureImageFragment(field_data.attachment_name)
                            : new MessageEnclosureImageFragment(field_data.attachment_name, BitmapFactory.decodeByteArray(field_data.attachment_data, 0, field_data.attachment_data.length))
            );
            transaction.commit();
        }
    }

    public void setDate(Calendar timepoint){
        String result = DateFormat.format("yyyy.MM.dd", timepoint.getTime()).toString();
        widget_time.setText(result);
    }

    public void setEnclosureImage(String enclosure_name){

    }
}
