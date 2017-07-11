/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2017 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __BASE_CCTYPES_H__
#define __BASE_CCTYPES_H__

#include <string>

#include "math/CCGeometry.h"
#include "math/CCMath.h"
#include "base/CCRef.h"
#include "platform/CCGL.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

struct Color4B;
struct Color4F;

/**
 * RGB color composed of bytes 3 bytes.
 * @since v3.0
 */
struct CC_DLL Color3B
{
    Color3B();
    Color3B(GLubyte _r, GLubyte _g, GLubyte _b);
    explicit Color3B(const Color4B& color);
    explicit Color3B(const Color4F& color);

    bool operator==(const Color3B& right) const;
    bool operator==(const Color4B& right) const;
    bool operator==(const Color4F& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4B& right) const;
    bool operator!=(const Color4F& right) const;

    bool equals(const Color3B& other) const
    {
        return (*this == other);
    }

    GLubyte r;
    GLubyte g;
    GLubyte b;

    static const Color3B LIGHTPINK; //浅粉红
    static const Color3B PINK; //粉红
    static const Color3B CRIMSON; //猩红
    static const Color3B LAVENDERBLUSH; //脸红的淡紫色
    static const Color3B PALEVIOLETRED; //苍白的紫罗兰红色
    static const Color3B HOTPINK; //热情的粉红
    static const Color3B DEEPPINK; //深粉色
    static const Color3B MEDIUMVIOLETRED; //适中的紫罗兰红色
    static const Color3B ORCHID; //兰花的紫色
    static const Color3B THISTLE; //蓟
    static const Color3B PLUM; //李子
    static const Color3B VIOLET; //紫罗兰
    static const Color3B MAGENTA; //洋红
    static const Color3B FUCHSIA; //灯笼海棠(紫红色)
    static const Color3B DARKMAGENTA; //深洋红色
    static const Color3B PURPLE; //紫色
    static const Color3B MEDIUMORCHID; //适中的兰花紫
    static const Color3B DARKVOILET; //深紫罗兰色
    static const Color3B DARKORCHID; //深兰花紫
    static const Color3B INDIGO; //靛青
    static const Color3B BLUEVIOLET; //深紫罗兰的蓝色
    static const Color3B MEDIUMPURPLE; //适中的紫色
    static const Color3B MEDIUMSLATEBLUE; //适中的板岩暗蓝灰色
    static const Color3B SLATEBLUE; //板岩暗蓝灰色
    static const Color3B DARKSLATEBLUE; //深岩暗蓝灰色
    static const Color3B LAVENDER; //熏衣草花的淡紫色
    static const Color3B GHOSTWHITE; //幽灵的白色
    static const Color3B BLUE; //纯蓝
    static const Color3B MEDIUMBLUE; //适中的蓝色
    static const Color3B MIDNIGHTBLUE; //午夜的蓝色
    static const Color3B DARKBLUE; //深蓝色
    static const Color3B NAVY; //海军蓝
    static const Color3B ROYALBLUE; //皇军蓝
    static const Color3B CORNFLOWERBLUE; //矢车菊的蓝色
    static const Color3B LIGHTSTEELBLUE; //淡钢蓝
    static const Color3B LIGHTSLATEGRAY; //浅石板灰
    static const Color3B SLATEGRAY; //石板灰
    static const Color3B DODERBLUE; //道奇蓝
    static const Color3B ALICEBLUE; //爱丽丝蓝
    static const Color3B STEELBLUE; //钢蓝
    static const Color3B LIGHTSKYBLUE; //淡蓝色
    static const Color3B SKYBLUE; //天蓝色
    static const Color3B DEEPSKYBLUE; //深天蓝
    static const Color3B LIGHTBLUE; //淡蓝
    static const Color3B POWDERBLUE; //火药蓝
    static const Color3B CADETBLUE; //军校蓝
    static const Color3B AZURE; //蔚蓝色
    static const Color3B LIGHTCYAN; //淡青色
    static const Color3B PALETURQUOISE; //苍白的绿宝石
    static const Color3B CYAN; //青色
    static const Color3B AQUA; //水绿色
    static const Color3B DARKTURQUOISE; //深绿宝石
    static const Color3B DARKSLATEGRAY; //深石板灰
    static const Color3B DARKCYAN; //深青色
    static const Color3B TEAL; //水鸭色
    static const Color3B MEDIUMTURQUOISE; //适中的绿宝石
    static const Color3B LIGHTSEAGREEN; //浅海洋绿
    static const Color3B TURQUOISE; //绿宝石
    static const Color3B AUQAMARIN; //绿玉\碧绿色
    static const Color3B MEDIUMAQUAMARINE; //适中的碧绿色
    static const Color3B MEDIUMSPRINGGREEN; //适中的春天的绿色
    static const Color3B MINTCREAM; //薄荷奶油
    static const Color3B SPRINGGREEN; //春天的绿色
    static const Color3B SEAGREEN; //海洋绿
    static const Color3B HONEYDEW; //蜂蜜
    static const Color3B LIGHTGREEN; //淡绿色
    static const Color3B PALEGREEN; //苍白的绿色
    static const Color3B DARKSEAGREEN; //深海洋绿
    static const Color3B LIMEGREEN; //酸橙绿
    static const Color3B LIME; //酸橙色
    static const Color3B FORESTGREEN; //森林绿
    static const Color3B GREEN; //纯绿
    static const Color3B DARKGREEN; //深绿色
    static const Color3B CHARTREUSE; //查特酒绿
    static const Color3B LAWNGREEN; //草坪绿
    static const Color3B GREENYELLOW; //绿黄色
    static const Color3B OLIVEDRAB; //橄榄土褐色
    static const Color3B BEIGE; //米色(浅褐色)
    static const Color3B LIGHTGOLDENRODYELLOW; //浅秋麒麟黄
    static const Color3B IVORY; //象牙
    static const Color3B LIGHTYELLOW; //浅黄色
    static const Color3B YELLOW; //纯黄
    static const Color3B OLIVE; //橄榄
    static const Color3B DARKKHAKI; //深卡其布
    static const Color3B LEMONCHIFFON; //柠檬薄纱
    static const Color3B PALEGODENROD; //灰秋麒麟
    static const Color3B KHAKI; //卡其布
    static const Color3B GOLD; //金
    static const Color3B CORNISLK; //玉米色
    static const Color3B GOLDENROD; //秋麒麟
    static const Color3B FLORALWHITE; //花的白色
    static const Color3B OLDLACE; //老饰带
    static const Color3B WHEAT; //小麦色
    static const Color3B MOCCASIN; //鹿皮鞋
    static const Color3B ORANGE; //橙色
    static const Color3B PAPAYAWHIP; //番木瓜
    static const Color3B BLANCHEDALMOND; //漂白的杏仁
    static const Color3B NAVAJOWHITE; //纳瓦霍白
    static const Color3B ANTIQUEWHITE; //古代的白色
    static const Color3B TAN; //晒黑
    static const Color3B BRULYWOOD; //结实的树
    static const Color3B BISQUE; //(浓汤)乳脂,番茄等
    static const Color3B DARKORANGE; //深橙色
    static const Color3B LINEN; //亚麻布
    static const Color3B PERU; //秘鲁
    static const Color3B PEACHPUFF; //桃色
    static const Color3B SANDYBROWN; //沙棕色
    static const Color3B CHOCOLATE; //巧克力
    static const Color3B SADDLEBROWN; //马鞍棕色
    static const Color3B SEASHELL; //海贝壳
    static const Color3B SIENNA; //黄土赭色
    static const Color3B LIGHTSALMON; //浅鲜肉(鲑鱼)色
    static const Color3B CORAL; //珊瑚
    static const Color3B ORANGERED; //橙红色
    static const Color3B DARKSALMON; //深鲜肉(鲑鱼)色
    static const Color3B TOMATO; //番茄
    static const Color3B MISTYROSE; //薄雾玫瑰
    static const Color3B SALMON; //鲜肉(鲑鱼)色
    static const Color3B SNOW; //雪
    static const Color3B LIGHTCORAL; //淡珊瑚色
    static const Color3B ROSYBROWN; //玫瑰棕色
    static const Color3B INDIANRED; //印度红
    static const Color3B RED; //纯红
    static const Color3B BROWN; //棕色
    static const Color3B FIREBRICK; //耐火砖
    static const Color3B DARKRED; //深红色
    static const Color3B MAROON; //栗色
    static const Color3B WHITE; //纯白
    static const Color3B WHITESMOKE; //白烟
    static const Color3B GAINSBORO; //亮灰色
    static const Color3B LIGHTGREY; //浅灰色
    static const Color3B SILVER; //银白色
    static const Color3B DARKGRAY; //深灰色
    static const Color3B GRAY; //灰色
    static const Color3B DIMGRAY; //暗淡的灰色
    static const Color3B BLACK; //纯黑
};

