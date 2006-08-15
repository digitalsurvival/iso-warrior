#ifndef bkPath_h
#define bkPath_h

void freePath(Path* path);
int getFilenameFromPath(char* srcPathAndName, char* filename);
int getLastDirFromString(char* srcPath, char* dirName);
int makeLongerPath(Path* origPath, char* newDir, Path** newPath);
int makeFilePathFromString(char* srcFile, FilePath* pathPath);
int makePathFromString(char* strPath, Path* pathPath);

#endif