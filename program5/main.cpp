#include <fstream>
#include <regex>
#include <ncurses.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>

using namespace std::chrono_literals;

const int XSIZE = 30, YSIZE = 11;

std::regex komentarz(R"(^#.*)");
std::regex rampa(R"(^(rampa)\s(\d+\.\d+|\d+)\s(\d+\.\d+|\d+)\s(\d+\.\d+|\d+))", std::regex_constants::icase);
std::regex izotermiczne(R"(^(izotermiczne)\s(\d+\.\d+|\d+))", std::regex_constants::icase);
std::regex skocz(R"(^(skocz)\s(\d+\.\d+|\d+))", std::regex_constants::icase);

class BladParsowania : std::exception {
    public:
        std::string komenda_;
        BladParsowania(std::string komenda) : komenda_(komenda) {}
};

void zrob_ramke() {
    for(int y=0; y<YSIZE; y++) {
        for(int x=0; x<XSIZE; x++) {
            if(y == 0 || y == YSIZE-1)
                mvaddch(y, x, '#');
            else
                if(x == 0 || x == XSIZE-1)
                    mvaddch(y, x, '#');
        }
    }
}

void odswiez_temperature(float temp) {
    clear();
    if(temp < 100)
        attron(COLOR_PAIR(1));
    else if(temp < 200)
        attron(COLOR_PAIR(2));
    else
        attron(COLOR_PAIR(3));
    zrob_ramke();
    std::ostringstream s_temp;
    s_temp << std::fixed << std::setprecision(1) << temp;
    std::string text = "Temp. " + s_temp.str() + " C";


    mvprintw(YSIZE/2, XSIZE/2-text.size()/2, text.c_str());
    refresh();
}

void napisz(std::string text) {
    clear();
    attron(COLOR_PAIR(1));
    zrob_ramke();
    mvprintw(YSIZE/2, XSIZE/2-text.size()/2, text.c_str());
    refresh();
}

void inicjuj_kolory() {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
}

void zrob_rampe(float start, float koniec, float interwal) {
    if(start < koniec) {
        while(start <= koniec) {
            odswiez_temperature(start);
            start += interwal/10;
            std::this_thread::sleep_for(100ms);
        }
    }
    else {
        while(start >= koniec) {
            odswiez_temperature(start);
            start -= interwal/10;
            std::this_thread::sleep_for(100ms);
        }
    }
}

void zrob_izotermiczne(float czas) {
    std::this_thread::sleep_for(std::chrono::duration<float>(czas));
}

void zrob_skocz(float temp) {
    odswiez_temperature(temp);
}

void parse_line(std::string line) {
    if(!std::regex_match(line, komentarz)) {
        std::match_results<std::string::const_iterator> dop;

        if(std::regex_search(line, dop, rampa)) {
            zrob_rampe(std::stof(dop[2]), std::stof(dop[3]), std::stof(dop[4]));
        }
        else if(std::regex_search(line, dop, izotermiczne)) {
            zrob_izotermiczne(std::stof(dop[2]));
        }
        else if(std::regex_search(line, dop, skocz)) {
            zrob_skocz(std::stof(dop[2]));
        }
        else
            throw BladParsowania(line);
    }
}

int main(int argc, char **argv) {
    // Inicjalizacja ncurses
    initscr();
    start_color();
    curs_set(0);
    inicjuj_kolory();
    zrob_ramke();

    if(argc != 2) {
        napisz("Zla liczba argumentow");
        getch();
        endwin();
        return 1;
    }

    std::string line;
    std::ifstream plik(argv[1]);
    while(std::getline(plik, line)) {
        try {
            parse_line(line);
        } 
        catch (BladParsowania &bp) {
            napisz("Nieznana komenda " + bp.komenda_);
            getch();
        }
        catch (std::exception &e) {
            endwin();
        }
    }
    

    endwin();
}