#include "FishKingGameBullet.h"
#include "FishKingGamePlayer.h"
#include "FishKingGameMathAide.h"
#include "FishKingGameAudio.h"

namespace FishKing
{
	GameBullet* GameBullet::create(const std::string & file, GamePlayer* player, GameFishManager* fishManager, BulletKind bulletKind, INT bulletId, INT bulletMulriple, FLOAT net_radius, FLOAT speed)
	{
		GameBullet* pRet = new GameBullet(player, fishManager, bulletKind, bulletId, bulletMulriple, net_radius, speed);
		if (nullptr != pRet && pRet->initWithSpriteFrameName(file))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}

	GameBullet::GameBullet(GamePlayer* player, GameFishManager* fishManager, BulletKind bulletKind, INT bulletId, INT bulletMulriple, FLOAT net_radius, FLOAT speed):
		_player(player), _fishManager (fishManager), _bullet_kind( bulletKind), 
		_bullet_id(bulletId), _bullet_mulriple(bulletMulriple), _netRadius(net_radius), 
		_speed(speed), onHitFishCallBack (nullptr), _isDoUpdateFUNC (true)
	{
		_lockFishId = INVALID_FISHID;
	}

	GameBullet::~GameBullet()
	{
	}

	void GameBullet::runStartAction(float radians)
	{
		_radians = radians;
		_WinSize = Director::getInstance()->getWinSize();

		scheduleUpdate();
	}

	void GameBullet::collisionDetection()
	{
		auto rect = this->getBoundingBox();
		auto currentSize = Size(rect.size.width / 2, rect.size.height / 2);
		rect.size = currentSize;

		for (auto ite = _fishManager->_fishList.begin(); ite != _fishManager->_fishList.end(); ite++)
		{
			auto fish = (Fish*)*ite;
			Fish* touchFish = nullptr;
			//������������㣬��������id������id��ͬ�ż����ײ
			if (_lockFishId != INVALID_FISHID)
			{
				if (fish->getFishID() == _lockFishId)
				{
					touchFish = fish;
				}
			}
			else
			{
				touchFish = fish;
			}

			if (nullptr == touchFish) continue;

			Rect rt = touchFish->getFishRect();
			if (touchFish->getCanTouch() && touchFish->isVisible() && rt.intersectsRect(rect)) //�����ӵ�
			{
				this->unscheduleUpdate();
				bulletExplosion();
				int anskind = (int)_bullet_kind;
				if (nullptr != onHitFishCallBack)
				{
					//����һ������ �ӵ����� ������ײ
					onHitFishCallBack(touchFish->getFishID(), _bullet_id, _bullet_kind, _bullet_mulriple);
				}
				break;
			}
		}
	}

	void GameBullet::bulletExplosion()
	{
		this->initWithSpriteFrameName("net21_01.png");
		FishKingGameAudio::playNetEffect();

		char str[24];

		auto cache = SpriteFrameCache::getInstance();
		Animation *animation = Animation::create();
		animation->setDelayPerUnit(0.05f);
		animation->setLoops(1);

		for (BYTE i = 1; i <= 12; i++)
		{
			std::string name("net31_");
			if (_bullet_kind == BULLET_KIND_1_NORMAL || _bullet_kind == BULLET_KIND_2_NORMAL ||
				_bullet_kind == BULLET_KIND_1_ION || _bullet_kind == BULLET_KIND_2_ION)
			{
				name = "net21_";
			}
			sprintf(str, "%02d.png", i);
			name.append(str);
			animation->addSpriteFrame(cache->getSpriteFrameByName(name));
		}
		this->setScale(0.7f);
		auto animate = Animate::create(animation);
		this->runAction(Sequence::create(animate, CallFunc::create([this](){

			bool canErase = false;
			auto ite = _player->_bulletList.begin();
			for (; ite != _player->_bulletList.end(); ite++)
			{
				if (*ite == this)
				{
					canErase = true;
					break;
				}
			}

			if (canErase)
			{
				_player->_bulletList.erase(ite);
			}			
			removeFromParent();
		}), nullptr));
	}

	void GameBullet::update(float dt)
	{
		if (!_isDoUpdateFUNC && _lockFishId == INVALID_FISHID)
		{
			_isDoUpdateFUNC = true;
			return;
		}
		_isDoUpdateFUNC = false;

		//�������߽���ײ
		collisionDetection();
		auto currentPos = this->getPosition();
		//�������Ļ���ұ߽���ײ
		if (currentPos.x <= 0 || currentPos.x >= _WinSize.width)
		{
			setRotation(-getRotation());
		}
		//�������Ļ���±߽���ײ
		if (currentPos.y <= 0 || currentPos.y >= _WinSize.height)
		{
			setRotation(180 - getRotation());
		}

		if (_lockFishId == INVALID_FISHID)
		{
			//�˶�����
			_radians = CC_DEGREES_TO_RADIANS(90 - getRotation());			
		}
		else
		{
			//����״̬�ӵ����ٰ��ճ�ǹ��ʱ��·�߷��У����Ǹ������������λ�ø����ƶ�
			auto fish = dynamic_cast<Fish*>(_fishManager->getFishById(_lockFishId));
			if (nullptr != fish)
			{
				Vec2 fishPos = fish->getPosition();
				//Ŀ������ӵ�ֱ�ӵľ���
				float range = sqrt(pow(abs(fishPos.x - currentPos.x), 2) + pow(abs(fishPos.y - currentPos.y), 2));
				//Ŀ������ӵ��Ļ���
				_radians = atan2(fishPos.y - currentPos.y, fishPos.x - currentPos.x);
			}
		}

		//������֪�Ļ��Ⱥ�λ���ٶȻ����һ������
		currentPos.x = getPositionX() + cosf(_radians) * _speed;
		currentPos.y = getPositionY() + sinf(_radians) * _speed;

		setPosition(currentPos);
	}
}