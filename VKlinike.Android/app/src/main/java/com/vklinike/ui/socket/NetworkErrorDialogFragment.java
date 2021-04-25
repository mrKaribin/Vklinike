package com.vklinike.ui.socket;

import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;

import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.DialogFragment;

import com.vklinike.GlobalData;

public class NetworkErrorDialogFragment extends DialogFragment {
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setMessage("Нет соединения с сервером")
                .setPositiveButton("Повторить", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        GlobalData.socket = new ClientSocket(GlobalData.host, GlobalData.port_tcp);
                        GlobalData.socket.setOnConnection(GlobalData.interface_connection);
                        GlobalData.socket.execute();
                    }
                })
                .setNegativeButton("Выход", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        getActivity().finish();
                    }
                });
        return builder.create();
    }
}
