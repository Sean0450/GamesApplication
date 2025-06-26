package com.example.gamesapplication;

import android.annotation.SuppressLint;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.gamesapplication.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity
        implements NavigationDrawerHelper.NavigationListener {
    private Button restart;
    GameArea gameArea;
    GameInformationPanel gameInformationPanel;
    NumberPanel numberPanel;
    Game[] games;
    private NavigationDrawerHelper navigationDrawerHelper;

    // Used to load the 'myapplication' library on application startup.
    static {
        System.loadLibrary("gamesapplication");
    }

    private ActivityMainBinding binding;

    @SuppressLint("ResourceAsColor")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        gameInformationPanel = new GameInformationPanel(binding.getRoot());
        numberPanel = new NumberPanel(binding.getRoot());

        gameArea = new GameArea(binding.getRoot(), displayMetrics, gameInformationPanel, numberPanel);

        restart = findViewById(R.id.restartButton);
        restart.setOnClickListener(v -> {
            restart();
            gameArea.setArea();
            gameInformationPanel.restart();
        });

        games = new Game[]{new Game(TypeOfGame.TicTacToe, 2, "Очки", 3, 3, false),
                new Game(TypeOfGame.Sudoku, 1, "Ошибки", 9, 9, true),
                new Game(TypeOfGame.Tags, 1, "Ходы", 4, 4, false)};

        navigationDrawerHelper = new NavigationDrawerHelper(this, this);

        changeGame(2);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return navigationDrawerHelper.onOptionsItemSelected(item) ||
                super.onOptionsItemSelected(item);
    }

    @Override
    public void onGameSelected(int gameIndex) {
        changeGame(gameIndex);
    }

    private void changeGame(int num) {
        InputDialog.showInputDialog(games[num].getPlayers() == 2, this).thenAccept(names -> {
            if (names == null) return;
            setGame(games[num].getType().name());
            gameArea.createArea(games[num].getRows(), games[num].getColumns(), games[num].getType());
            gameInformationPanel.changeValue(games[num].getTypeOfValue());
            if (names[1] == null) {
                Toast.makeText(this, "Введено имя: " + names[0], Toast.LENGTH_SHORT).show();
                gameInformationPanel.updatePanel(names[0], games[num].getType());
            } else {
                Toast.makeText(this, "Введены имена: " + names[0] + " и " + names[1], Toast.LENGTH_SHORT).show();
                gameInformationPanel.updatePanel(names[0], names[1], games[num].getType());
            }
            gameArea.setArea();
            numberPanel.setVisible(games[num].isDownMenu());
        });
    }

    public native void setGame(String name);
    public native void restart();
}