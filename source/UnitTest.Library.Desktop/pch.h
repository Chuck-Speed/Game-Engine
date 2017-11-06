#pragma once

#include "CppUnitTest.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

//Library
#include <stdexcept>
#include "glm.hpp"
#include "Foo.h"
#include "SList.h"
#include "Vector.h"
#include "Stack.h"
#include "Hashmap.h"
#include "Datum.h"
#include "Action.h"
#include "ActionList.h"
#include "ActionEvent.h"
#include "RTTI.h"
#include "Reaction.h"
#include "ReactionAttributed.h"
#include "EventMessageAttributed.h"
#include "expat.h"
#include "Event.h"
#include "XMLParseHelperFoo.h"
#include "XMLParseHelperTable.h"
#include "XMLParseHelperAction.h"
#include "World.h"
#include "WorldState.h"




