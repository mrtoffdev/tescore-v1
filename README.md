# Tescore

A terminal-centric tabulator with a fully functional responsive TUI chart & hotkey bindings, batteries included. First publicly released version of the Tescore series. Written in C and supports windows & unix systems.  

![Preview](https://raw.githubusercontent.com/mrtoffdev/tescore-v1/main/readme/long_preview.png)

---
### 📢 Warning: This repository is currently going through VCS platform migration. For the most stable release available, refer to the project hosted in [GitLab](https://gitlab.com/christopherjr.abadillos/tescore) 📢  
---  
## ⚀ Dependencies:

* [tiny-AES-c](https://github.com/kokke/tiny-AES-c) (Bundled):
* A Terminal with UTF8 & Ligatures support. Preferrably a [Nerd Font Family](https://www.nerdfonts.com/)

## ⚀ Features:
- **Lightweight:** Uses **0.8MB** of RAM and **82KB** of storage
- **On Point:** Ordered Entries in Descending Value for on the spot **ranking**
- **Visual:** Responsive **TUI bar chart** for data visualization (no Ncurses required)
- **Secure:** Uses an in-house, portable file format (**.dib**) with military grade encryption (AES128)
- **Multi Platform:** Ready for **Windows** and **Linux** system use cases

## ⚀ Keybinds:
- **[H]** : Show Helper Panel
- **[1]** : Graph Panel | **[2]** : Ordered Panel | **[3]** : MasterList
- **[W]** : Move Cursor Up | **[S]** : Move Cursor Down | **[A]** : Move Cursor Left | **[D]** : Move Cursor Right
- **[T]** : Add New Entry
- **[E]** : Edit Selected Entry
- **[Q]** : Exit Editing Mode / Cancel "Delete Entry" / Quit & Save
- **[R]** : Delete Entry
