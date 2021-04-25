package com.vklinike.ui.profile.doctor;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.ui.NotificationDialogFragment;
import com.vklinike.ui.socket.ClientSocket;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.data.PatientSubscriptionData;
import com.vklinike.data.Request;
import com.vklinike.data.TariffData;
import com.vklinike.data.ValutaData;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;


public class ProfileSubscriptionEditFragment extends Fragment {

    private PatientSubscriptionData field_data;

    private ArrayAdapter<String> object_adapter_specializations;
    private ArrayAdapter<String> object_adapter_durations;
    private ArrayAdapter<String> object_adapter_valuta;
    private ArrayAdapter<String> object_adapter_minutes;
    private ArrayAdapter<String> object_adapter_hours;

    private TextView widget_header;
    private Spinner widget_specialization;
    private Spinner widget_duration;
    private EditText widget_cost;
    private Spinner widget_valuta;
    private Spinner widget_time_hours;
    private Spinner widget_time_minutes;
    private Button widget_save;

    public ProfileSubscriptionEditFragment()
    {
        field_data = new PatientSubscriptionData();
    }

    public ProfileSubscriptionEditFragment(PatientSubscriptionData _data)
    {
        field_data = _data;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_subscription_edit, container, false);

        widget_header = view.findViewById(R.id.profile_subscription_edit_header);
        widget_specialization = view.findViewById(R.id.profile_subscription_edit_specialization);
        widget_duration = view.findViewById(R.id.profile_subscription_edit_duration);
        widget_cost = view.findViewById(R.id.profile_subscription_edit_cost);
        widget_valuta = view.findViewById(R.id.profile_subscription_edit_valuta);
        widget_time_hours = view.findViewById(R.id.profile_subscription_edit_time_hours);
        widget_time_minutes = view.findViewById(R.id.profile_subscription_edit_time_minutes);
        widget_save = view.findViewById(R.id.profile_subscription_edit_save);

        prepare();
        reload();

