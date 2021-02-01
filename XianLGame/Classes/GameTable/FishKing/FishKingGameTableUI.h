#ifndef __YZ_FishKing_GameTableUI_H__
#define __YZ_FishKing_GameTableUI_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "YZNetExport.h"
#include "FishKingGameTableLogic.h"
#include "FishKingGameTableUICallback.h"
#include "FishKingMessageHead.h"
#include "FishKingGamePlayer.h"
#include <vector>

USING_NS_CC;

using namespace cocos2d;
using namespace cocostudio;
using namespace std;
using namespace ui;

namespace FishKing
{
	struct catchResultInfo
	{
		LLONG userGoldMoney;							//��ҵ�ǰ�����õĽ��
		INT numberOfKindFIsh[FISH_KIND_COUNT];			//��ҵ�ǰÿ���㲶��������
	};

	static const FLOAT		PI					=	3.14159f;
	static const INT		BACKGROUND_ZORDER	=	0;
	static const INT		FISH_ZORDER			=	10;
	static const INT		NOTICE_ZORDER		=	50;
	static const INT  		BULLET_ZORDER		=	15;
	static const INT		WATER_ZORDER		=	9;
	static const INT		PLAYER_ZORDER		=	210;
	static const INT		MAX_ZORDER			=	280;

	class GameFishManager;
	class SceneFishTrace;

	class GameTableUI : public YZ::YZGameUIBase, public GameTableUICallback
	{

	private:
		BYTE						_deskIndex;
		bool						_bAutoCreate;
		bool						_isAllowFire;
		bool						_isAutoFire;
		bool						_isReadyLock;
		INT							_iBullet_id;
		Vec2						_touchPoint;
		ImageView*					_currentBg;
		ui::Layout*						_tableUi;
		CC_SYNTHESIZE(INT,			_lockFishId, LockRishId);

	public:
		Vec2						_fpCircleFishCenter[2];	//������Ⱥ���ĵ�

	private:
		GameFishManager*			_fishManager;
		GameTableLogic*				_tableLogic;
		SceneFishTrace*				_fishTrace;
		//GameNotice*					_notic;
		Label*                      _text;
		Sprite*						_NoticeBG;
		GamePlayer*					_players[PLAY_COUNT];
		catchResultInfo*			_resultInfo;			//��Ҳ�������Ϣ
		CMD_S_SwitchScene			_switchScene;

	public:
		GameTableUI();
		virtual ~GameTableUI();

		virtual void onEnter();
		virtual void onExit();
		virtual void onEnterTransitionDidFinish() override;

		static GameTableUI* create(BYTE bDeskIndex, bool autoCreate);
		bool init(BYTE bDeskIndex, bool bAutoCreate);
		bool initGameUI();
		void initToolBarData();
		void asyncBuildData();
		void delayedLoadAction(float dt);

	public:
		virtual void addUser(BYTE seatNo, bool bMe) override;									//������
		virtual void removeUser(BYTE seatNo, bool bMe) override;								//�Ƴ����
		virtual void dealSetUserMoney(BYTE seatNo, LLONG value) override;						//������ʾ��ҽ��
		virtual void dealSetUserCannonNum(BYTE seatNo, INT value ,INT valueCell) override;						//��������ڻ�����
		virtual void dealSetGameConfig(CMD_S_GameConfig* gConfig) override;						//�����ӵ��ٶȵȲ���
		virtual void dealSetSceneStyle(SceneStyle Scene) override;								//��Ϸ����id
		virtual void dealGameFire(CMD_S_UserFire* pFire, bool bMeFire) override;				//�յ�����˿�����Ϣ
		virtual void dealCatchFish(CMD_S_CatchFish*	pFish) override;							//��������Ϣ
		virtual void dealAddFishInfo(void* object, WORD objectSize) override;					//��ӵ�����Ϣ�����ȿ���Ϊ�����㣩
		virtual void dealAddGroupFishInfo(CMD_S_GroupFishTrace* pFish) override;				//�����Ⱥ��Ϣ
		virtual void dealCatchSweepFish(CMD_S_CatchSweepFish* pSweep) override;					//ץ���������㣨������ը����֪ͨ
		virtual void dealCatchSweepFishResult(CMD_S_CatchSweepFishResult* pResult) override;	//ץ��������������Ľ��������������ͬ��������
		virtual void dealCatchSweepFishResultEx(CMD_S_CatchSweepFishResultEx* pResult) override;//ץ������ϵͳ�㲥֪ͨ
		virtual void dealSwitchScene(CMD_S_SwitchScene* pScene) override;						//�л�����
		virtual void dealLockFishTimeOut() override;											//���������붨ס����ָ��˶�
		virtual void dealBulletTimeOut(BYTE seatNo) override;									//ȡ��������

		////////////////////////////////////////////////////////////////////
		//����
		////////////////////////////////////////////////////////////////////
		virtual void dealSetAdminConfig(bool bAdmin)  override;									//�Ƿ񳬶��û�
		virtual void dealStockOperateResult(CMD_S_StockOperateResult* pStock)  override;		//���ز������
		virtual void dealUpdateOnlinePlayerList(std::vector<OnLineUserInfo> users) override;	//������������б�
		virtual void dealUpdateContorlList(S_C_UPDATE_CONTROL_INFO* info) override;				//���¿����б���Ϣ
		virtual void dealUpdateSpecialList(S_C_UPDATE_SPECIAL_INFO* pSpecial) override;			//��������������б���Ϣ
		virtual void dealSetSwitchInfo(S_C_SWITCH_INFO* pSwitch) override;						//���ƿ���
		virtual void dealUpdateFishName(S_C_FISH_NAME* pName) override;							//���¿����������



		////////////////////////////////////////////////////////////////////

	public:
		virtual void dealGameStart() override;
		virtual void dealLeaveDesk() override;
		virtual void onDisconnect();
		void returnPlatform();

	public:
		//�����ӵ���������Ϣ
		void sendHitFish(BYTE bSeatNo, INT fishId , INT bulletId , BulletKind bulletKind , INT  bulletMuriple);
		//����ץ���������Ч
		void playAwardFishAnimation(BYTE bSeatNo, LLONG money, LLONG userMoney, Fish* fish);
		//�л���������
		void switchScene();

	public:
		//�����˳�
		void gameSettlementAndExit();

	private:
		//����¼�
		virtual bool onTouchBegan(Touch *touch, Event *unused_event);
		virtual void onTouchMoved(Touch *touch, Event *unused_event);
		virtual void onTouchEnded(Touch *touch, Event *unused_event);
		//�Զ����
		void setAtuoFire(float dt);
		//�����������
		void continuousFire(float dt);
		//������Ļ���
		void openFireByTouch(const Vec2& touchPoint);
		//��ʱ�������Զ��˳�
		void gameOutTime(bool bShow);

	private:
		//��ʱ��
		void timing(Node* node, int dt, std::function<void()> callFunc);
		//��ʾ֪ͨ��Ϣ
		void showNoticeMessage(const std::string& message);

	private:
		bool isValidSeat(BYTE seatNo);

	public:
		//�ֻ����ؼ������ص�����
		virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent) override;

	};
}


#endif // __YZ_FishKing_GameTableUI_H__