/**
 * RGBA color composed of 4 bytes.
 * @since v3.0
 */
struct CC_DLL Color4B
{
    Color4B();
    Color4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a);
    explicit Color4B(const Color3B& color, GLubyte _a = 255);
    explicit Color4B(const Color4F& color);
    
    inline void set(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    bool operator==(const Color4B& right) const;
    bool operator==(const Color3B& right) const;
    bool operator==(const Color4F& right) const;
    bool operator!=(const Color4B& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4F& right) const;

    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;

    static const Color4B WHITE;
    static const Color4B YELLOW;
    static const Color4B BLUE;
    static const Color4B GREEN;
    static const Color4B RED;
    static const Color4B MAGENTA;
    static const Color4B BLACK;
    static const Color4B ORANGE;
    static const Color4B GRAY;
};


/**
 * RGBA color composed of 4 floats.
 * @since v3.0
 */
struct CC_DLL Color4F
{
    Color4F();
    Color4F(float _r, float _g, float _b, float _a);
    explicit Color4F(const Color3B& color, float _a = 1.0f);
    explicit Color4F(const Color4B& color);

    bool operator==(const Color4F& right) const;
    bool operator==(const Color3B& right) const;
    bool operator==(const Color4B& right) const;
    bool operator!=(const Color4F& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4B& right) const;

