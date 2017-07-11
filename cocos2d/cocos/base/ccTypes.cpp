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

#include "base/ccTypes.h"

NS_CC_BEGIN

const std::string STD_STRING_EMPTY("");
const ssize_t CC_INVALID_INDEX = -1;

/**
 * Color3B
 */

Color3B::Color3B()
: r(0)
, g(0)
, b(0)
{}

Color3B::Color3B(GLubyte _r, GLubyte _g, GLubyte _b)
: r(_r)
, g(_g)
, b(_b)
{}

Color3B::Color3B(const Color4B& color)
: r(color.r)
, g(color.g)
, b(color.b)
{}

Color3B::Color3B(const Color4F& color)
: r(color.r * 255.0f)
, g(color.g * 255.0f)
, b(color.b * 255.0f)
{}

bool Color3B::operator==(const Color3B& right) const
{
    return (r == right.r && g == right.g && b == right.b);
}

bool Color3B::operator==(const Color4B& right) const
{
    return (r == right.r && g == right.g && b == right.b && 255 == right.a);
}

bool Color3B::operator==(const Color4F& right) const
{
    return (right.a == 1.0f && Color4F(*this) == right);
}

bool Color3B::operator!=(const Color3B& right) const
{
    return !(*this == right);
}

bool Color3B::operator!=(const Color4B& right) const
{
    return !(*this == right);
}

bool Color3B::operator!=(const Color4F& right) const
{
    return !(*this == right);
}

/**
 * Color4B
 */

Color4B::Color4B()
: r(0)
, g(0)
, b(0)
, a(0)
{}

Color4B::Color4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
: r(_r)
, g(_g)
, b(_b)
, a(_a)
{}

Color4B::Color4B(const Color3B& color, GLubyte _a)
: r(color.r)
, g(color.g)
, b(color.b)
, a(_a)
{}

Color4B::Color4B(const Color4F& color)
: r(color.r * 255)
, g(color.g * 255)
, b(color.b * 255)
, a(color.a * 255)
{}

bool Color4B::operator==(const Color4B& right) const
{
    return (r == right.r && g == right.g && b == right.b && a == right.a);
}

bool Color4B::operator==(const Color3B& right) const
{
    return (r == right.r && g == right.g && b == right.b && a == 255);
}

bool Color4B::operator==(const Color4F& right) const
{
    return (*this == Color4B(right));
}

bool Color4B::operator!=(const Color4B& right) const
{
    return !(*this == right);
}

bool Color4B::operator!=(const Color3B& right) const
{
    return !(*this == right);
}

bool Color4B::operator!=(const Color4F& right) const
{
    return !(*this == right);
}

/**
 * Color4F
 */

Color4F::Color4F()
: r(0.0f)
, g(0.0f)
, b(0.0f)
, a(0.0f)
{}

Color4F::Color4F(float _r, float _g, float _b, float _a)
: r(_r)
, g(_g)
, b(_b)
, a(_a)
{}

Color4F::Color4F(const Color3B& color, float _a)
: r(color.r / 255.0f)
, g(color.g / 255.0f)
, b(color.b / 255.0f)
, a(_a)
{}

Color4F::Color4F(const Color4B& color)
: r(color.r / 255.0f)
, g(color.g / 255.0f)
, b(color.b / 255.0f)
, a(color.a / 255.0f)
{}

bool Color4F::operator==(const Color4F& right) const
{
    return (r == right.r && g == right.g && b == right.b && a == right.a);
}

bool Color4F::operator==(const Color3B& right) const
{
    return (a == 1.0f && Color3B(*this) == right);
}

bool Color4F::operator==(const Color4B& right) const
{
    return (*this == Color4F(right));
}

bool Color4F::operator!=(const Color4F& right) const
{
    return !(*this == right);
}

bool Color4F::operator!=(const Color3B& right) const
{
    return !(*this == right);
}

bool Color4F::operator!=(const Color4B& right) const
{
    return !(*this == right);
}

/**
 * Color constants
 */

