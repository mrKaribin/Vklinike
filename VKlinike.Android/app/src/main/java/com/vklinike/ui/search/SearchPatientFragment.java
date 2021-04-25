package com.vklinike.ui.search;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Spinner;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.vklinike.ui.EmptyFragment;
import com.vklinike.ui.socket.ClientSocket;
import com.vklinike.GlobalData;
import com.vklinike.R;
import com.vklinike.data.ProfileBaseData;
import com.vklinike.data.Request;
import com.vklinike.data.SpecializationData;

import java.util.ArrayList;
import java.util.List;

public class SearchPatientFragment extends Fragment {

    public class SearchResultData
    {
        public SearchResultData(ProfileBaseData _profile, List<SpecializationData> _specializations, double  _rating){
            profile = _profile;
            specializations = _specializations;
            rating = _rating;
        }

        ProfileBaseData profile;
        List<SpecializationData> specializations;
        double rating;
    }

    private List<SearchResultData> array_data;

    private ArrayAdapter<String> object_adapter_specializations;

    private ImageButton widget_search_finding;
    private EditText widget_search_text;
    private Spinner widget_search_filter;

    public SearchPatientFragment()
    {
        array_data = new ArrayList<SearchResultData>();
    }

    public static SearchPatientFragment newInstance() {
        return new SearchPatientFragment();
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_search_patient, container, false);

        widget_search_finding = view.findViewById(R.id.search_patient_finding);
        widget_search_text = view.findViewById(R.id.search_patient_text);
        widget_search_filter = view.findViewById(R.id.search_patient_specialization);

        prepare();
        search();

        return view;
    }
    public void prepare()
    {
        List<String> specializations = new ArrayList<String>();
        for(int i = 0; i < GlobalData.availableSpecializations.size(); i++)
            specializations.add(GlobalData.availableSpecializations.get(i).name);
        object_adapter_specializations = new ArrayAdapter<String>(getContext(), R.layout.support_simple_spinner_dropdown_item, specializations);
        widget_search_filter.setAdapter(object_adapter_specializations);

        widget_search_finding.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                search();
            }
        });
    }

    public void reload()
    {
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        for(int i = 0; i < array_data.size(); i++)
        {
            SearchPatientPreviewFragment new_fragment = new SearchPatientPreviewFragment(
                    array_data.get(i).profile,
                    array_data.get(i).specializations,
                    array_data.get(i).rating
            );
            transaction.add(R.id.layout_search_patient_result, new_fragment);
        }
        if(array_data.isEmpty())
            transaction.replace(R.id.layout_search_patient_result, new EmptyFragment("По вашему запросу мы ничего не нашли"));
        transaction.commit();
    }

    public void search(){
        int specialization_id = -1;
        if(GlobalData.availableSpecializations.get(widget_search_filter.getSelectedItemPosition()) != null)
            specialization_id = GlobalData.availableSpecializations.get(widget_search_filter.getSelectedItemPosition()).id;

        Request request = new Request("Search Doctor");
        request.body.addProperty("key", widget_search_text.getText().toString());
        request.body.addProperty("specialization_id", specialization_id);

        GlobalData.socket.addExpectedRequest("Reply Search Doctor", new ClientSocket.OnMessageReceived() {
            @Override
            public void received(JsonObject body) {
                JsonElement element = body.get("status");
                if(element != null){
                    if(element.getAsString().equals("successful")){
                        element = body.get("Doctors");
                        if(element != null){
                            JsonArray array = element.getAsJsonArray();
                            for(int i = 0; i < array.size(); i++){
                                List<SpecializationData> specializations = new ArrayList<SpecializationData>();
                                JsonElement _profile = array.get(i).getAsJsonObject().get("Profile");
                                JsonElement _specializations = array.get(i).getAsJsonObject().get("Specializations");
                                JsonElement _rating = array.get(i).getAsJsonObject().get("Rating");

                                if(_specializations != null){
                                    JsonArray __specializations = _specializations.getAsJsonArray();
                                    for(int j = 0; j < __specializations.size(); j++)
                                        specializations.add(SpecializationData.createFromJson(__specializations.get(j).getAsJsonObject()));
                                }

                                if(_profile != null && _rating != null)
                                    array_data.add(new SearchResultData(
                                            ProfileBaseData.createFromJson(_profile.getAsJsonObject()),
                                            specializations,
                                            _rating.getAsFloat()
                                    ));
                            }
                            reload();
                        }
                    }
                    else{

                    }
                }
            }
        });
        GlobalData.socket.sendMessage(request);
    }
}
