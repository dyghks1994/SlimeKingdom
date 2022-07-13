#pragma once

typedef unsigned int uint;

#include <typeinfo>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <filesystem>
#include <assert.h>
#include <random>

namespace fs = filesystem;

#include "JsonManager.h"
#define _JSONMANAGER JsonManager::GetInstance()


#include "Unit.h"
#include"Gimmick.h"

#include "Bullet.h"

#include "Box.h"
#include "Bush.h"
#include "Rock.h"
#include "Block.h"
#include "Door.h"
#include "Switch.h"
#include "Statue.h"
#include "Sign.h"


#include "Player.h"
#include "Monster.h"

