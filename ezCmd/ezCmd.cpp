// ezCmd.cpp : This file is a demo for using eZCmdline
//

#include <iostream>
#include "ezCmdline.h"

int main(int argc, char* argv[])
{
    eZCmdline cmd("This program is a demo for how to use eZCmdline");
    eZParam param_helpinfo("-h", "-help", "Display help information.");

    eZParam param_strPar("-s", "-string", "Follow a string parameter.", true, eZParam::STRING_OPT);
    eZParam param_intPar("-n", "-int", "input a integer parameter.", true, eZParam::INT_OPT);
    eZParam param_floatPar("-f", "-float", "input a float parameter.", true, eZParam::INT_OPT);

    cmd.addOption(param_helpinfo);
    cmd.addOption(param_strPar);
    cmd.addOption(param_intPar);
    cmd.addOption(param_floatPar);

    if (argc <= 1)
        cmd.showOptions();
    cmd.parse(argc, argv);

    int nPara = 0;
    float fPara = 0;
    string strPara = "";

    param_strPar.getValue(strPara);
    param_intPar.getValue(nPara);
    param_floatPar.getValue(fPara);

    cout << "string parameter:" << strPara << endl;
    cout << "integer parameter:" << nPara << endl;
    cout << "float parameter:" << fPara << endl;


    return 0;
}

