package com.vklinike.ui.order;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;

import com.vklinike.R;


public class OrderBrowserFragment extends Fragment {

    private String field_adress;

    private WebView widget_browser;

    public OrderBrowserFragment(String _adress)
    {
        field_adress = _adress;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_browser, container, false);

        widget_browser = view.findViewById(R.id.browser);
        widget_browser.getSettings().setJavaScriptEnabled(true);
        widget_browser.setWebViewClient(new OrderBrowserWebViewClient(getActivity()));
        widget_browser.loadUrl(field_adress);

        return view;
    }
}
