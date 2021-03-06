#ifndef GUARD_FIELDMAP_H
#define GUARD_FIELDMAP_H

enum
{
    CONNECTION_DOWN = 1,
    CONNECTION_UP,
    CONNECTION_LEFT,
    CONNECTION_RIGHT,
    CONNECTION_DIVE,
    CONNECTION_EMERGE
};

typedef void (*TilesetCB)(void);

struct Tileset
{
    bool8 isCompressed;
    bool8 isSecondary;
    void *tiles;
    void *palettes;
    void *metatiles;
    void *metatileAttributes;
    TilesetCB callback;
};

struct MapData
{
    s32 width;
    s32 height;
    void *border;
    void *map;
    struct Tileset *primaryTileset;
    struct Tileset *secondaryTileset;
};

struct MapObjectTemplate
{
    /*0x00*/ u8 localId;
    /*0x01*/ u8 filler_1[0x3];
    /*0x04*/ s16 x;
    /*0x06*/ s16 y;
    /*0x08*/ u8 elevation;
    /*0x09*/ u8 movementType;
    /*0x0A*/ u8 filler_A[0x6];
    /*0x10*/ u8 *script;
    /*0x14*/ u8 filler_14[0x4];
};  /*size = 0x18*/

struct WarpEvent
{
    s16 x, y;
    s8 warpId;
    s8 mapGroup;
    s8 mapNum;
};

struct CoordEvent
{
    s16 x, y;
    u8 filler_4[0x2];
    u16 trigger;
    u16 index;
    u8 filler_A[0x2];
    u8 *script;
};

struct BgEvent
{
    s16 x, y;
    u8 filler_4;
    u8 kind;
    s16 filler_6;
    u8 *script;
};

struct MapEvents
{
    u8 mapObjectCount;
    u8 warpCount;
    u8 coordEventCount;
    u8 bgEventCount;

    struct MapObjectTemplate *mapObjects;
    struct WarpEvent *warps;
    struct CoordEvent *coordEvents;
    struct BgEvent *bgEvents;
};

struct MapConnection
{
    u8 direction;
    u32 offset;
    s8 mapGroup;
    s8 mapNum;
};

struct MapConnections
{
    s32 count;
    struct MapConnection *connections;
};

struct MapHeader
{
    struct MapData *mapData;
    struct MapEvents *events;
    u8 *mapScripts;
    struct MapConnections *connections;
    u16 music;
    u16 mapDataId;
    u8 name;
    u8 cave;
    u8 weather;
    /* 0x17 */ u8 light;
    u8 filler_18;
    u8 escapeRope;
    u8 flags;
    u8 battleType;
};

struct MapObject
{
    /*0x00*/ u32 active:1;
             u32 mapobj_bit_1:1;
             u32 mapobj_bit_2:1;
             u32 mapobj_bit_3:1;
             u32 mapobj_bit_4:1;
             u32 mapobj_bit_5:1;
             u32 mapobj_bit_6:1;
             u32 mapobj_bit_7:1;
    /*0x01*/ u32 mapobj_bit_8:1;
             u32 mapobj_bit_9:1;
             u32 mapobj_bit_10:1;
             u32 mapobj_bit_11:1;
             u32 mapobj_bit_12:1;
             u32 mapobj_bit_13:1;
             u32 mapobj_bit_14:1;
             u32 mapobj_bit_15:1;
    /*0x02*/ u32 mapobj_bit_16:1;
             u32 mapobj_bit_17:1;
             u32 mapobj_bit_18:1;
             u32 mapobj_bit_19:1;
             u32 mapobj_bit_20:1;
             u32 mapobj_bit_21:1;
             u32 mapobj_bit_22:1;
             u32 mapobj_bit_23:1;
    /*0x03*/ u32 mapobj_bit_24:1;
             u32 mapobj_bit_25:1;
             u32 mapobj_bit_26:1;
             u32 mapobj_bit_27:1;
             u32 mapobj_bit_28:1;
             u32 mapobj_bit_29:1;
             u32 mapobj_bit_30:1;
             u32 mapobj_bit_31:1;
    /*0x04*/ u8 spriteId;
    /*0x05*/ u8 graphicsId;
    /*0x06*/ u8 animPattern;
    /*0x07*/ u8 trainerType;
    /*0x08*/ u8 localId;
    /*0x09*/ u8 mapNum;
    /*0x0A*/ u8 mapGroup;
    /*0x0B*/ u8 mapobj_unk_0B_0:4;
             u8 elevation:4;
    /*0x0C*/ struct Coords16 coords1;
    /*0x10*/ struct Coords16 coords2;
    /*0x14*/ struct Coords16 coords3;
    /*0x18*/ u8 mapobj_unk_18:4;
    /*0x19*/ u8 mapobj_unk_19;
    /*0x1A*/ u8 mapobj_unk_1A;
    /*0x1B*/ u8 mapobj_unk_1B;
    /*0x1C*/ u8 mapobj_unk_1C;
    /*0x1D*/ u8 trainerRange_berryTreeId;
    /*0x1E*/ u8 mapobj_unk_1E;
    /*0x1E*/ u8 mapobj_unk_1F;
    /*0x20*/ u8 mapobj_unk_20;
    /*0x21*/ u8 mapobj_unk_21;
    /*size = 0x24*/
};

struct MapObjectGraphicsInfo
{
    u16 tileTag;
    u16 paletteTag1;
    u16 paletteTag2;
    u16 size;
    s16 width;
    s16 height;
    u8 paletteSlot:4;
    u8 shadowSize:2;
    u8 inanimate:1;
    u8 disableReflectionPaletteLoad:1;
    u8 tracks;
    struct OamData *oam;
    struct SubspriteTable *subspriteTables;
    union AnimCmd **anims;
    struct SpriteFrameImage *images;
    union AffineAnimCmd **affineAnims;
};

struct PlayerAvatar
{
    u8 bitfield;
    u8 bike;
    u8 running2;
    u8 running1;
    u8 spriteId;
    u8 mapObjectId;
    // TODO: rest of struct
};

extern struct MapObject gMapObjects[];
extern u8 gSelectedMapObject;
extern struct MapHeader gMapHeader;
extern struct PlayerAvatar gPlayerAvatar;

#endif // GUARD_FIELDMAP_H