    bool equals(const Color4F &other) const
    {
        return (*this == other);
    }

    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    static const Color4F WHITE;
    static const Color4F YELLOW;
    static const Color4F BLUE;
    static const Color4F GREEN;
    static const Color4F RED;
    static const Color4F MAGENTA;
    static const Color4F BLACK;
    static const Color4F ORANGE;
    static const Color4F GRAY;
};

/** A vertex composed of 2 floats: x, y
 @since v3.0
 */
// struct Vertex2F
// {
//     Vertex2F(float _x, float _y) :x(_x), y(_y) {}

//     Vertex2F(): x(0.f), y(0.f) {}

//     GLfloat x;
//     GLfloat y;
// };


/** A vertex composed of 2 floats: x, y
 @since v3.0
 */
// struct Vertex3F
// {
//     Vertex3F(float _x, float _y, float _z)
//         : x(_x)
//         , y(_y)
//         , z(_z)
//     {}

//     Vertex3F(): x(0.f), y(0.f), z(0.f) {}

//     GLfloat x;
//     GLfloat y;
//     GLfloat z;
// };

/** @struct Tex2F
 * A TEXCOORD composed of 2 floats: u, y
 * @since v3.0
 */
struct CC_DLL Tex2F {
    Tex2F(float _u, float _v): u(_u), v(_v) {}

    Tex2F(): u(0.f), v(0.f) {}

    GLfloat u;
    GLfloat v;
};

/** @struct PointSprite
 * Vec2 Sprite component.
 */
struct CC_DLL PointSprite
{
    Vec2   pos;        // 8 bytes
    Color4B    color;      // 4 bytes
    GLfloat    size;       // 4 bytes
};

/** @struct Quad2
 * A 2D Quad. 4 * 2 floats.
 */
struct CC_DLL Quad2
{
    Vec2        tl;
    Vec2        tr;
    Vec2        bl;
    Vec2        br;
};

/** @struct Quad3
 * A 3D Quad. 4 * 3 floats.
 */
struct CC_DLL Quad3 {
    Vec3        bl;
    Vec3        br;
    Vec3        tl;
    Vec3        tr;
};

/** @struct V2F_C4B_T2F
 * A Vec2 with a vertex point, a tex coord point and a color 4B.
 */
struct V2F_C4B_T2F
{
    /// vertices (2F)
    Vec2       vertices;
    /// colors (4B)
    Color4B        colors;
    /// tex coords (2F)
    Tex2F          texCoords;
};

/** @struct V2F_C4B_PF
 *
 */
struct V2F_C4B_PF
{
    /// vertices (2F)
    Vec2       vertices;
    /// colors (4B)
    Color4B        colors;
    /// pointsize
    float      pointSize;
};

/** @struct V2F_C4F_T2F
 * A Vec2 with a vertex point, a tex coord point and a color 4F.
 */
