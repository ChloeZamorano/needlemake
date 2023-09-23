const ccstr HelpSource =

"# Terminal Usage\n"
"Now that you have your configuration, your toolset and your project file, you need to run needlemake in the directory where you have your project file, though that's not necessary though but more on that later.\n"
"\n"
"## Actions\n"
"The first argument should never be empty, and it's an action, an action is, as the name implies, what the tool will do on this run, and there are three of them, here they are with an explanation of exactly what they do:\n"
"\n"
"- Help: Will print a help page.\n"
"- MakeProject: This will extract all the packages referenced in the project file, from the disks directory -or DLC disks directory if it applies-, and they will be moved to the intermediate directory. The miscellaneous files and package sub-files marked as an override will then be copied to your project folder with the same directory structure, unless the file already exists.\n"
"- BuildMod: With this action, all the folders representing packages in your project's directory, will be copied over to the intermediate directory, any file conflicts will be resolved keeping the file from the project. Next, the packages in the intermediate directory will be packed again with the appropriate tool before deleting any files marked as an exclude, and they will be copied to the mods directory, as well as the miscellaneous files in your project. The mod.ini file will be updated with the information in the project file, unless it doesn't exist, then it will be created automatically with default values in the Main category.\n"
"\n"
"## Options\n"
"All other arguments after the first one are referred to as an option, and they will be interpreted as a flag or a project, they always begin with a dash, and here's how you use them:\n"
"\n"
"### Projects\n"
"If the option is lowercase p, then that's a project. The project option needs to have a path value, and you'll write it as such: `-p=E:/Some/Path/Can/Be/Relative`\n"
"You can define many project options, and Needlemake will gather them all in a list and run with the action and flags you define for each of them, one after the other. If you don't have any project option, the working directory will be used instead.\n"
"\n"
"### Flags\n"
"Flags are like actions, but they're optional and you can have many of them in one run. You define them by just writing a dash and the flags you want as such: `-ExRxCm` and they are not separated, the first letter of each is uppercase for readability, and you can have several options with different flags if you want, or one option for every flag, though I don't know why you'd want to do that, with the way I implemented it you kinda just can.\n"
"There are six flags, and they are the following:\n"
"\n"
"- ExtractDisks (Ex): This will extract the disks referenced in the project file.\n"
"- RextractDisks (Rx): When extracting a disk, if the folder for that disk already exists, after reporting it you'll be asked if you wanna delete it and extract it again instead of skipping it, before the tool continues.\n"
"- PrecleanMod (Pcm): The disk folder in the mod's directory will be deleted before running the action.\n"
"- PrecleanInt (Pci): The intermediate directory will be deleted before running the action.\n"
"- CleanMod (Cm): The disk folder in the mod's directory will be deleted after running the action.\n"
"- CleanInt (Ci): The intermediate directory will be deleted after running the action.\n"
"\n"
"## Example Usage\n"
"1. Run `needlemake Help` to get a quick reminder of how to use Needlemake\n"
"2. Write your project file.\n"
"3. Run `needlemake MakeProject -ExRxPciCm`.\n"
"4. Edit any files you want, add any files you want.\n"
"5. Run `needlemake BuildMod -Pcm`.\n"
"6. Run the game to see if you like your changes.\n"
"\n"
"And that's it, you can then zip your mod and upload it as-is.\n"

;