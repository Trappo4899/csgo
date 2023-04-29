#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <assert.h>
#include <array>
#include <sstream>
#include <codecvt>
#include <locale>
#include <unordered_map>
#include <algorithm>

/* UTIL */
#include "address.h"
#include "hash.h"
#include "modules.h"
#include "pe.h"
#include "xor.h"
#include "winternals.h"
#include "util.h"
#include "hooking.h"
#include "vmt.h"
#include "interfaces.h"

/* MATH */
#include "vector.h"
#include "matrix3x4.h"
#include "color.h"
#include "math.h"

/* SDK */
#include "netvars.h"
#include "convars.h"
#include "entitylist.h"
#include "entities.h"
#include "engineclient.h"
#include "netchannelinfo.h"
#include "baseclient.h"
#include "model.h"
#include "debugoverlay.h"
#include "vgui.h"
#include "consoledisplay.h"
#include "system.h"

/* HEADERS */
#include "client.h"
#include "csgo.h"
#include "render.h"

/* FEATURES */
#include "features.h"

/* MENU */
#include "window.h"
#include "input.h"
#include "menu.h"
#include "element.h"
#include "tabs.h"
#include "group.h"
#include "checkbox.h"
#include "slider.h"
#include "dropdown.h"
#include "multidropdown.h"
#include "colourpicker.h"