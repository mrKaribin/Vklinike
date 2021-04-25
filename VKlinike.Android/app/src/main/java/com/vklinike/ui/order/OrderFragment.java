package com.vklinike.ui.order;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.TextView;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.ui.socket.ClientSocket;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ViewerActivity;
import com.vklinike.data.PatientSubscriptionData;
import com.vklinike.data.Request;
import com.vklinike.data.ValutaData;


public class OrderFragment extends Fragment {

    private PatientSubscriptionData field_data;

    private TextView widget_fio;
    private TextView widget_specialization;
    private TextView widget_duration;
    private TextView widget_time;
    private TextView widget_cost;
    private CheckBox widget_payout_paypal;
    private CheckBox widget_payout_yandex;
    private Button widget_payout;

    public OrderFragment(PatientSubscriptionData _data)
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
        final View view = inflater.inflate(R.layout.fragment_order, container, false);

        widget_fio = view.findViewById(R.id.order_fio);
        widget_specialization = view.findViewById(R.id.order_specialization);
        widget_duration = view.findViewById(R.id.order_duration);
        widget_time = view.findViewById(R.id.order_time);
        widget_cost = view.findViewById(R.id.order_cost);
        widget_payout_paypal = view.findViewById(R.id.order_payout_paypal);
        widget_payout_yandex = view.findViewById(R.id.order_payout_yandex);
        widget_payout = view.findViewById(R.id.order_payout);

        widget_payout_paypal.setOnClickListener(function_paypal_clickListener);
        widget_payout_yandex.setOnClickListener(function_yandex_clickListener);
        widget_payout.setOnClickListener(function_payout_clickListener);
        reload();

        return view;
    }

    public void reload()
    {
        setFio(field_data.doctor.name, field_data.doctor.surname, field_data.doctor.patronymic);
        widget_specialization.setText(field_data.specialization.name);
        setDuration(field_data.duration);
        setTime(field_data.time);
        setCost(field_data.cost, field_data.valuta);
    }

    public void setFio(String name, String surname, String patronymic)
    {
        String result = "";
        result = surname + " " + name + " " + patronymic;
        widget_fio.setText(result);
    }

    public void setDuration(int _duration)
    {
        switch (_duration) {
            case 24:
                widget_duration.setText("Дневная");
                break;
            case 168:
                widget_duration.setText("Недельная");
                break;
            case 744:
                widget_duration.setText("Месячная");
                break;
        }
    }

    public void setTime(int _time)
    {
        String result = String.valueOf(_time) + " секунд";
        widget_time.setText(result);
    }

    public void setCost(int _cost, ValutaData _valuta)
    {
        String result;
        String val;
        switch (_valuta.abbreviation) {
            case "руб":
                val = "рублей";
                break;
            case "долл":
                val = "долларов";
                break;
            default:
                val = "";
        }
        result = String.valueOf(_cost) + " " + val;
        widget_cost.setText(result);
    }

    public void payout_uncheckAll()
    {
        widget_payout_paypal.setChecked(false);
        widget_payout_yandex.setChecked(false);
    }

    private CheckBox.OnClickListener function_paypal_clickListener = new CheckBox.OnClickListener() {
        @Override
        public void onClick(View view) {
            if(widget_payout_paypal.isChecked())
            {
                payout_uncheckAll();
                widget_payout_paypal.setChecked(true);
            }
        }
    };

    private CheckBox.OnClickListener function_yandex_clickListener = new CheckBox.OnClickListener() {
        @Override
        public void onClick(View view) {
            if(widget_payout_yandex.isChecked())
            {
                payout_uncheckAll();
                widget_payout_yandex.setChecked(true);
            }
        }
    };

    private CheckBox.OnClickListener function_payout_clickListener = new CheckBox.OnClickListener() {
        @Override
        public void onClick(View view) {
            if(widget_payout_paypal.isChecked())
            {
                Request request = new Request("New Payment PayPal");
                request.body.addProperty("doctor_id", field_data.doctor.id);
                request.body.addProperty("patient_id", GlobalData.currentProfileBase.id);
                request.body.addProperty("tariff_id", field_data.tariff_id);
                GlobalData.socket.addExpectedRequest("Reply New Payment PayPal", new ClientSocket.OnMessageReceived() {
                    @Override
                    public void received(JsonObject body) {
                        JsonElement element = body.get("status");
                        if(element != null && body.get("link") != null){
                            if(element.getAsString().equals("successful")){
                                Intent intent = new Intent(getActivity(), ViewerActivity.class);
                                ViewerActivity.currentFragment = new OrderBrowserFragment(body.get("link").getAsString());
                                ViewerActivity.currentInterfaceBack = new ViewerActivity.OnBackPressed() {
                                    @Override
                                    public void onPressed() {
                                        Request request = new Request("Cancel Payment PayPal");
                                        request.body.addProperty("reason", "canceled");
                                        GlobalData.socket.sendMessage(request);
                                    }
                                };
                                startActivity(intent);
                            }
                            else{

                            }
                        }
                    }
                });
                GlobalData.socket.sendMessage(request);
            }
            else if(widget_payout_yandex.isChecked())
            {
                Intent intent = new Intent(getActivity(), ViewerActivity.class);
                ViewerActivity.currentFragment = new OrderBrowserFragment("https://money.yandex.ru");
                startActivity(intent);
            }
        }
    };
}