const Color3B Color3B::LIGHTPINK(255,182,193); //浅粉红 255,182,193
const Color3B Color3B::PINK(255,192,203); //粉红 255,192,203
const Color3B Color3B::CRIMSON(220,20,60); //猩红 220,20,60
const Color3B Color3B::LAVENDERBLUSH(255,240,245); //脸红的淡紫色 255,240,245
const Color3B Color3B::PALEVIOLETRED(219,112,147); //苍白的紫罗兰红色 219,112,147
const Color3B Color3B::HOTPINK(255,105,180); //热情的粉红 255,105,180
const Color3B Color3B::DEEPPINK(255,20,147); //深粉色 255,20,147
const Color3B Color3B::MEDIUMVIOLETRED(199,21,133); //适中的紫罗兰红色 199,21,133
const Color3B Color3B::ORCHID(218,112,214); //兰花的紫色 218,112,214
const Color3B Color3B::THISTLE(216,191,216); //蓟 216,191,216
const Color3B Color3B::PLUM(221,160,221); //李子 221,160,221
const Color3B Color3B::VIOLET(238,130,238); //紫罗兰 238,130,238
const Color3B Color3B::MAGENTA(255,0,255); //洋红 255,0,255
const Color3B Color3B::FUCHSIA(255,0,255); //灯笼海棠(紫红色) 255,0,255
const Color3B Color3B::DARKMAGENTA(139,0,139); //深洋红色 139,0,139
const Color3B Color3B::PURPLE(128,0,128); //紫色 128,0,128
const Color3B Color3B::MEDIUMORCHID(186,85,211); //适中的兰花紫 186,85,211
const Color3B Color3B::DARKVOILET(148,0,211); //深紫罗兰色 148,0,211
const Color3B Color3B::DARKORCHID(153,50,204); //深兰花紫 153,50,204
const Color3B Color3B::INDIGO(75,0,130); //靛青 75,0,130
const Color3B Color3B::BLUEVIOLET(138,43,226); //深紫罗兰的蓝色 138,43,226
const Color3B Color3B::MEDIUMPURPLE(147,112,219); //适中的紫色 147,112,219
const Color3B Color3B::MEDIUMSLATEBLUE(123,104,238); //适中的板岩暗蓝灰色 123,104,238
const Color3B Color3B::SLATEBLUE(106,90,205); //板岩暗蓝灰色 106,90,205
const Color3B Color3B::DARKSLATEBLUE(72,61,139); //深岩暗蓝灰色 72,61,139
const Color3B Color3B::LAVENDER(230,230,250); //熏衣草花的淡紫色 230,230,250
const Color3B Color3B::GHOSTWHITE(248,248,255); //幽灵的白色 248,248,255
const Color3B Color3B::BLUE(0,0,255); //纯蓝 0,0,255
const Color3B Color3B::MEDIUMBLUE(0,0,205); //适中的蓝色 0,0,205
const Color3B Color3B::MIDNIGHTBLUE(25,25,112); //午夜的蓝色 25,25,112
const Color3B Color3B::DARKBLUE(0,0,139); //深蓝色 0,0,139
const Color3B Color3B::NAVY(0,0,128); //海军蓝 0,0,128
const Color3B Color3B::ROYALBLUE(65,105,225); //皇军蓝 65,105,225
const Color3B Color3B::CORNFLOWERBLUE(100,149,237); //矢车菊的蓝色 100,149,237
const Color3B Color3B::LIGHTSTEELBLUE(176,196,222); //淡钢蓝 176,196,222
const Color3B Color3B::LIGHTSLATEGRAY(119,136,153); //浅石板灰 119,136,153
const Color3B Color3B::SLATEGRAY(112,128,144); //石板灰 112,128,144
const Color3B Color3B::DODERBLUE(30,144,255); //道奇蓝 30,144,255
const Color3B Color3B::ALICEBLUE(240,248,255); //爱丽丝蓝 240,248,255
const Color3B Color3B::STEELBLUE(70,130,180); //钢蓝 70,130,180
const Color3B Color3B::LIGHTSKYBLUE(135,206,250); //淡蓝色 135,206,250
const Color3B Color3B::SKYBLUE(135,206,235); //天蓝色 135,206,235
const Color3B Color3B::DEEPSKYBLUE(0,191,255); //深天蓝 0,191,255
const Color3B Color3B::LIGHTBLUE(173,216,230); //淡蓝 173,216,230
const Color3B Color3B::POWDERBLUE(176,224,230); //火药蓝 176,224,230
const Color3B Color3B::CADETBLUE(95,158,160); //军校蓝 95,158,160
const Color3B Color3B::AZURE(240,255,255); //蔚蓝色 240,255,255
const Color3B Color3B::LIGHTCYAN(225,255,255); //淡青色 225,255,255
const Color3B Color3B::PALETURQUOISE(175,238,238); //苍白的绿宝石 175,238,238
const Color3B Color3B::CYAN(0,255,255); //青色 0,255,255
const Color3B Color3B::AQUA(0,255,255); //水绿色 0,255,255
const Color3B Color3B::DARKTURQUOISE(0,206,209); //深绿宝石 0,206,209
const Color3B Color3B::DARKSLATEGRAY(47,79,79); //深石板灰 47,79,79
const Color3B Color3B::DARKCYAN(0,139,139); //深青色 0,139,139
const Color3B Color3B::TEAL(0,128,128); //水鸭色 0,128,128
const Color3B Color3B::MEDIUMTURQUOISE(72,209,204); //适中的绿宝石 72,209,204
const Color3B Color3B::LIGHTSEAGREEN(32,178,170); //浅海洋绿 32,178,170
const Color3B Color3B::TURQUOISE(64,224,208); //绿宝石 64,224,208
const Color3B Color3B::AUQAMARIN(127,255,170); //绿玉\碧绿色 127,255,170
const Color3B Color3B::MEDIUMAQUAMARINE(0,250,154); //适中的碧绿色 0,250,154
const Color3B Color3B::MEDIUMSPRINGGREEN(0,255,127); //适中的春天的绿色 0,255,127
const Color3B Color3B::MINTCREAM(245,255,250); //薄荷奶油 245,255,250
const Color3B Color3B::SPRINGGREEN(60,179,113); //春天的绿色 60,179,113
const Color3B Color3B::SEAGREEN(46,139,87); //海洋绿 46,139,87
const Color3B Color3B::HONEYDEW(240,255,240); //蜂蜜 240,255,240
const Color3B Color3B::LIGHTGREEN(144,238,144); //淡绿色 144,238,144
const Color3B Color3B::PALEGREEN(152,251,152); //苍白的绿色 152,251,152
const Color3B Color3B::DARKSEAGREEN(143,188,143); //深海洋绿 143,188,143
const Color3B Color3B::LIMEGREEN(50,205,50); //酸橙绿 50,205,50
const Color3B Color3B::LIME(0,255,0); //酸橙色 0,255,0
const Color3B Color3B::FORESTGREEN(34,139,34); //森林绿 34,139,34
const Color3B Color3B::GREEN(0,128,0); //纯绿 0,128,0
const Color3B Color3B::DARKGREEN(0,100,0); //深绿色 0,100,0
const Color3B Color3B::CHARTREUSE(127,255,0); //查特酒绿 127,255,0
const Color3B Color3B::LAWNGREEN(124,252,0); //草坪绿 124,252,0
const Color3B Color3B::GREENYELLOW(173,255,47); //绿黄色 173,255,47
const Color3B Color3B::OLIVEDRAB(85,107,47); //橄榄土褐色 85,107,47
const Color3B Color3B::BEIGE(245,245,220); //米色(浅褐色) 245,245,220
const Color3B Color3B::LIGHTGOLDENRODYELLOW(250,250,210); //浅秋麒麟黄 250,250,210
const Color3B Color3B::IVORY(255,255,240); //象牙 255,255,240
const Color3B Color3B::LIGHTYELLOW(255,255,224); //浅黄色 255,255,224
const Color3B Color3B::YELLOW(255,255,0); //纯黄 255,255,0
const Color3B Color3B::OLIVE(128,128,0); //橄榄 128,128,0
const Color3B Color3B::DARKKHAKI(189,183,107); //深卡其布 189,183,107
const Color3B Color3B::LEMONCHIFFON(255,250,205); //柠檬薄纱 255,250,205
const Color3B Color3B::PALEGODENROD(238,232,170); //灰秋麒麟 238,232,170
const Color3B Color3B::KHAKI(240,230,140); //卡其布 240,230,140
const Color3B Color3B::GOLD(255,215,0); //金 255,215,0
const Color3B Color3B::CORNISLK(255,248,220); //玉米色 255,248,220
const Color3B Color3B::GOLDENROD(218,165,32); //秋麒麟 218,165,32
const Color3B Color3B::FLORALWHITE(255,250,240); //花的白色 255,250,240
const Color3B Color3B::OLDLACE(253,245,230); //老饰带 253,245,230
const Color3B Color3B::WHEAT(245,222,179); //小麦色 245,222,179
const Color3B Color3B::MOCCASIN(255,228,181); //鹿皮鞋 255,228,181
const Color3B Color3B::ORANGE(255,165,0); //橙色 255,165,0
const Color3B Color3B::PAPAYAWHIP(255,239,213); //番木瓜 255,239,213
const Color3B Color3B::BLANCHEDALMOND(255,235,205); //漂白的杏仁 255,235,205
const Color3B Color3B::NAVAJOWHITE(255,222,173); //纳瓦霍白 255,222,173
const Color3B Color3B::ANTIQUEWHITE(250,235,215); //古代的白色 250,235,215
const Color3B Color3B::TAN(210,180,140); //晒黑 210,180,140
const Color3B Color3B::BRULYWOOD(222,184,135); //结实的树 222,184,135
const Color3B Color3B::BISQUE(255,228,196); //(浓汤)乳脂,番茄等 255,228,196
const Color3B Color3B::DARKORANGE(255,140,0); //深橙色 255,140,0
const Color3B Color3B::LINEN(250,240,230); //亚麻布 250,240,230
const Color3B Color3B::PERU(205,133,63); //秘鲁 205,133,63
const Color3B Color3B::PEACHPUFF(255,218,185); //桃色 255,218,185
const Color3B Color3B::SANDYBROWN(244,164,96); //沙棕色 244,164,96
const Color3B Color3B::CHOCOLATE(210,105,30); //巧克力 210,105,30
const Color3B Color3B::SADDLEBROWN(139,69,19); //马鞍棕色 139,69,19
const Color3B Color3B::SEASHELL(255,245,238); //海贝壳 255,245,238
const Color3B Color3B::SIENNA(160,82,45); //黄土赭色 160,82,45
const Color3B Color3B::LIGHTSALMON(255,160,122); //浅鲜肉(鲑鱼)色 255,160,122
const Color3B Color3B::CORAL(255,127,80); //珊瑚 255,127,80
const Color3B Color3B::ORANGERED(255,69,0); //橙红色 255,69,0
const Color3B Color3B::DARKSALMON(233,150,122); //深鲜肉(鲑鱼)色 233,150,122
const Color3B Color3B::TOMATO(255,99,71); //番茄 255,99,71
const Color3B Color3B::MISTYROSE(255,228,225); //薄雾玫瑰 255,228,225
const Color3B Color3B::SALMON(250,128,114); //鲜肉(鲑鱼)色 250,128,114
const Color3B Color3B::SNOW(255,250,250); //雪 255,250,250
const Color3B Color3B::LIGHTCORAL(240,128,128); //淡珊瑚色 240,128,128
const Color3B Color3B::ROSYBROWN(188,143,143); //玫瑰棕色 188,143,143
const Color3B Color3B::INDIANRED(205,92,92); //印度红 205,92,92
const Color3B Color3B::RED(255,0,0); //纯红 255,0,0
const Color3B Color3B::BROWN(165,42,42); //棕色 165,42,42
const Color3B Color3B::FIREBRICK(178,34,34); //耐火砖 178,34,34
const Color3B Color3B::DARKRED(139,0,0); //深红色 139,0,0
const Color3B Color3B::MAROON(128,0,0); //栗色 128,0,0
const Color3B Color3B::WHITE(255,255,255); //纯白 255,255,255
const Color3B Color3B::WHITESMOKE(245,245,245); //白烟 245,245,245
const Color3B Color3B::GAINSBORO(220,220,220); //亮灰色 220,220,220
const Color3B Color3B::LIGHTGREY(211,211,211); //浅灰色 211,211,211
const Color3B Color3B::SILVER(192,192,192); //银白色 192,192,192
const Color3B Color3B::DARKGRAY(169,169,169); //深灰色 169,169,169
const Color3B Color3B::GRAY(128,128,128); //灰色 128,128,128
const Color3B Color3B::DIMGRAY(105,105,105); //暗淡的灰色 105,105,105
const Color3B Color3B::BLACK(0,0,0); //纯黑 0,0,0


