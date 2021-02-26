#!/usr/bin/env python
# -*- coding: utf-8 -*-
from random import choice
import gi

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class list_2d(list):
    def __init__(self, *args, **kwargs):
        super(list_2d, self).__init__(args)
    
    def get_row(self, row_number):
        return self[row_number]

    def get_col(self, col_number):
        for row in self:
            yield row[col_number]

    def get_rows(self):
        for i in range(len(self)):
            yield self.get_row(i)

    def get_cols(self):
        for i in range(len(self[0])):
            yield list(self.get_col(i))

    def get_diagonals(self):
        diags = ([], [])
        for i in range(len(self)):
            diags[0].append(self[i][i])
            diags[1].append(self[i][len(self)-1 - i])
        return diags

    def flatten(self):
        return [item for row in self for item in row]

class morpion(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Morpion")

        self.current_player = "player"

        self.buttons = list_2d()

        # Make a top level container
        self.top_level_frame = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)
        self.add(self.top_level_frame)

        self.build_game_ui()

    def build_game_ui(self, rows=3, cols=3):
        # Make a grid to contain the 3x3 buttons
        grid = Gtk.Grid(column_homogeneous=True)
        self.top_level_frame.pack_start(grid, True, True, 0)

        # create the buttons
        for y in range(rows):
            self.buttons.append([])
            for x in range(cols):
                btn = Gtk.Button(label=" ")
                btn.connect("clicked", self.toggle_btn)

                self.buttons[-1].append(btn)
                grid.attach(btn, x, y, 1, 1)

        self.play_btn = Gtk.Button(label="Play again")
        self.play_btn.connect("clicked", lambda e:self.reset())
        self.play_btn.set_sensitive(False)
        self.top_level_frame.pack_end(self.play_btn, True, True, 0)

        self.msg = Gtk.Label(label="")
        self.msg.set_line_wrap(True)
        self.top_level_frame.pack_end(self.msg, True, True, 10)

    def toggle_btn(self, btn, new_txt="X", player="human"):
        if btn.get_label() == " ":
            btn.set_label(new_txt)

            # check if current player has won
            if self.check_victory():
                self.end_game()
                return
            
            # otherwise, let the next player do their thing
            if player == "human":
                self.run_bot()


    def set_grid_sensitivity(self, sensitivity):
        for row in self.buttons:
            for btn in row:
                btn.set_sensitive(sensitivity)
    
    def run_bot(self):
        self.current_player = "bot"

        # get remaining free buttons
        free_buttons = [btn for row in self.buttons for btn in row if btn.get_label() == " "]
        # get the bot to press a random button
        self.toggle_btn(choice(free_buttons), "0", player="bot")

        self.current_player = "player"

    def check_victory(self):
        # check rows
        for row in self.buttons.get_rows():
            if all(btn.get_label() == "0" for btn in row) or all(btn.get_label() == "X" for btn in row):
               return True
        # check cols
        for col in self.buttons.get_cols():
            if all(btn.get_label() == "0" for btn in col) or all(btn.get_label() == "X" for btn in col):
               return True
        # check diagonals
        for diag in self.buttons.get_diagonals():
            if all(btn.get_label() == "0" for btn in diag) or all(btn.get_label() == "X" for btn in diag):
               return True
        # check if all buttons have been played -> draw
        if all(btn.get_label() != " " for btn in self.buttons.flatten()):
            self.end_game(draw=True)
        else:
            return False

    def end_game(self, draw=False):
        self.set_grid_sensitivity(False)
        self.play_btn.set_sensitive(True)
        if not draw and self.current_player == "player":
            self.msg.set_label("You win!!!\nCongratulations")
        elif not draw:
            self.msg.set_label("You lose!\nTry again next time...")
        else:
            self.msg.set_label("Draw!\nTry again next time.")
    
    def reset(self):
        for btn in self.buttons.flatten():
            btn.set_label(" ")
        self.set_grid_sensitivity(True)
        self.play_btn.set_sensitive(False)
        self.msg.set_label("")


win = morpion()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()
