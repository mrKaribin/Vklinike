package com.vklinike.ui.profile.doctor;

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
import com.vklinike.data.ProfileDoctorData;
import com.vklinike.ui.socket.ClientSocket;

import java.util.Calendar;


public class ProfileInformationDoctor extends Fragment {

    private ProfileDoctorData fld_data;
    private GlobalData.Access fld_access;

    private TextView obj_workTime;
    private TextView obj_replyTime;
    private TextView obj_education;
    private TextView obj_job;

    public ProfileInformationDoctor(ProfileDoctorData _data, GlobalData.Access _access)
    {
        fld_data = _data;
        fld_access = _access;
    }

    public static ProfileInformationDoctor newInstance(ProfileDoctorData _data, GlobalData.Access _access) {
        return new ProfileInformationDoctor(_data, _access);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_information_doctor, container, false);

        obj_workTime = view.findViewById(R.id.profile_information_doctor_workTime);
        obj_replyTime = view.findViewById(R.id.profile_information_doctor_replyTime);
        obj_education = view.findViewById(R.id.profile_information_doctor_education);
        obj_job = view.findViewById(R.id.profile_information_doctor_job);

        prepare();

        return view;
    }

    public void prepare(){
        reload();

        GlobalData.socket.addFixedRequest("Updated ProfileDoctor " + String.valueOf(fld_data.id), new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("ProfileDoctor");
                if(element != null) {
                    fld_data.load(element.getAsJsonObject());
                    reload();
                }
                else{
                }
            }
        });
    }

    void reload()
    {
        setTimetable(fld_data.workTime_begin, fld_data.workTime_end);
        setReplyTime(fld_data.replyInterval);
        setEducation(fld_data.education);
        setJob(fld_data.job);
    }

    public void setTimetable(Calendar work_start, Calendar work_finish)
    {
        String result = "";
        result += "С " + String.valueOf(work_start.get(Calendar.HOUR_OF_DAY)) + ":" + String.valueOf(work_start.get(Calendar.MINUTE));
        result += " до " + String.valueOf(work_finish.get(Calendar.HOUR_OF_DAY) + ":" + String.valueOf(work_finish.get(Calendar.MINUTE)));
        obj_workTime.setText(result);
    }

    public void setReplyTime(int seconds)
    {
        String result = String.valueOf(seconds) + " секунд";
        obj_replyTime.setText(result);
    }

    public void setEducation(String _education)
    {
        obj_education.setText(_education);
    }

    public void setJob(String _job)
    {
        obj_job.setText(_job);
    }
}
