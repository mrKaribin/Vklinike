package com.vklinike.ui.profile.doctor;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.PatientSubscriptionData;
import com.vklinike.data.TariffData;
import com.vklinike.data.ValutaData;
import com.vklinike.ui.profile.doctor.ProfilePackageFragment;
import com.vklinike.ui.profile.doctor.ProfileSubscriptionEditFragment;


public class ProfileTariffFragment extends Fragment {

    private TariffData fld_data;
    private GlobalData.Access field_access = GlobalData.Access.Owner;

    private ProfilePackageFragment obj_parent;
    private LinearLayout obj_tariff;
    private TextView obj_cost;
    private TextView obj_time;

    public ProfileTariffFragment(TariffData _data, ProfilePackageFragment _parent, GlobalData.Access _access)
    {
        fld_data = _data;
        obj_parent = _parent;
        field_access = _access;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_tariff, container, false);

        obj_tariff = view.findViewById(R.id.subscription_tariff);
        obj_cost = view.findViewById(R.id.subscription_tariff_cost);
        obj_time = view.findViewById(R.id.subscription_tariff_time);

        obj_tariff.setOnClickListener(function_tariff_clickListener);
        reload();

        return view;
    }

    public void reload()
    {
        setCost(fld_data.cost, fld_data.valuta);
        setTime(fld_data.time);
    }

    public void setCost(int _cost, ValutaData _valuta)
    {
        String result;
        String val = _valuta.abbreviation;
        result = String.valueOf(_cost) + val;
        obj_cost.setText(result);
    }

    public void setTime(int seconds)
    {
        String result = String.valueOf(seconds) + " c.";
        obj_time.setText(result);
    }

    private LinearLayout.OnClickListener function_tariff_clickListener = new LinearLayout.OnClickListener() {
        @Override
        public void onClick(View view) {
            if(field_access != GlobalData.Access.Owner) {
                PatientSubscriptionData subscription = new PatientSubscriptionData();
                subscription.cost = fld_data.cost;
                subscription.valuta = fld_data.valuta;
                subscription.time = fld_data.time;
                subscription.tariff_id = fld_data.id;
                obj_parent.tariffChanged(subscription);
            }
            else{
                Intent intent = new Intent(getActivity(), ViewerActivity.class);
                PatientSubscriptionData data = new PatientSubscriptionData();
                data.specialization = obj_parent.getParent().getData().specialization;
                data.package_id = obj_parent.getData().id;
                data.duration = obj_parent.getData().duration;
                data.tariff_id = fld_data.id;
                data.cost = fld_data.cost;
                data.valuta = fld_data.valuta;
                data.time = fld_data.time;
                ViewerActivity.currentFragment = new ProfileSubscriptionEditFragment(data);
                startActivity(intent);
            }
        }
    };
}
