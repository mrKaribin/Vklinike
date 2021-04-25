package com.vklinike.ui.profile.patient;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.vklinike.R;
import com.vklinike.data.PatientSubscriptionData;

import java.util.Calendar;
import java.util.GregorianCalendar;


public class ProfilePatientSubscriptionPreview extends Fragment {

    private PatientSubscriptionData fld_subscription;

    private TextView obj_specialization;
    private TextView obj_fio;
    private TextView obj_duration;
    private TextView obj_balance_time;
    private TextView obj_balance_consultation;

    public ProfilePatientSubscriptionPreview(PatientSubscriptionData _subscription)
    {
        fld_subscription = _subscription;
    }

    public static ProfilePatientSubscriptionPreview newInstance(PatientSubscriptionData _subscription) {
        return new ProfilePatientSubscriptionPreview(_subscription);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_patient_subscription_preview, container, false);

        obj_specialization = view.findViewById(R.id.patient_subscription_preview_specialization);
        obj_fio = view.findViewById(R.id.patient_subscription_preview_fio);
        obj_duration = view.findViewById(R.id.patient_subscription_preview_duration);
        obj_balance_time = view.findViewById(R.id.patient_subscription_preview_balance_time);
        obj_balance_consultation = view.findViewById(R.id.patient_subscription_preview_balance_consultation);

        reload();

        return view;
    }

    public void reload()
    {
        obj_specialization.setText(fld_subscription.specialization.name);
        setFio(fld_subscription.doctor.name, fld_subscription.doctor.surname, fld_subscription.doctor.patronymic);
        setDuration(fld_subscription.duration);
        setFinishTime(fld_subscription.finish_time);
        setConsultationBalance(fld_subscription.time);
    }

    public void setFio(String name, String surname, String patronymic)
    {
        String result = patronymic + " " + name + " " + surname;
        obj_fio.setText(result);
    }

    public void setDuration(int _duration)
    {
        switch (_duration) {
            case 1:
                obj_duration.setText("дневная");
                break;
            case 7:
                obj_duration.setText("недельная");
                break;
            case 30:
                obj_duration.setText("месячная");
                break;
            case 365:
                obj_duration.setText("годовая");
                break;
        }
    }

    public void setFinishTime(Calendar _finish_time)
    {
        Calendar remaining = new GregorianCalendar();
        Calendar currentTime = Calendar.getInstance();
        long interval = _finish_time.getTimeInMillis() - currentTime.getTimeInMillis();
        remaining.setTimeInMillis(interval);

        String result = "";
        int count = 2;
        if(remaining.get(Calendar.YEAR) != 1970)
        {
            result += String.valueOf(remaining.get(Calendar.YEAR)) + " г. ";
            count --;
        }
        if(remaining.get(Calendar.MONTH) != Calendar.JANUARY && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.MONTH)) + " мес. ";
            count --;
        }
        if(remaining.get(Calendar.DAY_OF_MONTH) != 1 && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.DAY_OF_MONTH) - 1)  + " дн. ";
            count --;
        }
        if(remaining.get(Calendar.HOUR_OF_DAY) != 1 && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.HOUR_OF_DAY))  + " ч. ";
            count --;
        }
        if(remaining.get(Calendar.MINUTE) != 1 && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.MINUTE))  + " мин. ";
            count --;
        }
        if(remaining.get(Calendar.SECOND) != 1 && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.SECOND))  + " сек. ";
            count --;
        }
        obj_balance_time.setText(result);
    }

    public void setConsultationBalance(int time)
    {
        Calendar remaining = new GregorianCalendar();
        remaining.setTimeInMillis(time * 1000);

        String result = "";
        int count = 2;
        int hours = 0;
        if(remaining.get(Calendar.YEAR) != 1970)
        {
            hours += remaining.get(Calendar.YEAR) * 8760;
        }
        if(remaining.get(Calendar.MONTH) != Calendar.JANUARY && count != 0)
        {
            hours += remaining.get(Calendar.MONTH) * 720;
        }
        if(remaining.get(Calendar.DAY_OF_MONTH) != 1 && count != 0)
        {
            hours += remaining.get(Calendar.DAY_OF_MONTH) * 24;
        }
        if(remaining.get(Calendar.HOUR_OF_DAY) != 1 && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.HOUR_OF_DAY) + hours)  + " ч. ";
            count --;
        }
        if(remaining.get(Calendar.MINUTE) != 1 && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.MINUTE))  + " мин. ";
            count --;
        }
        if(remaining.get(Calendar.SECOND) != 1 && count != 0)
        {
            result += String.valueOf(remaining.get(Calendar.SECOND))  + " сек. ";
        }
        obj_balance_consultation.setText(result);
    }
}
