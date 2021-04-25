package com.vklinike.ui.profile.doctor;

import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.HorizontalScrollView;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.google.android.material.tabs.TabLayout;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.ui.dialog.DialogActivity;
import com.vklinike.data.DialogData;
import com.vklinike.ui.EmptyFragment;
import com.vklinike.ui.NotificationDialogFragment;
import com.vklinike.ui.profile.ProfileBaseEditFragment;
import com.vklinike.ui.profile.ProfileInformationBase;
import com.vklinike.ui.socket.ClientSocket;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.AchievementData;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.ProfileDoctorData;
import com.vklinike.data.Request;

import java.util.List;

public class ProfileDoctorFragment extends Fragment {

    private GlobalData.Access fld_access;
    private ProfileBaseData fld_data_base;
    private ProfileDoctorData fld_data_doctor;

    private ImageView obj_avatar;
    private TextView obj_header_name;
    private TextView obj_header_surname;
    private TextView obj_header_patronymic;
    private HorizontalScrollView obj_achievements;
    private TabLayout obj_menu;
    private Button obj_edit;
    private Button obj_dialog;

    public ProfileDoctorFragment(ProfileBaseData _data_base, ProfileDoctorData _data_doctor, GlobalData.Access _access)
    {
        fld_data_base = _data_base;
        fld_data_doctor = _data_doctor;
        fld_access = _access;
    }

    public static ProfileDoctorFragment newInstance(ProfileBaseData _data_base, ProfileDoctorData _data_doctor, GlobalData.Access _access) {
        return new ProfileDoctorFragment(_data_base, _data_doctor, _access);
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_doctor, container, false);

        obj_avatar = view.findViewById(R.id.profile_doctor_header_image);
        obj_menu = view.findViewById(R.id.profile_doctor_menu);
        obj_header_name = view.findViewById(R.id.profile_doctor_header_name);
        obj_header_surname = view.findViewById(R.id.profile_doctor_header_surname);
        obj_header_patronymic = view.findViewById(R.id.profile_doctor_header_patronymic);
        obj_achievements = view.findViewById(R.id.profile_doctor_achievements);
        obj_edit = view.findViewById(R.id.profile_doctor_edit);
        obj_dialog = view.findViewById(R.id.profile_doctor_dialog);

        TabLayout.Tab tab = obj_menu.newTab();
        tab.setText("Информация");
        obj_menu.addTab(tab);
        tab = obj_menu.newTab();
        tab.setText("Подписки");
        obj_menu.addTab(tab);
        tab = obj_menu.newTab();
        tab.setText("Отзывы");
        obj_menu.addTab(tab);
        obj_menu.addOnTabSelectedListener(interface_menu);
        openInformation();

        if(fld_access != GlobalData.Access.Owner) {
            obj_edit.setVisibility(View.INVISIBLE);
        }

        if(fld_access.toInt() == GlobalData.Access.Owner.toInt()) {
            obj_dialog.setVisibility(Button.INVISIBLE);
        }

        obj_edit.setOnClickListener(interface_edit);
        obj_dialog.setOnClickListener(interface_dialogCreate);

        prepare();

