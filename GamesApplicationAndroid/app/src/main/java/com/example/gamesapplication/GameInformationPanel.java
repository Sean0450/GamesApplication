package com.example.gamesapplication;

import android.view.View;
import android.widget.TextView;

public class GameInformationPanel {
    private TextView text;
    private String player1;
    private String player2;
    private int value1;
    private int value2;
    String typeOfValue;
    TypeOfGame typeOfGame;
    boolean lock;
    public GameInformationPanel(View rootView){
        text = rootView.findViewById(R.id.gameInfoText);
    }

    public void updatePanel(){
        value1++;
        text.setText(toString());
    }

    public void updatePanel(String player, TypeOfGame type){
        player1 = player;
        sendPlayerName(player);
        player2 = null;
        value1 = 0;
        value2 = 0;
        typeOfGame = type;
        text.setText(toString());
        lock = false;
    }

    public void updatePanel(String player1, String player2, TypeOfGame type){
        this.player1 = player1;
        sendPlayerName(player1);
        this.player2 = player2;
        sendPlayerName(player2);
        value1 = 0;
        value2 = 0;
        text.setText(toString());
        typeOfGame = type;
        lock = false;
    }
    public void changeValue(String type){
        typeOfValue = type;
    }

    @Override
    public String toString(){
        String result = "";

        if(player2 == null){
            result += "Игрок: " + player1;
            if (typeOfValue != null){
                result += "\t|\t" + typeOfValue + ": " + value1;
            }
        } else {
            result += "Игрок 1: " + player1 + "\t | \t" + typeOfValue + ": " + value1 + "\n"
                    + "Игрок 2: " + player2 + "\t | \t" + typeOfValue + ": " + value2 + "\n";
        }

        return result;
    }

    public boolean isAll(){
        String winner = getWinnerInformation();
        if(winner.isEmpty())
            return false;
        if(!lock) {
            if (winner.equals(player1)) value1 += 1;
            else value2 += 1;
            text.setText(toString());
            lock = true;
        }
        return true;
    }

    public void restart(){
        if(typeOfGame != TypeOfGame.TicTacToe){
            value1 = 0;
            value2 = 0;
            text.setText(toString());
        }
        lock = false;
    }

    public native void sendPlayerName(String name);
    public native String getWinnerInformation();
}
