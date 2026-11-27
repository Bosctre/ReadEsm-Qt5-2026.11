# ReadEsm-Qt5 2026.11

Reader for digital tachograph data files (`.ddd`, `.esm`, `.tgd`) from driver cards and vehicle units.
It turns a card dump into a readable report: one page per card, a 0–24 h activity graph for every day,
a monthly timesheet, events, faults, vehicles used and places.

*Lecteur de fichiers de chronotachygraphe numérique (`.ddd`, `.esm`) : rapport HTML lisible avec un
graphique d'activité 0–24 h par jour et un récapitulatif mensuel.*

This is a **port of ReadEsm to Qt (Qt 6, Qt 5.15 still supported) and Debian 13**, also built for Windows, based on the original program by
**Andreas Gölzer** (<http://andreas.goelzer.de>). It is not the official upstream release.

## Features

- Reads CardPeek `.ddd` files and standard ESM files.
- Daily activity graphs (SVG), identical to the original program:
  red = break/rest, green = driving, yellow = work, black = availability,
  orange = short break, purple = unknown.
- Monthly **Timesheet** tables (driving, work, rest, available, with a Summary row).
- Per-day list of every activity change (collapsible).
- HTML report identical in structure to the original ReadEsm report.
- Qt window with embedded graphs, or command-line conversion without a display.

## Downloads

- Debian 13 / Ubuntu package (`.deb`), Windows installer, source archives (`.tar.xz`, `.zip`):
  [GitHub Releases](https://github.com/Bosctre/ReadEsm-Qt5-2026.11/releases) and
  [SourceForge](https://sourceforge.net/projects/readesm-qt5-2026-11/files/).
- macOS: no ready-made package, see "Build on macOS" below.

## Build (Debian 13)

With Qt 6 (default when installed):

```bash
sudo apt install build-essential cmake qt6-base-dev qt6-svg-dev qt6-tools-dev qt6-tools-dev-tools libgl-dev
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
make -j$(nproc)
sudo make install
```

With Qt 5.15 instead: install `qtbase5-dev libqt5svg5-dev qttools5-dev qttools5-dev-tools`
(instead of the `qt6-…` packages) and add `-DWITH_QT5=ON` to the `cmake` command.
The libraries `libgcrypt20-dev libgmp-dev` are also needed on Linux.

Uninstall: `sudo xargs rm -v < build/install_manifest.txt`

## Windows

A 64-bit installer (`readesm-qt5_<version>_windows-x64-setup.exe`, Windows 10/11) is built by GitHub Actions
(`.github/workflows/windows.yml`, MSYS2 with Qt 5). It is **not signed**: Windows SmartScreen shows a warning
("More info" → "Run anyway").

## Build on macOS (from source, untested)

There is no macOS package yet and the program has not been tried on a Mac. It should build with Homebrew:

```bash
brew install cmake qt
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
cmake --build build
cd build && ./readesm card.ddd      # run from this folder so that the translations (*.qm) are found
```

Optional installation: add `-DCMAKE_INSTALL_PREFIX=/usr/local` to the first command, then
`sudo cmake --install build`. The libraries gcrypt and GMP are not needed on macOS.
Reports and corrections from Mac users are welcome (GitHub "Issues"); please never attach real `.ddd` files.

## Usage

```bash
readesm card.ddd                  # open the window
readesm card.ddd report.html      # write an HTML report, no display needed
readesm -f html card.ddd -        # HTML on standard output
readesm --help
```

Options: `-f/--format` (output format), `-l/--locale` (language, e.g. `fr`).

## Languages

The interface and the HTML export are available in English and in 25 languages: all 24 official EU languages, plus Catalan and Russian (`bg, ca, cs, da, de, el, es, et, fi, fr, ga, hr, hu, it, lt, lv, mt, nl, pl, pt, ro, ru, sk, sl, sv`). The language follows the system; use `readesm -l <code> file.ddd` to force one. Portuguese is European Portuguese (`pt_PT`).

ca, de, es, fr, hu and ru come from earlier work. The 19 others (bg, cs, da, el, et, fi, ga, hr, it, lt, lv, mt, nl, pl, pt, ro, sk, sl, sv) were added in 2026 with the help of an AI assistant and **have not been reviewed by native speakers**: corrections to the `.ts` files in `ressources/translations/` are very welcome.

## Installation (Debian 13 / Ubuntu) — paquet .deb

Télécharger `readesm-qt5_2026.11_amd64.deb` (page « Releases » de GitHub ou
fichiers SourceForge), puis :

    sudo apt install ./readesm-qt5_2026.11_amd64.deb

Le programme s'installe dans `/usr/bin/readesm` et apparaît dans le menu
des applications. La langue du système est détectée automatiquement
(bg, ca, cs, da, de, el, es, et, fi, fr, ga, hr, hu, it, lt, lv, mt, nl, pl, pt, ro, ru, sk, sl, sv ; anglais par défaut), pour l'interface comme pour
l'export HTML. Pour forcer une langue : `readesm -l fr fichier.ddd`.

Désinstallation : `sudo apt remove readesm-qt5`

## Reading a driver card

Use [cardpeek](https://github.com/pannzh/cardpeek) with a PC/SC reader: **Analyzer → Tachograph card**,
then save the `.ddd` file. With cardpeek 0.8.4 and a recent Lua, the script `tachograph.lua` may stop on
`attempt to index a nil value (local 'conversion')`; guard the `iconv.open` call in `Tacho_TEXT_8859`
(use `pcall` and fall back to the plain text conversion).

## Privacy

Tachograph files contain personal data (name, birth date, card number, vehicle plates, trips).
**Do not publish `.ddd` files or reports made from real cards.** Use anonymised test files only.

## Credits and licence

- Original ReadEsm: © Andreas Gölzer, GNU General Public License v3 or later.
- Qt5 / Debian 13 port, report structure, timesheet and GUI changes: 2026 (see `CHANGELOG`).
by Jean-Paul FRAYSSE : https://sourceforge.net/projects/readesm-qt5-2026-11/

This program is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version. It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY. See `COPYING`. The original upstream README is kept as `README.upstream`.
