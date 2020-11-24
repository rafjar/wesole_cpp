#include "macierz.hpp"

#include <allegro.h>
#include <cmath>
#include <chrono>
#include <iostream>

const double A_PARAM = 0.2; // Stała do kolorowania
const int xsize = 500, ysize = 500; // Rozmiary okienka
Macierz macierz(xsize, ysize); // Macierz wartości temp pixeli
int end = 0; // Zmienna do kończenia symulacji
const double psi = 0.99; // Stała psi (ze wzorku)
const double delta_t = 0.4; // Stała delta_t (ze wzorku)
const int FLAME_SIZE = 5; // Rozmiar płomienia spawacza

// Kolorowanie okienka
BITMAP *koloruj(BITMAP *bmp) {
    auto wymiary = macierz.rozmiar();
    for(int x=0; x<wymiary.first; ++x) {
        for(int y=0; y<wymiary.second; ++y) {
            // Fancy funkcje kolorowania - chociaż nie miałem pomysłu jak to zrobić ciekawiej :(
            int r = 255. / (1 + std::exp(-A_PARAM*macierz.element(x, y)));
            int g = 128. / (A_PARAM * macierz.element(x, y) + 1);
            int b = 255. / (1 + std::exp(-3*A_PARAM * macierz.element(x, y)));
            putpixel(bmp, x, y, makecol(r, g, b));
        }
    }
    return bmp;
}

// Zmiana temp od elementów sąsiednich
void zmiana_temp() {
    auto wymiary = macierz.rozmiar();
    for(int x=1; x<wymiary.first-1; ++x) {
        for(int y=1; y<wymiary.second-1; ++y) {
            double suma = 4*macierz.element(x, y) - macierz.element(x-1, y) - macierz.element(x+1, y) - macierz.element(x, y-1) - macierz.element(x, y+1);
            macierz.element(x, y) -= psi * delta_t * suma;
            if(macierz.element(x, y) < 0)
                macierz.element(x, y) = 0;
        }
    }
}
END_OF_FUNCTION(zmiana_temp)

// Funkcja przerwania myszy - dodawanie temp spawanym kwadracikom
void przerwanie_myszy(int m) {
    if(m & (MOUSE_FLAG_MOVE | MOUSE_FLAG_LEFT_DOWN)) {
        // Zwiększenia płomienia (płomień o wielkości 2FlameSize*2FlameSize)
        if(mouse_x > FLAME_SIZE && mouse_x < xsize-1-FLAME_SIZE && mouse_y > FLAME_SIZE && mouse_y < ysize-1-FLAME_SIZE) {
            for(int x=0; x<FLAME_SIZE; ++x) {
                for(int y=0; y<FLAME_SIZE; ++y) {
                    macierz.element(mouse_x+x, mouse_y+y) += 10.;
                    macierz.element(mouse_x-x, mouse_y-y) += 10.;
                }
            }
        }
    }
}
END_OF_FUNCTION(przerwanie_myszy)

// Przerwanie służące do wyłączenia programu
int przerwanie_klawiatury(int k) {
    if((k>>8) == KEY_ESC)
        end = 1;
    return 0;
}
END_OF_FUNCTION(przerwanie_klawiatury)

int main() {
    // Inicjalizacja i włączenie przerwań
    allegro_init();
    install_timer();
    LOCK_FUNCTION(przerwanie_myszy);
    LOCK_FUNCTION(przerwanie_klawiatury);
    install_keyboard();
    install_mouse();
    keyboard_callback = przerwanie_klawiatury;
    mouse_callback = przerwanie_myszy;

    // Ustawienie kolorków i odpalenie wersji okienkowej
    set_color_depth(24);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, xsize, ysize, 0, 0) != 0) {
        allegro_exit();
        std::cerr << "Blad inicjowania trybu graficznego!" << std::endl;
        return 1;
    }
    set_window_title("Symulator spawacza");

    // Wywołuj f. zmiany temp 25razy/s
    LOCK_FUNCTION(zmiana_temp);
    install_int_ex(zmiana_temp, BPS_TO_TIMER(25));

    // Utworzenie bitmapy i wyczyszczenie bufora klawiszy
    BITMAP *bmp = create_bitmap(xsize, ysize);
    clear_keybuf();

    // Pętla spawacza - odświeżanie ekranu co 40ms
    auto time = std::chrono::steady_clock::now();
    while(!end) {
        int diff_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - time).count();

        if(diff_time > 40) {
            time = std::chrono::steady_clock::now();
            bmp = koloruj(bmp);
            blit(bmp, screen, 0, 0, 0, 0, xsize, ysize);
        }
        show_mouse(screen);
    }

    // Niszczenie bitmapy i koniec programu
    destroy_bitmap(bmp);
    allegro_exit();
    return 0;
}
END_OF_MAIN()