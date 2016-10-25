package com.baishan.ndkdemo;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText("");
    }

    public void play(View v){
       final int type =  Integer.parseInt((String) v.getTag());
        new Thread(new Runnable() {
            @Override
            public void run() {
                String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "rayyeung.m4a";
                VoiceFix.fix(path, type);
            }
        }).start();
    }


    // Used to load the 'native-lib' library on application startup.

}
