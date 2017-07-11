//#include "cocos2d.h"
//USING_NS_CC;
//
////顺时针,逆时针运动方向定义
//typedef enum {
//	kColckWise = 0,	//顺时针
//	kAntiClockWise,	//逆时针
//} E_ClockWise;
//
///************************************************************************/
///* 圆周运动                                                             */
///************************************************************************/
//class CCCircleBy : public ActionInterval
//{
//public:
//	static CCCircleBy* create(float t, Vec2 p, float r, E_ClockWise cw = kColckWise);
//	bool initWithDuration(float t, Vec2 p, float r, E_ClockWise cw = kColckWise);
//
//	virtual Ref* copyWithZone(void* pZone);
//	virtual void startWithTarget(Node *pTarget);
//	virtual void update(float t);
//	inline void debugDraw(bool draw, float height=1.f) {
//		m_bDebugDraw = draw;
//		m_fDrawHeight = height;
//	}
//
//protected:
//	bool m_bDebugDraw;
//	float m_fDrawHeight;
//	Vec2 m_circelCenter; //圆心位置
//	float m_radius;			//半径
//	float m_radian;			//弧度
//	float m_moveTimes;		//刷新次数
//	E_ClockWise m_cw;		//顺,逆时针方向
//};
//
//ActionInterval* GetCircleActionForNode(Node* pNode, float t, E_ClockWise wise);
//
///************************************************************************/
///* 椭圆运动                                                             */
///************************************************************************/
//// 定义一个结构来包含确定椭圆的参数  
//struct T_EllipseConfig{  
//	//中心点坐标  
//	Vec2 centerPosition;  
//	//椭圆a长，三角斜边  
//	float aLength;  
//	//椭圆c长，三角底边  
//	float cLength;  
//	//运动方向
//	E_ClockWise wise;
//	
//	T_EllipseConfig() {
//		centerPosition = Vec2(0,0);
//		aLength = 1;
//		cLength = 1;
//		wise = kColckWise;
//	}
//
//	T_EllipseConfig(Vec2 p, float a, float c, E_ClockWise w = kColckWise) {
//		centerPosition = p;
//		aLength = a;
//		cLength = c;
//		wise = w;
//	}
//};  
//
//class CCEllipseBy : public ActionInterval
//{  
//public:  
//	//用“动作持续时间”和“椭圆控制参数”创建动作  
//	static CCEllipseBy *create(float t, const T_EllipseConfig& c); 
//	//用“动作持续时间”和“椭圆控制参数”初始化动作  
//	bool initWithDuration(float t, const T_EllipseConfig& c);  
//	virtual void update(float time);//利用update函数来不断的设定坐标  
//	static inline float ellipseXat( float a, float bx, float c, float t ){ //X坐标参数方程      
//		return a*cos(2*M_PI*t);
//	}
//	static inline float ellipseYat( float a, float by, float c, float t ){ //Y坐标参数方程 
//		return c*sin(2*M_PI*t);
//	}
//	inline void debugDraw(bool draw, float height=1.f) {
//		m_bDebugDraw = draw;
//		m_fDrawHeight = height;
//	}
//	virtual Ref* copyWithZone(CCZone* pZone);
//	virtual void startWithTarget(Node *pTarget);
//protected:  
//	float m_fDrawHeight;
//	bool m_bDebugDraw;
//	T_EllipseConfig m_sConfig;  
//	Vec2 m_startPosition;  
//	Vec2 s_startPosition;  
//};  
//
//ActionInterval* GetEllipseAction(float t, T_EllipseConfig cf);
//
//ActionInterval* GetEllipseActionForNode(Node* pNode, float t, E_ClockWise wise);
//
///************************************************************************/
///* 矩形运动                                                             */
///************************************************************************/
//struct T_RectangleConfig {
//	float width ; //长
//	float height; //宽
//	Vec2 center; //中心点
//	
//	T_RectangleConfig();
//	
//	T_RectangleConfig(float w, float h, Vec2 c) {
//		width  = w;
//		height = h;
//		center = c;
//	}
//};
//
//ActionInterval* GetRectangleAction(const T_RectangleConfig& cf, float t, E_ClockWise wise);
//
//ActionInterval* GetRectangleActionForNode(Node* pNode, float t, E_ClockWise wise);
