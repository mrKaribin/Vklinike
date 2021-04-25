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
import android.widget.ImageView;
import android.widget.TextView;

import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.PackageData;
import com.vklinike.data.PatientSubscriptionData;


public class ProfilePackageFragment extends Fragment {

    private PackageData fld_data;
    private int fld_layout_id;
    private GlobalData.Access fld_access;

    private ProfileSpecializationFragment obj_parent;
    private ImageView obj_type_icon;
    private TextView obj_type_name;

    public ProfilePackageFragment(PackageData _data, ProfileSpecializationFragment _parent, GlobalData.Access _access)
    {
        fld_data = _data;
        obj_parent = _parent;
        fld_access = _access;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_package, container, false);

        obj_type_name = view.findViewById(R.id.subscription_package_type_name);
        obj_type_icon = view.findViewById(R.id.subscription_package_type_icon);
        fld_layout_id = View.generateViewId();
        view.findViewById(R.id.layout_tariffs).setId(fld_layout_id);

        reload();

        return view;
    }

    void reload()
    {
        setType(fld_data.duration);

        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        for(int i = 0; i < fld_data.tariffs.size(); i++)
        {
            ProfileTariffFragment new_tariff = new ProfileTariffFragment(fld_data.tariffs.get(i), this, fld_access);
            if(i == 0)
                transaction.replace(fld_layout_id, new_tariff);
            else
                transaction.add(fld_layout_id, new_tariff);
        }
        if(fld_access == GlobalData.Access.Owner) {
            ProfileSubscriptionAddFragment widget_add = new ProfileSubscriptionAddFragment(
                    function_add_clickListener,
                    (int) getResources().getDimension(R.dimen.profile_subscription_add_thickness),
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    (int) getResources().getDimension(R.dimen.margin_small)
            );
            if(fld_data.tariffs.isEmpty())
                transaction.replace(fld_layout_id, widget_add);
            else
                transaction.add(fld_layout_id, widget_add);
        }
        transaction.commit();
    }

    public void setType(int _duration)
    {
        switch (_duration) {
            case 24:
                obj_type_icon.setImageDrawable(getResources().getDrawable(R.drawable.icon_subscription_daily));
                obj_type_name.setText("Дневная");
                break;
            case 168:
                obj_type_icon.setImageDrawable(getResources().getDrawable(R.drawable.icon_subscription_weekly));
                obj_type_name.setText("Недельная");
                break;
            case 744:
                obj_type_icon.setImageDrawable(getResources().getDrawable(R.drawable.icon_subscription_monthly));
                obj_type_name.setText("Месячная");
                break;
        }
    }

    public void tariffChanged(PatientSubscriptionData subscription)
    {
        subscription.package_id = fld_data.id;
        subscription.duration = fld_data.duration;
        obj_parent.tariffChanged(subscription);
    }

    public ProfileSpecializationFragment getParent(){
        return obj_parent;
    }

    public PackageData getData(){
        return fld_data;
    }

    public FrameLayout.OnClickListener function_add_clickListener = new FrameLayout.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(getActivity(), ViewerActivity.class);
            PatientSubscriptionData data = new PatientSubscriptionData();
            data.specialization = obj_parent.getData().specialization;
            data.package_id = fld_data.id;
            data.duration = fld_data.duration;
            ViewerActivity.currentFragment = new ProfileSubscriptionEditFragment(data);
            startActivity(intent);
        }
    };
}
