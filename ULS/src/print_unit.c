#include "../inc/uls.h"

void print_unit_color(const char *unit, mode_t mode) {
    if (S_ISDIR(mode)) {
        mx_printstr(BLUE_COLOR);
        mx_printstr(unit);
        mx_printstr(RESET_COLOR);
        mx_printstr(" ");
    } else if (S_ISLNK(mode)) {
        mx_printstr(CYAN_COLOR);
        mx_printstr(unit);
        mx_printstr(RESET_COLOR);
        mx_printstr(" ");
    } else if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
        mx_printstr(GREEN_COLOR);
        mx_printstr(unit);
        mx_printstr(RESET_COLOR);
        mx_printstr(" ");
    } else if (S_ISCHR(mode) || S_ISBLK(mode)) {
        mx_printstr(YELLOW_COLOR);
        mx_printstr(unit);
        mx_printstr(RESET_COLOR);
        mx_printstr(" ");
    } else if (S_ISREG(mode)) {
        mx_printstr(RESET_COLOR);
        mx_printstr(unit);
        mx_printstr(RESET_COLOR);
        mx_printstr(" ");
    } else {
        mx_printstr(MAGENTA_COLOR);
        mx_printstr(unit);
        mx_printstr(RESET_COLOR);
        mx_printstr(" ");
    }
}

void print_unit(const char *unit, char *color) {
    mx_printstr(color);
    mx_printstr(unit);
    mx_printstr(RESET_COLOR);
    mx_printstr("  ");
}

void print_unit_info(Unit *unit) {
    mx_printchar(unit->type);
    mx_printstr(unit->permissions);
    mx_printstr(" ");
    mx_printstr(unit->owner);
    mx_printstr(" ");
    mx_printstr(unit->group);
    mx_printstr(" ");

    // Convert size to string using mx_itoa
    mx_printstr(mx_itoa(unit->size));

    mx_printstr(" ");

    mx_printstr(unit->modification_time);
    mx_printstr(" ");
    mx_printstr(unit->name);

    // Print symlink information if it exists
    if (unit->symlink != NULL) {
        mx_printstr(" -> ");
        mx_printstr(unit->symlink);
    }

    mx_printstr("\n");
}
