# What's Needlemake?
Needlemake is a headless "build system" in the style of Premake5, except instead of building software, it builds mods for Hedgehog Engine games automatically. Support for non-HE games that use CPK disk files and the same style of packages that HE games use, such as Platinum Games' Bayonetta, Metal Gear Rising and Nier Automata is being considered.

## About Needlemake
Needlemake basically reads a project file that describes metadata about your mod and the files it overrides/adds to the game, fetches the files and puts them in your project for you to edit, and afterwards packs them into the mod's folder automatically skipping files marked to be excluded.

## How Aoes It Work?
Needlemake will use [mini-yaml](https://github.com/jimmiebergmann/mini-yaml) to read a [YAML](https://yaml.org/) project file mentioned in the previous section, as well as the configuration file that contains paths to the relevant folders for the tool to work its magic.

Once the project file is all parsed correctly, Needlemake -using paths to the relevant folders in the settings file- goes and unpacks the disks of the game, and then unpacks the package files within in an intermediate directory, then the files in the overrides for that package are copied over to the project folder for you to edit and add any files you like

Once you've made all your changes to the package -and any miscellaneous files that are directly in the disk, like actstgmission LUA scripts from Sonic Forces- you run the tool again with a different argument, and it will copy over your project files to the intermediate directory to package it and then copy that to the folder of your mod. Needlemake also updates your mod.ini file in this step, or creates it if it's not there already, using [mINI](https://github.com/pulzed/mINI).

## With What Does It Accomplish This?
- To handle disk files, Needlemake uses [PackCpk.exe](https://github.com/blueskythlikesclouds/SkythTools/blob/master/Common/PackCpk.exe) and [CpkMaker.dll](https://github.com/blueskythlikesclouds/SkythTools/blob/master/Common/CpkMaker.dll).
- For packages the following are currently used for these games respectively:
	* Sonic Generations: [ar0pack](https://github.com/blueskythlikesclouds/SkythTools/blob/master/Sonic%20Generations/ar0pack.exe) and [ar0unpack](https://github.com/blueskythlikesclouds/SkythTools/blob/master/Sonic%20Generations/ar0pack.exe)
	* Sonic Lost World: [pacpack.exe](https://github.com/DarioSamo/libgens-sonicglvl/blob/master/bin/pacpack.exe)
	* Sonic Forces: [SFPac](https://gist.github.com/blueskythlikesclouds/887d227301dd3c0ea3c62ab6984388cc)
	* Sonic Frontiers: None at the moment, the code has an entry for this game but the path for the tool is never even set to anything.

### Why Not Just Use HedgeArcPack?
So HAP (HedgeArcPack) supports is pretty much a no-brainer choice, and if you're asking this question you probably know why. So why don't I use that instead? Well I have my reasons, none are to be disclosed here.

If you know of some tool for Sonic Frontiers' package files, do message me on [my many socials](https://chloecake.com/cont) as I do want to support it, except if you're gonna recommend HAP, I'm just gonna ignore it. I'm not accepting merge requests that use HAP either.

Kindly do not go into Twitter, my DMs or my Discord/Revolt server to bother me about this. You're free to fork Needlemake under the terms of the [license](./LICENSE) with HAP, this is an open source project after all.

# Using Needlemake


## Installing Prebuilt Binaries For Needlemake
You can find a binary for Needlemake along with an MSI file for the same binary in the [releases page.](https://github.com/ChloeZamorano/needlemake/releases)

The binary *should* be identical to what you'd get compiling it yourself in the debug configuration, and the MSI file simply places this same binary in `Program Files/needlemake/needlemake.exe`, as well as a configuration file in `%appdata%/chloeware/chloeconf.yml` and adds `Program Files/needlemake` to the system PATH variable for you to use needlemake in any directory like built-in commands.

## Building And Compiling Yourself
If you don't trust my binaries, then you can compile Needlemake yourself, here how:

### What You'll Need With An Asterisk
Building and compiling Needlemake is the simplest thing you could do, specially building as I'm including [Premake5](https://premake.github.io/) since you can't just install it on Windows like you could in Linux by typing say `sudo pacman -Syu premake`, but you'll need to install [GCC](https://gcc.gnu.org/) and (GNU Make)[https://www.gnu.org/software/make/], and that should allow you to compile Needlemake running two simple commands.

### The Problem
There's a problem though, GCC and GNU Make are tools designed and developed for [UNIX](https://www.hpc.iastate.edu/guides/unix-introduction) based systems like GNU/Linux or FreeBSD, and you're most likely on a Windows machine which is the farthest thing from being [POSIX](https://www.techtarget.com/whatis/definition/POSIX-Portable-Operating-System-Interface) compliant you could find -aside from maybe [TempleOS](https://templeos.org/) but we don't talk about TempleOS *yet*- which is also one reason I'm not supporting Linux yet. This effectively means, you can't really install GCC on Windows so what do we do?

### Why Not MSVC?
Why of course, [MSVC](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options?view=msvc-170) is terrible and may or may not contain spyware as does *basically anything [Microsoft](https://www.microsoft.com/) makes*, but it just so happens Windows is the most widely used OS around for *some reason*, so naturally people smarter than me came up with a way to bring tools for UNIX into Windows!

### Introducing [Cygwin](https://www.cygwin.com/)
Cygwin is a little complicated, but for the sake of compiling Needlemake, all you need to know is that Cygwin allows you to use various tools for Linux systems on Windows, and even gives you a POSIX compliant terminal with commands such as [grep](https://en.wikipedia.org/wiki/Grep).

Installing Cygwin can be a bit tricky if you don't know exactly what you're looking for, but worry not, cause you can just install [MSYS2](https://www.msys2.org/), a Cygwin distribution, just follow the quick instructions in the site, then you can simply install any package provided by MSYS2, which includes GCC -and the instructions even tell you that you can install GCC at the end. I believe MSYS2 also provides GNU Make, but it doesn't matter cause there *is* a [version of GNU Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm) -though you can install it with one command using [Chocolatey](https://chocolatey.org/install).

### Tiny Problem
If you've successfully installed GNU Make and GCC, there's a chance it won't work when you try and type `make` in your terminal still, if this happens that means the folders containing the binaries for Make -and pressumably GCC as well but we don't need to run it manually, that's what GNU Make is for- are not in your PATH environment variable.

The fix for this is quite simple, you wanna simply add the paths for them to a PATH environment variable (Whether it's for the system or the user doesn't matter). To do this you can just follow these [instructions from Oracle](https://www.java.com/en/download/help/path.html).

For GCC or any other program installed with MSYS2 it would be `C:/msys2/usr/bin` usually, unless you changed the path when installing MSYS2. For GNU Make, *I don't actually know* but you should be able to find it in your program files folders very easily, or you could also install it with Chocolatey as mentioned earlier, which automatically places it in a PATH variable anyways but in case it doesn't for whatever reason it should be in `C:\ProgramData\chocolatey\bin`.

### Now We Compilin'
So that was a mouthful, installing these tools may be kinda tedious, but such is the life of a Windows user anyways, and hey, now you don't need to use Visual Studio and didn't install any more spyware than we already have from just using Windows, you could use Notepad instead if you really wanted to and it'll work just fine -but don't do that, use [Neovim](https://neovim.io/) or [Visual Studio Codium](https://vscodium.com/) if you're not comfortable with or willing to learn modal editors.

Now that we have everything setup -assuming you already have [Git](https://git-scm.com/) and know how to use it, which if you're compiling this yourself you probably do- you can simply clone this repo, go into the directory for it, and two commands are needed to compile:

- First you wanna build the project file, this will be as simple as running `.\tools\premake5.exe gmake2`, this generates GNU Make scripts from the much simpler and more readable Premake5 project, which is literally just a LUA script that defines a bunch of strings and arrays of strings. This will take a couple hundred milliseconds.
- After this, you wanna run GNU Make, this will use GCC and the scripts generated by Premake5 to actually compile the program, but you have to pick a configuration for this, you can run `make help` to see the configurations you can use, but here they are for you:
	* debug_windows: No optimizations, symbols and logging are enabled.
	* release_windows: Some optimizations, symbols and some logging are enabled.
	* deploy_windows: Aggressive optimizations, no symbols and minimal logging.
- Once you know the configuration you want is, you simply run `make config=some_configuration needlemake` and you'll be given a tiny binary for Needlemake in a bin folder that will be created. If GNU Make complains that it can't create the folder, you can just copy the path it's complaining about and create it, then it should work fine.
- If you want, for convenience, you can take that binary and drop it somewhere in your system files and add that to a PATH variable, then you can just type `needlemake` like any built-in commands such as `dir` or `ls` on POSIX compliant systems or your MSYS2 terminal.

## Setting Up Needlemake
This is very simple, you just need to know what you're doing, it needs a single configuration file and a folder for the [tools it uses](#with-what)

### The Configuration File
This file is very simple, it's simply a YAML file with the path %APPDATA%/chloeware/chloeconf.yml, and Needlemake will need the following entries:
```yml
needlemake:
  blueblur:
    disks_dir: Path/To/Sonic/Generations/Disk/Folder
    int_dir: Path/To/The/Intermediate/Folder/Maybe/TEMP/Doesnt/Matter
    mods_dir: Path/To/Sonic/Generations/Mods/Folder
  sonic2013:
    disks_dir: Path/To/Sonic/Lost/World/Disk/Folder
    dlc_disks_dir: Path/To/Sonic/Lost/World/DLC/Disk/Folder # Unique to Lost World as far as I'm aware
    int_dir: Path/To/The/Intermediate/Folder/Maybe/TEMP/Doesnt/Matter
    mods_dir: Path/To/Sonic/Lost/World/Mods/Folder
  wars:
    disks_dir: Path/To/Sonic/Forces/Disk/Folder
    int_dir: Path/To/The/Intermediate/Folder/Maybe/TEMP/Doesnt/Matter
    mods_dir: Path/To/Sonic/Forces/Mods/Folder
  rangers:
    disks_dir: Path/To/Sonic/Frontiers/Disk/Folder
    int_dir: Path/To/The/Intermediate/Folder/Maybe/TEMP/Doesnt/Matter
    mods_dir: Path/To/Sonic/Frontiers/Mods/Folder
```
If the file or any of these entries doesn't exist, they'll be created but the values will be empty.
- The disks directory for these games is usually just `GAME_ROOT/disk`, except for HE2 games where `GAME_ROOT\image\x64\disk` for some reason.
- The DLC disks directory for Sonic Lost World is just `GAME_ROOT/dlc`, and every DLC disk is annoyingly in a subfolder folder with the ID for the DLC but I'm handling that automatically, so you can write your project like the disk file is directly in the DLC folder.
- The intermediate directory is simply a place where the packages from the game will be unpacked, this can be anywhere you want, it could be `%TEMP%/needlemake` for example.
- The mods directory, as far as I'm aware is always `GAME_EXEC_DIR/mods` or `GAME_EXEC_DIR/Mods` with a capital M.

This configuration file may get a little more complicated when support for other games is added, additionally, it will be used by my other software as well, which is why it's not called `needlemake_conf.yml` and all the configuration is in a node called `needlemake` instead of being in the root.

### The Toolset
Simply download [all the tools Needlemake uses](#with-what) and place them all under `%LOCALAPPDATA%/Programs/needlemake`, simple as that, now Needlemake is setup and ready to use!

## Using Needlemake *Finally*
### The Project File
Needlemake works like Premake5, in that you basically have a project file and you just run the tool with the options you want in that directory. For Premake5, you have a premake5.lua file, with which Premake5 can generate GNU Make, XCode or Visual Studio files (Don't even try it, it's not gonna work and I don't intent to make it work). For Needlemake, you'll have in your project's folder a needlemake.yml file, and it's structure will go as follows:

```yml
game: wars # Use the code name for the game, for example wars or blueblur, caps don't matter.
pathName: testMod # Name of the folder where the mod will go, basically output name.

# This is for the mod.ini file.
Title: Test Mod
Description: Literally nothing
Version: 0.0
Author: Me
AuthorURL: https://papertoilet.com/ # This site is funny, visit it please.

# This is the files you want to take from the unmodded game for your project.
disks:
  wars_0: # This is a disk file, you can choose any and have many.
    actstgmission.lua: # Files that aren't a folder or package need the extension in the name
      type: LUA # Just make sure it's not Folder, Package or DISK
    customize:
      type: Folder
      ctp_body:
        type: Folder
        body_001:
          type: Package
          overrides: # These files will be copied to your project for you to edit.
            - ctp_body_001.model
            - ctp_body_001.material
            - ctp_cmn_body_001a_main_abd.dds
            - ctp_cmn_body_001b_main_abd.dds
            - ctp_cmn_body_001c_main_abd.dds
          excludes: # These files will be deleted from the intermediate directory before repacking.
            - ctp_cmn_body_001_main_nrm.dds
            - ctp_cmn_body_001_main_prm.dds
      ctp_pattern:
        type: Folder
        pattern_002:
          type: Package
          overrides:
            - bdy_cmn_body_002_prm.dds
            - bdy_cmn_body_002a_abd.dds
            - bdy_cmn_body_002b_abd.dds
            - bdy_cmn_body_002c_abd.dds
```
### Terminal Usage
Now that you have your configuration, your toolset and your project file, you need to run needlemake in the directory where you have your project file, though that's not necessary though but more on that later.

#### Actions
The first argument should never be empty, and it's an action, an action is, as the name implies, what the tool will do on this run, and there are three of them, here they are with an explanation of exactly what they do:

- Help: Will print a help page.
- MakeProject: This will extract all the packages referenced in the project file, from the disks directory -or DLC disks directory if it applies-, and they will be moved to the intermediate directory. The miscellaneous files and package sub-files marked as an override will then be copied to your project folder with the same directory structure, unless the file already exists.
- BuildMod: With this action, all the folders representing packages in your project's directory, will be copied over to the intermediate directory, any file conflicts will be resolved keeping the file from the project. Next, the packages in the intermediate directory will be packed again with the appropriate tool before deleting any files marked as an exclude, and they will be copied to the mods directory, as well as the miscellaneous files in your project. The mod.ini file will be updated with the information in the project file, unless it doesn't exist, then it will be created automatically with default values in the Main category.

#### Options
All other arguments after the first one are referred to as an option, and they will be interpreted as a flag or a project, they always begin with a dash, and here's how you use them:

##### Projects
If the option is lowercase p, then that's a project. The project option needs to have a path value, and you'll write it as such: `-p=E:/Some/Path/Can/Be/Relative`
You can define many project options, and Needlemake will gather them all in a list and run with the action and flags you define for each of them, one after the other. If you don't have any project option, the working directory will be used instead.

##### Flags
Flags are like actions, but they're optional and you can have many of them in one run. You define them by just writing a dash and the flags you want as such: `-ExRxCm` and they are not separated, the first letter of each is uppercase for readability, and you can have several options with different flags if you want, or one option for every flag, though I don't know why you'd want to do that, with the way I implemented it you kinda just can.
There are six flags, and they are the following:

- ExtractDisks (Ex): This will extract the disks referenced in the project file.
- RextractDisks (Rx): When extracting a disk, if the folder for that disk already exists, after reporting it you'll be asked if you wanna delete it and extract it again instead of skipping it, before the tool continues.
- PrecleanMod (Pcm): The disk folder in the mod's directory will be deleted before running the action.
- PrecleanInt (Pci): The intermediate directory will be deleted before running the action.
- CleanMod (Cm): The disk folder in the mod's directory will be deleted after running the action.
- CleanInt (Ci): The intermediate directory will be deleted after running the action.

#### Example Usage
1. Run `needlemake Help` to get a quick reminder of how to use Needlemake
2. Write your project file.
3. Run `needlemake MakeProject -ExRxPciCm`.
4. Edit any files you want, add any files you want.
5. Run `needlemake BuildMod -Pcm`.
6. Run the game to see if you like your changes.

And that's it, you can then zip your mod and upload it as-is.

## How To Contribute
This page is bound to change over time.

### Dependencies
All dependencies should be submodules if possible, and you should place them under the deps folder, for example `git submodule add https://github.com/jimmiebergmann/mini-yaml ./deps/mini-yaml`.
Single-header dependencies like mINI are preferable, if not something simple that can be added as a project in the Premake5 script like I did with mini-yaml are still preferable. If you can't find what you want meeting this standard, you can either write it yourself or write a whole dedicated Premake5 script for it.

### Code Styling

#### Lines
No line should be over 100 columns long, break them in the most aesthetically pleasing manner you can think of, like separating "categories" in the arguments of a function call by breaking the line.

#### Indentation
If any given line of your code requires more than three levels of indentation, then you should take that chunk out and make it into a function or macro instead.

There are cases where 4 or even 5 levels of indentation are allowed, and that's if it's an statement with only one or two lines in the body, or if you have a line that's very long and you break it into many, you can go over 4 levels.

Indentation should be with tabs and not spaces, unless it's a YAML file since for some reason they don't allow tabs.

Members of a namespace directly in the global scope should have an indentation level of 0 as if they were in the global scope.

#### Includes
Any headers from dependencies or the STL should be in the `pch.hpp` file and should use less/greater-than symbols.

All source, inline and header files should include `pch.hpp`, for headers and inlines it should be right after the `#pragma once` directive, and for source files -other than main.cpp as it doesn't have one- it should be right before including the associated header.

Files from Needlemake itself should be included in every file that uses features from that header directly, even if it's already indirectly included, and these includes should use quotation marks, and they should be right after the `pch.hpp` file for headers and inlines, or after the associated header for source files, separated by an empty line.


