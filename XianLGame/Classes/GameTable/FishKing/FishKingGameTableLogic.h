#ifndef __HN__FishKing_GameTableLogic_H__
#define __HN__FishKing_GameTableLogic_H__


#include "cocos2d.h"
#include "YZNetExport.h"
#include "FishKingMessageHead.h"

using namespace std;
using namespace YZ;

namespace FishKing
{
	class GameTableUICallback;

	class GameTableLogic : public YZGameLogicBase
	{
		GameTableUICallback*			_tableUICallBack;

	public:
		BYTE							_MYSEATNO;
		bool							_playerSitted[PLAY_COUNT];			//����Ƿ��Ѿ�����
		std::vector<OnLineUserInfo>		_users;							//��������б�

	public:
		GameTableLogic(GameTableUICallback* tableUICallBack, BYTE deskNo, bool bAutoCreate);
		virtual ~GameTableLogic();

	public:
		void enterGame();
		void loadUsers();
		LLONG getUserMoney(BYTE seatNo);
		LLONG getUserCannonNum(BYTE seatNo);
		void setGameConfig();

	public:
		//��ҿ���
		void sendOpenFire(CMD_C_UserFire* pFire, INT size);
		//ץ����
		void sendHitFish(BYTE seatNo, INT fishId, INT bulletId, BulletKind bulletKind, INT bulletMuriple);
		//���������ץ������ʱ��ǰ��Ļ�е�������
		void sendSweepFish(CMD_C_CatchSweepFish* pRet, INT size);

		//��ѯ���ز���
		void sendStockOperate(BYTE operate_code);

	private:
		// ��Ϸ��Ϣ����Ϸ��������Ϣ�������
		virtual void dealGameMessage(NetMessageHead* messageHead, void* object, INT objectSize) override;

		/*
		 * @func: framework message function.
		 * @info: they will be called when frame message come from base class.
		 */
		virtual void dealUserAgreeResp(MSG_GR_R_UserAgree* agree) {};
		virtual void dealGameStartResp(BYTE bDeskNO) override;
		virtual void dealGameEndResp(BYTE deskNo) override;
		virtual void dealGamePointResp(void* object, INT objectSize) override;
		virtual void dealUserSitResp(MSG_GR_R_UserSit * userSit, UserInfoStruct* user) override;
		virtual void dealQueueUserSitMessage(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& user) override;
		virtual void dealUserUpResp(MSG_GR_R_UserSit * userSit, UserInfoStruct* user) override;
		virtual void dealGameInfoResp(MSG_GM_S_GameInfo* pGameInfo) override;
		virtual void dealGameStationResp(void* object, INT objectSize) override;

	public:
		virtual void sendUserUp() override;
		virtual void sendForceQuit() override;


	private:
		virtual void initParams() override;
		/*
		 * refresh member before every game start.
		 */
		virtual void refreshParams() override;

		void setSeatOffset(BYTE seatNo);


	};

}


#endif // __HN_FishKing_GameTableLogic_H__