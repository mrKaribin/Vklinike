package com.vklinike.ui.messages;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.vklinike.ui.dialog.DialogActivity;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.data.DialogData;


public class MessagePreviewFragment extends Fragment {

    private DialogData fld_data;

    private LinearLayout obj_layout;
    private ImageView obj_avatar;
    private TextView obj_fio;
    private TextView obj_specialization;

    public MessagePreviewFragment(DialogData _data)
    {
        fld_data = _data;
    }

    public static MessagePreviewFragment newInstance(DialogData _data) {
        return new MessagePreviewFragment(_data);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_message_preview, container, false);

        obj_layout = view.findViewById(R.id.message_preview);
        obj_avatar = view.findViewById(R.id.message_preview_avatar);
        obj_fio = view.findViewById(R.id.message_preview_fio);
        obj_specialization = view.findViewById(R.id.message_preview_specialization);

        obj_layout.setOnClickListener(fnc_layout_clickListener);
        reload();

        return view;
    }

    public void reload()
    {
        obj_avatar.setImageBitmap(fld_data.companion.miniature);
        setFio(fld_data.companion.name, fld_data.companion.surname, fld_data.companion.patronymic);
        obj_specialization.setText(fld_data.specialization.name);
    }

    public void setFio(String name, String surname, String patronymic)
    {
        String result = "";
        if(GlobalData.currentMode == GlobalData.Mode.Doctor)
            result = name;
        else if(GlobalData.currentMode == GlobalData.Mode.Patient)
            result = name + " " + patronymic;
        obj_fio.setText(result);
    }

    private LinearLayout.OnClickListener fnc_layout_clickListener = new LinearLayout.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(getActivity(), DialogActivity.class);
            DialogActivity.new_data = fld_data;
            startActivity(intent);
        }
    };
}
