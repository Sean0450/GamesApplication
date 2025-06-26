package com.example.gamesapplication;
import android.view.MenuItem;

import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;

import com.google.android.material.navigation.NavigationView;

public class NavigationDrawerHelper {
    private final DrawerLayout drawerLayout;
    private final ActionBarDrawerToggle drawerToggle;
    private final NavigationView navigationView;
    private final NavigationListener navigationListener;

    public interface NavigationListener {
        void onGameSelected(int gameIndex);
    }

    public NavigationDrawerHelper(AppCompatActivity activity, NavigationListener listener) {
        this.navigationListener = listener;

        drawerLayout = activity.findViewById(R.id.drawer_layout);
        navigationView = activity.findViewById(R.id.nav_view);

        if (activity.getSupportActionBar() != null) {
            activity.getSupportActionBar().setDisplayHomeAsUpEnabled(true);
            drawerToggle = new ActionBarDrawerToggle(
                    activity, drawerLayout, R.string.open_drawer, R.string.close_drawer);
            drawerLayout.addDrawerListener(drawerToggle);
            drawerToggle.syncState();
        } else {
            drawerToggle = null;
        }

        setupNavigation();
    }

    private void setupNavigation() {
        navigationView.setNavigationItemSelectedListener(item -> {
            int id = item.getItemId();

            if (id == R.id.nav_TicTacToe) {
                navigationListener.onGameSelected(0);
            } else if (id == R.id.nav_Sudoku) {
                navigationListener.onGameSelected(1);
            } else if (id == R.id.nav_Tags) {
                navigationListener.onGameSelected(2);
            }

            drawerLayout.closeDrawer(GravityCompat.START);
            return true;
        });
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        return drawerToggle != null && drawerToggle.onOptionsItemSelected(item);
    }
}