package com.vklinike;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.vklinike.data.DialogsData;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.ProfileDoctorData;
import com.vklinike.data.ProfilePatientData;
import com.vklinike.data.SpecializationData;
import com.vklinike.data.ValutaData;
import com.vklinike.ui.socket.ClientSocket;

import java.util.List;

public class GlobalData {

    public enum Mode {
        Doctor (0),
        Patient (1);

        private int title;

        Mode(int _title)
        {
            title = _title;
        }

        public int toInt()
        {
            return title;
        }
    }

    public enum Access {
        Owner (0),
        Friend (1),
        Guest (2);

        private int title;

        Access(int _title){
            title = _title;
        }

        public int toInt(){
            return title;
        }
    }

    public static String host = "delphino.ddnsking.com";
    public static int port_tcp = 10228;
    public static int port_second = 10322;

    public static Mode currentMode;
    public static String currentLogin;
    public static String currentPassword;
    public static ClientSocket socket;
    public static ClientSocket.OnConnectionListener interface_connection;
    public static ProfileBaseData currentProfileBase;
    public static ProfileDoctorData currentProfileDoctor;
    public static ProfilePatientData currentProfilePatient;
    public static DialogsData currentDialogs;
    public static List<SpecializationData> availableSpecializations;
    public static List<ValutaData> availableValutes;

    public static void setAvailableSpecializations(JsonArray array) {
        availableSpecializations.clear();
        for(int i = 0; i < array.size(); i++) {
            JsonElement element = array.get(i);
            if(element != null)
                availableSpecializations.add(SpecializationData.createFromJson(element.getAsJsonObject()));
        }
    }

    public static void setAvailableValutes(JsonArray array) {
        availableValutes.clear();
        for(int i = 0; i < array.size(); i++) {
            JsonElement element = array.get(i);
            if(element != null)
                availableValutes.add(ValutaData.createFromJson(element.getAsJsonObject()));
        }
    }
}
