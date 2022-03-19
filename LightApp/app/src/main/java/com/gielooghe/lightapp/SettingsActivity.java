package com.gielooghe.lightapp;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;


public class SettingsActivity extends AppCompatActivity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.d("myTag", "Start Settings");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.settings_activity);
    }
}