#include "FishKingGameFishObject.h"
#include "FishKingGameMathAide.h"
#include "FontConfig.h" 

namespace FishKing
{
	static const char*	FISH_ANIMI			=	"fishAnimation";
	static const char*	DASANYUAN			=	"fishKing/fishAnimation/dasanyuan.csb";
	static const char*	DASIXI				=	"fishKing/fishAnimation/dasixi.csb";
	static const char*	ZXDASANYUAN			=	"fishKing/fishAnimation/ZXdasanyuan.csb";
	static const char*	ZXDASIXI			=	"fishKing/fishAnimation/ZXdasixi.csb";
	static const char*	PLATEKING			=	"fishKing/fishAnimation/KingTray.png";

	Fish::Fish(int fishId, FishKind fishKind, FishKind fishKind_ex[5])
		: _fishID (fishId), _fishKind (fishKind), onMoveOutCallBack (nullptr)
		, _isTouch(true), _isPause(false), _fishSize (Size::ZERO), _isLock (false)
		, _fishMoveAction (nullptr), _fishSpeed (0), _fishRect(0, 0, 0, 0)
		, _oldPosition (Vec2(0, 0)), _desPosition (Vec2(0, 0)), _isSwitch (false)
		, _gameBG (nullptr), _isUseFishTrace (true),_stop_index(0), _stop_count(0), _current_stop_count(0)
		, onUnLockCallBack (nullptr)
	{	
		_winSize = Director::getInstance()->getWinSize();
		memcpy(_fishKind_ex, fishKind_ex, sizeof(fishKind_ex));
	}

	Fish::~Fish()
	{
		//release();
	}

	Fish* Fish::create(int fishId, FishKind fishKind, FishKind fishKind_ex[5])
	{
		Fish* pRet = new Fish(fishId, fishKind, fishKind_ex);
		if (pRet && pRet->init())
		{ 
			pRet->autorelease();
			//�˴���Ҫretainһ�Σ���Ϊ�ظ����õ�ʱ���а����Ƴ����ڵ㣬�ᵼ���㱻�ͷţ���������release
			pRet->retain();
			return pRet;
		} 
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}

	bool Fish::init()
	{
		if (!YZSprite::init()) return false;
		//�����ӽڵ���Ÿ��ڵ��͸���ȱ仯����������ûᵼ���㲻������
		this->setCascadeOpacityEnabled(true);
		//����֡����ͼƬ��Ϣ
		onRender();

		switch (_fishKind)
		{
		case  FISH_KIND_27: //���Ǵ���Ԫ
			createDaSanYuanFish(_fishKind_ex[0]);
			break;
		case  FISH_KIND_28: //ֱ�ߴ���Ԫ
			createZXDaSanYuanFish(_fishKind_ex[0]);
			break;
		case  FISH_KIND_29: //�ĽǴ���ϲ
			createDaSixiFish(_fishKind_ex[0]);
			break;
		case  FISH_KIND_30: //ֱ�ߴ���ϲ
			createZXDaSiXiFish(_fishKind_ex[0]);
			break;
		case  FISH_KIND_31: //��ɫ����
			createRedKingFish(_fishKind_ex[0]);
			break;
		case  FISH_KIND_32: //����������
			createPlatekingFish(_fishKind_ex[0]);
			break;
		default:			//��ͨ��
			createNormalFish(_fishKind);
			break;
		}
		return true;
	}

	Animation* Fish::addFishData(FishSpirteInfo fish, BYTE kind)
	{
		auto spCache = SpriteFrameCache::getInstance();
		auto aniCache = AnimationCache::getInstance();
		char str[32];

		//�������ζ�����
		Animation *bMove = Animation::create();
		bMove->setDelayPerUnit(fish.time);
		bMove->setLoops(-1);
		for (int i=1; i <= fish.count; i++)
		{
			std::string name(fish.name);
			sprintf(str, "walking1_%02d.png",i);
			name.append(str);
			bMove->addSpriteFrame(spCache->getSpriteFrameByName(name));
		}
		sprintf(str, "fish_%d", kind);
		aniCache->addAnimation(bMove, str);
		return bMove;
	}

