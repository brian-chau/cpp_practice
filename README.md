# C++ on WSL2 with VS Code

This is an example of how to use:
* Visual Studio Code with a C++ application written for GCC compiler
* ncurses to display a menu and select an option
* GMP for large numbers

## Setting up WSL2
1. Install WSL
    1. Start "Command Prompt"
    2. Run `wsl --set-default-version 2`
    3. Run `wsl --list --online` to see available distributions
    4. Run `wsl --install -d <distro_name>` based on what you see in the list.
        * This will take several minutes

2. Start WSL
    1. Press Ctrl+R
    2. Type `wsl`
    3. Press Enter

3. Fix the command line path name.
    1. Edit the ~/.bashrc file.
        * At the top of the file, paste the following code snippet, where <current_directory> is the name of the 
          mount point shown in the console window (e.g. "/mnt/c/Users/`username`")
            ```
            if [[ $PWD == /mnt/c/Users/<username> ]]; then
              cd /home/user/user
            else
              case $PWD/ in
                /mnt/c/Users/<username>/*)
                  without_prefix=${PWD#/mnt/c/Users/<username>/}
                  cd /home/user/user/$without_prefix
                  ;;
              esac
            fi
            ```
    2. Look for the line that says `if [ "$color_prompt" = yes ]; then`
        * In the following line, remove the part that specifies the username "\u" and the host name "\h"
        * Do the same for the "else" block.

4. Update the system
    ```
    sudo apt update
    sudo apt upgrade
    sudo apt autoremove
    ```

5. Add custom aliases to ~/.bash_aliases
    ```
    alias cls="printf '\ec'; history -c"
    alias nanos="nano -ET4"
    alias ii="explorer.exe"
    ```

6. Add GitHub settings
    1. Restart WSL
    2. Run `mkdir repos`
    3. Connect to GitHub
        1. Sign in to GitHub
        2. Click profile picture in upper right corner, then click Settings
        3. Delete any old SSH keys if any.
        4. Start creating SSH keys
            1. Run the following commands:
                ```
                ssh-keygen -t ed25519 -C "your_email@example.com"
                eval "$(ssh-agent -s)"
                ssh-add ~/.ssh/id_ed25519
                cat ~/.ssh/id_ed25519.pub
                ```
            2. Copy the result and go to this page: https://github.com/settings/ssh/new
            3. For "Title," put "Linux".
            4. For "Key," paste the copied key.
            5. Click "Add SSH Key"
            6. Run `ssh -T git@github.com`, then type "yes"

## Setting up the dependencies for this project
1. Download the project source code:
    1. Open WSL.
        1. Ctrl+R
        2. Type `wsl`
        3. Press Enter

    2. Run these commands:
        ```
        cd repos
        git clone git@github.com:brian-chau/cpp_wsl_ncurses.git
        ```
2. Setup the project
    1. Navigate to the project with `cd cpp_wsl_ncurses`
    2. Run this command to install the necessary libraries: `sudo apt install make build-essential lzip m4 libncurses5-dev`
    3. (Optional) Install "gmp":
        1. Download GMP from here: https://gmplib.org/
        2. Unpack it with the command: `sudo tar --lzip -xvf gmp-x.y.z.tar.lz`
        3. Navigate into that folder: `cd gmp-x.y.z`
        4. Run the following commands:
            ```
            sudo ./configure --enable-cxx
            sudo make
            sudo make check
            sudo make install
            ```
    4. Run: `make`
    5. Run: `sudo ldconfig`

## Setting up VSCode
1. Right-click on the project folder, select `Open in Terminal` to open the application in WSL2, then type `code .`
2. Press Ctrl+Shift+X to open the "Extensions" window.
3. Install the following extensions
    1. C/C++ Themes
    2. C/C++ Extension Pack
    3. Makefile Tools
    4. Remote - WSL
    5. Better C++ Syntax
4. Close VSCode
5. Type `code .` in the terminal to restart it.
6. Press Ctrl+Shift+X again to open the "Extensions" window.
7. If any of the above extensions say "Install in WSL: Ubuntu-20.04", then click that button.
8. Configure editor settings
    1. Click the gear icon in the lower left corner.
    2. Click Settings.
    3. In the search bar, type "minimap" and uncheck "Editor > Minimap: Enabled" where the checkbox says "Controls whether the minimap is shown"
    4. In the search bar, type "Trim Trailing Whitespace" and check the box for "Files: Trim Trailing Whitespace"
    5. In the search bar, type "Detect Indentation" and uncheck the box for "Editor: Detect Indentation"
    6. In the search bar, type "Format On Save" and check the box for "Editor: Format On Save"
    7. In the search box, type `C_Cpp.clang_format_fallbackStyle`
        1. In the field that appears, change `Visual Studio` to `{ BasedOnStyle: Google, IndentWidth: 4 }`
9. Set the key bindings to build and clean the solution.
    1. Press Ctrl+K Ctrl+S
    2. In the keybindings search box, type "makefile: build clean the target ALL"
        1. Double-click the keybinding and replace it with Ctrl+Shift+B.
            * There is already a keybinding for that in VSCode, but you can remove the other keybinding to replace it with this.
        2. Press Enter to save the keybinding.
    3. In the keybindings search box, type "Makefile: Build clean the current target"
        1. Double-click the keybinding and replace it with Ctrl+Shift+Z.