struct CC_DLL V2F_C4F_T2F
{
    /// vertices (2F)
    Vec2       vertices;
    /// colors (4F)
    Color4F        colors;
    /// tex coords (2F)
    Tex2F          texCoords;
};

/** @struct V3F_C4B_T2F
 * A Vec2 with a vertex point, a tex coord point and a color 4B.
 */
struct CC_DLL V3F_C4B_T2F
{
    /// vertices (3F)
    Vec3     vertices;            // 12 bytes

    /// colors (4B)
    Color4B      colors;              // 4 bytes

    // tex coords (2F)
    Tex2F        texCoords;           // 8 bytes
};

/** @struct V3F_T2F
 * A Vec2 with a vertex point, a tex coord point.
 */
struct CC_DLL V3F_T2F
{
    /// vertices (2F)
    Vec3       vertices;
    /// tex coords (2F)
    Tex2F          texCoords;
};

/** @struct V2F_C4B_T2F_Triangle
 * A Triangle of V2F_C4B_T2F.
 */
struct CC_DLL V2F_C4B_T2F_Triangle
{
    V2F_C4B_T2F a;
    V2F_C4B_T2F b;
    V2F_C4B_T2F c;
};

/** @struct V2F_C4B_T2F_Quad
 * A Quad of V2F_C4B_T2F.
 */
struct CC_DLL V2F_C4B_T2F_Quad
{
    /// bottom left
    V2F_C4B_T2F    bl;
    /// bottom right
    V2F_C4B_T2F    br;
    /// top left
    V2F_C4B_T2F    tl;
    /// top right
    V2F_C4B_T2F    tr;
};

/** @struct V3F_C4B_T2F_Quad
 * 4 Vertex3FTex2FColor4B.
 */
struct CC_DLL V3F_C4B_T2F_Quad
{
    /// top left
    V3F_C4B_T2F    tl;
    /// bottom left
    V3F_C4B_T2F    bl;
    /// top right
    V3F_C4B_T2F    tr;
    /// bottom right
    V3F_C4B_T2F    br;
};

/** @struct V2F_C4F_T2F_Quad
 * 4 Vertex2FTex2FColor4F Quad.
 */
struct CC_DLL V2F_C4F_T2F_Quad
{
    /// bottom left
    V2F_C4F_T2F    bl;
    /// bottom right
    V2F_C4F_T2F    br;
    /// top left
    V2F_C4F_T2F    tl;
    /// top right
    V2F_C4F_T2F    tr;
};

/** @struct V3F_T2F_Quad
 *
 */
struct CC_DLL V3F_T2F_Quad
{
    /// bottom left
    V3F_T2F    bl;
    /// bottom right
    V3F_T2F    br;
    /// top left
    V3F_T2F    tl;
    /// top right
    V3F_T2F    tr;
};

/** @struct BlendFunc
 * Blend Function used for textures.
 */
struct CC_DLL BlendFunc
{
    /** source blend function */
    GLenum src;
    /** destination blend function */
    GLenum dst;

    /** Blending disabled. Uses {GL_ONE, GL_ZERO} */
    static const BlendFunc DISABLE;
    /** Blending enabled for textures with Alpha premultiplied. Uses {GL_ONE, GL_ONE_MINUS_SRC_ALPHA} */
    static const BlendFunc ALPHA_PREMULTIPLIED;
    /** Blending enabled for textures with Alpha NON premultiplied. Uses {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA} */
    static const BlendFunc ALPHA_NON_PREMULTIPLIED;
    /** Enables Additive blending. Uses {GL_SRC_ALPHA, GL_ONE} */
    static const BlendFunc ADDITIVE;

    bool operator==(const BlendFunc &a) const
    {
        return src == a.src && dst == a.dst;
    }

    bool operator!=(const BlendFunc &a) const
    {
        return src != a.src || dst != a.dst;
    }

    bool operator<(const BlendFunc &a) const
    {
        return src < a.src || (src == a.src && dst < a.dst);
    }
};

/** @enum TextVAlignment
 * Vertical text alignment type.
 *
 * @note If any of these enums are edited and/or reordered, update Texture2D.m.
 */
enum class CC_DLL TextVAlignment
{
    TOP,
    CENTER,
    BOTTOM
};

/** @enum TextHAlignment
 * Horizontal text alignment type.
 *
 * @note If any of these enums are edited and/or reordered, update Texture2D.m.
 */
enum class CC_DLL TextHAlignment
{
    LEFT,
    CENTER,
    RIGHT
};

