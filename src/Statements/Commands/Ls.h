#ifndef SHELL_INTERPRETER_LS_H
#define SHELL_INTERPRETER_LS_H

#include "../Statement.h"
#include "../../Exceptions.h"
#include <iostream>
#include <dirent.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <cstring>

namespace Commands {
    class Ls : public Statement {
    public:
        void execute() override {
            if (fork() == 0) {
                bool l_flag = false, i_flag = false, a_flag = false;

                if (arguments.size() > 4) {
                    throw InvalidNumberOfParametersException();
                }

                for (int i = 0; i < arguments.size() && !arguments.empty(); i++) {
                    if (arguments[i][0] != '-') {
                        if (i < arguments.size() - 1)
                            throw InvalidArgumentsException();
                        else
                            break;
                    } else if (arguments[i].size() < 2) {
                        throw InvalidArgumentsException();
                    } else {
                        for (int j = 1; j < arguments[i].size(); j++) {
                            if (arguments[i][j] == 'l')
                                l_flag = true;
                            else if (arguments[i][j] == 'a')
                                a_flag = true;
                            else if (arguments[i][j] == 'i')
                                i_flag = true;
                            else
                                throw InvalidArgumentsException();
                        }
                    }
                }

                DIR *dir;
                struct dirent *ent;
                std::stringstream files;
                int fileCounter = 0;
                int filesInOneLineCounter = 0;
                std::string path;
                bool matchFileNameToPatern = false;
                std::string filePattern;

                path = arguments.empty() || arguments[arguments.size() - 1][0] == '-' ?
                    "." : arguments[arguments.size() - 1];

                std::string currDir = get_current_dir_name();

                //For ls *.txt
                size_t founded = path.find('.');
                if (founded != std::string::npos && founded != 0) {
                    matchFileNameToPatern = true;
                    filePattern = path;
                    path = ".";
                }
                if ((dir = opendir(path.c_str())) != NULL) {
                    while ((ent = readdir(dir)) != NULL) { //read files
                        if (l_flag) {
                            if (!a_flag && ent->d_name[0] == '.') { //ignore hidden
                                continue;
                            }

                            std::string s = currDir + '/' + path + '/' + std::string(ent->d_name);

                            struct stat ret;
                            if ((stat((currDir + '/' + path + '/' + std::string(ent->d_name)).c_str(),
                                    &ret)) == -1) {
//                            throw InvalidArgumentsException();
                                continue;
                            }
                            if (matchFileNameToPatern && !Statement::isStringMatchPatern(std::string(ent->d_name), filePattern)) {
                                continue;
                            }
                            if (i_flag) {
                                files << ent->d_ino << " "; //inode number
                            }

                            files << getFileTypeFromInt(ent->d_type) << " "; //file type


                            files << getPermsForFile(ret) << "\t"; //permissions

                            files << ret.st_nlink << "\t"; //number of hardlinks

                            files << getpwuid(ret.st_uid)->pw_name << "\t"; //owner name

                            files << getgrgid(ret.st_gid)->gr_name << "\t"; //group name

                            files << ret.st_size << "\t"; //file size in bytes

                            if (ret.st_size < 1000)
                                files << "\t";

                            files << ent->d_name << "\n"; //file name
                        } else {
                            if (!a_flag && ent->d_name[0] == '.') //ignore hidden
                                continue;

                            if (matchFileNameToPatern && !Statement::isStringMatchPatern(std::string(ent->d_name), filePattern)) {
                                continue;
                            }
                            if (i_flag)
                                files << ent->d_ino << " "; //inode number

                            files << ent->d_name << "\t\t"; //file name

                            if (++filesInOneLineCounter == 4) {
                                filesInOneLineCounter = 0;
                                files << "\n";
                            }
                        }

                        fileCounter++;
                    }
                } else
                    throw NoSuchPathException();

                if(filesInOneLineCounter)
                    files << "\n";

                std::stringstream output;
                output << "total: " << fileCounter << "\n" << files.str();

                std::cout << output.str() << std::endl;
            } else {
                wait(NULL);
            }
        }

    private:

        std::string getPermsForFile(struct stat &ret) {
            int owner = (ret.st_mode & S_IRUSR) | (ret.st_mode & S_IWUSR) | (ret.st_mode & S_IXUSR); //owner
            int group = (ret.st_mode & S_IRGRP) | (ret.st_mode & S_IWGRP) | (ret.st_mode & S_IXGRP); //group
            int other = (ret.st_mode & S_IROTH) | (ret.st_mode & S_IWOTH) | (ret.st_mode & S_IXOTH); //other

            return mapPermsToString(owner) + mapPermsToString(group) + mapPermsToString(other);
        }

        std::string mapPermsToString(int perms) {
            std::string r = "-", w = "-", x = "-";

            if (perms % 2 != 0)
                x = "x";

            if (perms >= 4)
                r = "r";

            if (perms / 2 == 1 || perms / 2 == 3)
                w = "w";

            return r + w + x;
        }

        char getFileTypeFromInt(int typeInt) {
            switch (typeInt) {
                case DT_UNKNOWN:
                    return '?';
                case DT_REG:
                    return '-';
                case DT_DIR:
                    return 'd';
                case DT_LNK:
                    return 'l';
                case DT_FIFO:
                    return 'p';
                case DT_SOCK:
                    return 's';
                case DT_BLK:
                    return 'b';
                case DT_CHR:
                    return 'c';
                default:
                    return '?';
            }
        }
    };
}
#endif //SHELL_INTERPRETER_LS_H
