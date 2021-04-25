package com.vklinike.ui.profile.patient;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.vklinike.GlobalData;
import com.vklinike.GlobalData.Access;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.ProfilePatientData;
import com.vklinike.ui.EmptyFragment;
import com.vklinike.ui.profile.ProfileBaseEditFragment;
import com.vklinike.ui.profile.ProfileInformationBase;

import java.util.Calendar;


public class ProfilePatientFragment extends Fragment {

    private ProfileBaseData fld_data_base;
    private ProfilePatientData fld_data_patient;
    private Access fld_access;

    private ImageView obj_avatar;
    private TextView obj_header_name;
    private TextView obj_header_surname;
    private TextView obj_header_patronymic;
    private Button obj_edit;

    public ProfilePatientFragment(ProfileBaseData _data_base, ProfilePatientData _data_patient, Access _access)
    {
        fld_data_base = _data_base;
        fld_data_patient = _data_patient;
        fld_access = _access;
    }

    public static ProfilePatientFragment newInstance(ProfileBaseData _data_base, ProfilePatientData _data_patient, Access _access) {
        return new ProfilePatientFragment(_data_base, _data_patient, _access);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_patient, container, false);

        obj_avatar = view.findViewById(R.id.profile_patient_header_image);
        obj_header_name = view.findViewById(R.id.profile_patient_header_name);
        obj_header_surname = view.findViewById(R.id.profile_patient_header_surname);
        obj_header_patronymic = view.findViewById(R.id.profile_patient_header_patronymic);
        obj_edit = view.findViewById(R.id.profile_patient_edit);

        obj_edit.setOnClickListener(function_edit_clickListener);
        reload();

        return view;
    }

    public void reload()
    {
        obj_avatar.setImageBitmap(fld_data_base.miniature);
        setFio(fld_data_base.name, fld_data_base.surname, fld_data_base.patronymic);
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();

        Calendar currentDate = Calendar.getInstance();
        int age = currentDate.get(Calendar.YEAR) - GlobalData.currentProfileBase.birthday.get(Calendar.YEAR);
        ProfileInformationBase new_information = new ProfileInformationBase(fld_data_base, fld_access);
        transaction.replace(R.id.layout_profile_patient, new_information);
        for(int i =  0; i < fld_data_patient.subscriptions.size(); i++)
        {
            ProfilePatientSubscriptionPreview new_preview = ProfilePatientSubscriptionPreview.newInstance(fld_data_patient.subscriptions.get(i));
            transaction.add(R.id.layout_profile_patient, new_preview);
        }
        if(fld_data_patient.subscriptions.isEmpty())
            transaction.replace(R.id.layout_profile_patient, new EmptyFragment("У вас еще нет подписок"));
        transaction.commit();
    }

    public void setFio(String name, String surname, String patronymic)
    {
        obj_header_name.setText(name);
        obj_header_surname.setText(surname);
        obj_header_patronymic.setText(patronymic);
    }

    private Button.OnClickListener function_edit_clickListener = new Button.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(getActivity(), ViewerActivity.class);
            ViewerActivity.currentFragment = new ProfileBaseEditFragment();
            startActivity(intent);
        }
    };
}
