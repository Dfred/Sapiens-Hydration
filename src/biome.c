#include "SPBiome.h"

// leave the function if a condition isn't met
#define BAILIF(__expr__, __ret__) if (__expr__) return __ret__;

// create a new *water* game object type
#define GAMEOBJ_WATER_CREATETYPE(__subtype__) static uint32_t gameObjectType_water##__subtype__;

// create a new index for *water* game object type
#define GAMEOBJ_WATER_GETTYPEINDEX(__subtype__) \
gameObjectType_water##__subtype__ = threadState->getGameObjectTypeIndex(threadState, "water"#__subtype__);

// Dave's macro to safely add a type in spBiomeGetTransientGameObjectTypesForFaceSubdivision()
#define ADD_OBJECT(__addType__)\
types[addedCount++] = __addType__;\
if(addedCount >= BIOME_MAX_GAME_OBJECT_COUNT_PER_SUBDIVISION)\
{\
    return addedCount;\
}


GAMEOBJ_WATER_CREATETYPE(Clear)
GAMEOBJ_WATER_CREATETYPE(Tainted)
GAMEOBJ_WATER_CREATETYPE(Salted)
GAMEOBJ_WATER_CREATETYPE(SpringPop)
GAMEOBJ_WATER_CREATETYPE(SpringLeak)

static SPSimpleObjectSpawnerCollection* spawnerCollection;

void spBiomeInit(SPBiomeThreadState* threadState)
{
    if(threadState->getGameObjectTypeIndex) //this function isn't set where game object types aren't required eg. in the initial world creation screen
    {
        GAMEOBJ_WATER_GETTYPEINDEX(Clear)
        GAMEOBJ_WATER_GETTYPEINDEX(Tainted)
        GAMEOBJ_WATER_GETTYPEINDEX(Salted)
        GAMEOBJ_WATER_GETTYPEINDEX(SpringPop)
        GAMEOBJ_WATER_GETTYPEINDEX(SpringLeak)
        
        spawnerCollection = threadState->getSimpleObjectSpawnerCollection(threadState);
    }
}

void spBiomeGetTagsForPoint(SPBiomeThreadState* threadState,
                            uint16_t* tagsOut,
                            int* tagCountOut,
                            SPVec3 pointNormal,
                            SPVec3 noiseLoc,
                            double altitude,
                            double steepness,
                            double riverDistance,
                            double temperatureSummer,
                            double temperatureWinter,
                            double rainfallSummer,
                            double rainfallWinter)
{
    *tagCountOut = 0;
    *tagsOut = 0;
}

// Converts the steepness value into radians going from 0 to π/2
double get_AngleFromSteepness(double steepness) {
    return isnan(steepness) ? 0 : atan(steepness / sqrt(32));
}

// Create Transient Objects
int spBiomeGetTransientGameObjectTypesForFaceSubdivision(
    SPBiomeThreadState* threadState,
    int                 incomingTypeCount,  // Amount of already generated objects
    uint32_t*           types,              // Array of types to be generated with size BIOME_MAX_GAME_OBJECT_COUNT_PER_SUBDIVISION
    uint16_t*           biomeTags,          // Array of biome tags at the position to generate
    int                 tagCount,           // Amount of biome tags at the position to generate
    SPVec3              pointNormal,        // Coordinates in the world
    SPVec3              noiseLoc,           // Location to be used in conjunction with the given noiseGenerator
    uint64_t            faceUniqueID,       // The unique id of the face, can be used to get random values
    int                 level,              // The level of subdivisions the face has undergone. The higher this value, the denser that gameObjects will be placed. Method called only for [13-21] levels.
    double              baseAltitude,       // Altitude of the face. There is no "absolute minimum" or "absolute maximum", but running some tests it seems to fall between -0.001 and 0.001, with 0 being the sea level. A value of 0.001 translates to about 4335. 1 meter translates to 0.00000023 units in baseAltitude.
    double              steepness,          // The steepness of that coordinate. It is calculated by taking two other samples 4m away, one to the north, and one to the east, of which the maximum absolute difference between those heights and the base point height in meters is taken.
    double              riverDistance       // Distance to the closest river. A river distance of 1 indicates that the nearest river is about 7650 hexagons away.
){
    int addedCount = incomingTypeCount;

    BAILIF(addedCount >= BIOME_MAX_GAME_OBJECT_COUNT_PER_SUBDIVISION, addedCount)
    BAILIF(baseAltitude <= -0.0000001, addedCount)
    BAILIF(level < SP_SUBDIVISIONS - 7, addedCount)

    // no sources too close to a river
    BAILIF(100 < riverDistance * 7650, addedCount)

    // throw dices for number of objects to create
    SPVec3 noiseLookup = spVec3Mul(noiseLoc, 999.0);
    SPVec3 scaledNoiseLoc = spVec3Mul(noiseLookup, 400.0);
    double rawValue = spNoiseGet(threadState->spNoise1, scaledNoiseLoc, 2);
    double rangedFractionValue = rawValue * rawValue * 8.0;
    int objectCount = (((int)spRandomIntegerValueForUniqueIDAndSeed(faceUniqueID, 5243, 40)) - 38 + 2 * rangedFractionValue) / 2;
    BAILIF(objectCount < 0, addedCount)

    // water type from steepness
    uint32_t water_type = get_AngleFromSteepness(steepness) < 5 ? gameObjectType_waterSpringPop : gameObjectType_waterSpringLeak;
    ADD_OBJECT(water_type)
    
    return addedCount;
}
