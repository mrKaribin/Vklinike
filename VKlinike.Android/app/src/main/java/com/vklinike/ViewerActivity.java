package com.vklinike;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class ViewerActivity extends AppCompatActivity {

    private OnBackPressed interface_back;

    private Fragment widget_fragment;
    private ImageButton widget_back;

    public static Fragment currentFragment;
    public static OnBackPressed currentInterfaceBack;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_viewer);
        getSupportActionBar().hide();

        widget_fragment = currentFragment;
        interface_back = currentInterfaceBack;
        widget_back = findViewById(R.id.viewer_back);

        FragmentManager manager = getSupportFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();
        transaction.replace(R.id.layout_viewer, currentFragment);
        transaction.commit();
        widget_back.setOnClickListener(new ImageButton.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(interface_back != null)
                    interface_back.onPressed();
                onBackPressed();
            }
        });
    }

    public interface OnBackPressed{
        void onPressed();
    }
}
