extern char* FILENAME_FOR_WORK;
extern char* FILENAME_DATA_BASE;
extern int MODE_ARG;

enum ModeARGUMENT{
    ARG_MARIIA,
    ARG_DED,
    ARG_ERROR
};

void CheckArgComStr(int argc, char* argv[]);
int CheckMode(const char* argModeFromComStr);
