#include "FishKingGameAdmin.h"
#include "YZUIExport.h"
#include "GamePrompt.h"

namespace FishKing
{
	static const char* ADMINUI_PATH			= "fishKing/AdminUi/AdminNode.csb";
	static const char* LIST_BG1				= "fishKing/AdminUi/Res/listItem_1.png";               //listBG
	static const char* LIST_BG2				= "fishKing/AdminUi/Res/listItem_2.png";               //listBG
	static const char* LIST_BG3				= "fishKing/AdminUi/Res/listItem_3.png";               //listBG

	GameAdmin::GameAdmin(GameTableLogic* tableLogic)
		: _tableLogic (tableLogic)
		, onCloseCallBack (nullptr)
	{
	}

	GameAdmin::~GameAdmin()
	{
	}

	void GameAdmin::closeAdmin()
	{
		_adminUI.adminUI->runAction(Sequence::create(FadeOut::create(0.1f), CCCallFunc::create([&]()
		{
			if (nullptr != onCloseCallBack)
			{
				onCloseCallBack();
			}
			this->removeFromParent();
		}), nullptr));
	}

	GameAdmin* GameAdmin::create(GameTableLogic* tableLogic)
	{
		GameAdmin *admin = new GameAdmin(tableLogic);
		if (admin && admin->init())
		{ 
			admin->autorelease();
			return admin;
		} 
		CC_SAFE_DELETE(admin);
		return nullptr;
	}

	bool GameAdmin::init()
	{
		if ( !YZLayer::init()) return false;

		ignoreAnchorPointForPosition(false);
		setAnchorPoint(Vec2::ANCHOR_MIDDLE);

		Size winSize = Director::getInstance()->getWinSize();

		auto admin_Node = CSLoader::createNode(ADMINUI_PATH);
		this->addChild(admin_Node, 1, 10);

		auto panel_admin = (Layout*)admin_Node->getChildByName("Panel_Admin");
		panel_admin->setAnchorPoint(Vec2(0.5f, 0.5f));
		panel_admin->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

		float scaleX = winSize.width / panel_admin->getContentSize().width;
		float scaleY = winSize.height / panel_admin->getContentSize().height;
		panel_admin->setScale(scaleX, scaleY);

		_adminUI.adminUI = (Layout*)panel_admin->getChildByName("Panel_BG");
		//����
		float scX = 1280 / winSize.width;
		float scY = 720 / winSize.height;
		_adminUI.adminUI->setScale(scX, scY);

		getOnlinePageUi();
		getControlPageUi();
		getSpecialPageUi();
		getCommonButton();

		return true;
	}

	//��������б�ҳ��
	void GameAdmin::getOnlinePageUi()
	{
		//ҳ�汳��
		_adminUI.Image_OnLineBg = dynamic_cast<ImageView*>(_adminUI.adminUI->getChildByName("Image_OnLineBg"));

		if (nullptr!= _adminUI.Image_OnLineBg)
		{
			//��������б�
			_ListView_Online = dynamic_cast<ui::ListView*>(_adminUI.Image_OnLineBg->getChildByName("ListView_Online"));
			_ListView_Online->addEventListener(ListView::ccListViewCallback(CC_CALLBACK_2(GameAdmin::onLineUsersListEventCallBack, this)));

			//��ѯ���ذ�ť
			auto btnStockQuery = dynamic_cast<Button*>(_adminUI.Image_OnLineBg->getChildByName("Button_StockQuery"));
			btnStockQuery->addClickEventListener([=](Ref*){
				_tableLogic->sendStockOperate(0);
			});

			//���ӽ��ذ�ť
			auto btnStockAdd = dynamic_cast<Button*>(_adminUI.Image_OnLineBg->getChildByName("Button_StockAdd"));
			btnStockAdd->addClickEventListener([=](Ref*){
				_tableLogic->sendStockOperate(2);
			});

			//���㽱�ذ�ť
			auto btnStockClear = dynamic_cast<Button*>(_adminUI.Image_OnLineBg->getChildByName("Button_StockClear"));
			btnStockClear->addClickEventListener([=](Ref*){
				_tableLogic->sendStockOperate(1);
			});

			//��ѯ��ˮ��ť
			auto btnBrokerage = dynamic_cast<Button*>(_adminUI.Image_OnLineBg->getChildByName("Button_Brokerage"));
			btnBrokerage->addClickEventListener([=](Ref*){
				_tableLogic->sendStockOperate(3);
			});
		}
	}

