#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include <filesystem>
#include <fstream>
#include <algorithm>

using namespace std;

void take_input(int argc, char * argv[], const string main_file, const vector<string> libraries);

string get_location(const string main_file);

vector<string> get_libs(const string file_path, const vector<string> existing_libs);

vector<string> get_libs_in_file(const string file_path);

void compile_windows(const string file_name, const vector<string> libraries, const string output);

void compile_linux(const string file_name, const vector<string> libraries, const string output);

void compile_mac(const string file_name, const vector<string> libraries, const string output);


int main(int argc, char * argv[]) {

    cout << "PotatoEngine Compiler\n" << endl;
    
    if (argc < 2) {
        cout << "No file to compile!" << endl;
        return 1;
    }

    const string main_file_relative = argv[1];
    
    if (!filesystem::exists(main_file_relative)) {
        cout << "Invalid file to compile!" << endl;
        return 1;
    }

    const string main_file_absolute = get_location(main_file_relative);
    
    cout << "Compiling file \'" << main_file_absolute << "\'\n" << endl;
    
    vector<string> potato_engine_libs = {"PotatoEngine"};

    const vector<string> used_libraries = get_libs(main_file_absolute, potato_engine_libs);
    
    for (string lib : used_libraries) {
        cout << "Using Header: " << lib << endl;
    }
    cout << endl;

    take_input(argc, argv, main_file_absolute, used_libraries);

    return 0;
}

void take_input(int argc, char * argv[], const string main_file, const vector<string> libraries) {
    int opt;
    int index;

    const struct option longopts[] = {
        {"windows", no_argument, 0, 'w'},
        {"mac", no_argument, 0, 'm'},
        {"linux", no_argument},
        {"output", required_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'}
    };

    bool platform[3] = {false, false ,false}; // Windows, Linux, Mac
    string output;

    while ( (opt = getopt_long(argc, argv, ":wmlo:h", longopts, &index)) != -1)
    {
        switch (opt) {
            case 'w':
                std::cout << "Compiling for Windows with MinGW\n" << std::endl;
                platform[0] = true;
                break;
            case 'm':
                std::cout << "Compiling for MacOS with ???\n" << std::endl;
                platform[2] = true;
                break;
            case 'l':
                std::cout << "Compiling for Linux with G++\n" << std::endl;
                platform[1] = true;
                break;
            case 'o':
                std::cout << "Outputting to \'" << optarg << "\'" << std::endl;
                output = optarg;
                break;
            case 'h':
                std::cout << "\nPotatoEngine Compile Help\n" <<
                "Command Syntax:\n" <<
                argv[0] << " <main .cpp file> <options>\n\n" <<
                "-w or --windows: Compile for windows using MinGW\n" <<
                "-m or --mac    : Compile for MacOS using ??? (Not implemented)\n" <<
                "-l or --linux  : Compile for Linux using G++ (default)\n" <<
                "Multiple of these options can be used at once.\n\n" <<
                "-o or --output : Decide what name your executable should have. By default, program.exe/app/elf\n" <<
                "-h or --help   : Brings you to this menu!\n" << std::endl;
                break;
            default:
                break;
        }
    }

    if (!(platform[0] || platform[1] || platform[2])) {
        cout << "Compiling for Linux with G++ (Default)\n" << endl;
        platform[1] = true;
    }

    if (output == "") {
        output = "program";
    }

    if (platform[0]) {
        compile_windows(main_file, libraries, output);
    }

    if (platform[1]) {
        compile_linux(main_file, libraries, output);
    }

    if (platform[2]) {
        compile_mac(main_file, libraries, output);
    }

}

string get_location(const string main_file) {
    filesystem::path relative = main_file;
    filesystem::path absolute = filesystem::absolute(relative);

    return absolute;
}

vector<string> get_libs(const string main_file_path, const vector<string> existing_libs) {
    vector <string> all_libs;
    
    vector<string> main_libs = get_libs_in_file(main_file_path);

    for (string lib : main_libs) {
        bool exists = false;
        for(string engine_lib : existing_libs) {
            if (lib == engine_lib) {
                exists = true;
            }
        }

        if (exists) {
            main_libs.erase(remove(main_libs.begin(), main_libs.end(), lib), main_libs.end());
            continue;
        }

        filesystem::path lib_file = main_file_path;
        lib_file = lib_file.parent_path();
        lib_file /= lib;

        vector<string> new_libs = main_libs;
        new_libs.insert(new_libs.end(), existing_libs.begin(), existing_libs.end());

        vector<string> lib_libs = get_libs(lib_file, new_libs);

        main_libs.insert(main_libs.end(), lib_libs.begin(), lib_libs.end());
    }

    return main_libs;

}

vector<string> get_libs_in_file(const string file_path) {
    ifstream file;
    file.open(file_path);

    vector<string> libraries;
    string current_line;
    while (getline(file, current_line)) {
        string first_chars = current_line.substr(0, 10);

        if (first_chars == "#include \"") {
            int end_of_lib = (current_line.substr(10, current_line.length() - 10)).find_first_of('\"');

            string lib = current_line.substr(10, end_of_lib);

            libraries.push_back(lib);
            continue;
        }

        first_chars = current_line.substr(0, 11);

        if (first_chars == "# include \"") {
            int end_of_lib = (current_line.substr(11, current_line.length() - 11)).find_first_of('\"');

            string lib = current_line.substr(11, end_of_lib);

            libraries.push_back(lib);
            continue;
        }
    }

    file.close();

    return libraries;
} 

void compile_windows(const string file_name, const vector<string> libraries, const string output) {
    
}

void compile_linux(const string file_name, const vector<string> libraries, const string output) {
    vector<string> lib_copy = libraries;

    filesystem::path lib_dir = file_name;
    lib_dir = lib_dir.parent_path().parent_path();
    lib_dir /= "lib";

    for (string lib : libraries) {
        filesystem::path this_lib = lib_dir;
        this_lib /= lib.substr(0, lib.find_last_of('.'));
        if (filesystem::is_directory(this_lib)) continue;
        else lib_copy.erase(remove(lib_copy.begin(), lib_copy.end(), lib), lib_copy.end());
    }

    string compile_command = "g++ " + file_name + " -I" + filesystem::path(file_name).parent_path().string() + " ";

    for ( string lib : lib_copy) {
        string lib_name = lib.substr(0, lib.find_last_of('.'));
        filesystem::path this_lib = lib_dir;
        this_lib /= lib_name;
        
        compile_command += "-L" + this_lib.string();
        
        filesystem::path lib_a = this_lib;
        lib_a /= ("lib" + lib_name + ".a");
        
        if (filesystem::exists(lib_a)) {
            compile_command += " -l" + lib_name;
        }
        
        compile_command += " -I" + this_lib.string();
    }

    filesystem::path bin = filesystem::path(file_name).parent_path().parent_path();
    bin /= "bin";
    bin /= "";

    compile_command += " -o " + bin.string() + output + ".elf";

    cout << "Running command:\n" << compile_command << "\n" << endl;

    system(compile_command.c_str());
}

void compile_mac(const string file_name, const vector<string> libraries, const string output) {
    // TODO: Fix this
    cout << "Error: MacOS Compilation impossible.\nCompilation for MacOS is not possible at this time." << endl;
}
