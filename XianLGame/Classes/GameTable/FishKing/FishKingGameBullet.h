#ifndef __YZ_FishKing_GameBullet_H__
#define __YZ_FishKing_GameBullet_H__

#include "YZNetExport.h"
#include "YZUIExport.h"
#include "cocos2d.h"
#include "FishKingMessageHead.h"
#include "FishKingGameFishManager.h"
USING_NS_CC;

namespace FishKing
{
	class GamePlayer;

	class GameBullet: public YZ::YZSprite
	{
	public:
		typedef std::function<void (INT fishId , INT bulletId , BulletKind bulletKind , INT  bulletMuriple)> HitFishCallBack;
		HitFishCallBack  onHitFishCallBack;
	public:
		~GameBullet();
		static GameBullet* create(const std::string & file, GamePlayer* player, GameFishManager* fishManager, BulletKind bulletKind, INT bulletId, INT bulletMulriple, FLOAT net_radius, FLOAT speed);
		void runStartAction(float radians);
		//�ӵ��˶�
		virtual void update(float dt);
		//�ӵ�������ײ���
		virtual void collisionDetection();
		//�ӵ���ը����
		void bulletExplosion();	

	protected:
		GameBullet(GamePlayer* cannonUI, GameFishManager* fishManager, BulletKind bulletKind, INT bulletId, INT bulletMulriple, FLOAT net_radius, FLOAT speed);
	protected:
		CC_SYNTHESIZE(FLOAT,		_speed, Bullet_speed);				//�ӵ��ٶ�
		CC_SYNTHESIZE(FLOAT,		_radians, Bullet_Radians);			//�ӵ�����
		CC_SYNTHESIZE(FLOAT,		_netRadius, Net_Radians);			//��������
		CC_SYNTHESIZE(INT,			_bullet_id, Bullet_id);				//�ӵ�ID
		CC_SYNTHESIZE(INT,			_bullet_mulriple, Bullet_mulriple);	//�ӵ�����
		CC_SYNTHESIZE(BulletKind,	_bullet_kind, Bullet_Kind);			//�ӵ�����
		CC_SYNTHESIZE(INT,			_lockFishId, LockFish_id);			//���������id

		Size						_WinSize;
		bool						_isDoUpdateFUNC;				//��Ϊpc��ÿ��30֡������60֡�����Կ���2֡����һ�Σ�Ϊ�˸�pcͬ��
	protected:
		GameFishManager*		_fishManager;
		GamePlayer*				_player;

	};
}

#endif // __FishKing_GameBullet_H__
