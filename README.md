# Tajemství prstenu - Hra ve stylu RPG s dlaždicovou mapou

## Spuštění hry pro windows (Release)

- Nejprve stáhněte celou složku `Game_win_x86_64` do počítače.
- Ve stažené složce spusťte `Tajemstviprstenu.exe`.
- Hra podporuje pouze Windows 64‑bit (x64). Spouštění na jiných platformách není oficiálně podporováno.

Ujistěte se, že v `Game_win_x86_64` jsou přítomny všechny potřebné DLL (SFML) a adresář `assets` pokud nejsou integrovány do EXE.

## Spuštění hry pro linux (Release)

- Nejprve stáhněte celou složku `Game_linux_x86_64` do počítače.
- Ve stažené složce spusťte `Tajemství_prstenu-x86_64.AppImage`.
- Hra podporuje pouze linux 64‑bit (x64). Spouštění na jiných platformách není oficiálně podporováno.

## Stručné použití / ovládání

- Pohyb postavy: šipky (Up, Down, Left, Right)
- Interakce: pokud je implementováno klikání, použijte levé tlačítko myši pro posun hráče.
- Hra neobsahuje hledání cesty a vyhýbání se kolizním objektům. Proto je možné, že při použití myši hráč uvízne za objekty. V takovém případě použijte klávesy pro pohyb.

## Složka pro spuštění hry

- `assets/` — obrázky a data map
- `README.md` — tento soubor
- `ReleaseGame/` — připravená složka s bází pro spuštění na Windows (x64)


## Hlavní vlastnosti

Hra je jednoduchý výukový projekt napsaný v C++ s využitím knihovny SFML. Projekt slouží jako cvičení pro práci s 2D grafikou, tilemapami a základními herními mechanismy (postavy, kolize, z-indexování/Y-sort a jednoduchý systém dialogů řízený JSONem). Aplikace má formu jednoduché click & point adventury, kde se příběh a interaktivní prvky definují v externím JSON souboru.

- Tilemap rendering ze spritesheetu
- Vícevrstvá mapa (spodní vrstva, překrývající objekty pro Y‑sort, horní vrstva)
- Podpora vlastních colliderů pro dlaždice (atribut `custom_collider`)
- Interaktivní dlaždice definované v JSON (atribut `interactive`)
- Postavy (hráč a NPC) s jednoduchým systémem animací
- Dialogy řízené `DialogueManager` a událostmi přes `GameEventsManager`

## Požadavky

- Visual Studio 2026 (nebo jiný moderní C++ překladač podporující C++17)
- SFML 2.x (grafika, okno, vstup) – knihovnu je potřeba nainstalovat a správně nastavit v projektu
- Soubory v adresáři `assets` (spritesheety, mapy, zvuky pokud jsou použity)

## Instalace a spuštění (Visual Studio)

1. Naklonujte repozitář do lokální složky.
2. Otevřete řešení v Visual Studio 2026.
3. Nainstalujte a nakonfigurujte SFML (binaries, include a lib cesty) pro konfigurace Debug/Release a cílovou platformu (x64/x86), podle vaší instalace SFML.
4. Zkontrolujte, že následující soubory jsou ve `assets` a jsou kopírovány do pracovní složky EXE:
   - `map-level-01.png`
   - `characters.png`
   - Jakékoliv JSON soubory s mapou/příběhem (většinou `map.json` nebo podobně)
5. Překompilujte projekt a spusťte binárku z Visual Studia.

Poznámka: Pokud používáte SFML DLL, ujistěte se, že jsou dostupné ve stejném adresáři jako spouštěný EXE nebo ve PATH.

## Stručné použití / ovládání

- Pohyb postavy: šipky (Up, Down, Left, Right)
- Interakce: pokud je implementováno klikání, použijte levé tlačítko myši pro aktivaci interaktivních dlaždic nebo NPC; dialogy lze ovládat klávesami/GUI dle implementace `DialogueManager`.
- Kamera sleduje pozici hráče (view se nastaví v hlavním cyklu).

## Formát mapy a interakcí (JSON)

Mapa a interaktivní prvky jsou definované v JSONu. Důležité body:

- Každá dlaždice má `id`, `x`, `y` a volitelně `attributes`.
- Atribut `custom_collider` je string ve formátu `"left,top,width,height"` a překládá se na `sf::FloatRect`.
- Atribut `interactive` obsahuje jméno interaktivního objektu, které hra používá k identifikaci (např. `"Barrel"`).

Příklad atributu:

```json
{
  "attributes": {
    "custom_collider": "59,110,20,5",
    "interactive": "Barrel"
  }
}
```

## Tipy pro vývoj a ladění

- Při rozšiřování vrstev buďte opatrní při ukládání ukazatelů na prvky vektorů: standardní `std::vector` může při `push_back` provést realokaci a tím zneplatnit dříve uložené ukazatele. Použijte stabilní vlastnictví (např. `std::unique_ptr` vektor), indexy nebo rezervujte kapacitu (`reserve`) předem.
- Spusťte aplikaci v Debug módu a sledujte výstup pro chyby parsování JSON nebo chybné indexy dlaždic.

## Struktura repozitáře (stručně)

- `src/` — zdrojové kódy (třídy jako `MapGenerator`, `Player`, `Npc`, `DialogueManager`)
- `assets/` — obrázky a data map
- `README.md` — tento soubor

## Příspěvky

Pokud chcete přidat funkce nebo opravy, vytvořte PR s jasným popisem změn a kroků jak reprodukovat chování.

## Licence

Projekt slouží jako výukový příklad; použijte dle potřeby. Pokud plánujete veřejné šíření, přidejte prosím vhodnou licenci.