	//�ܿ�����б�ҳ��
	void GameAdmin::getControlPageUi()
	{
		//ҳ�汳��
		_adminUI.Image_ControlBg = dynamic_cast<ImageView*>(_adminUI.adminUI->getChildByName("Image_ControlBg"));
		if (nullptr!= _adminUI.Image_ControlBg)
		{
			//�ܿ�����б�
			_ListView_Control = dynamic_cast<ui::ListView*>(_adminUI.Image_ControlBg->getChildByName("ListView_Control"));
			_ListView_Control->addEventListener(ListView::ccListViewCallback(CC_CALLBACK_2(GameAdmin::controlUsersListEventCallBack, this)));

			//���ظ�ѡ��
			_CheckBox_Control = dynamic_cast<ui::CheckBox*>(_adminUI.Image_ControlBg->getChildByName("CheckBox_Control"));
			_CheckBox_Control->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameAdmin::checkBoxCallback, this)));

			auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_UserID"));
			auto TextField_Score = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_Score"));
			auto TextField_Chance = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_Chance"));

			//��Ӯ��ѡ��
			auto CheckBox_Win = dynamic_cast<ui::CheckBox*>(_adminUI.Image_ControlBg->getChildByName("CheckBox_Win"));
			auto CheckBox_Lose = dynamic_cast<ui::CheckBox*>(_adminUI.Image_ControlBg->getChildByName("CheckBox_Lose"));
			CheckBox_Win->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameAdmin::checkBoxCallback, this)));
			CheckBox_Lose->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameAdmin::checkBoxCallback, this)));

			auto Button_Add = dynamic_cast<Button*>(_adminUI.Image_ControlBg->getChildByName("Button_Add"));
			Button_Add->addClickEventListener([=](Ref*){
				
				if (!Tools::verifyNumber(TextField_UserID->getString()))
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ȷ�����ID��"));
					return;
				}

				ControlInfo info;
				info.user_id_ = atoi(TextField_UserID->getString().c_str());
				info.limit_score_ = atoi(TextField_Score->getString().c_str());
				info.catch_rate_ = atoi(TextField_Chance->getString().c_str());
				info.win_or_lose_ = CheckBox_Win->isSelected();

				if (!Tools::verifyNumber(TextField_Score->getString().c_str()) || info.limit_score_ <= 0)
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���������0�ķ�����"));
					return;
				}

				RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, C_S_ADD_CONTROL_INFO_SIG, &info, sizeof(info));
			});

			auto Button_Cut = dynamic_cast<Button*>(_adminUI.Image_ControlBg->getChildByName("Button_Cut"));
			Button_Cut->addClickEventListener([=](Ref*){

				if (!Tools::verifyNumber(TextField_UserID->getString()))
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ȷ�����ID��"));
					return;
				}

				C_S_DELETE_CONTROL_INFO control;
				control.user_id_ = atoi(TextField_UserID->getString().c_str());

				RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, C_S_DELETE_CONTROL_INFO_SIG, &control, sizeof(control));
			});
		}
	}

	//�������ܿ�����б�ҳ��
	void GameAdmin::getSpecialPageUi()
	{
		//ҳ�汳��
		_adminUI.Image_SpecialBg = dynamic_cast<ImageView*>(_adminUI.adminUI->getChildByName("Image_SpecialBg"));
		if (nullptr!= _adminUI.Image_SpecialBg)
		{
			//�������ܿ�����б�
			_ListView_UserID = dynamic_cast<ui::ListView*>(_adminUI.Image_SpecialBg->getChildByName("ListView_UserID"));
			_ListView_UserID->addEventListener(ListView::ccListViewCallback(CC_CALLBACK_2(GameAdmin::specialFishUserListEventCallBack, this)));

			//���ظ�ѡ��
			_CheckBox_Special = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Special"));
			_CheckBox_Special->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameAdmin::checkBoxCallback, this)));

			//���б�
			_ListView_Fish = dynamic_cast<ui::ListView*>(_adminUI.Image_SpecialBg->getChildByName("ListView_Special"));

			char str[24];
			for (int i = 1; i <= 4; i++)
			{
				sprintf(str, "CheckBox_Fish%d", i);
				auto checkBox_Fish = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName(str));
				checkBox_Fish->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameAdmin::specialCheckBoxCallBack, this)));
			}

			auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_UserID"));
			auto TextField_Num = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_Num"));
			auto TextField_Chance = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_Chance"));

			//��Ӱ�ť
			auto Button_Append = dynamic_cast<Button*>(_adminUI.Image_SpecialBg->getChildByName("Button_Append"));
			Button_Append->addClickEventListener([=](Ref*){
				if (!Tools::verifyNumber(TextField_UserID->getString()))
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ȷ�����ID��"));
					return;
				}
				char str[24];
				int kind = 0;
				for (int i = 1; i <= 4; i++)
				{
					sprintf(str, "CheckBox_Fish%d", i);
					auto checkBox_Fish = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName(str));
					if (checkBox_Fish->isSelected())
					{
						kind = checkBox_Fish->getTag();
						break;
					}
				}
				C_S_ADD_SPECIAL add_special;
				add_special.user_id_ = atoi(TextField_UserID->getString().c_str());
				add_special.fish_kind_ = kind;
				add_special.left_num_ = atoi(TextField_Num->getString().c_str());
				add_special.catch_rate_ = atoi(TextField_Chance->getString().c_str());

				if (!Tools::verifyNumber(TextField_Num->getString().c_str()) || add_special.left_num_ <= 0)
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���������0��ʣ��������"));
					return;
				}
				RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, C_S_ADD_SPECIAL_SIG, &add_special, sizeof(add_special));
			});

			//ɾ����ť
			auto Button_Delete = dynamic_cast<Button*>(_adminUI.Image_SpecialBg->getChildByName("Button_Delete"));
			Button_Delete->addClickEventListener([=](Ref*){
				if (!Tools::verifyNumber(TextField_UserID->getString()))
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ȷ�����ID��"));
					return;
				}
				char str[24];
				int kind = 0;
				for (int i = 1; i <= 4; i++)
				{
					sprintf(str, "CheckBox_Fish%d", i);
					auto checkBox_Fish = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName(str));
					if (checkBox_Fish->isSelected())
					{
						kind = checkBox_Fish->getTag();
						break;
					}
				}
				C_S_DELETE_SPECIAL delete_special;
				delete_special.user_id_ = atoi(TextField_UserID->getString().c_str());
				delete_special.fish_kind_ = kind;
				RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, C_S_DELETE_SPECIAL_SIG, &delete_special, sizeof(delete_special));
			});
		}
	}

	//������ť
	void GameAdmin::getCommonButton()
	{
		//�رհ�ť
		Button* btnClose = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Close"));
		btnClose->addClickEventListener([=](Ref*){closeAdmin();});

		//�������ҳ�水ť
		Button* btnOnline = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Online"));
		//�ܿ����ҳ�水ť
		Button* btnControl = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Control"));
		//�������ܿ����ҳ�水ť
		Button* btnSpecial = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Special"));

		btnOnline->addClickEventListener([=](Ref*){
			updateButtonEnabled(1);
		});

		btnControl->addClickEventListener([=](Ref*){
			updateButtonEnabled(2);
		});

		btnSpecial->addClickEventListener([=](Ref*){
			updateButtonEnabled(3);
		});

		//�������ݰ�ť
		Button* btnUpdate = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Update"));
		btnUpdate->addClickEventListener([=](Ref*){
			RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, C_S_UPDATE_SUPER_INFO_SIG);
		});
	}

	//���°�ť״̬
	void GameAdmin::updateButtonEnabled(BYTE type)
	{
		//�������ҳ�水ť
		Button* btnOnline = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Online"));
		//�ܿ����ҳ�水ť
		Button* btnControl = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Control"));
		//�������ܿ����ҳ�水ť
		Button* btnSpecial = dynamic_cast<Button*>(_adminUI.adminUI->getChildByName("Button_Special"));

		bool onLine = 1 == type ? true : false;
		bool contorl = 2 == type ? true : false;
		bool special = 3 == type ? true : false;

		btnOnline->setBright(!onLine);
		btnControl->setBright(!contorl);
		btnSpecial->setBright(!special);
		btnOnline->setEnabled(!onLine);
		btnControl->setEnabled(!contorl);
		btnSpecial->setEnabled(!special);
		_adminUI.Image_OnLineBg->setVisible(onLine);
		_adminUI.Image_ControlBg->setVisible(contorl);
		_adminUI.Image_SpecialBg->setVisible(special);
	}

	//���¿���ҳ�水ť�͸�ѡ��״̬
	void GameAdmin::updateControlPageButtonEnabled(bool enabled)
	{
		_CheckBox_Control->setSelected(enabled);

		//���ID�����
		auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_UserID"));
		TextField_UserID->setTouchEnabled(enabled);
		//���Ʒ��������
		auto TextField_Score = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_Score"));
		TextField_Score->setTouchEnabled(enabled);
		//�����������
		auto TextField_Chance = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_Chance"));
		TextField_Chance->setTouchEnabled(enabled);

		//��Ӯѡ��ѡ��
		auto CheckBox_Win = dynamic_cast<ui::CheckBox*>(_adminUI.Image_ControlBg->getChildByName("CheckBox_Win"));
		if (!CheckBox_Win->isSelected()) CheckBox_Win->setTouchEnabled(enabled);
		CheckBox_Win->setBright(enabled);
		auto CheckBox_Lose = dynamic_cast<ui::CheckBox*>(_adminUI.Image_ControlBg->getChildByName("CheckBox_Lose"));
		if (!CheckBox_Lose->isSelected()) CheckBox_Lose->setTouchEnabled(enabled);
		CheckBox_Lose->setBright(enabled);

		//���Ӽ��ٰ�ť
		auto Button_Add = dynamic_cast<Button*>(_adminUI.Image_ControlBg->getChildByName("Button_Add"));
		Button_Add->setEnabled(enabled);
		Button_Add->setBright(enabled);
		auto Button_Cut = dynamic_cast<Button*>(_adminUI.Image_ControlBg->getChildByName("Button_Cut"));
		Button_Cut->setEnabled(enabled);
		Button_Cut->setBright(enabled);
	}

	//�������������ҳ�水ť�͸�ѡ��״̬
	void GameAdmin::updateSpecialPageButtonEnabled(bool enabled)
	{
		_CheckBox_Special->setSelected(enabled);

		//���������㸴ѡ��
		auto CheckBox_Fish1 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish1"));
		CheckBox_Fish1->setTouchEnabled(enabled);
		CheckBox_Fish1->setBright(enabled);
		auto CheckBox_Fish2 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish2"));
		CheckBox_Fish2->setTouchEnabled(enabled);
		CheckBox_Fish2->setBright(enabled);
		auto CheckBox_Fish3 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish3"));
		CheckBox_Fish3->setTouchEnabled(enabled);
		CheckBox_Fish3->setBright(enabled);
		auto CheckBox_Fish4 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish4"));
		CheckBox_Fish4->setTouchEnabled(enabled);
		CheckBox_Fish4->setBright(enabled);

		//���ID�����
		auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_UserID"));
		TextField_UserID->setTouchEnabled(enabled);
		//ʣ�����������
		auto TextField_Num = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_Num"));
		TextField_Num->setTouchEnabled(enabled);
		//ץ�����������
		auto TextField_Chance = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_Chance"));
		TextField_Chance->setTouchEnabled(enabled);

		//���ɾ����ť
		auto Button_Append = dynamic_cast<Button*>(_adminUI.Image_SpecialBg->getChildByName("Button_Append"));
		Button_Append->setEnabled(enabled);
		Button_Append->setBright(enabled);
		auto Button_Delete = dynamic_cast<Button*>(_adminUI.Image_SpecialBg->getChildByName("Button_Delete"));
		Button_Delete->setEnabled(enabled);
		Button_Delete->setBright(enabled);
	}

	//������������б�
	void GameAdmin::createOnlineList(std::vector<OnLineUserInfo> users)
	{
		_ListView_Online->removeAllItems();
		for (auto user : users)
		{
			addOnlineItem(user);
		}
	}

	//�����ܿ�����б�
	void GameAdmin::createControlList(S_C_UPDATE_CONTROL_INFO* info)
	{
		_ListView_Control->removeAllItems();

		for (int i = 0; i < 40; i++)
		{
			if (0 != info->control_infos_[i].user_id_)
			{
				addControlItem(&info->control_infos_[i]);
			}
		}
	}

	//�����������ܿ�����б�
	void GameAdmin::createSprcialList(S_C_UPDATE_SPECIAL_INFO* info)
	{
		_ListView_UserID->removeAllItems();
		_userList.clear();

		for (int i = 0, n = 0; i < 20; i++)
		{
			if (0 != info->special_infos_[i].user_id_)
			{
				addSpecialItem(info->special_infos_[i], n);
				n++;
			}
		}
	}

	//��������������
	void GameAdmin::addOnlineItem(OnLineUserInfo info)
	{
		// ����������б���ͼ
		auto listItem = ImageView::create(LIST_BG1);
		float itemWidth = listItem->getContentSize().width;
		float itemHeight = listItem->getContentSize().height;
		listItem->setTouchEnabled(true);

		char str[32];
		//���id
		sprintf(str, "%d", info.userID);
		auto userIdText = Text::create(str, "", 22);
		userIdText->setPosition(Vec2(itemWidth * 0.12f, itemHeight * 0.55f));
		listItem->addChild(userIdText);

		listItem->setTag(info.userID);

		//����ǳ�
		sprintf(str, "%s", info.nickName);
		auto nickNameText = Text::create(GBKToUtf8(str), "", 22);
		nickNameText->setPosition(Vec2(itemWidth * 0.35f, itemHeight * 0.55f));
		listItem->addChild(nickNameText);

		//�������
		sprintf(str, "%d", info.deskNo + 1);		
		auto deskNoText = Text::create(str, "", 22);
		deskNoText->setPosition(Vec2(itemWidth * 0.62f, itemHeight * 0.55f));
		listItem->addChild(deskNoText);
		if (255 == info.deskNo)
		{
			deskNoText->setString(GBKToUtf8("����"));
		}

		//�����Ϸ��
		sprintf(str, "%d", info.i64UserMoney);
		auto uMoneyText = Text::create(str, "", 22);
		uMoneyText->setPosition(Vec2(itemWidth * 0.85f, itemHeight * 0.55f));
		listItem->addChild(uMoneyText);

		_ListView_Online->pushBackCustomItem(listItem);
	}

	//����ܿ��������
	void GameAdmin::addControlItem(ControlInfo* info)
	{
		// �ܿ�������б���ͼ
		auto listItem = ImageView::create(LIST_BG1);
		float itemWidth = listItem->getContentSize().width;
		float itemHeight = listItem->getContentSize().height;
		listItem->setTouchEnabled(true);

		char str[32];
		//���id
		sprintf(str, "%d", info->user_id_);
		auto userIdText = Text::create(str, "", 22);
		userIdText->setPosition(Vec2(itemWidth * 0.12f, itemHeight * 0.55f));
		listItem->addChild(userIdText);

		listItem->setTag(info->user_id_);

		//��Ӯ����
		sprintf(str, "%d", info->catch_rate_);
		auto rateText = Text::create(str, "", 22);
		rateText->setPosition(Vec2(itemWidth * 0.35f, itemHeight * 0.55f));
		listItem->addChild(rateText);

		//���Ʒ���
		sprintf(str, "%lld", info->limit_score_);
		auto limitText = Text::create(str, "", 22);
		limitText->setPosition(Vec2(itemWidth * 0.62f, itemHeight * 0.55f));
		listItem->addChild(limitText);

		//Ӯ������
		sprintf(str, "%s", info->win_or_lose_ ? "Ӯ" : "��");
		auto winOrloseText = Text::create(GBKToUtf8(str), "", 22);
		winOrloseText->setPosition(Vec2(itemWidth * 0.85f, itemHeight * 0.55f));
		listItem->addChild(winOrloseText);

		_ListView_Control->pushBackCustomItem(listItem);
	}

	//����������ܿ��������
	void GameAdmin::addSpecialItem(SpecialUser user, int idx)
	{
		// �ܿ�������б���ͼ
		auto listItem = ImageView::create(LIST_BG2);
		float itemWidth = listItem->getContentSize().width;
		float itemHeight = listItem->getContentSize().height;
		listItem->setTouchEnabled(true);
		_userList.push_back(user);
		listItem->setTag(user.user_id_);

		char str[32];
		//���id
		sprintf(str, "%d", user.user_id_);
		auto userIdText = Text::create(str, "", 22);
		userIdText->setPosition(Vec2(itemWidth / 2, itemHeight * 0.55f));
		listItem->addChild(userIdText);

		_ListView_UserID->pushBackCustomItem(listItem);
	}

	//����������ܿ�����
	void GameAdmin::addSpecialFishIten(SpecialFish fish)
	{
		// �ܿ�������б���ͼ
		auto listItem = ImageView::create(LIST_BG3);
		float itemWidth = listItem->getContentSize().width;
		float itemHeight = listItem->getContentSize().height;
		
		char str[32];
		for (int i = 0; i < 4; i++)
		{
			sprintf(str, "Text_Fish%d", i + 1);
			auto text = dynamic_cast<Text*>(_adminUI.Image_SpecialBg->getChildByName(str));
			std::string temp = Utf8ToGB(text->getString().c_str());
			if (fish.fish_kind_ == text->getTag())
			{
				sprintf(str, "%s", temp.c_str());
				break;
			}
		}

		//������
		auto fishKindText = Text::create(GBKToUtf8(str), "", 22);
		fishKindText->setPosition(Vec2(itemWidth * 0.15f, itemHeight * 0.55f));
		listItem->addChild(fishKindText);

		//ʣ������
		sprintf(str, "%d", fish.left_num_);
		auto numText = Text::create(str, "", 22);
		numText->setPosition(Vec2(itemWidth / 2, itemHeight * 0.55f));
		listItem->addChild(numText);

		//ץ������
		sprintf(str, "%d", fish.catch_rate_);
		auto rateText = Text::create(str, "", 22);
		rateText->setPosition(Vec2(itemWidth * 0.8f, itemHeight * 0.55f));
		listItem->addChild(rateText);

		_ListView_Fish->pushBackCustomItem(listItem);
	}

	//��������б����ص�
	void GameAdmin::onLineUsersListEventCallBack(Ref* pSender, ui::ListView::EventType type)
	{
		if (ListView::EventType::ON_SELECTED_ITEM_END != type) return;
		ListView* listItems = dynamic_cast<ListView*>(pSender);
		UINT selected = listItems->getCurSelectedIndex();
		Widget* listItem = listItems->getItem(selected);	
		char str[12];
		sprintf(str, "%d", listItem->getTag());

		//�����������б��ʱ��������ƿ��ظ�ѡ�򱻹�ѡ��ѵ�������id��д������ҳ���������
		if (_CheckBox_Control->isSelected())
		{
			auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_UserID"));
			TextField_UserID->setString(str);
		}

		//�����������б��ʱ��������ƿ��ظ�ѡ�򱻹�ѡ��ѵ�������id��д������ҳ���������
		if (_CheckBox_Special->isSelected())
		{
			auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_UserID"));
			TextField_UserID->setString(str);
		}
	}

	//�ܿ�����б����ص�
	void GameAdmin::controlUsersListEventCallBack(Ref* pSender, ui::ListView::EventType type)
	{
		if (ListView::EventType::ON_SELECTED_ITEM_END != type) return;
		if (!_CheckBox_Control->isSelected()) return;

		ListView* listItems = dynamic_cast<ListView*>(pSender);
		UINT selected = listItems->getCurSelectedIndex();
		Widget* listItem = listItems->getItem(selected);	
		char str[12];
		sprintf(str, "%d", listItem->getTag());
		auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_ControlBg->getChildByName("TextField_UserID"));
		TextField_UserID->setString(str);
	}

	//�������ܿ�����б����ص�
	void GameAdmin::specialFishUserListEventCallBack(Ref* pSender, ui::ListView::EventType type)
	{
		if (ListView::EventType::ON_SELECTED_ITEM_END != type) return;
		ListView* listItems = dynamic_cast<ListView*>(pSender);
		UINT selected = listItems->getCurSelectedIndex();
		Widget* listItem = listItems->getItem(selected);	
		SpecialUser user = (SpecialUser)_userList.at(selected);

		if (_CheckBox_Special->isSelected())
		{
			char str[12];
			sprintf(str, "%d", listItem->getTag());
			auto TextField_UserID = dynamic_cast<TextField*>(_adminUI.Image_SpecialBg->getChildByName("TextField_UserID"));
			TextField_UserID->setString(str);
		}

		_ListView_Fish->removeAllItems();

		for (int i = 0; i < 4; i++)
		{
			auto fish = user.special_fish_[i];
			if (fish.left_num_ == 0) continue;
			addSpecialFishIten(fish);
		}
	}

	// ��ѡ��ص�����
	void GameAdmin::checkBoxCallback(Ref* pSender, CheckBox::EventType type)
	{
		auto checkBox = dynamic_cast<CheckBox*>(pSender);
		auto name = checkBox->getName();

		//��Ӯ��ѡ��
		auto CheckBox_Win = dynamic_cast<ui::CheckBox*>(_adminUI.Image_ControlBg->getChildByName("CheckBox_Win"));
		auto CheckBox_Lose = dynamic_cast<ui::CheckBox*>(_adminUI.Image_ControlBg->getChildByName("CheckBox_Lose"));

		if (name.compare("CheckBox_Control") == 0)
		{
			bool select = checkBox->isSelected();
			updateControlPageButtonEnabled(select);
			RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, C_S_SWITCH_CONTROL_SIG, &select, sizeof(select));
		}

		if (name.compare("CheckBox_Special") == 0)
		{
			bool select = checkBox->isSelected();
			updateSpecialPageButtonEnabled(select);
			RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, C_S_SWITCH_SPECIAL_SIG, &select, sizeof(select));
		}

		if (name.compare("CheckBox_Win") == 0)
		{
			CheckBox_Win->setTouchEnabled(false);
			CheckBox_Lose->setTouchEnabled(true);
			CheckBox_Lose->setSelected(false);
		}

		if (name.compare("CheckBox_Lose") == 0)
		{
			CheckBox_Lose->setTouchEnabled(false);
			CheckBox_Win->setTouchEnabled(true);
			CheckBox_Win->setSelected(false);
		}
	}

	//��������Ƹ�ѡ��ص�
	void GameAdmin::specialCheckBoxCallBack(Ref* pSender, CheckBox::EventType type)
	{
		auto checkBox = dynamic_cast<CheckBox*>(pSender);
		auto name = checkBox->getName();

		//�����㸴ѡ��
		auto CheckBox_Fish1 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish1"));
		auto CheckBox_Fish2 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish2"));
		auto CheckBox_Fish3 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish3"));
		auto CheckBox_Fish4 = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName("CheckBox_Fish4"));

		if (name.compare("CheckBox_Fish1") == 0)
		{
			CheckBox_Fish1->setTouchEnabled(false);
			CheckBox_Fish2->setTouchEnabled(true);
			CheckBox_Fish3->setTouchEnabled(true);
			CheckBox_Fish4->setTouchEnabled(true);
			CheckBox_Fish2->setSelected(false);
			CheckBox_Fish3->setSelected(false);
			CheckBox_Fish4->setSelected(false);
		}

		if (name.compare("CheckBox_Fish2") == 0)
		{
			CheckBox_Fish2->setTouchEnabled(false);
			CheckBox_Fish1->setTouchEnabled(true);
			CheckBox_Fish3->setTouchEnabled(true);
			CheckBox_Fish4->setTouchEnabled(true);
			CheckBox_Fish1->setSelected(false);
			CheckBox_Fish3->setSelected(false);
			CheckBox_Fish4->setSelected(false);
		}

		if (name.compare("CheckBox_Fish3") == 0)
		{
			CheckBox_Fish3->setTouchEnabled(false);
			CheckBox_Fish1->setTouchEnabled(true);
			CheckBox_Fish2->setTouchEnabled(true);
			CheckBox_Fish4->setTouchEnabled(true);
			CheckBox_Fish1->setSelected(false);
			CheckBox_Fish2->setSelected(false);
			CheckBox_Fish4->setSelected(false);
		}

		if (name.compare("CheckBox_Fish4") == 0)
		{
			CheckBox_Fish4->setTouchEnabled(false);
			CheckBox_Fish1->setTouchEnabled(true);
			CheckBox_Fish2->setTouchEnabled(true);
			CheckBox_Fish3->setTouchEnabled(true);
			CheckBox_Fish1->setSelected(false);
			CheckBox_Fish2->setSelected(false);
			CheckBox_Fish3->setSelected(false);
		}
	}

	//��ʾ���ز������
	void GameAdmin::showStockOperateResult(std::string msg)
	{
		auto text = dynamic_cast<Text*>(_adminUI.Image_OnLineBg->getChildByName("Text_Message"));
		text->setVisible(true);
		text->setString(GBKToUtf8(msg.c_str()));
	}

	//���ÿ����������
	void GameAdmin::setSpecialFishName(S_C_FISH_NAME* pName)
	{
		char str[32];
		for (int i = 0; i < 4; i++)
		{
			sprintf(str, "Text_Fish%d", i + 1);
			auto text = dynamic_cast<Text*>(_adminUI.Image_SpecialBg->getChildByName(str));
			sprintf(str, "%s", pName->cFishName[i]);
			text->setString(GBKToUtf8(str));
			text->setTag(pName->byFishKind + i);

			sprintf(str, "CheckBox_Fish%d", i + 1);
			auto checkBox = dynamic_cast<ui::CheckBox*>(_adminUI.Image_SpecialBg->getChildByName(str));
			checkBox->setTag(pName->byFishKind + i);
		}
	}

	//���¸�ѡ����Ϣ
	void GameAdmin::setCheckBoxState(S_C_SWITCH_INFO* pSwitch)
	{
		//���¿���ҳ�水ť�͸�ѡ��״̬
		updateControlPageButtonEnabled(pSwitch->control_switch_);
		//�������������ҳ�水ť�͸�ѡ��״̬
		updateSpecialPageButtonEnabled(pSwitch->special_switch_);
	}
}
