//#include "CCActionExt.h"
//
///************************************************************************/
///* 圆周运动                                                             */
///************************************************************************/
//CCCircleBy* CCCircleBy::create(float t, Vec2 p, float r, E_ClockWise cw) {
//	CCCircleBy *pAct = new CCCircleBy();
//	pAct->initWithDuration(t, p, r, cw);
//	pAct->autorelease();
//
//	return pAct;
//}
//
//bool CCCircleBy::initWithDuration(float t, Vec2 p, float r, E_ClockWise cw) {
//	if (ActionInterval::initWithDuration(t))
//	{
//		m_bDebugDraw = false;
//		m_fDrawHeight = 1.f;
//		m_circelCenter = p;
//		m_radius = r;
//		m_radian = 2.f * M_PI / (t / Director::getInstance()->getAnimationInterval());
//		m_moveTimes = 1;
//		m_cw = cw;
//		return true;
//	}
//
//	return false;
//}
//
//void CCCircleBy::update(float t) {
//	float radian = m_radian * m_moveTimes;
//	float p1 = m_radius * sin(radian);
//	float p2 = m_radius * cos(radian);
//	float x = (m_cw == kColckWise ? p1 : p2) + m_circelCenter.x;
//	float y = (m_cw == kColckWise ? p2 : p1) + m_circelCenter.y;
//	Vec2 pos = Vec2(x,y);
//	m_pTarget->setPosition(pos);
//	m_moveTimes += 1;
//
//	if(m_bDebugDraw) {
//		DrawNode *node = DrawNode::create();
//		node->drawDot(pos, m_fDrawHeight, Color4F(128,128,128,128));
//		m_pTarget->getParent()->addChild(node);
//	}
//}
//
//Ref* CCCircleBy::copyWithZone(void* pZone) {
//	CCZone* pNewZone = NULL;
//	CCCircleBy* pCopy = NULL;
//	if(pZone && pZone->m_pCopyObject) 
//	{
//		pCopy = (CCCircleBy*)(pZone->m_pCopyObject);
//	}
//	else
//	{
//		pCopy = new CCCircleBy();
//		pZone = pNewZone = new CCZone(pCopy);
//	}
//
//	ActionInterval::copyWithZone(pZone);
//
//
//	pCopy->initWithDuration(m_fDuration, m_circelCenter, m_radius, m_cw);
//
//	CC_SAFE_DELETE(pNewZone);
//	return pCopy;
//}
//
//void CCCircleBy::startWithTarget(CCNode *pTarget) {
//	ActionInterval::startWithTarget(pTarget);	
//}
//
//ActionInterval* GetCircleActionForNode(CCNode* pNode, float t, E_ClockWise wise) {
//	CCSize size = pNode->getContentSize();
//	float w = size.width/2, h = size.height/2;
//	return  CCCircleBy::create(t, Vec2(w, h), w, wise);
//}
//
///************************************************************************/
///* 椭圆运动                                                             */
///************************************************************************/
//CCEllipseBy* CCEllipseBy::create(float t, const T_EllipseConfig& c)
//{  
//	CCEllipseBy *pAct = new CCEllipseBy();  
//	pAct->initWithDuration(t, c);  
//	pAct->autorelease();  
//
//	return pAct;  
//}  
//
//bool CCEllipseBy::initWithDuration(float t, const T_EllipseConfig& c)  
//{  
//	if (ActionInterval::initWithDuration(t))  
//	{  
//		m_sConfig = c;  
//		m_bDebugDraw = false;
//		m_fDrawHeight = 1.f;
//		return true;  
//	}  
//
//	return false;  
//}  
//
//void CCEllipseBy::update(float time)  
//{  
//	if (m_pTarget)  
//	{  
//		Vec2 s_startPosition = m_sConfig.centerPosition;//中心点坐标  
//		float a = m_sConfig.aLength;  
//		float c = m_sConfig.cLength;  
//		float bx = m_sConfig.centerPosition.x;  
//		float by = m_sConfig.centerPosition.y;  
//		float x = ellipseXat(a, bx, c, time);//调用之前的坐标计算函数来计算出坐标值  
//		float y = (m_sConfig.wise == kColckWise ? -1 : 1) * ellipseYat(a, by, c, time);  
//		Vec2 pos = Vec2Add(s_startPosition, Vec2(x, y));
//		m_pTarget->setPosition(pos);//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标  
//
//		if(m_bDebugDraw) {
//			CCDrawNode *node = CCDrawNode::create();
//			node->drawDot(pos, m_fDrawHeight, ccc4f(128,128,128,128));
//			m_pTarget->getParent()->addChild(node);
//		}
//	}  
//}  
//
//Ref* CCEllipseBy::copyWithZone(CCZone* pZone) {
//	CCZone* pNewZone = NULL;
//	CCEllipseBy* pCopy = NULL;
//	if(pZone && pZone->m_pCopyObject) 
//	{
//		//in case of being called at sub class
//		pCopy = (CCEllipseBy*)(pZone->m_pCopyObject);
//	}
//	else
//	{
//		pCopy = new CCEllipseBy();
//		pZone = pNewZone = new CCZone(pCopy);
//	}
//
//	ActionInterval::copyWithZone(pZone);
//
//
//	pCopy->initWithDuration(m_fDuration, m_sConfig);
//
//	CC_SAFE_DELETE(pNewZone);
//	return pCopy;
//}
//
//void CCEllipseBy::startWithTarget(CCNode *pTarget) {
//	ActionInterval::startWithTarget(pTarget);	
//}
//
//ActionInterval* GetEllipseAction(float t, T_EllipseConfig cf) {
//	return CCEllipseBy::create(t, cf);
//}
//
//ActionInterval* GetEllipseActionForNode(CCNode* pNode, float t, E_ClockWise wise) {
//	CCSize size = pNode->getContentSize();
//	float a = size.width / 2, c = size.height / 2;
//	return GetEllipseAction(t, T_EllipseConfig(Vec2(a, c), a, c, wise));
//}
//
///************************************************************************/
///* 矩形运动                                                             */
///************************************************************************/
//ActionInterval* GetRectangleAction(const T_RectangleConfig& cf, float t, E_ClockWise wise) {
//	float w = cf.width, h = cf.height;
//	float tSpeed = 2 * (w + h) / t;
//	float xSpeed = w / tSpeed, ySpeed = h / tSpeed;
//	MoveBy* a1 = MoveBy::create(ySpeed, Vec2(0, h));
//	MoveBy* a2 = MoveBy::create(xSpeed, Vec2(w, 0));
//	MoveBy* a3 = MoveBy::create(ySpeed, Vec2(0, -h));
//	MoveBy* a4 = MoveBy::create(xSpeed, Vec2(-w, 0));
//	return wise == kColckWise ? CCSequence::create(a1, a2, a3, a4, NULL) : CCSequence::create(a2, a1, a4, a3, NULL);
//}
//
//ActionInterval* GetRectangleActionForNode(CCNode* pNode, float t, E_ClockWise wise) {
//	CCSize size = pNode->getContentSize();
//	float w = size.width, h = size.height;
//	T_RectangleConfig cf = T_RectangleConfig(w, h, Vec2(w/2,h/2));
//	return GetRectangleAction(cf, t, wise);
//}
