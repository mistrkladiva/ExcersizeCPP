#pragma once
#include "Structs.h"
#include <iostream>
#include <fstream>
//#include <vector>
#include <string>
class MapJsonParse
{
public:

    static MapData LoadMapFromJsonFile(const std::string& filepath);
};

