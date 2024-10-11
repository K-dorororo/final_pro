package com.iot.afinal;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView tempTextView = findViewById(R.id.tempTextView);
        final TextView humidityTextView = findViewById(R.id.humidityTextView);

        ApiService apiService = RetrofitClient.getApiService();
        Call<SensorData> call = apiService.getSensorData();

        call.enqueue(new Callback<SensorData>() {
            @Override
            public void onResponse(Call<SensorData> call, Response<SensorData> response) {
                if (response.isSuccessful()) {
                    SensorData sensorData = response.body();
                    if (sensorData != null) {
                        tempTextView.setText("현재 온도: " + sensorData.getTemperature() + "°C");
                        humidityTextView.setText("현재 습도: " + sensorData.getHumidity() + "%");
                    }
                } else {
                    Log.e(TAG, "Request failed with code: " + response.code());
                }
            }

            @Override
            public void onFailure(Call<SensorData> call, Throwable t) {
                Log.e(TAG, "Request failed: " + t.getMessage());
            }
        });

        // 홈
        LinearLayout homeBtn = findViewById(R.id.btn_home);
        homeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });

        // 리포트
        LinearLayout reportBtn = findViewById(R.id.btn_report);
        reportBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, ReportActivity.class);
                startActivity(intent);
            }
        });

        // 메뉴
        LinearLayout menuBtn = findViewById(R.id.btn_menu);
        menuBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, MenuActivity.class);
                startActivity(intent);
            }
        });
    }
}
