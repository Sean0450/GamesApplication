package com.example.gamesapplication;



import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.GradientDrawable;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import java.util.Optional;

public class GameArea {
    DisplayMetrics displayMetrics;
    View rootView;
    int columns;
    int rows;
    int cell_size;
    boolean lock;
    TableLayout area;
    NumberPanel numberPanel;
    GameInformationPanel informationPanel;
    TypeOfGame type;
    Drawable originalAreaBackground;
    public GameArea(View rootView, DisplayMetrics displayMetrics, GameInformationPanel gameInformationPanel, NumberPanel numberPanel){
        this.area = rootView.findViewById(R.id.gameArea);
        this.rootView = rootView;
        this.displayMetrics = displayMetrics;
        this.informationPanel = gameInformationPanel;
        this.numberPanel = numberPanel;
        this.lock = false;
        originalAreaBackground = area.getBackground();
    }

    public void createArea(int columns, int rows, TypeOfGame type){
        this.type = type;
        area.removeAllViews();
        area.setBackground(originalAreaBackground);
        int widthPixels = displayMetrics.widthPixels;
        int heightPixels = displayMetrics.heightPixels;
        float density = displayMetrics.density;
        int screenWidthDp = Math.round(widthPixels / density);
        int screenHeightDp = Math.round(heightPixels / density);

        cell_size = Math.min((screenWidthDp - 20) / columns, (screenHeightDp - 20) / rows);

        this.columns = columns;
        this.rows = rows;

        int cellSizePx = (int) TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                cell_size,
                area.getContext().getResources().getDisplayMetrics()
        );

        TableLayout.LayoutParams tableParams = new TableLayout.LayoutParams(
                TableLayout.LayoutParams.WRAP_CONTENT,
                TableLayout.LayoutParams.WRAP_CONTENT
        );

        TableRow.LayoutParams cellParams = new TableRow.LayoutParams(
                cellSizePx,
                cellSizePx
        );

        for (int row = 0; row < rows; row++) {
            TableRow tableRow = new TableRow(area.getContext());

            for (int col = 0; col < columns; col++) {
                GradientDrawable border = new GradientDrawable();
                TextView cell = new TextView(area.getContext());

                cell.setLayoutParams(cellParams);
                cell.setBackgroundResource(R.drawable.cell_border);
                cell.setGravity(Gravity.CENTER);
                cell.setText(" ");
                cell.setAutoSizeTextTypeWithDefaults(TextView.AUTO_SIZE_TEXT_TYPE_UNIFORM);
                cell.setId(row * columns + col);

                border.setStroke(2, Color.BLACK);
                if(type == TypeOfGame.Sudoku){
                    if ((col % 3 == 1) && (row % 3 == 1)){
                        border.setBounds(1, 1, 3, 1);
                        border.setColor(Color.LTGRAY);
                    }
                }
                cell.setBackground(border);

                cell.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        if (!lock) {
                            Optional<Integer> optional;
                            switch (type) {
                                case Tags: {
                                    optional = sendData(cell.getId(), Optional.empty());
                                    if (!optional.isEmpty()) {
                                        TextView newCell = rootView.findViewById(optional.get());
                                        newCell.setText(cell.getText());
                                        cell.setText("");
                                        informationPanel.updatePanel();
                                    }
                                    break;
                                }
                                case Sudoku: {
                                    int number = numberPanel.getNumber();
                                    if (number != -1) {
                                        optional = sendData(cell.getId(), Optional.of(number));
                                        if (!optional.isEmpty()) {
                                            cell.setText(String.valueOf(number));
                                        } else {
                                            informationPanel.updatePanel();
                                        }
                                    }
                                    break;
                                }
                                case TicTacToe: {
                                    optional = sendData(cell.getId(), Optional.empty());
                                    if (optional.get() == 1) {
                                        cell.setText("X");
                                    } else {
                                        cell.setText("O");
                                    }
                                    break;
                                }
                            }
                        }
                        if (informationPanel.isAll()){
                            lock = true;
                            GradientDrawable border = new GradientDrawable();
                            border.setStroke(8, Color.GREEN);
                            area.setBackground(border);
                        }
                    }
                });
                tableRow.addView(cell);
            }
            area.addView(tableRow);
        }

    }

    public void setArea() {
        area.setBackground(originalAreaBackground);
        if(type != TypeOfGame.TicTacToe) {
            int[] newArea = getUserArea();
            TextView[] cells = new TextView[newArea.length];
            for (int i=0; i<newArea.length; i++) {
                System.out.println(newArea[i]+" ");
            }
            for (int i=0; i<newArea.length; i++) {
                cells[i] = rootView.findViewById(i);
                if (newArea[i] != 0) {
                    cells[i].setText(String.valueOf(newArea[i]));
                } else {
                    cells[i].setText(" ");
                }
            }
        } else {
            TextView[] cells = new TextView[9];
            for (int i=0; i<9; i++){
                    cells[i] = rootView.findViewById(i);
                    cells[i].setText(" ");
            }
        }
        lock = false;
    }

    public native Optional<Integer> sendData(int index, Optional<Integer> value);
    public native int[] getUserArea();
}
