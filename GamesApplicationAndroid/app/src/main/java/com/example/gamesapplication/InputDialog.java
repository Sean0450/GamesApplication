package com.example.gamesapplication;

import android.app.AlertDialog;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import java.util.concurrent.CompletableFuture;

public class InputDialog {
    public static CompletableFuture<String[]> showInputDialog(boolean needTwoNames, Context context) {
        CompletableFuture<String[]> future = new CompletableFuture<>();

        LayoutInflater inflater = LayoutInflater.from(context);
        View dialogView = inflater.inflate(R.layout.dialog_name_input, null);

        EditText editTextName1 = dialogView.findViewById(R.id.editTextName1);
        EditText editTextName2 = dialogView.findViewById(R.id.editTextName2);
        TextView labelName2 = dialogView.findViewById(R.id.labelName2);

        editTextName2.setVisibility(needTwoNames ? View.VISIBLE : View.GONE);
        labelName2.setVisibility(needTwoNames ? View.VISIBLE : View.GONE);

        AlertDialog dialog = new AlertDialog.Builder(context)
                .setTitle("Введите имена")
                .setView(dialogView)
                .setPositiveButton("OK", (d, which) -> {
                    String name1 = editTextName1.getText().toString().trim();
                    String name2 = needTwoNames ? editTextName2.getText().toString().trim() : null;
                    future.complete(new String[]{name1, name2});
                })
                .setNegativeButton("Отмена", (d, which) -> {
                    future.complete(null);
                })
                .create();

        dialog.setOnDismissListener(d -> {
            if (!future.isDone()) {
                future.complete(null);
            }
        });

        dialog.show();
        return future;
    }
}