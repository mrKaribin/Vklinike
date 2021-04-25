package com.vklinike.ui.login;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.ui.socket.ClientSocket;
import com.vklinike.GlobalData;
import com.vklinike.MainActivity;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.DialogsData;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.ProfileDoctorData;
import com.vklinike.data.ProfilePatientData;
import com.vklinike.data.Request;
import com.vklinike.data.SpecializationData;
import com.vklinike.data.ValutaData;
import com.vklinike.ui.socket.NetworkErrorDialogFragment;

import java.util.ArrayList;

public class LoginActivity extends AppCompatActivity {

    private TextView header;
    private EditText username;
    private EditText password;
    private Button login;
    private Button registration;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        getSupportActionBar().hide();

        header = findViewById(R.id.login_header);
        username = findViewById(R.id.login_username);
        password = findViewById(R.id.login_password);
        login = findViewById(R.id.login_signin);
        registration = findViewById(R.id.login_registration);

        login.setOnClickListener(interface_login_clickListener);
        registration.setOnClickListener(interface_registration_clickListener);

        GlobalData.currentMode = GlobalData.Mode.Doctor;
        GlobalData.availableSpecializations = new ArrayList<SpecializationData>();
        GlobalData.availableValutes = new ArrayList<ValutaData>();
        GlobalData.currentProfileBase = new ProfileBaseData();
        GlobalData.currentProfileDoctor = new ProfileDoctorData();
        GlobalData.currentProfilePatient = new ProfilePatientData();
        GlobalData.currentDialogs = new DialogsData();
        GlobalData.socket = new ClientSocket(GlobalData.host, GlobalData.port_tcp);
        GlobalData.socket.setOnConnection(interface_connection);
        GlobalData.socket.execute();
    }

    private Button.OnClickListener interface_login_clickListener = new Button.OnClickListener() {
        @Override
        public void onClick(View view) {
            logining(username.getText().toString(), password.getText().toString());
        }
    };

    private Button.OnClickListener interface_registration_clickListener = new Button.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(LoginActivity.this, ViewerActivity.class);
            ViewerActivity.currentFragment = new RegistrationFragment();
            RegistrationFragment.parent = LoginActivity.this;
            startActivity(intent);
        }
    };

    public void wrongData()
    {
        header.setText("Проверьте правильность введенных данных");
    }

    public void logining(String _login, String _password)
    {
        GlobalData.socket.addExpectedRequest("Reply Autorization", interface_login);
        Request request = new Request("Autorization");
        request.body.addProperty("login", _login);
        request.body.addProperty("password", _password);
        GlobalData.socket.sendMessage(request);
    }

    public void logined()
    {
        GlobalData.currentLogin = username.getText().toString();
        GlobalData.currentPassword = password.getText().toString();
        Intent intent = new Intent(LoginActivity.this, MainActivity.class);
        startActivity(intent);
    }

    private ClientSocket.OnConnectionListener interface_connection = new ClientSocket.OnConnectionListener() {
        @Override
        public void onConnected() {

        }

        @Override
        public void onDisconnected() {
            new NetworkErrorDialogFragment().show(getSupportFragmentManager(), "networkDialog");
        }
    };

    private ClientSocket.OnMessageReceived interface_login = new ClientSocket.OnMessageReceived() {
        @Override
        public void received(JsonObject body) {
            JsonElement element = body.get("status");
            if(element != null){
                if(element.getAsString().equals("successful"))
                    logined();
                else
                    wrongData();
            }
        }
    };
}
