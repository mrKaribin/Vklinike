package com.vklinike.ui.login;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.ui.socket.ClientSocket;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.Request;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;


public class RegistrationFragment extends Fragment {

    private ProfileBaseData field_data_base;
    private Calendar field_currentBirthday;
    private boolean field_ok = true;
    static final int GALLERY_REQUEST = 1;

    private ArrayAdapter<String> object_adapter_days;
    private ArrayAdapter<String> object_adapter_months;
    private ArrayAdapter<String> object_adapter_years;

    private ImageView widget_avatar;
    private EditText widget_name;
    private EditText widget_surname;
    private EditText widget_patronymic;
    private Spinner widget_birthday_day;
    private Spinner widget_birthday_month;
    private Spinner widget_birthday_year;
    private CheckBox widget_sex_male;
    private CheckBox widget_sex_female;
    private EditText widget_email;
    private EditText widget_phone;
    private EditText widget_password;
    private Button widget_save;

    public static LoginActivity parent;

    public RegistrationFragment()
    {
        field_data_base = new ProfileBaseData();
        field_currentBirthday = new GregorianCalendar();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_registration, container, false);

        widget_avatar = view.findViewById(R.id.registration_avatar);
        widget_name = view.findViewById(R.id.registration_name);
        widget_surname = view.findViewById(R.id.registration_surname);
        widget_patronymic = view.findViewById(R.id.registration_patronymic);
        widget_birthday_day = view.findViewById(R.id.registration_birthday_day);
        widget_birthday_month = view.findViewById(R.id.registration_birthday_month);
        widget_birthday_year = view.findViewById(R.id.registration_birthday_year);
        widget_sex_male = view.findViewById(R.id.registration_sex_male);
        widget_sex_female = view.findViewById(R.id.registration_sex_female);
        widget_email = view.findViewById(R.id.registration_email);
        widget_phone = view.findViewById(R.id.registration_phone);
        widget_password = view.findViewById(R.id.registration_password);
        widget_save= view.findViewById(R.id.registration_save);

        widget_avatar.setOnClickListener(interface_avatarChanged);
        widget_birthday_month.setOnItemSelectedListener(function_birthday_month_itemClickListener);
        widget_sex_male.setOnCheckedChangeListener(function_sex_male_checkedChangeListener);
        widget_sex_female.setOnCheckedChangeListener(function_sex_female_checkedChangeListener);
        widget_save.setOnClickListener(function_save_clickListener);

        prepare();
        reload();

