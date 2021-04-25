package com.vklinike.ui.profile;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.ui.socket.ClientSocket;

import java.util.Calendar;
import java.util.GregorianCalendar;


public class ProfileInformationBase extends Fragment {

    private ProfileBaseData fld_data;;
    private GlobalData.Access fld_access;

    private TextView obj_age;
    private TextView obj_email;
    private TextView obj_phone;

    public ProfileInformationBase(ProfileBaseData _data, GlobalData.Access _access)
    {
        fld_data = _data;
        fld_access = _access;
    }

    public static ProfileInformationBase newInstance(ProfileBaseData _data, GlobalData.Access _access) {
        return new ProfileInformationBase(_data, _access);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_information_base, container, false);

        obj_age = view.findViewById(R.id.profile_information_base_age);
        obj_email = view.findViewById(R.id.profile_information_base_email);
        obj_phone = view.findViewById(R.id.profile_information_base_phone);

        prepare();

        return view;
    }

    public void prepare()
    {
        reload();
        GlobalData.socket.addFixedRequest("Updated ProfileBase " + String.valueOf(fld_data.id), new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("ProfileBase");
                if(element != null) {
                    fld_data.load(element.getAsJsonObject());
                    reload();
                }
            }
        });
    }

    public void reload()
    {
        setAge(fld_data.birthday);
        setPhone(fld_data.phone);
        obj_email.setText(fld_data.email);
        setAge(fld_data.birthday);
    }

    public void setPhone(String _phone)
    {
        String result = "";
        if(_phone.length() == 7)
        {
            char [] buffer =  new char[10];
            _phone.getChars(0, 3, buffer, 0);
            buffer[3] = ' ';
            _phone.getChars(3, 5, buffer, 4);
            buffer[6] = ' ';
            _phone.getChars(5, 7, buffer, 7);
            buffer[9] = '\0';
            result = String.copyValueOf(buffer);
        }
        else if(_phone.length() >= 12)
        {
            char [] buffer =  new char[_phone.length() + 5];
            int ind = 14 - _phone.length();
            _phone.getChars(0, ind, buffer, 0);
            buffer[ind] = ' ';
            _phone.getChars(ind, ind + 3, buffer, ind + 1);
            buffer[ind + 4] = ' ';
            _phone.getChars(ind + 3, ind + 6, buffer, ind + 5);
            buffer[ind + 8] = ' ';
            _phone.getChars(ind + 6, ind + 8, buffer, ind + 9);
            buffer[ind + 11] = ' ';
            _phone.getChars(ind + 8, ind + 10, buffer, ind + 12);
            buffer[ind + 14] = '\0';
            result = String.copyValueOf(buffer);
        }
        obj_phone.setText(result);
    }

    public void setAge(Calendar _birthday)
    {
        Calendar currentTime = Calendar.getInstance();
        long msecs = currentTime.getTimeInMillis() - _birthday.getTimeInMillis();
        Calendar age = new GregorianCalendar();
        age.setTimeInMillis(msecs);
        String result = String.valueOf(age.get(Calendar.YEAR) - 1970) + " лет";
        obj_age.setText(result);
    }
}
