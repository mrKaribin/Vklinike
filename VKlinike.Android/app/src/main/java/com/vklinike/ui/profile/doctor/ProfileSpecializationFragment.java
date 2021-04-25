package com.vklinike.ui.profile.doctor;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.PatientSubscriptionData;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.SubscriptionData;
import com.vklinike.ui.order.OrderFragment;
import com.vklinike.ui.profile.doctor.ProfilePackageFragment;
import com.vklinike.ui.socket.ClientSocket;


public class ProfileSpecializationFragment extends Fragment {

    private SubscriptionData fld_data;
    private ProfileBaseData fld_profile;
    private int fld_layout_id;
    private GlobalData.Access fld_access;

    private TextView obj_name;

    public ProfileSpecializationFragment(SubscriptionData _data, ProfileBaseData _profile, GlobalData.Access _access)
    {
        fld_data = _data;
        fld_profile = _profile;
        fld_access = _access;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_specialization, container, false);

        obj_name = view.findViewById(R.id.subscription_specialization_name);
        fld_layout_id = View.generateViewId();
        view.findViewById(R.id.layout_packages).setId(fld_layout_id);

        reload();

        return view;
    }

    public void reload()
    {
        obj_name.setText(fld_data.specialization.name);

        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        for(int i = 0; i < fld_data.packages.size(); i++)
        {
            ProfilePackageFragment new_package = new ProfilePackageFragment(fld_data.packages.get(i), this, fld_access);
            if(i == 0)
                transaction.replace(fld_layout_id, new_package);
            else
                transaction.add(fld_layout_id, new_package);
        }
        transaction.commit();
    }

    public void tariffChanged(PatientSubscriptionData subscription)
    {
        subscription.doctor = fld_profile;
        subscription.specialization.name = fld_data.specialization.name;
        subscription.specialization.id = fld_data.specialization.id;
        Intent intent = new Intent(getActivity(), ViewerActivity.class);
        ViewerActivity.currentFragment = new OrderFragment(subscription);
        startActivity(intent);
    }

    public SubscriptionData getData(){
        return fld_data;
    }

    public FrameLayout.OnClickListener function_add_clickListener = new FrameLayout.OnClickListener() {
        @Override
        public void onClick(View view) {

        }
    };
}
