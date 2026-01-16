# Tajemství prstenu - Hra ve stylu RPG s dlaždicovou mapou

## Spuštění hry pro windows (Release)

- Nejprve stáhněte celou složku `Game_win_x86_64` do počítače.
- Ve stažené složce spusťte `Tajemstviprstenu.exe`.
- Hra podporuje pouze Windows 64‑bit (x64). Spouštění na jiných platformách není oficiálně podporováno.

Ujistěte se, že v `Game_win_x86_64` jsou přítomny všechny potřebné DLL (SFML) a adresář `assets` pokud nejsou integrovány do EXE.

## Stručné použití / ovládání

- Pohyb postavy: šipky (Up, Down, Left, Right)
- Interakce: pokud je implementováno klikání, použijte levé tlačítko myši pro posun hráče.
- Hra neobsahuje hledání cesty a vyhýbání se kolizním objektům. Proto je možné, že při použití myši hráč uvízne za objekty. V takovém případě použijte klávesy pro pohyb.

## Složka pro spuštění hry

- `assets/` — obrázky a data map
- `README.md` — tento soubor
- `Game_win_x86_64/` — připravená složka s bází pro spuštění na Windows (x64)