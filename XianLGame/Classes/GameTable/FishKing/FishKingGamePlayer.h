#ifndef __FishKing_GamePlayer_H__
#define __FishKing_GamePlayer_H__

#include "cocostudio/CocoStudio.h"
#include "FishKingGameFishManager.h"
#include "FishKingMessageHead.h"
#include "ui/CocosGUI.h"
#include <string>

using namespace ui;
using namespace std;
using namespace YZ;

USING_NS_CC;

namespace FishKing
{
	class GameTableUI;
	class GameBullet;

	class GamePlayer : public YZLayer
	{
	public:
		enum CANNON_TYPE{
			DoubleTube = 0,
			ThreeTube
		};
	public:
		ui::Text*		AtlasLabel_Money;
		ui::Text*		AtlasLabel_CannonNum;
		Layout*         Layout_Table;
		ImageView*		Image_Battery;
		ImageView*		Image_MoneyBox;
		Sprite*			Sprite_Cannon;
		//ImageView*        Sprite_Cannon;
		ImageView*		Image_Card;
		ImageView*		Image_Lock;
		Sprite*			Sprite_Bingo;
        Button*         btn_add;
        Button*         btn_sub;

		GamePlayer();
		virtual ~GamePlayer();

	public:
		static GamePlayer* createGamePlayer(BYTE seatNo, Layout* Panel_Table, GameFishManager* fishManager);
		bool init(BYTE seatNo, Layout* Panel_Table, GameFishManager* fishManager);

	public:
		//���ø��ֲ���
		void setConfig(CMD_S_GameConfig* gConfig);
		//������̨�Ƿ�ɼ�����λ���Ƿ�����ң�
		void setBatteryVisible(bool bVisible);
		//��ʾ��ҽ��
		void setUserMoney(const LLONG money);
		//��ʾ������ڵȼ�
		void setCannonNum(const INT cannonNum);

		void setCannonNumCell(const INT cannonNumCell);
		//������������
		void setCannonType(CANNON_TYPE type);
		//�����ӵ�����
		void setBulletKind(BulletKind kind);
		//�����Ƿ�������
		void setIsEnergyCannon(bool isEnergyCannon);
		//�����Ƿ�������
		void setIsLockFish(bool bLock, INT fishId);
		//����bingoת��
		void setBingo(LLONG money);
        
        void setCannonAddOrSubVisible(int userId,bool visible);

	public:
		//��ȡ��ǰ����Ƿ����
		bool batteryIsVisible();
		//��ȡ��ǰ����λ��
		Vec2 getCannonPoint();
		//��ȡ��ҽ��λ�ã�Ϊ�����������ն���
		Vec2 getMoneyPoint();
		//��ȡ������Χ
		FLOAT getBulletNetRadiusById(BYTE id);
		//�ܷ񿪻�
		bool isFireEnable();
		//����ָʾ��������
		void showLockIndicatorLine(float dt);


	public:
		//��ʾ����
		void gameFire(FLOAT degree, BYTE seatNo, INT bulletId, BulletKind bulletKind, INT bulletMulriple, INT lockFishId, bool isRobot = false);
		//�������ڿ��𶯻�
		void playCannonFireAction();
		void menuEventCallBack(Ref* pSender, Widget::TouchEventType type);

	private:
		CC_SYNTHESIZE(bool,			_isMe, IsMe);
		CC_SYNTHESIZE(bool,			_isRobot, Robot);
		CC_SYNTHESIZE(BYTE,			_seatNo, SeatNo);
		CC_SYNTHESIZE(INT,			_userId, UserID);
		CC_SYNTHESIZE(LLONG,		_currentMoney, CurrentMoney);
		CC_SYNTHESIZE(INT,			_min_bullet_multiple, MinMultiple);
		CC_SYNTHESIZE(INT,			_max_bullet_multiple, MaxMultiple);
		CC_SYNTHESIZE(INT,			_currentFirepower, Firepower);
		CC_SYNTHESIZE(GameTableUI*,	_tableUI, GameTable);
		CC_SYNTHESIZE(INT,			_bulletNum, BulletNum);
		CC_SYNTHESIZE(bool,			_bLock, Lock_Fish);
		CC_SYNTHESIZE(INT,			_lockFishId, LockFishId);
		CC_SYNTHESIZE(BulletKind,	_currentBulletKind, Bullet_Kind);

		INT							_bulletSpeed[BULLET_KIND_COUNT];
		INT							_netRadius[BULLET_KIND_COUNT];
		std::string					bulletName[BULLET_KIND_COUNT];
		bool						_bEnergyCannon;
		GameFishManager*			_fishManager;
		Armature*					_cannonArmature;
		CANNON_TYPE					_cannonType;
		INT                         _currentFireCell;

	public:
		std::vector<GameBullet*>	_bulletList;
		std::vector<Sprite*>		_bubbleList;
	};

}


#endif // __FishKing_GamePlayer_H__
