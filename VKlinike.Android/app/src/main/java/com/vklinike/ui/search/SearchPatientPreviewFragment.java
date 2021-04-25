package com.vklinike.ui.search;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.ProfileDoctorData;
import com.vklinike.data.ProfilePatientData;
import com.vklinike.data.SpecializationData;
import com.vklinike.ui.profile.doctor.ProfileDoctorFragment;
import com.vklinike.ui.profile.patient.ProfilePatientFragment;

import java.util.List;


public class SearchPatientPreviewFragment extends Fragment {

    private ProfileBaseData field_data;
    private double field_rating;
    private List<SpecializationData> field_specializations;

    private LinearLayout widget_preview;
    private ImageView widget_avatar;
    private TextView widget_fio;
    private TextView widget_rating;
    private TextView widget_specialization;

    public SearchPatientPreviewFragment(ProfileBaseData _data, List<SpecializationData> _specializations, double _rating)
    {
        field_data = _data;
        field_specializations = _specializations;
        field_rating = _rating;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        final View view = inflater.inflate(R.layout.fragment_search_patient_preview, container, false);

        widget_preview = view.findViewById(R.id.search_preview);
        widget_avatar = view.findViewById(R.id.search_preview_avatar);
        widget_fio = view.findViewById(R.id.search_preview_fio);
        widget_rating = view.findViewById(R.id.search_preview_rating);
        widget_specialization = view.findViewById(R.id.search_preview_specialization);

        widget_preview.setOnClickListener(funtion_preview_clickListener);
        reload();

        return view;
    }

    public void reload()
    {
        widget_avatar.setImageBitmap(field_data.miniature);
        setFio(field_data.name, field_data.surname, field_data.patronymic);
        widget_rating.setText(String.valueOf(field_rating));
        setSpecializations(field_specializations);
    }

    public void setFio(String name, String surname, String patronymic)
    {
        String result;
        result = surname + " " + name + " " + patronymic;
        widget_fio.setText(result);
    }

    public void setSpecializations(List<SpecializationData> _specializations)
    {
        String result = "";
        for(int i = 0; i <_specializations.size(); i++)
        {
            if(i > 0)
                result += ", ";
            result += _specializations.get(i).name;
        }
        widget_specialization.setText(result);
    }

    private ImageView.OnClickListener funtion_preview_clickListener = new ImageView.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(getActivity(), ViewerActivity.class);
            if(GlobalData.currentMode == GlobalData.Mode.Patient)
                ViewerActivity.currentFragment = new ProfileDoctorFragment(field_data, new ProfileDoctorData(), GlobalData.Access.Guest);
            if(GlobalData.currentMode == GlobalData.Mode.Doctor)
                ViewerActivity.currentFragment = new ProfilePatientFragment(field_data, new ProfilePatientData(), GlobalData.Access.Guest);
            startActivity(intent);
        }
    };
}
