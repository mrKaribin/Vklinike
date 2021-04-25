package com.vklinike.ui.dialog;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.vklinike.R;


public class DialogEnclosureImageFragment extends Fragment {

    private Uri object_imageUri;
    private Bitmap object_image;

    private ImageView widget_image;

    private OnDeleteListener interface_delete;

    public DialogEnclosureImageFragment(Uri image_uri){
        object_imageUri = image_uri;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_dialog_enclosure_image, container, false);

        widget_image = view.findViewById(R.id.dialog_enclosure_image);

        widget_image.setImageURI(object_imageUri);
        object_image = ((BitmapDrawable) widget_image.getDrawable()).getBitmap();
        int width = object_image.getWidth();
        int height = object_image.getHeight();
        int maxLength = Math.max(width, height);
        float coef = (float) maxLength / 150;
        Bitmap _image = Bitmap.createScaledBitmap(object_image, (int) (width / coef), (int) (height / coef),false);
        widget_image.setImageBitmap(_image);

        widget_image.setOnClickListener(new ImageView.OnClickListener() {
            @Override
            public void onClick(View view) {
                interface_delete.deleting();
            }
        });

        return view;
    }

    public void delete(){
        interface_delete.deleting();
    }

    public void setDeleteInterface(OnDeleteListener _interface){
        interface_delete = _interface;
    }

    public Bitmap getImage(){
        return object_image;
    }

    interface OnDeleteListener{
        void deleting();
    }
}
