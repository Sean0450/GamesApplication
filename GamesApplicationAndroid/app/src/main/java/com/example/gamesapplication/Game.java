package com.example.gamesapplication;

public class Game {
    TypeOfGame type;
    int players;
    String typeOfValue;
    int rows;
    int columns;
    boolean downMenu;
    public Game(TypeOfGame type, int players, String typeOfValue, int rows, int columns, boolean downMenu) {
        this.type = type;
        this.players = players;
        this.typeOfValue = typeOfValue;
        this.rows = rows;
        this.columns = columns;
        this.downMenu = downMenu;
    }

    public TypeOfGame getType() {
        return type;
    }

    public int getPlayers() {
        return players;
    }

    public String getTypeOfValue() {
        return typeOfValue;
    }

    public int getRows() {
        return rows;
    }

    public int getColumns() {
        return columns;
    }

    public boolean isDownMenu() {
        return downMenu;
    }
}
