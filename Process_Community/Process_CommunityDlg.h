
// Process_CommunityDlg.h: 头文件
//

#pragma once


// CProcessCommunityDlg 对话框
class CProcessCommunityDlg : public CDialogEx
{
// 构造
public:
	CProcessCommunityDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESS_COMMUNITY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRecv();
	afx_msg void OnBnClickedCreateBtn();
	afx_msg void OnBnClickedButtonSend();
};
