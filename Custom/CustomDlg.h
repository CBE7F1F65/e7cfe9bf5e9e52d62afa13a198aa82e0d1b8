// CustomDlg.h : ͷ�ļ�
//

#pragma once

#include "../DES_GOBSTG/DES_GOBSTG/Header/Export.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/ConstResource.h"

// CCustomDlg �Ի���
class CCustomDlg : public CDialog
{
// ����
public:
	CCustomDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CUSTOM_DIALOG };

	void SetDisplay();
	void LoadIniValue();
	void LoadDefaultValue();

	void getScreenmodeValue();
	void getRenderskipValue();

	bool checkValid(bool reporterror = true);
	bool saveFile();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	bool havejoy;
	union{
		struct{
			int keyUp;
			int keyDown;
			int keyLeft;
			int keyRight;
			int keyFire;
			int keyQuick;
			int keySlow;
			int keyDrain;
			int keyPause;
			int keySkip;
			int keyEnter;
			int keyEscape;
			int keyCapture;
		};
		int keyKey[2][13];
	};
	union{
		struct{
			int	joyFire;
			int	joyQuick;
			int	joySlow;
			int	joyDrain;
			int	joyPause;
		};
		int		joyKey[2][5];
	};
	bool keycombineslowdrain[M_PL_MATCHMAXPLAYER];
	bool joycombineslowdrain[M_PL_MATCHMAXPLAYER];
	int screenmode;
	int renderskip;

	int defaultwindow;
	int windowleftx;
	int windowtopy;
	int windoww;
	int windowh;
	int windowtopmost;

	int musicvol;
	int sevol;
	char username[RPYINFO_USERNAMEMAX];

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDefaultwindow();
	afx_msg void OnBnClickedTopmost();
	afx_msg void OnBnClickedFullscreen();
	afx_msg void OnBnClickedWindow();
	afx_msg void OnBnClickedReload();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRenderskip0();
	afx_msg void OnBnClickedRenderskip2();
	afx_msg void OnBnClickedRenderskip3();
	afx_msg void OnEnChangeJoyFire();
	afx_msg void OnEnChangeJoyQuick();
	afx_msg void OnEnChangeJoySlow();
	afx_msg void OnEnChangeJoyDrain();
	afx_msg void OnEnChangeJoyPause();
	afx_msg void OnBnClickedCheck1();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnEnChangeJoyFire2();
	afx_msg void OnEnChangeJoyQuick2();
	afx_msg void OnEnChangeJoySlow2();
	afx_msg void OnEnChangeJoyDrain2();
	afx_msg void OnEnChangeJoyPause2();
	afx_msg void OnBnClickedKeyCombineSlowDrain();
	afx_msg void OnBnClickedKeyCombineSlowDrain2();
	afx_msg void OnBnClickedJoyCombineSlowDrain();
	afx_msg void OnBnClickedJoyCombineSlowDrain2();
	afx_msg void OnEnChangeMusicvol();
	afx_msg void OnEnChangeSevol();
	afx_msg void OnEnChangeLeftX();
	afx_msg void OnEnChangeTopY();
	afx_msg void OnEnChangeWindowW();
	afx_msg void OnEnChangeWindowH();
	afx_msg void OnEnChangeUsername();
	afx_msg void OnEnKillfocusUsername();
};
