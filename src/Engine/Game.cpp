//
// Created by rei on 31.10.24.
//

#include "Game.h"
#include <curses.h>
#include <chrono>
#include <thread>
#include <string>
#include "CreatureLoader.h"

namespace DespoilerEngine {
    CreatureCollection LowCreatures;
    CreatureCollection MediumCreatures;
    WINDOW* main_window;
    WINDOW* game_window;
    Game::rect game_area = {{0, 0}, {0, 0}};
    Game::rect screen_area = {{0, 0}, {0, 0}};

    void Game::drawBox(WINDOW* window, int pos_y, int pos_x, bool refresh)
    {
        if(refresh) werase(main_window);
        wattron(window, A_BOLD);
        box(window, pos_y, pos_x);
        wattroff(window, A_BOLD);
    }

    void Game::enableKeyBlockInput(WINDOW* window)
    {
        keypad(window, true);
        nodelay(window, false);
    }

    void Game::loadCreature()
    {
        LowCreatures.Creatures = CreatureLoader::loadCreatures("./resources/Creatures/low");
        MediumCreatures.Creatures = CreatureLoader::loadCreatures("./resources/Creatures/medium");
    }


    int Game::init()
    {
        loadCreature();
        main_window = initscr();
        cbreak();
        noecho();
        clear();
        refresh();
        resize_term(0,0);;
        PDC_set_title("Dungeon Despoiler");
        curs_set(0); // Make cursor invisible
        if(!has_colors())
        {
            endwin();
            printf("Error: Terminal does not support color.\n");
            exit(1);
        }

        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);

        constexpr int_fast8_t screen_width = 80;
        constexpr int_fast8_t screen_height = 24;
        constexpr int infopanel = 4;

        screen_area = {{0, 0}, {screen_width, screen_height}};
        game_area = {{0, 0}, {static_cast<int_fast8_t>(screen_area.width() - 2), static_cast<int_fast8_t>(screen_area.height() - infopanel - 4)}};
        game_window = newwin(static_cast<int>(screen_area.height() - infopanel - 2), static_cast<int>(screen_area.width() - 2),
                             static_cast<int>(screen_area.top() + 1), static_cast<int>(screen_area.left() + 1));
        main_window = newwin(static_cast<int>(screen_area.height()), static_cast<int>(screen_area.width()), 0, 0);

        enableKeyBlockInput(game_window);
        enableKeyBlockInput(main_window);

        return 0;
    }

    void Game::run()
    {
        player.display_char = '0';
        player.position = {1, 1};
        /* Main game loop */
        bool exit_req = false;
        drawBox(main_window, 0, 0, false);
        wmove(main_window, static_cast<int>(game_area.bottom() + 3), 1);
        whline(main_window, '-', static_cast<int>(screen_area.width() - 2));

        wrefresh(main_window);
        wattron(game_window, COLOR_PAIR(1));
        mvwaddch(game_window, 9, 9, '!');
        wattroff(game_window, COLOR_PAIR(1));
        mvwaddch(game_window, player.position.y, player.position.x, player.display_char);
        wrefresh(game_window);

        while(true)
        {
            werase(game_window);

            mvwaddch(game_window, player.position.y, player.position.x, ' ');
            switch (tolower(wgetch(main_window)))
            {
                case 'q':
                    exit_req = true;
                    break;
                case KEY_UP:
                case 'w':
                    if(player.position.y > game_area.top())
                        player.position.y -= 1;
                    break;
                case KEY_DOWN:
                case 's':
                    if(player.position.y < game_area.bottom())
                        player.position.y += 1;
                    break;
                case KEY_LEFT:
                case 'a':
                    if(player.position.x > game_area.left() + 1)
                        player.position.x -= 1;
                    break;
                case KEY_RIGHT:
                case 'd':
                    if(player.position.x < game_area.right() - 2)
                        player.position.x += 1;
                    break;
                default:
                    break;
            }

            wattron(game_window, A_BOLD);
            mvwaddch(game_window, player.position.y, player.position.x, player.display_char);
            wattroff(game_window, A_BOLD);
            wrefresh(main_window);
            wrefresh(game_window);
            if (exit_req) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Game::close()
    {
        endwin();
    }

} // DespoilerEngine