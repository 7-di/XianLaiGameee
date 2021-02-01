#ifndef __FishKing_GameAdmin_H__
#define __FishKing_GameAdmin_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "FishKingMessageHead.h"
#include "FishKingGameTableLogic.h"
#include "ui/CocosGUI.h"
#include "YZNetExport.h"
#include "YZUIExport.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

namespace FishKing
{
	class GameAdmin : public YZLayer
	{
	public:

		typedef std::function<void ()> OnCloseCallBack;
		OnCloseCallBack	onCloseCallBack;


	public:
		GameAdmin(GameTableLogic* tableLogic);
		virtual ~GameAdmin();

	public:
		static GameAdmin* create(GameTableLogic* tableLogic);

	public:
		virtual bool init() override;
		//�رճ��˹���ҳ��
		void closeAdmin();

		//������������б�
		void createOnlineList(std::vector<OnLineUserInfo> users);
		//�����ܿ�����б�
		void createControlList(S_C_UPDATE_CONTROL_INFO* info);
		//�����������ܿ�����б�
		void createSprcialList(S_C_UPDATE_SPECIAL_INFO* info);

	public:
		//��ʾ���ز������
		void showStockOperateResult(std::string msg);
		//���ÿ����������
		void setSpecialFishName(S_C_FISH_NAME* pName);
		//���¸�ѡ����Ϣ
		void setCheckBoxState(S_C_SWITCH_INFO* pSwitch);

	private:
		//��������б�ҳ��
		void getOnlinePageUi();
		//�ܿ�����б�ҳ��
		void getControlPageUi();
		//�������ܿ�����б�ҳ��
		void getSpecialPageUi();
		//������ť
		void getCommonButton();

	private:
		//���¹�����ť״̬
		void updateButtonEnabled(BYTE type);
		//���¿���ҳ�水ť�͸�ѡ��״̬
		void updateControlPageButtonEnabled(bool enabled);
		//���¿���ҳ�水ť�͸�ѡ��״̬
		void updateSpecialPageButtonEnabled(bool enabled);
		//��������������
		void addOnlineItem(OnLineUserInfo info);
		//����ܿ��������
		void addControlItem(ControlInfo* info);
		//����������ܿ��������
		void addSpecialItem(SpecialUser user, int idx);
		//����������ܿ�����
		void addSpecialFishIten(SpecialFish fish);

	private:
		//��������б����ص�
		void onLineUsersListEventCallBack(Ref* pSender, ui::ListView::EventType type);
		//�ܿ�����б����ص�
		void controlUsersListEventCallBack(Ref* pSender, ui::ListView::EventType type);
		//�������ܿ�����б����ص�
		void specialFishUserListEventCallBack(Ref* pSender, ui::ListView::EventType type);


	private:
		//��ѡ��ص�
		void checkBoxCallback(Ref* pSender, CheckBox::EventType type);
		//��������Ƹ�ѡ��ص�
		void specialCheckBoxCallBack(Ref* pSender, CheckBox::EventType type);

	
	protected:
		struct ADMIN_UI
		{
			ImageView*		Image_OnLineBg;		//�����б���
			ImageView*		Image_ControlBg;	//��ҿ��Ʊ���
			ImageView*		Image_SpecialBg;	//��������Ʊ���

			Button*			Button_Online;		//�������ҳ�水ť
			Button*			Button_Control;		//�ܿ����ҳ�水ť
			Button*			Button_Special;		//�������ܿ�ҳ�水ť

			Widget*			adminUI;
		}_adminUI;

		ui::ListView*		_ListView_Online;	//��������б�
		ui::ListView*		_ListView_Control;	//�ܿ�����б�
		ui::ListView*		_ListView_UserID;	//�������ܿ�����б�
		ui::ListView*		_ListView_Fish;		//�ܿ��������б�

		ui::CheckBox*		_CheckBox_Control;	//����Ƿ��ܿؿ��ظ�ѡ��
		ui::CheckBox*		_CheckBox_Special;	//�������Ƿ��ܿؿ��ظ�ѡ��

		std::vector<SpecialUser> _userList;		//�ܿ�����б�����

		GameTableLogic*		_tableLogic;

	};

}

#endif // __GAMEADMIN_LAYER_H__
