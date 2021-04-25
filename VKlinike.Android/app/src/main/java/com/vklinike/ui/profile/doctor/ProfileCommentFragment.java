package com.vklinike.ui.profile.doctor;

import android.graphics.drawable.Drawable;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.vklinike.R;
import com.vklinike.data.CommentData;


public class ProfileCommentFragment extends Fragment {

    private CommentData fld_data;

    private TextView obj_fio;
    private ImageView obj_star1;
    private ImageView obj_star2;
    private ImageView obj_star3;
    private ImageView obj_star4;
    private ImageView obj_star5;
    private TextView obj_text;

    public ProfileCommentFragment(CommentData _data)
    {
        fld_data = _data;
    }

    public static ProfileCommentFragment newInstance(CommentData _data) {
        return new ProfileCommentFragment(_data);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_profile_comment, container, false);

        obj_fio = view.findViewById(R.id.profile_comment_fio);
        obj_star1 = view.findViewById(R.id.profile_comment_rating_star1);
        obj_star2 = view.findViewById(R.id.profile_comment_rating_star2);
        obj_star3 = view.findViewById(R.id.profile_comment_rating_star3);
        obj_star4 = view.findViewById(R.id.profile_comment_rating_star4);
        obj_star5 = view.findViewById(R.id.profile_comment_rating_star5);
        obj_text = view.findViewById(R.id.profile_comment_text);

        setFio(fld_data.sender.name, fld_data.sender.surname, fld_data.sender.patronymic);
        setRating(fld_data.rating);
        obj_text.setText(fld_data.text);

        return view;
    }

    public void setFio(String name, String surname, String patronymic)
    {
        String result;
        result = patronymic + " " + name + " " + surname;
        obj_fio.setText(result);
    }

    public void setRating(int _rating)
    {
        ImageView stars [] = {obj_star1, obj_star2, obj_star3, obj_star4, obj_star5};
        for(int i = 1; i < 6; i++)
        {
            Drawable new_star;
            if(fld_data.rating >= i)
                new_star = getResources().getDrawable(R.drawable.icon_profile_comment_star_gold);
            else
                new_star = getResources().getDrawable(R.drawable.icon_profile_comment_star_empty);
            stars[i-1].setImageDrawable(new_star);
        }
    }
}
