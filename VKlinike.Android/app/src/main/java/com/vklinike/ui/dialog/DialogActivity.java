package com.vklinike.ui.dialog;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.PopupMenu;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.DialogData;
import com.vklinike.data.MessageData;
import com.vklinike.data.ProfileDoctorData;
import com.vklinike.data.ProfilePatientData;
import com.vklinike.data.Request;
import com.vklinike.ui.EmptyFragment;
import com.vklinike.ui.profile.doctor.ProfileDoctorFragment;
import com.vklinike.ui.profile.patient.ProfilePatientFragment;
import com.vklinike.ui.socket.ClientSocket;

import java.io.ByteArrayOutputStream;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class DialogActivity extends AppCompatActivity {

    private DialogData field_data;
    private int field_nextMessageId = -1;
    static final int GALLERY_REQUEST = 1;

    private FragmentManager object_manager;

    private List<DialogEnclosureImageFragment> array_enclosures;

    private LinearLayout layout_enclosures;

    private ImageButton widget_back;
    private ImageButton widget_call;
    private ImageButton widget_video;
    private ImageButton widget_options;
    private ImageButton widget_enclosure;
    private ImageButton widget_send;
    private LinearLayout widget_profile;
    private ImageView widget_avatar;
    private TextView widget_fio;
    private EditText widget_text;

    public static DialogData new_data;

    public DialogActivity()
    {
        field_data = new_data;
        array_enclosures = new ArrayList<DialogEnclosureImageFragment>();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dialog);
        getSupportActionBar().hide();

        layout_enclosures = findViewById(R.id.layout_dialog_enclosures);
        widget_back = findViewById(R.id.dialog_back);
        widget_call = findViewById(R.id.dialog_phone);
        widget_video = findViewById(R.id.dialog_video);
        widget_options= findViewById(R.id.dialog_options);
        widget_send = findViewById(R.id.dialog_send);
        widget_enclosure = findViewById(R.id.dialog_enclosure);
        widget_profile = findViewById(R.id.dialog_profile);
        widget_avatar = findViewById(R.id.dialog_avatar);
        widget_fio = findViewById(R.id.dialog_fio);
        widget_text = findViewById(R.id.dialog_text);

        object_manager = getSupportFragmentManager();
        Request request = new Request("Get Dialog");
        request.body.addProperty("id", field_data.id);
        GlobalData.socket.addExpectedRequest("Reply Get Dialog", new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("status");
                if(element != null) {
                    if (element.getAsString().equals("successful")) {
                        element = body.get("Messages");
                        if (element != null)
                            field_data.loadMessages(element.getAsJsonArray());
                        reload();
                    } else
                        loadingFailed();
                }
            }
        });
        GlobalData.socket.sendMessage(request);
        FragmentTransaction transaction = object_manager.beginTransaction();
        for (Fragment fragment : getSupportFragmentManager().getFragments()) {
            if(fragment != null)
                transaction.remove(fragment);
        }
        transaction.commit();

        widget_back.setOnClickListener(interface_back_clickListener);
        widget_call.setOnClickListener(interface_call_clickListener);
        widget_video.setOnClickListener(interface_video_clickListener);
        widget_options.setOnClickListener(interface_options_clickListener);
        widget_enclosure.setOnClickListener(interface_enclosure);
        widget_send.setOnClickListener(interface_send_clickListener);
        widget_profile.setOnClickListener(interface_profile_clickListener);
        reload();
    }

    void reload()
    {
        setFio(field_data.companion.name, field_data.companion.surname, field_data.companion.patronymic);
        setMessages(field_data.messages);
        reloadEnclosures();
    }

    public void reloadEnclosures(){
        if(array_enclosures.isEmpty())
            layout_enclosures.setVisibility(View.INVISIBLE);
        else
            layout_enclosures.setVisibility(View.VISIBLE);
    }

    public void setFio(String name, String surname, String patronymic)
    {
        String result = "";
        if(GlobalData.currentMode == GlobalData.Mode.Patient)
            result = surname + "\n" + name + " " + patronymic;
        if(GlobalData.currentMode == GlobalData.Mode.Doctor)
            result = name;
        widget_fio.setText(result);
    }

    public void setMessages(List<MessageData> messages){
        FragmentTransaction transaction = object_manager.beginTransaction();
        for(int i = 0; i < messages.size(); i++){
            MessageFragment fragment;
            if(messages.get(i).sender_id == GlobalData.currentProfileBase.id)
                fragment = new MessageFragment(MessageFragment.Type.Output, messages.get(i));
            else
                fragment = new MessageFragment(MessageFragment.Type.Input, messages.get(i));
            if(i == 0)
                transaction.replace(R.id.layout_dialog, fragment);
            else
                transaction.add(R.id.layout_dialog, fragment);
        }
        if(messages.isEmpty())
            transaction.replace(R.id.layout_dialog, new EmptyFragment("Тут еще нет сообщений"));
        transaction.commit();
    }

    public void addMessage(MessageData message){
        field_data.messages.add(message);
        FragmentTransaction transaction = object_manager.beginTransaction();
        MessageFragment fragment;

        if(message.sender_id == GlobalData.currentProfileBase.id)
            fragment = new MessageFragment(MessageFragment.Type.Output, message);
        else
            fragment = new MessageFragment(MessageFragment.Type.Input, message);

        if(field_data.messages.isEmpty())
            transaction.replace(R.id.layout_dialog, fragment);
        else
            transaction.add(R.id.layout_dialog, fragment);

        transaction.commit();
    }

    private void loadingFailed(){

    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        finish();
    }

    private ClientSocket.OnMessageReceived interface_send_reply = new ClientSocket.OnMessageReceived() {
        @Override
        public void received(JsonObject body) {
            try{
                JsonElement element = body.get("status");
                if(element != null){
                    if(element.getAsString().equals("successful")){
                        element = body.get("lastId");
                        if(element != null && body.get("newId") != null){
                            int id = element.getAsInt();
                            for(int i = 0; i < field_data.messages.size(); i++){
                                if(field_data.messages.get(i).id == id)
                                    field_data.messages.get(i).id = body.get("newId").getAsInt();
                            }
                        }
                    }
                    else{

                    }
                }
            } catch (Exception e){
                e.getMessage();
            }
        }
    };

    private ImageButton.OnClickListener interface_back_clickListener = new ImageButton.OnClickListener() {
        @Override
        public void onClick(View view) {
            onBackPressed();
        }
    };

    private ImageButton.OnClickListener interface_call_clickListener = new ImageButton.OnClickListener() {
        @Override
        public void onClick(View view) {

        }
    };

    private ImageButton.OnClickListener interface_video_clickListener = new ImageButton.OnClickListener() {
        @Override
        public void onClick(View view) {

        }
    };

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent imageReturnedIntent) {
        super.onActivityResult(requestCode, resultCode, imageReturnedIntent);
        switch(requestCode) {
            case GALLERY_REQUEST:
                Uri selectedImage = imageReturnedIntent.getData();
                if(selectedImage != null){
                    final DialogEnclosureImageFragment fragment = new DialogEnclosureImageFragment(selectedImage);
                    fragment.setDeleteInterface(new DialogEnclosureImageFragment.OnDeleteListener() {
                        @Override
                        public void deleting() {
                            array_enclosures.remove(fragment);
                            FragmentTransaction transaction = object_manager.beginTransaction();
                            transaction.remove(fragment);
                            transaction.commit();
                            reloadEnclosures();
                        }
                    });
                    array_enclosures.add(fragment);

                    FragmentTransaction transaction = object_manager.beginTransaction();
                    transaction.add(R.id.layout_dialog_enclosures, fragment);
                    transaction.commit();
                    reloadEnclosures();
                }
                break;
        }
    }

    private ImageButton.OnClickListener interface_options_clickListener = new ImageButton.OnClickListener() {
        @Override
        public void onClick(View view) {
            PopupMenu popup = new PopupMenu(DialogActivity.this, widget_options);
            popup.getMenuInflater().inflate(R.menu.dialog_menu, popup.getMenu());
            popup.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                public boolean onMenuItemClick(MenuItem item) {
                    switch (item.getItemId())
                    {
                        default:
                            return false;
                    }
                }
            });
            popup.show();
        }
    };

    private ImageButton.OnClickListener interface_enclosure = new ImageButton.OnClickListener() {
        @Override
        public void onClick(View view) {
            PopupMenu popup = new PopupMenu(DialogActivity.this, widget_enclosure);
            popup.getMenuInflater().inflate(R.menu.enclosures_menu, popup.getMenu());
            popup.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                public boolean onMenuItemClick(MenuItem item) {
                    switch (item.getItemId())
                    {
                        case R.id.dialog_enclosures_image:
                            Intent photoPickerIntent = new Intent(Intent.ACTION_PICK);
                            photoPickerIntent.setType("image/*");
                            startActivityForResult(photoPickerIntent, 1);
                            return true;
                        default:
                            return false;
                    }
                }
            });
            popup.show();
        }
    };

    private ImageButton.OnClickListener interface_send_clickListener = new ImageButton.OnClickListener() {
        @Override
        public void onClick(View view) {
            Request request = new Request("New Message");
            MessageData new_data = new MessageData();
            new_data.id = field_nextMessageId;
            new_data.sender_id = GlobalData.currentProfileBase.id;
            new_data.dialog_id = field_data.id;
            new_data.timepoint = Calendar.getInstance();
            new_data.message = widget_text.getText().toString();
            if(!array_enclosures.isEmpty()){
                DialogEnclosureImageFragment _enclosure = array_enclosures.get(0);
                new_data.attachment_type = "jpg";
                new_data.attachment_name = "new_attachment_user_" + GlobalData.currentProfileBase.id;
                ByteArrayOutputStream stream = new ByteArrayOutputStream();
                _enclosure.getImage().compress(Bitmap.CompressFormat.JPEG, 100, stream);
                new_data.attachment_data = stream.toByteArray();
                GlobalData.socket.sendEnclosure(new_data.attachment_name, new_data.attachment_data);

                _enclosure.delete();
            }
            request.body.add("Message", new_data.toJson());
            GlobalData.socket.addExpectedRequest("Reply New Message", interface_send_reply);
            GlobalData.socket.sendMessage(request);
            field_nextMessageId--;
            addMessage(new_data);
            widget_text.setText("");
        }
    };

    private LinearLayout.OnClickListener interface_profile_clickListener = new LinearLayout.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent intent = new Intent(DialogActivity.this, ViewerActivity.class);
            if(GlobalData.currentMode == GlobalData.Mode.Patient)
                ViewerActivity.currentFragment = new ProfileDoctorFragment(field_data.companion, new ProfileDoctorData(), GlobalData.Access.Friend);
            if(GlobalData.currentMode == GlobalData.Mode.Doctor)
                ViewerActivity.currentFragment = new ProfilePatientFragment(field_data.companion, new ProfilePatientData(), GlobalData.Access.Friend);
            startActivity(intent);
        }
    };
}
