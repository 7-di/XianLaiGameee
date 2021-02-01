#ifndef __HN_FishKing_GameTableUICallback_H__
#define __HN_FishKing_GameTableUICallback_H__

#include "YZBaseType.h"
#include "YZNetExport.h"
#include "FishKingMessageHead.h"

/************************************************************************/
/* ���ͣ��ص��ӿ�                                                        */
/* ���ܣ����������߼����յ���Ϣʱ���ý���ĺ����ӿ�                        */
/************************************************************************/

namespace FishKing
{
	class GameTableUICallback 
	{
	public:
		virtual void addUser(BYTE seatNo, bool bMe) = 0;											//������
		virtual void removeUser(BYTE seatNo, bool bMe) = 0;											//�Ƴ����
		virtual void dealSetUserMoney(BYTE seatNo, LLONG value) = 0;								//������ҽ����Ŀ
		virtual void dealSetUserCannonNum(BYTE seatNo, INT value,INT valueCell) = 0;								//��������ڻ�ȼ�

		///////////////////////////////////////////////////////////////////
		virtual void dealSetGameConfig(CMD_S_GameConfig* gConfig) = 0;								//������Ϸ����
		virtual void dealSetSceneStyle(SceneStyle Scene) = 0;										//��Ϸ����id
		virtual void dealGameFire(CMD_S_UserFire* pFire, bool bMeFire) = 0;							//��ҿ���
		virtual void dealCatchFish(CMD_S_CatchFish*	pFish) = 0;										//ץ����ͨ����Ϣ
		virtual void dealAddFishInfo(void* object  , WORD objectSize) = 0;							//�����ͨ��
		virtual void dealAddGroupFishInfo(CMD_S_GroupFishTrace* pFish) = 0;							//������������������С����
		virtual void dealCatchSweepFish(CMD_S_CatchSweepFish* pSweep) = 0;							//��Ҳ�������
		virtual void dealCatchSweepFishResult(CMD_S_CatchSweepFishResult* pResult) = 0;				//��Ҳ���������
		virtual void dealCatchSweepFishResultEx(CMD_S_CatchSweepFishResultEx* pResult) = 0;			//��������ϵͳ֪ͨ
		virtual void dealSwitchScene(CMD_S_SwitchScene* pScene) = 0;								//�л�����
		virtual void dealLockFishTimeOut() = 0;														//���������붨ס����ָ��˶�
		virtual void dealBulletTimeOut(BYTE seatNo) = 0;											//ȡ��������


		////////////////////////////////////////////////////////////////////
		virtual void dealGameStart() = 0;
		virtual void dealLeaveDesk() = 0;
		virtual void onDisconnect() = 0;

		////////////////////////////////////////////////////////////////////
		//����
		////////////////////////////////////////////////////////////////////
		virtual void dealSetAdminConfig(bool bAdmin) = 0;											//�Ƿ񳬶��û�
		virtual void dealStockOperateResult(CMD_S_StockOperateResult* pStock) = 0;					//���ز������
		virtual void dealUpdateOnlinePlayerList(std::vector<OnLineUserInfo> users) = 0;			//������������б�
		virtual void dealUpdateContorlList(S_C_UPDATE_CONTROL_INFO* info) = 0;						//���¿����б���Ϣ
		virtual void dealUpdateSpecialList(S_C_UPDATE_SPECIAL_INFO* pSpecial) = 0;					//��������������б���Ϣ
		virtual void dealSetSwitchInfo(S_C_SWITCH_INFO* pSwitch) = 0;									//���ƿ���
		virtual void dealUpdateFishName(S_C_FISH_NAME* pName) = 0;									//���¿����������

	};
};

#endif //__FishKing_GameTableUICallback_H__