/**
* @brief Possible GlyphCollection used by Label.
*
* Specify a collections of characters to be load when Label created.
* Consider using DYNAMIC.
*/
enum class GlyphCollection {
    DYNAMIC,
    NEHE,
    ASCII,
    CUSTOM
};

// Types for animation in particle systems

/** @struct T2F_Quad
 * Texture coordinates for a quad.
 */
struct CC_DLL T2F_Quad
{
    /// bottom left
    Tex2F    bl;
    /// bottom right
    Tex2F    br;
    /// top left
    Tex2F    tl;
    /// top right
    Tex2F    tr;
};

/** @struct AnimationFrameData
 * Struct that holds the size in pixels, texture coordinates and delays for animated ParticleSystemQuad.
 */
struct CC_DLL AnimationFrameData
{
    T2F_Quad texCoords;
    float delay;
    Size size;
};

/**
 types used for defining fonts properties (i.e. font name, size, stroke or shadow)
 */

/** @struct FontShadow
 * Shadow attributes.
 */
struct CC_DLL FontShadow
{
public:

    // shadow is not enabled by default
    FontShadow()
        : _shadowEnabled(false)
        , _shadowBlur(0)
        , _shadowOpacity(0)
    {}

    /// true if shadow enabled
    bool   _shadowEnabled;
    /// shadow x and y offset
    Size   _shadowOffset;
    /// shadow blurriness
    float  _shadowBlur;
    /// shadow opacity
    float  _shadowOpacity;
};

/** @struct FontStroke
 * Stroke attributes.
 */
struct CC_DLL FontStroke
{
public:

    // stroke is disabled by default
    FontStroke()
        : _strokeEnabled(false)
        , _strokeColor(Color3B::BLACK)
        , _strokeAlpha(255)
        , _strokeSize(0)
    {}

    /// true if stroke enabled
    bool      _strokeEnabled;
    /// stroke color
    Color3B   _strokeColor;
    /// stroke alpha
    GLubyte   _strokeAlpha;
    /// stroke size
    float     _strokeSize;

};

/** @struct FontDefinition
 * Font attributes.
 */
struct CC_DLL FontDefinition
{
public:
    /**
     * @js NA
     * @lua NA
     */
    FontDefinition()
        : _fontSize(0)
        , _alignment(TextHAlignment::CENTER)
        , _vertAlignment(TextVAlignment::TOP)
        , _dimensions(Size::ZERO)
        , _fontFillColor(Color3B::WHITE)
        , _fontAlpha(255)
        , _enableWrap(true)
        , _overflow(0)
    {}

    /// font name
    std::string           _fontName;
    /// font size
    int                   _fontSize;
    /// horizontal alignment
    TextHAlignment        _alignment;
    /// vertical alignment
    TextVAlignment _vertAlignment;
    /// rendering box
    Size                  _dimensions;
    /// font color
    Color3B               _fontFillColor;
    /// font alpha
    GLubyte               _fontAlpha;
    /// font shadow
    FontShadow            _shadow;
    /// font stroke
    FontStroke            _stroke;
    /// enable text wrap
    bool                  _enableWrap;
    /** There are 4 overflows: none, clamp, shrink and resize_height.
     *  The corresponding integer values are 0, 1, 2, 3 respectively
     * For more information, please refer to Label::Overflow enum class.
     */
    int                  _overflow;
};

/**
 * @brief Effects used by `Label`
 *
 */
enum class LabelEffect {
    // FIXME: Covert them to bitwise. More than one effect should be supported
    NORMAL,
    OUTLINE,
    SHADOW,
    GLOW,
    ITALICS,
    BOLD,
    UNDERLINE,
    STRIKETHROUGH,
    ALL
};

/** @struct Acceleration
 * The device accelerometer reports values for each axis in units of g-force.
 */
class CC_DLL Acceleration
    : public Ref
{
public:
    double x;
    double y;
    double z;

    double timestamp;

    Acceleration(): x(0), y(0), z(0), timestamp(0) {}
};

extern const std::string CC_DLL STD_STRING_EMPTY;
extern const ssize_t CC_DLL CC_INVALID_INDEX;

enum class SetIntervalReason : char
{
    BY_GAME = 0,
    BY_ENGINE,
    BY_SYSTEM,
    BY_SCENE_CHANGE,
    BY_DIRECTOR_PAUSE
};

NS_CC_END
// end group
/// @}
#endif //__BASE_CCTYPES_H__