        return view;
    }

    public void prepare()
    {
        List<String> specializations = new ArrayList<String>();
        for(int i = 0; i < GlobalData.availableSpecializations.size(); i++)
            specializations.add(GlobalData.availableSpecializations.get(i).name);
        object_adapter_specializations = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, specializations);
        widget_specialization.setAdapter(object_adapter_specializations);

        List<String> durations = new ArrayList<String>();
        durations.add("Дневная");
        durations.add("Недельная");
        durations.add("Месячная");
        durations.add("Годовая");
        object_adapter_durations = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, durations);
        widget_duration.setAdapter(object_adapter_durations);

        List<String> valutes = new ArrayList<String>();
        for(int i = 0; i < GlobalData.availableValutes.size(); i++)
            valutes.add(GlobalData.availableValutes.get(i).abbreviation);
        object_adapter_valuta = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, valutes);
        widget_valuta.setAdapter(object_adapter_valuta);

        List<String> hours = new ArrayList<String>();
        for(int i = 0; i < 23; i++)
            hours.add(String.valueOf(i));
        object_adapter_hours = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, hours);
        widget_time_hours.setAdapter(object_adapter_hours);

        List<String> minutes = new ArrayList<String>();
        for(int i = 0; i < 59; i++)
            minutes.add(String.valueOf(i));
        object_adapter_minutes = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, minutes);
        widget_time_minutes.setAdapter(object_adapter_minutes);

        widget_save.setOnClickListener(interface_save);
    }

    public void reload()
    {
        if(field_data.specialization.id != -1)
            setSpecialization(field_data.specialization.name);
        if(field_data.package_id != -1)
            setDuration(field_data.duration);
        if(field_data.tariff_id != -1)
        {
            setCost(field_data.cost, field_data.valuta);
            setTime(field_data.time);
            widget_header.setText("Редактирование тарифа");
            widget_save.setText(getResources().getString(R.string.default_save));
        }
        else {
            widget_header.setText("Создание тарифа");
            widget_save.setText(getResources().getString(R.string.default_add));
        }
    }

    public void setSpecialization(String _specialization_name)
    {
        for(int i = 0; i < GlobalData.availableSpecializations.size(); i++)
        {
            if(GlobalData.availableSpecializations.get(i).name == _specialization_name) {
                widget_specialization.setSelection(i);
                return;
            }
        }
    }

    public void setDuration(int _duration)
    {
        switch (_duration)
        {
            case 1:
                widget_duration.setSelection(0);
                break;
            case 7:
                widget_duration.setSelection(1);
                break;
            case 31:
                widget_duration.setSelection(2);
                break;
            case 365:
                widget_duration.setSelection(3);
                break;
        }
    }

    private void setCost(int _cost, ValutaData _valuta)
    {
        widget_cost.setText(String.valueOf(_cost));
        for(int i = 0; i < GlobalData.availableValutes.size(); i++)
        {
            if(GlobalData.availableValutes.get(i).name.equals(_valuta.name)) {
                widget_specialization.setSelection(i);
                return;
            }
        }
    }

    private void setTime(int seconds)
    {
        Calendar time = new GregorianCalendar(2000, 1, 1, 0, 0, 0);
        time.setTimeInMillis(time.getTimeInMillis() + seconds * 1000);
        widget_time_hours.setSelection(time.get(Calendar.HOUR_OF_DAY));
        widget_time_minutes.setSelection(time.get(Calendar.MINUTE));
    }

    private Button.OnClickListener interface_save = new Button.OnClickListener(){
        @Override
        public void onClick(View view) {
            field_data.cost = Integer.valueOf(widget_cost.getText().toString());

            String valuta_name = widget_valuta.getSelectedItem().toString();
            for(int i = 0; i < GlobalData.availableValutes.size(); i++){
                if(valuta_name == GlobalData.availableValutes.get(i).abbreviation)
                    field_data.valuta = GlobalData.availableValutes.get(i);
            }

            String specialization_name = widget_specialization.getSelectedItem().toString();
            for(int i = 0; i < GlobalData.availableSpecializations.size(); i++){
                if(specialization_name == GlobalData.availableSpecializations.get(i).name)
                    field_data.specialization = GlobalData.availableSpecializations.get(i);
            }

            String duration = widget_duration.getSelectedItem().toString();
            switch (duration){
                case "Дневная":
                    field_data.duration = 24;
                    break;
                case "Недельная":
                    field_data.duration = 7 * 24;
                    break;
                case "Месячная":
                    field_data.duration = 31 * 24;
                    break;
                case "Годовая":
                    field_data.duration = 265 * 24;
                    break;
            }

            field_data.time = Integer.valueOf(widget_time_hours.getSelectedItem().toString()) * 60 * 60
                    + Integer.valueOf(widget_time_minutes.getSelectedItem().toString()) * 60;

            if(field_data.tariff_id == -1){
                GlobalData.socket.addExpectedRequest("Reply New Tariff", interface_loading);
                Request request = new Request("New Tariff");
                request.body.add("Tariff", new TariffData(
                        field_data.cost,
                        field_data.valuta,
                        field_data.time
                ).toJson());
                request.body.addProperty("specialization_id", field_data.specialization.id);
                request.body.addProperty("duration", field_data.duration);
                request.body.addProperty("doctor_id", GlobalData.currentProfileDoctor.id);
                GlobalData.socket.sendMessage(request);
            }
            else{
                GlobalData.socket.addExpectedRequest("Reply Update Tariff", interface_loading);
                Request request = new Request("Update Tariff");
                TariffData tariff = new TariffData(field_data.cost,field_data.valuta,field_data.time);
                tariff.id = field_data.tariff_id;
                tariff.package_id = field_data.package_id;
                request.body.add("Tariff", tariff.toJson());
                request.body.addProperty("duration", field_data.duration);
                request.body.addProperty("specialization_id", field_data.specialization.id);
                GlobalData.socket.sendMessage(request);
            }
        }
    };

    private ClientSocket.OnMessageReceived interface_loading = new ClientSocket.OnMessageReceived() {
        @Override
        public void received(JsonObject body) {
            try{
                JsonElement element = body.get("status");
                if(element != null){
                    if(element.getAsString().equals("successful")){
                        getActivity().onBackPressed();
                    }
                    else {
                        new NotificationDialogFragment("Не удалось сохранить изменения подписки").show(getFragmentManager(), "notification");
                    }
                }
            } catch (Exception e){
                e.getMessage();
            }
        }
    };
}
