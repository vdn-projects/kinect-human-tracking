
// Robot VisionDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"
#include "kinect\nui\Kinect.h"
#include "kinect\nui\ImageFrame.h"

// CRobotVisionDlg dialog
class CRobotVisionDlg : public CDialogEx
{
// Construction
public:
	CRobotVisionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ROBOTVISION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboBitRate;
	CComboBox m_cboComPort;
	CComboBox m_cboDataBit;
	CComboBox m_cboHandshaking;
	CComboBox m_cboParityBit;
	CComboBox m_cboStopBit;
	CString m_strReceive;
	CString m_strTransfer;
	CMscomm1 m_mscomm1;
	
	void InitComboBox(void);
	void Settings(void);
	CString getCurStrInCombobox(const CComboBox &a);
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClear();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	void moveRobot( kinect::nui::Kinect& kinect, const POINT& pt );
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonBackward();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonM1forward();
	afx_msg void OnBnClickedButtonM1stop();
	afx_msg void OnBnClickedButtonM1backward();
	afx_msg void OnBnClickedButtonM2forward();
	afx_msg void OnBnClickedButtonM2stop();
	afx_msg void OnBnClickedButtonM2backward();
	afx_msg void OnBnClickedButtonTest();
};