	//������ͨ�㣨����0-25��
	void Fish::createNormalFish(BYTE fishKind)
	{
		char name[12];
		sprintf(name, "fish_%d", _fishKind);
		auto animation = dynamic_cast<Animation*>(AnimationCache::getInstance()->getAnimation(name));

		if (nullptr == animation)
		{
			animation = addFishData(_fishName[fishKind], fishKind);
		}
		
		auto animate = Animate::create(animation);
		auto fish = Sprite::create();
		fish->runAction(animate);
		this->addChild(fish, 2);

		//Ӱ��
		auto fish_Shadow = Sprite::create();
		fish_Shadow->runAction(animate->clone());
		fish_Shadow->setPosition(Vec2(fish->getPositionX() + 15, fish->getPositionY() + 15));
		fish_Shadow->setColor(Color3B(0, 0, 0));
		fish_Shadow->setOpacity(60);	
		this->addChild(fish_Shadow);
	}

	//�������Ǵ���Ԫ��
	void Fish::createDaSanYuanFish(BYTE fishKind)
	{
		auto node=dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("fishKing/GameTableUi/dasanyuan.json"));
		this->addChild(node);
		char str[12];
		for (int i = 0; i < 4; i++)
		{
			Armature*armature = Armature::create("bigFishAnimation");
			sprintf(str, "Fish%d", i);
			auto fishPos = static_cast<ImageView*>(ui::Helper::seekWidgetByName(node,str));
			fishPos->setVisible(false);
            armature->setPosition(fishPos->getPosition());
			if (i>0)
			{
				armature->getAnimation()->playByIndex(1);
			}
			else
			{
				armature->getAnimation()->playByIndex(0);
			}
            
            node->addChild(armature);
		}
		for (int i = 0; i < 4; i++)
		{
			sprintf(str, "Fish%d", i);
			auto fishPos = static_cast<ImageView*>(ui::Helper::seekWidgetByName(node,str));
			sprintf(str, "fish_%d", fishKind);

			auto animation = dynamic_cast<Animation*>(AnimationCache::getInstance()->getAnimation(str));
			if (nullptr == animation)
			{
				animation = addFishData(_fishName[fishKind], fishKind);
			}

			auto animate = Animate::create(animation);
			auto fish = Sprite::create();
			fish->runAction(animate);
			fish->setPosition(fishPos->getPosition());
			this->addChild(fish, 2);
		}
	}

	//����ֱ�ߴ���Ԫ��
	void Fish::createZXDaSanYuanFish(BYTE fishKind)
	{
		auto node=dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("fishKing/GameTableUi/ZXdasanyuan.json"));
		this->addChild(node);
		char str[12];
		Armature*armature = Armature::create("bigFishAnimation");
		auto fPos = static_cast<ImageView*>(ui::Helper::seekWidgetByName(node,"Armature"));
		armature->setPosition(fPos->getPosition());
		fPos->setVisible(false);
		armature->getAnimation()->playByIndex(3);
		node->addChild(armature);
                   
		for (int i = 0; i < 3; i++)
		{
			sprintf(str, "Fish%d", i);
			auto fishPos = static_cast<ImageView*>(ui::Helper::seekWidgetByName(node,str));
			sprintf(str, "fish_%d", fishKind);
			
			auto animation = dynamic_cast<Animation*>(AnimationCache::getInstance()->getAnimation(str));
			if (nullptr == animation)
			{
				animation = addFishData(_fishName[fishKind], fishKind);
			}

			auto animate = Animate::create(animation);
			auto fish = Sprite::create();
			fish->runAction(animate);
			fish->setPosition(fishPos->getPosition());
			this->addChild(fish, 2);
		}
	}

	//�����ĽǴ���ϲ��
	void Fish::createDaSixiFish(BYTE fishKind)
	{
		auto node=dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("fishKing/GameTableUi/dasixi.json"));
		this->addChild(node); 
		char str[12];
		for (int i = 0; i < 5; i++)
		{
			Armature*armature = Armature::create("bigFishAnimation");
			sprintf(str, "Fish%d", i);
			auto fishPos = static_cast<ImageView*>(ui::Helper::seekWidgetByName(node,str));
			fishPos->setVisible(false);
            armature->setPosition(fishPos->getPosition());
			if (i>0)
			{
				armature->getAnimation()->playByIndex(1);
			}
			else
			{
				armature->getAnimation()->playByIndex(0);
			}
            
            node->addChild(armature);
		}
		for (int i = 0; i < 5; i++)
		{
			sprintf(str, "Fish%d", i);
			auto fishPos = static_cast<ImageView*>(ui::Helper::seekWidgetByName(node,str));
			sprintf(str, "fish_%d", fishKind);
			
			auto animation = dynamic_cast<Animation*>(AnimationCache::getInstance()->getAnimation(str));
			if (nullptr == animation)
			{
				animation = addFishData(_fishName[fishKind], fishKind);
			}

			auto animate = Animate::create(animation);
			auto fish = Sprite::create();
			fish->runAction(animate);
			fish->setPosition(fishPos->getPosition());
			this->addChild(fish, 2);
		}
	}

	//����ֱ�ߴ���ϲ��
	void Fish::createZXDaSiXiFish(BYTE fishKind)
	{
		auto node=dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("fishKing/GameTableUi/ZXdasixi.json"));
		this->addChild(node);
		char str[12];
		Armature*armature = Armature::create("bigFishAnimation");
		auto fPos = static_cast<ImageView*>(ui::Helper::seekWidgetByName(node,"Armature"));
		armature->setPosition(fPos->getPosition());
		fPos->setVisible(false);
		armature->getAnimation()->playByIndex(2);
		node->addChild(armature);
		for (BYTE i = 0; i < 4; i++)
		{
			sprintf(str, "Fish%d", i);
			auto fishPos = static_cast<Node*>(node->getChildByName(str));
			sprintf(str, "fish_%d", fishKind);
			
			auto animation = dynamic_cast<Animation*>(AnimationCache::getInstance()->getAnimation(str));
			if (nullptr == animation)
			{
				animation = addFishData(_fishName[fishKind], fishKind);
			}

			auto animate = Animate::create(animation);
			auto fish = Sprite::create();
			fish->runAction(animate);
			fish->setPosition(fishPos->getPosition());
			this->addChild(fish, 2);
		}
	}

	//������ɫ����
	void Fish::createRedKingFish(BYTE fishKind)
	{
		char name[12];
		sprintf(name, "fish_%d", fishKind);
		
		auto animation = dynamic_cast<Animation*>(AnimationCache::getInstance()->getAnimation(name));
		if (nullptr == animation)
		{
			animation = addFishData(_fishName[fishKind], fishKind);
		}

		auto animate = Animate::create(animation);

		auto fish = Sprite::create();
		fish->runAction(animate);
		fish->setColor(colorRed);
		this->addChild(fish);

		auto fish_Shadow = Sprite::create();
		fish_Shadow->runAction(animate->clone());
		fish_Shadow->setPosition(Vec2(fish->getPositionX() + 15, fish->getPositionY() + 15));
		fish_Shadow->setColor(Color3B(0, 0, 0));
		fish_Shadow->setOpacity(60);	
		this->addChild(fish_Shadow, 1);
	}

	//���������̵�����
	void Fish::createPlatekingFish(BYTE fishKind)
	{
		auto fish = Sprite::create(PLATEKING);
		fish->runAction(RepeatForever::create(RotateBy::create(0.5f, 90.0f)));
		this->addChild(fish, -1);

		char name[12];
		sprintf(name, "fish_%d", fishKind);
		
		auto animation = dynamic_cast<Animation*>(AnimationCache::getInstance()->getAnimation(name));
		if (nullptr == animation)
		{
			animation = addFishData(_fishName[fishKind], fishKind);
		}

		auto animate = Animate::create(animation);
		auto smallFish = Sprite::create();
		smallFish->runAction(animate);
		this->addChild(smallFish);
	}

	/////////////////////////////////////////////////////////
	//���������������
	void Fish::playFishDieAction()
	{
		//�����㲻�ܱ���ײ����ֹ�������������ڽ���Ȼ����赲�ӵ�
		this->setCanTouch(false);
		//�Ƴ�Update����ֹͣǰ��
		this->unscheduleUpdate();

		//������㱻��������������ʱ��Ҫ����
		if (_isLock)
		{
			if (nullptr != onUnLockCallBack)
			{
				_isLock = false;
				onUnLockCallBack(_fishID);
			}
		}

		switch (_fishKind)
		{
		case  FISH_KIND_27: //���Ǵ���Ԫ
		case  FISH_KIND_28: //ֱ�ߴ���Ԫ
		case  FISH_KIND_29: //�ĽǴ���ϲ
		case  FISH_KIND_30: //ֱ�ߴ���ϲ
		case  FISH_KIND_32: //����������
			{
				this->runAction(Sequence::create(DelayTime::create(1.0f), 
					RemoveSelf::create(true), nullptr));
			}
			break;
		case  FISH_KIND_31: //��ɫ����
			{
				this->runAction(Sequence::create(Shake::create(1.0f, 10, 10),
					RemoveSelf::create(true), nullptr));
			}
			break;
		default:			//��ͨ��
			{
				this->runAction(Sequence::create(Shake::create(1.0f, 10, 10),
					CallFunc::create([this](){
						setHide();
				}), nullptr));
			}
			break;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////
	void Fish::setPosition(const Vec2& pos)
	{
		Sprite::setPosition(pos);

		float tanX = pos.x - _oldPosition.x;
		float tanY = pos.y - _oldPosition.y;
		float radians = -1 * atan2(tanY, tanX);
		float degree = CC_RADIANS_TO_DEGREES(radians);

		this->setRotation(degree);
		_oldPosition = pos;
	}

	void Fish::setHide()
	{
		if (nullptr != _fishMoveAction)
		{
			_fishMoveAction->release();
			_fishMoveAction = nullptr;
		}
		refreshParams();
		if (nullptr != onMoveOutCallBack)
		{
			onMoveOutCallBack(_fishID);
		}
	}

	void Fish::refreshParams()
	{
		unscheduleUpdate();
		setVisible(false);
		_isTouch = false;
		_isSwitch = false;
		_isLock = false;
		_gameBG = nullptr;
		_FishTraceIndex = 0;
		_isUseFishTrace = true;
		_fishTraceList.clear();
		_stop_count = 0;
		_stop_index = -1;
		_current_stop_count = 0;
		memset(_fishKind_ex, 0, sizeof(_fishKind_ex));
	}

	void Fish::setFishTraceList(std::vector<FPointAngle> fishTraceList, bool isUseFishTtrace)
	{
		_fishTraceList.clear();
		_fishTraceList	= fishTraceList;
		_isUseFishTrace	= isUseFishTtrace;
	}

	void Fish::playFishActionByTraceList()
	{
		if (_fishTraceList.empty()) return;

		_oldPosition = Vec2(_fishTraceList[0].x, _winSize.height - _fishTraceList[0].y);
		this->setPosition(Vec2(_fishTraceList[1].x, _winSize.height - _fishTraceList[1].y));
		_FishTraceIndex = 2;

		scheduleUpdate();
	}

	//�㰴��·���ζ�������ֱ������ʱֻ�е�һ�͵ڶ��������в�������������������������
	FiniteTimeAction* Fish::getActionInThreePoint(Vec2 first, Vec2 second, Vec2 third, TraceType actionType)
	{
		FiniteTimeAction* action = nullptr;
		switch (actionType)
		{
		case TRACE_LINEAR:		//����ֱ��
			{
				//������֮���ֱ�߾��� �� |Xa-Xb|^ + |Ya-Yb|^ = �����ƽ�� ��abs:����ֵ��pow:ƽ����sqrt:������
				auto range = sqrt(pow(abs(first.x - second.x), 2) + pow(abs(first.y - second.y), 2));
				auto time = range / (30 * _fishSpeed);

				action = MoveTo::create(time, second);
			}
			break;
		case TRACE_BEZIER:		//����������
			{	
				float range1 = sqrt(pow(abs(first.x - second.x), 2) + pow(abs(first.y - second.y), 2));
				float range2 = sqrt(pow(abs(second.x - third.x), 2) + pow(abs(second.y - third.y), 2));
				float range = range1 + range2;
				auto time = range / (30 * _fishSpeed);

				ccBezierConfig bezier;
				bezier.controlPoint_1 = first;
				bezier.controlPoint_2 = second;
				bezier.endPosition	  = third;
				action = BezierTo::create(time, bezier);
			}
			break;
		default:
			break;
		}
		return action;
	}

	void Fish::playFishAction(std::vector<Vec2>* fishTrace, TraceType traceType, FLOAT speed)
	{
		_fishSpeed = speed;
		this->setCanTouch(true);
		this->setVisible(true);
		this->setPauseAction(false);
		this->setSwitchScene(false);

		if (!_isUseFishTrace)
		{
			//�㳱����
			playFishActionByTraceList();
			return;
		}

		if (nullptr == fishTrace) return;

		_oldPosition = (*fishTrace)[0];
		if (traceType == TRACE_LINEAR)
		{
			_desPosition = (*fishTrace)[1];
		}
		else
		{
			_desPosition = (*fishTrace)[2];
		}

		float go_degree = MathAide::CalcAngle1(_desPosition.x, _desPosition.y, _oldPosition.x, _oldPosition.y);
		float goX = cos(go_degree);
		float goY = sin(go_degree);
		
		this->setPosition(Vec2((*fishTrace)[0].x + goX, (*fishTrace)[0].y + goY));

		if (nullptr != _fishMoveAction)
		{
			_fishMoveAction->release();
			_fishMoveAction = nullptr;
		}

		if (traceType == TRACE_LINEAR)
		{
			_fishMoveAction = getActionInThreePoint((*fishTrace)[0], (*fishTrace)[1],  Vec2::ZERO, traceType);
		}
		else
		{
			_fishMoveAction = getActionInThreePoint((*fishTrace)[0], (*fishTrace)[1],  (*fishTrace)[2], traceType);
		}
		
		_fishMoveAction->retain();
		_fishMoveAction->startWithTarget(this);

		scheduleUpdate();
	}

	void Fish::setFishStop(std::vector<FPointAngle>::size_type stop_index, std::vector<FPointAngle>::size_type stop_count) 
	{
		_stop_index = stop_index;
		_stop_count = stop_count;
		_current_stop_count = 0;
	}

	void Fish::update(float dt)
	{
		//�����л���ʱ���������±���ͼ��������
		if (_isSwitch)
		{
			if (this->getPositionX() < 0 || this->getPositionX() > _winSize.width ||
				this->getPositionY() < 0 || this->getPositionY() > _winSize.height)
			{
				if (_isLock && nullptr != onUnLockCallBack)
				{
					_isLock = false;
					onUnLockCallBack(_fishID);
				}
				setHide();
				return;
			}
			auto rect = _gameBG->getBoundingBox();
			if (rect.intersectsRect(this->getFishRect()))
			{
				if (_isLock && nullptr != onUnLockCallBack)
				{
					_isLock = false;
					onUnLockCallBack(_fishID);
				}
				setHide();
				return;
			}
		}

		//������ж������룬��ֹͣ�ζ�
		if (_isPause)
		{
			return;
		}

		auto winSize = Director::getInstance()->getWinSize();
		//���������Ͼ��ε�λ��(�������ӵ�������ײ���)
		setFishRect(Rect(this->getPositionX() - _fishSize.width / 2, this->getPositionY() - _fishSize.height / 2,
			_fishSize.width, _fishSize.height));

		//������㱻���������γ���Ļʱ��Ҫ����
		if (_isLock)
		{
			if (this->getPositionX() < 0 || this->getPositionX() > winSize.width 
				|| this->getPositionY() < 0 || this->getPositionY() > winSize.height)
			{
				if (nullptr != onUnLockCallBack)
				{
					_isLock = false;
					onUnLockCallBack(_fishID);
				}
			}
		}

		if (nullptr != _fishMoveAction)
		{
			if (_fishMoveAction->isDone())
			{
				setHide();
				return;
			}
			_fishMoveAction->step(dt);
			return;
		}

		if (!_isDoUpdateFUNC)
		{
			_isDoUpdateFUNC = true;
			return;
		}
		_isDoUpdateFUNC = false;

		//�㳱2��������С����һ��ʱ������Ҫ��ֹͣ
		if (_stop_count > 0 && _FishTraceIndex == _stop_index && _current_stop_count < _stop_count) 
		{
			++_current_stop_count;
			if (_current_stop_count >= _stop_count) setFishStop(0, 0);
			return;
		}
		else if (_FishTraceIndex >= _fishTraceList.size())
		{
			setHide();
			return;
		}
		this->setPosition(Vec2(_fishTraceList[_FishTraceIndex].x, _winSize.height - _fishTraceList[_FishTraceIndex].y));
		_FishTraceIndex++;
	}

	FishKind Fish::getFishKindEx()
	{
		return _fishKind_ex[0];
	}

	void Fish::onRender()
	{
		_fishName[0].name = "fish_woniuyu_";					//��ţ��
		_fishName[0].count = 16;
		_fishName[0].time = 0.11f;

		_fishName[1].name = "fish_lvcaoyu_";					//�̲���
		_fishName[1].count = 16;
		_fishName[1].time = 0.11f;

		_fishName[2].name = "fish_huangcaoyu_";					//�Ʋ���
		_fishName[2].count = 23;
		_fishName[2].time = 0.1f;

		_fishName[3].name = "fish_dayanyu_";					//������
		_fishName[3].count = 14;
		_fishName[3].time = 0.12f;

		_fishName[4].name = "fish_huangbianyu_";				//������
		_fishName[4].count = 16;
		_fishName[4].time = 0.12f;

		_fishName[5].name = "fish_xiaochouyu_";					//С����
		_fishName[5].count = 17;
		_fishName[5].time = 0.12f;

		_fishName[6].name = "fish_xiaociyu_";					//С����
		_fishName[6].count = 36;
		_fishName[6].time = 0.1f;

		_fishName[7].name = "fish_lanyu_";						//����
		_fishName[7].count = 17;
		_fishName[7].time = 0.08f;

		_fishName[8].name = "fish_denglongyu_";					//�������
		_fishName[8].count = 23;
		_fishName[8].time = 0.08f;

		_fishName[9].name = "fish_lvDenglongyu_";				//�̵�����
		_fishName[9].count = 9;
		_fishName[9].time = 0.12f;

		_fishName[10].name = "fish_haigui_";					//����
		_fishName[10].count = 24;
		_fishName[10].time = 0.1f;

		_fishName[11].name = "fish_huabanyu_";					//������
		_fishName[11].count = 24;
		_fishName[11].time = 0.12f;

		_fishName[12].name = "fish_hudieyu_";					//������
		_fishName[12].count = 24;
		_fishName[12].time = 0.12f;

		_fishName[13].name = "fish_kongqueyu_";					//��ȸ��
		_fishName[13].count = 24;
		_fishName[13].time = 0.12f;

		_fishName[14].name = "fish_jianyu_";					//����
		_fishName[14].count = 23;
		_fishName[14].time = 0.12f;

		_fishName[15].name = "fish_bianfuyu_";					//������
		_fishName[15].count = 24;
		_fishName[15].time = 0.1f;

		_fishName[16].name = "fish_yinsha_";					//������
		_fishName[16].count = 24;
		_fishName[16].time = 0.1f;

		_fishName[17].name = "fish_jinsha_";					//������
		_fishName[17].count = 24;
		_fishName[17].time = 0.1f;

		_fishName[18].name = "fish_jingubang_";					//�𹿰�
		_fishName[18].count = 1;
		_fishName[18].time = 0.3f;

		_fishName[19].name = "fish_dashayu_";					//������
		_fishName[19].count = 9;
		_fishName[19].time = 0.15f;

		_fishName[20].name = "fish_yinlong_";					//����
		_fishName[20].count = 16;
		_fishName[20].time = 0.08f;

		_fishName[21].name = "fish_jinlong_";					//����
		_fishName[21].count = 16;
		_fishName[21].time = 0.08f;

		_fishName[22].name = "fish_haizao_";					//����
		_fishName[22].count = 4;
		_fishName[22].time = 0.3f;

		_fishName[23].name = "fish_bomb_";						//ȫ��ը��
		_fishName[23].count = 3;
		_fishName[23].time = 0.3f;

		_fishName[24].name = "fish_jinjinchan_";				//��ɫ���
		_fishName[24].count = 3;
		_fishName[24].time = 0.3f;

		_fishName[25].name = "fish_shuangshayu_";				//˫ͷ��
		_fishName[25].count = 9;
		_fishName[25].time = 0.2f;
	}
}