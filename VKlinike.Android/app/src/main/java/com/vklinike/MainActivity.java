package com.vklinike;


import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.PopupMenu;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.data.Request;
import com.vklinike.ui.messages.MessagesFragment;
import com.vklinike.ui.profile.doctor.ProfileDoctorFragment;
import com.vklinike.ui.profile.patient.ProfilePatientFragment;
import com.vklinike.ui.search.SearchPatientFragment;
import com.vklinike.ui.socket.ClientSocket;

import androidx.annotation.NonNull;

import static com.google.android.material.bottomnavigation.BottomNavigationView.*;

public class MainActivity extends AppCompatActivity {

    private TextView obj_header;
    private ImageButton obj_options;
    private BottomNavigationView obj_navView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getSupportActionBar().hide();

        obj_navView = findViewById(R.id.nav_view);
        obj_options = findViewById(R.id.main_menu);
        obj_header = findViewById(R.id.main_header);

        obj_navView.setOnNavigationItemSelectedListener(function_ItemSelectedListener);
        obj_options.setOnClickListener(fnc_option_clickListener);

        prepare();
    }

    public void prepare()
    {
        GlobalData.socket.addFixedRequest("Updated ProfileBase " + String.valueOf(GlobalData.currentProfileBase.id), new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("ProfileBase");
                if(element != null) {
                    GlobalData.currentProfileBase.load(element.getAsJsonObject());
                }
            }
        });

        GlobalData.socket.addFixedRequest("Updated ProfileDoctor " + String.valueOf(GlobalData.currentProfileDoctor.id), new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("ProfileDoctor");
                if(element != null) {
                    GlobalData.currentProfileDoctor.load(element.getAsJsonObject());
                }
            }
        });

        GlobalData.socket.addFixedRequest("Updated Dialogs", new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("DialogList");
                if(element != null) {
                    GlobalData.currentDialogs.load(element.getAsJsonArray());
                }
            }
        });
        reload();
    }

    public void reload(){
        GlobalData.socket.addExpectedRequest("Reply Get BasicUserData", interface_loading);
        Request request = new Request("Get BasicUserData");
        request.body.addProperty("login", GlobalData.currentLogin);
        request.body.addProperty("password", GlobalData.currentPassword);
        request.body.addProperty("mode", GlobalData.currentMode.toInt());
        GlobalData.socket.sendMessage(request);
    }

    private void loadFragment(Fragment fragment) {
        FragmentManager manager = getSupportFragmentManager();
        FragmentTransaction ft = manager.beginTransaction();
        ft.replace(R.id.nav_host_fragment, fragment);
        ft.commit();
    }

    @SuppressLint("MissingSuperCall")
    @Override
    protected void onSaveInstanceState(Bundle outState) {

    }

    @Override
    public void onBackPressed() {

    }

    private void loadingFailed()
    {

    }

    private ClientSocket.OnMessageReceived interface_loading = new ClientSocket.OnMessageReceived() {
        @Override
        public void received(JsonObject body) {
            try{
                JsonElement element = body.get("status");
                if(element != null){
                    if(element.getAsString().equals("successful")){
                        element = body.get("ProfileBase");
                        if(element != null)
                            GlobalData.currentProfileBase.load(element.getAsJsonObject());

                        switch (GlobalData.currentMode.toInt()) {
                            case 0:
                                element = body.get("ProfileDoctor");
                                if(element != null)
                                    GlobalData.currentProfileDoctor.load(element.getAsJsonObject());

                                element = body.get("Subscriptions");
                                if(element != null)
                                    GlobalData.currentProfileDoctor.loadSubscriptions(element.getAsJsonArray());

                                element = body.get("Comments");
                                if(element != null)
                                    GlobalData.currentProfileDoctor.loadComments(element.getAsJsonArray());
                                break;
                            case 1:
                                element = body.get("ProfilePatient");
                                if(element != null)
                                    GlobalData.currentProfilePatient.load(element.getAsJsonObject());

                                element = body.get("Subscriptions");
                                if(element != null)
                                    GlobalData.currentProfilePatient.loadSubscriptions(element.getAsJsonArray());
                                break;
                        }

                        element = body.get("DialogList");
                        if(element != null)
                            GlobalData.currentDialogs.load(element.getAsJsonArray());

                        element = body.get("Specializations");
                        if(element != null)
                            GlobalData.setAvailableSpecializations(element.getAsJsonArray());

                        element = body.get("Valutes");
                        if(element != null)
                            GlobalData.setAvailableValutes(element.getAsJsonArray());

                        obj_navView.setSelectedItemId(R.id.navigation_messages);
                    }
                    else
                        loadingFailed();
                }
            } catch (Exception e){
                e.getMessage();
            }
        }
    };

    private Button.OnClickListener fnc_option_clickListener = new Button.OnClickListener() {
        @Override
        public void onClick(View view) {
            PopupMenu popup = new PopupMenu(MainActivity.this, obj_options);
            popup.getMenuInflater().inflate(R.menu.main_menu, popup.getMenu());
            popup.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                public boolean onMenuItemClick(MenuItem item) {
                    switch (item.getItemId())
                    {
                        case R.id.main_menu_mode:
                            if(GlobalData.currentMode == GlobalData.Mode.Doctor)
                                GlobalData.currentMode = GlobalData.Mode.Patient;
                            else if(GlobalData.currentMode == GlobalData.Mode.Patient)
                                GlobalData.currentMode = GlobalData.Mode.Doctor;
                            reload();
                            return true;
                        default:
                            return false;
                    }
                }
            });
            popup.show();
        }
    };

    private OnNavigationItemSelectedListener function_ItemSelectedListener
            = new OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            switch (item.getItemId()) {
                case R.id.navigation_profile:
                    if(GlobalData.currentMode == GlobalData.Mode.Patient)
                        loadFragment(new ProfilePatientFragment(GlobalData.currentProfileBase, GlobalData.currentProfilePatient, GlobalData.Access.Owner));
                    else if(GlobalData.currentMode == GlobalData.Mode.Doctor)
                        loadFragment(new ProfileDoctorFragment(GlobalData.currentProfileBase, GlobalData.currentProfileDoctor, GlobalData.Access.Owner));
                    return true;
                case R.id.navigation_messages:
                    loadFragment(MessagesFragment.newInstance());
                    return true;
                case R.id.navigation_search:
                    if(GlobalData.currentMode ==  GlobalData.Mode.Patient)
                        loadFragment(SearchPatientFragment.newInstance());
                    return true;
            }
            return false;
        }
    };
}
