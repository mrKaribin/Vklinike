package com.vklinike.ui;

import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;

import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.DialogFragment;

import com.vklinike.GlobalData;
import com.vklinike.ui.socket.ClientSocket;

public class NotificationDialogFragment extends DialogFragment {

    private String field_text;

    public NotificationDialogFragment(String _text){
        field_text = _text;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setMessage(field_text)
                .setPositiveButton("Понятно", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        GlobalData.socket = new ClientSocket(GlobalData.host, GlobalData.port_tcp);
                        GlobalData.socket.setOnConnection(GlobalData.interface_connection);
                        GlobalData.socket.execute();
                    }
                });
        return builder.create();
    }
}