        return view;
    }

    public void prepare(){
        reload();

        if(fld_access != GlobalData.Access.Owner){
            Request request = new Request("Get ProfileDoctor");
            request.body.addProperty("mode", fld_access.toInt());
            request.body.addProperty("login", fld_data_base.email);
            GlobalData.socket.addExpectedRequest("Reply Get ProfileDoctor", new ClientSocket.OnMessageReceived() {
                @Override
                public void received(JsonObject body) {
                    JsonElement element = body.get("status");
                    if(element != null) {
                        if (element.getAsString().equals("successful")) {
                            element = body.get("ProfileDoctor");
                            if (element != null)
                                fld_data_doctor.load(element.getAsJsonObject());

                            element = body.get("Subscriptions");
                            if (element != null)
                                fld_data_doctor.loadSubscriptions(element.getAsJsonArray());

                            element = body.get("Comments");
                            if (element != null)
                                fld_data_doctor.loadComments(element.getAsJsonArray());
                            reload();
                        } else{

                        }
                    }
                }
            });
            GlobalData.socket.sendMessage(request);
        }

        GlobalData.socket.addFixedRequest("Updated ProfileBase " + String.valueOf(fld_data_base.id), new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("ProfileBase");
                if(element != null) {
                    fld_data_base.load(element.getAsJsonObject());
                    reload();
                }
            }
        });

        GlobalData.socket.addFixedRequest("Updated Subscriptions", new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("Subscriptions");
                if(element != null) {
                    fld_data_doctor.loadSubscriptions(element.getAsJsonArray());
                    if(obj_menu.getSelectedTabPosition() == 1)
                        openSubscription();
                }
            }
        });
    }

    public void reload()
    {
        obj_avatar.setImageBitmap(fld_data_base.miniature);
        setAchievements(fld_data_doctor.achievements);
        setFio(fld_data_base.name, fld_data_base.surname, fld_data_base.patronymic);
    }

    public void setFio(String name, String surname, String patronymic)
    {
        obj_header_name.setText(name);
        obj_header_surname.setText(surname);
        obj_header_patronymic.setText(patronymic);
    }

    private TabLayout.BaseOnTabSelectedListener interface_menu = new TabLayout.BaseOnTabSelectedListener() {
        @Override
        public void onTabSelected(TabLayout.Tab tab) {
            String tab_name = tab.getText().toString();
            switch (tab_name)
            {
                case "Информация":
                    openInformation();
                    break;
                case "Подписки":
                    openSubscription();
                    break;
                case "Отзывы":
                    openComments();
                    break;
            }
        }

        @Override
        public void onTabUnselected(TabLayout.Tab tab) {

        }

        @Override
        public void onTabReselected(TabLayout.Tab tab) {

        }
    };

    public void setAchievements(List<AchievementData> _achievements)
    {
        if(_achievements.isEmpty()){
            obj_achievements.setVisibility(View.INVISIBLE);
            return;
        }
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        for(int i = 0; i < _achievements.size(); i++)
        {
            Drawable icon = getResources().getDrawable(R.drawable.icon_profile_achievement);
            ProfileAchievementFragment new_fragment = ProfileAchievementFragment.newInstance(_achievements.get(i).icon, _achievements.get(i).text);
            if(i == 0)
                transaction.replace(R.id.layout_profile_achievements, new_fragment);
            else
                transaction.add(R.id.layout_profile_achievements, new_fragment);
        }
        transaction.commit();
    }

    public void openInformation()
    {
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        ProfileInformationBase new_info_base = ProfileInformationBase.newInstance(fld_data_base, fld_access);
        ProfileInformationDoctor new_info_doctor = new ProfileInformationDoctor(fld_data_doctor, fld_access);
        transaction.replace(R.id.layout_profile_menu, new_info_base);
        transaction.add(R.id.layout_profile_menu, new_info_doctor);
        transaction.commit();
    }

    public void openSubscription()
    {
        try {
            FragmentManager fragmentManager = getFragmentManager();
            FragmentTransaction transaction = fragmentManager.beginTransaction();
            for (int i = 0; i < fld_data_doctor.subscriptions.size(); i++) {
                ProfileSpecializationFragment new_subscription = new ProfileSpecializationFragment(fld_data_doctor.subscriptions.get(i), fld_data_base, fld_access);
                if (i == 0)
                    transaction.replace(R.id.layout_profile_menu, new_subscription);
                else
                    transaction.add(R.id.layout_profile_menu, new_subscription);
            }
            if (fld_data_doctor.subscriptions.isEmpty())
                transaction.replace(R.id.layout_profile_menu, new EmptyFragment("У вас еще нет подписок"));
            if (fld_access == GlobalData.Access.Owner) {
                transaction.add(R.id.layout_profile_menu, new ProfileSubscriptionAddFragment(
                        interface_add,
                        ViewGroup.LayoutParams.MATCH_PARENT,
                        (int) getResources().getDimension(R.dimen.profile_subscription_add_thickness),
                        (int) getResources().getDimension(R.dimen.margin_default)
                ));
            }
            transaction.commit();
        }
        catch(Exception e)
        {
            GlobalData.Access access = GlobalData.Access.Friend;
        }
    }

    public void openComments()
    {
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        for(int i = 0; i < fld_data_doctor.comments.size(); i++)
        {
            ProfileCommentFragment new_comment = new ProfileCommentFragment(fld_data_doctor.comments.get(i));
            if(i == 0)
                transaction.replace(R.id.layout_profile_menu, new_comment);
            else
                transaction.add(R.id.layout_profile_menu, new_comment);
        }
        if(fld_data_doctor.comments.isEmpty())
            transaction.replace(R.id.layout_profile_menu, new EmptyFragment("Комментариев пока что нет"));
        transaction.commit();
    }

    private Button.OnClickListener interface_dialogCreate = new Button.OnClickListener(){
        @Override
        public void onClick(View view) {
            Request request = new Request("New Dialog");
            request.body.addProperty("user_1_id", GlobalData.currentProfileBase.id);
            request.body.addProperty("user_2_id", fld_data_base.id);
            request.body.addProperty("user_1_mode", GlobalData.currentMode.toInt());
            request.body.addProperty("user_2_mode", GlobalData.Mode.Doctor.toInt());
            GlobalData.socket.addExpectedRequest("Reply New Dialog", new ClientSocket.OnMessageReceived() {
                @Override
                public void received(JsonObject body) {
                    JsonElement element = body.get("status");
                    if(element != null) {
                        if (element.getAsString().equals("successful")) {
                            element = body.get("Dialog");
                            if(element != null){
                                Intent intent = new Intent(getActivity(), DialogActivity.class);
                                DialogActivity.new_data = DialogData.createFromJson(element.getAsJsonObject());
                                startActivity(intent);
                            }
                        }
                        else {
                            new NotificationDialogFragment("Не удалось начать диалог").show(getFragmentManager(), "notification");
                        }
                    }
                }
            });
            GlobalData.socket.sendMessage(request);
        }
    };

    private Button.OnClickListener interface_edit = new Button.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(getActivity(), ViewerActivity.class);
            ViewerActivity.currentFragment = new ProfileBaseEditFragment();
            startActivity(intent);
        }
    };

    private FrameLayout.OnClickListener interface_add = new FrameLayout.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(getActivity(), ViewerActivity.class);
            ViewerActivity.currentFragment = new ProfileSubscriptionEditFragment();
            startActivity(intent);
        }
    };
}