const Color4B Color4B::WHITE  (255, 255, 255, 255);
const Color4B Color4B::YELLOW (255, 255,   0, 255);
const Color4B Color4B::GREEN  (  0, 255,   0, 255);
const Color4B Color4B::BLUE   (  0,   0, 255, 255);
const Color4B Color4B::RED    (255,   0,   0, 255);
const Color4B Color4B::MAGENTA(255,   0, 255, 255);
const Color4B Color4B::BLACK  (  0,   0,   0, 255);
const Color4B Color4B::ORANGE (255, 127,   0, 255);
const Color4B Color4B::GRAY   (166, 166, 166, 255);

const Color4F Color4F::WHITE  (    1,     1,     1, 1);
const Color4F Color4F::YELLOW (    1,     1,     0, 1);
const Color4F Color4F::GREEN  (    0,     1,     0, 1);
const Color4F Color4F::BLUE   (    0,     0,     1, 1);
const Color4F Color4F::RED    (    1,     0,     0, 1);
const Color4F Color4F::MAGENTA(    1,     0,     1, 1);
const Color4F Color4F::BLACK  (    0,     0,     0, 1);
const Color4F Color4F::ORANGE (    1,  0.5f,     0, 1);
const Color4F Color4F::GRAY   (0.65f, 0.65f, 0.65f, 1);

const BlendFunc BlendFunc::DISABLE = {GL_ONE, GL_ZERO};
const BlendFunc BlendFunc::ALPHA_PREMULTIPLIED = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
const BlendFunc BlendFunc::ALPHA_NON_PREMULTIPLIED = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
const BlendFunc BlendFunc::ADDITIVE = {GL_SRC_ALPHA, GL_ONE};

NS_CC_END
