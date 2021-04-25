package com.vklinike.ui.dialog;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Point;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.Display;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.ui.socket.ClientSocket;


public class MessageEnclosureImageFragment extends Fragment {

    private Bitmap field_enclosure;
    private String field_enclosure_name;

    private ImageView widget_enclosure;

    public MessageEnclosureImageFragment(String _enclosure_name){
        field_enclosure_name = _enclosure_name;
    }

    public MessageEnclosureImageFragment(String _enclosure_name, Bitmap _enclosure){
        field_enclosure_name = _enclosure_name;
        field_enclosure = _enclosure;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_message_enclosure_image, container, false);

        widget_enclosure = view.findViewById(R.id.enclosure_image);
        if(field_enclosure != null)
            setImage(field_enclosure);
        if(!field_enclosure_name.isEmpty())
            loadImage(field_enclosure_name);

        return view;
    }

    public void setImage(Bitmap image){
        Display display = getActivity().getWindowManager().getDefaultDisplay();
        Point point = new Point();
        display.getSize(point);
        int maximumSize = Math.min((int)(point.x * 0.6), image.getWidth());
        int width = image.getWidth();
        int height = image.getHeight();
        int maxLength = Math.max(width, height);
        float coef = (float) maxLength / maximumSize;
        field_enclosure = Bitmap.createScaledBitmap(image, (int)(width / coef) - 1, (int)(height / coef) - 1, true);
        widget_enclosure.setImageBitmap(field_enclosure);
    }

    public void loadImage(String _enclosure_name){
        field_enclosure_name = _enclosure_name;
        GlobalData.socket.addExpectedEnclosure(field_enclosure_name, new ClientSocket.OnEnclosureReceived() {
            @Override
            public void received(byte[] body) {
                Bitmap image = BitmapFactory.decodeByteArray(body, 0 ,body.length);
                setImage(image);
            }
        });
    }
}
