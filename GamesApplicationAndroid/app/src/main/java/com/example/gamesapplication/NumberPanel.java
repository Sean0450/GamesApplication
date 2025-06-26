package com.example.gamesapplication;

import android.view.View;
import android.widget.Button;
import android.widget.HorizontalScrollView;

import androidx.core.content.ContextCompat;

public class NumberPanel {
    private Button lastClickedButton = null;
    Button[] numberButtons;
    private HorizontalScrollView numberPanel;

    public NumberPanel(View rootView){
        numberButtons = new Button[]{rootView.findViewById(R.id.btn1),
                rootView.findViewById(R.id.btn2), rootView.findViewById(R.id.btn3),
                rootView.findViewById(R.id.btn4), rootView.findViewById(R.id.btn5),
                rootView.findViewById(R.id.btn6), rootView.findViewById(R.id.btn7),
                rootView.findViewById(R.id.btn8), rootView.findViewById(R.id.btn9)};
        for (Button btn : numberButtons){
            btn.setOnClickListener(v -> {
                if (lastClickedButton != null) {
                    lastClickedButton.setBackgroundColor(ContextCompat.getColor(btn.getContext(), R.color.purple_200));
                }
                btn.setBackgroundColor(ContextCompat.getColor(btn.getContext(), R.color.purple_500));
                lastClickedButton = btn;
            });
        }

        numberPanel = rootView.findViewById(R.id.number_Panel);
    }

    public void setVisible(boolean visible){
        if (visible) {
            numberPanel.setVisibility(View.VISIBLE);
        } else {
            numberPanel.setVisibility(View.GONE);
        }
    }

    public int getNumber(){
        if(lastClickedButton != null){
            return Integer.parseInt(lastClickedButton.getText().toString());
        }
        return -1;
    }
}
