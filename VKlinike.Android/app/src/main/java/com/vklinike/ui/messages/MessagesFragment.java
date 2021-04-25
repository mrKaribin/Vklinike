package com.vklinike.ui.messages;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ui.EmptyFragment;

public class MessagesFragment extends Fragment {

    public static MessagesFragment newInstance() {
        return new MessagesFragment();
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_messages, container, false);
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        for(int i = 0; i < GlobalData.currentDialogs.dialogs.size(); i++)
        {
            MessagePreviewFragment new_fragment = MessagePreviewFragment.newInstance(GlobalData.currentDialogs.dialogs.get(i));
            transaction.add(R.id.layout_messages_preview, new_fragment);
        }
        if(GlobalData.currentDialogs.dialogs.isEmpty())
            transaction.replace(R.id.layout_messages_preview, new EmptyFragment("У вас еще нет диалогов"));
        transaction.commit();
        return view;
    }
}