        return view;
    }

    public void prepare()
    {
        List<String> years = new ArrayList<String>();
        int currentYear = Calendar.getInstance().get(Calendar.YEAR);
        for(int i = 0; i < 150; i++)
            years.add(String.valueOf(currentYear - i));
        object_adapter_years = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, years);
        widget_birthday_year.setAdapter(object_adapter_years);


        List<String> array_months = new ArrayList<String>();
        String [] _months = getResources().getStringArray(R.array.default_months);
        for(int i = 0; i < 12; i++)
        {
            array_months.add(_months[i]);
        }
        object_adapter_months = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, array_months);
        widget_birthday_month.setAdapter(object_adapter_months);
    }

    public void reload()
    {
        Bitmap avatar = BitmapFactory.decodeResource(getResources(), R.drawable.image_patient);
        int width = avatar.getWidth();
        int height = avatar.getHeight();
        int maxLength = Math.max(width, height);
        float coef = (float) maxLength / 240;
        field_data_base.avatar = avatar;
        field_data_base.miniature = Bitmap.createScaledBitmap(avatar, (int) (width / coef), (int) (height / coef),false);
        widget_avatar.setImageBitmap(field_data_base.miniature);

        widget_avatar.setImageBitmap(field_data_base.avatar);
        widget_name.setText(field_data_base.name);
        widget_surname.setText(field_data_base.surname);
        widget_patronymic.setText(field_data_base.patronymic);

        if(timepointIsNull(field_data_base.birthday))
        {
            field_currentBirthday = Calendar.getInstance();
            setBirthday(field_currentBirthday);
        }
        else
        {
            setBirthday(field_data_base.birthday);
        }

        switch (field_data_base.sex)
        {
            case 0:
                widget_sex_male.setChecked(true);
                break;
            case 1:
                widget_sex_female.setChecked(true);
        }

        widget_email.setText(field_data_base.email);
        widget_phone.setText(field_data_base.phone);
    }

    public void reload_birthday_days(int month)
    {
        List<String> days = new ArrayList<String>();
        //int last_index = widget_birthday_day.getSelectedItemPosition();
        int max = field_currentBirthday.getActualMaximum(Calendar.DAY_OF_MONTH);
        for(int i = 1; i <= max; i++)
            days.add(String.valueOf(i));
        //object_adapter_days.clear();
        //object_adapter_days.addAll(days);
        object_adapter_days = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, days);
        widget_birthday_day.setAdapter(object_adapter_days);
        //setDay(last_index);
    }

    public boolean timepointIsNull(Calendar _timepoint)
    {
        if(_timepoint.get(Calendar.YEAR) == 1970 &&
                _timepoint.get(Calendar.MONTH) == Calendar.JANUARY &&
                _timepoint.get(Calendar.DAY_OF_MONTH) == 1 &&
                _timepoint.get(Calendar.HOUR_OF_DAY) == 0 &&
                _timepoint.get(Calendar.MINUTE) == 0 &&
                _timepoint.get(Calendar.SECOND) == 0)
            return true;
        else
            return false;
    }

    public void setBirthday(Calendar _birthday)
    {
        setYear(_birthday.get(Calendar.YEAR));
        setMonths(_birthday.get(Calendar.MONTH));
        setDay(_birthday.get(Calendar.DAY_OF_MONTH));
    }

    public void setYear(int year)
    {
        int currentYear = Calendar.getInstance().get(Calendar.YEAR);
        if(year == 0 || year > currentYear || year < currentYear - 150) {
            widget_birthday_year.setSelection(0);
            field_currentBirthday.set(Calendar.YEAR, currentYear);
        }
        else {
            widget_birthday_year.setSelection(currentYear - year - 1);
            field_currentBirthday.set(Calendar.YEAR, year);
        }
    }

    public void setMonths(int month)
    {
        reload_birthday_days(month);
        if(month <= 0 || month > 12) {
            widget_birthday_year.setSelection(0);
            field_currentBirthday.set(Calendar.MONTH, Calendar.JANUARY);
        }
        else {
            widget_birthday_year.setSelection(month - 1);
            field_currentBirthday.set(Calendar.MONTH, month);
        }
    }

    public void setDay(int day)
    {
        if(day <= 0 || day > field_currentBirthday.getActualMaximum(Calendar.DAY_OF_MONTH)) {
            widget_birthday_year.setSelection(0);
            field_currentBirthday.set(Calendar.DAY_OF_MONTH, 1);
        }
        else {
            widget_birthday_year.setSelection(day - 1);
            field_currentBirthday.set(Calendar.DAY_OF_MONTH, day);
        }
    }

    private boolean isOk()
    {
        if(field_ok) {
            widget_save.setClickable(true);
            widget_save.setTextColor(getResources().getColor(R.color.text_default));
        }
        else{
            widget_save.setClickable(false);
            widget_save.setTextColor(getResources().getColor(R.color.text_inactive));
        }
        return field_ok;
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent imageReturnedIntent) {
        super.onActivityResult(requestCode, resultCode, imageReturnedIntent);
        switch(requestCode) {
            case GALLERY_REQUEST:
                Uri selectedImage = imageReturnedIntent.getData();
                if(selectedImage != null) {
                    widget_avatar.setImageURI(selectedImage);
                    field_data_base.avatar = ((BitmapDrawable) widget_avatar.getDrawable()).getBitmap();
                    int width = field_data_base.avatar.getWidth();
                    int height = field_data_base.avatar.getHeight();
                    int maxLength = Math.max(width, height);
                    float coef = (float) maxLength / 240;
                    field_data_base.miniature = Bitmap.createScaledBitmap(field_data_base.avatar, (int) (width / coef), (int) (height / coef), false);
                    widget_avatar.setImageBitmap(field_data_base.miniature);
                }
                break;
        }
    }

    private ImageView.OnClickListener interface_avatarChanged = new ImageView.OnClickListener() {
        @Override
        public void onClick(View view) {
            Intent photoPickerIntent = new Intent(Intent.ACTION_PICK);
            photoPickerIntent.setType("image/*");
            startActivityForResult(photoPickerIntent, GALLERY_REQUEST);
        }
    };

    private Spinner.OnItemSelectedListener function_birthday_month_itemClickListener = new Spinner.OnItemSelectedListener() {
        @Override
        public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
            if(object_adapter_months.getItem(i) != null) {
                int currentMonth = i;
                field_currentBirthday.set(Calendar.MONTH, currentMonth);
                reload_birthday_days(currentMonth);
            }
        }

        @Override
        public void onNothingSelected(AdapterView<?> adapterView) {

        }
    };

    private CheckBox.OnCheckedChangeListener function_sex_male_checkedChangeListener = new CheckBox.OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
            if(b)
            {
                widget_sex_female.setChecked(false);
            }
        }
    };

    private CheckBox.OnCheckedChangeListener function_sex_female_checkedChangeListener = new CheckBox.OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
            if(b)
            {
                widget_sex_male.setChecked(false);
            }
        }
    };

    private Button.OnClickListener function_save_clickListener = new Button.OnClickListener() {
        @Override
        public void onClick(View view) {
            if (!isOk())
                return;

            field_data_base.name = widget_name.getText().toString();
            field_data_base.surname = widget_surname.getText().toString();
            field_data_base.patronymic = widget_patronymic.getText().toString();
            field_data_base.birthday = field_currentBirthday;
            if (widget_sex_male.isChecked())
                field_data_base.sex = 0;
            else if (widget_sex_female.isChecked())
                field_data_base.sex = 1;
            field_data_base.email = widget_email.getText().toString();
            field_data_base.phone = widget_phone.getText().toString();
            field_data_base.password = widget_password.getText().toString();

            GlobalData.currentProfileBase = field_data_base;

            GlobalData.socket.addExpectedRequest("Reply Registration", new ClientSocket.OnMessageReceived() {
                @Override
                public void received(JsonObject body) {
                    JsonElement element = body.get("status");
                    if (element != null) {
                        parent.logining(field_data_base.email, field_data_base.password);
                        getActivity().onBackPressed();
                    } else {

                    }
                }
            });
            Request request = new Request("Registration");
            request.body.add("ProfileBase", field_data_base.toJson());
            GlobalData.socket.sendMessage(request);
        }
    };
}
