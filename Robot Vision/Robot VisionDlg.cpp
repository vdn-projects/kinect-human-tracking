
// Robot VisionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Robot Vision.h"
#include "Robot VisionDlg.h"
#include "afxdialogex.h"

//#include <tchar.h>
//#include <stdarg.h>
//-----------------------------------
#include <iostream>
#include <sstream>

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//------------------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRobotVisionDlg dialog

CRobotVisionDlg::CRobotVisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRobotVisionDlg::IDD, pParent)
	, m_strReceive(_T(""))
	, m_strTransfer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRobotVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BITRATE, m_cboBitRate);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_cboComPort);
	DDX_Control(pDX, IDC_COMBO_DATABIT, m_cboDataBit);
	DDX_Control(pDX, IDC_COMBO_HANDSHAKING, m_cboHandshaking);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_cboParityBit);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_cboStopBit);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_strReceive);
	DDX_Text(pDX, IDC_EDIT_TRANSFER, m_strTransfer);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm1);
}

BEGIN_MESSAGE_MAP(CRobotVisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CRobotVisionDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CRobotVisionDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CRobotVisionDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &CRobotVisionDlg::OnBnClickedButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CRobotVisionDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CRobotVisionDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CRobotVisionDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD, &CRobotVisionDlg::OnBnClickedButtonBackward)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CRobotVisionDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CRobotVisionDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CRobotVisionDlg message handlers

BOOL CRobotVisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitComboBox();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRobotVisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRobotVisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRobotVisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRobotVisionDlg::InitComboBox(void)
{
	// ComboBox ComPort
		m_cboComPort.ResetContent();
		m_cboComPort.AddString(L"COM1");
		m_cboComPort.AddString(L"COM2");
		m_cboComPort.AddString(L"COM3");
		m_cboComPort.AddString(L"COM4");
		m_cboComPort.AddString(L"COM5");
		m_cboComPort.AddString(L"COM6");
		m_cboComPort.AddString(L"COM7");
		m_cboComPort.AddString(L"COM8");
		m_cboComPort.AddString(L"COM9");
		m_cboComPort.SetCurSel(5);
	//m_cboComPort
	// ComboBox BitRate
		m_cboBitRate.ResetContent();
		m_cboBitRate.InsertString(0,L"600");
		m_cboBitRate.InsertString(1,L"1200");
		m_cboBitRate.InsertString(2,L"2400");
		m_cboBitRate.InsertString(3,L"4800");
		m_cboBitRate.InsertString(4,L"9600");
		m_cboBitRate.InsertString(5,L"14400");
		m_cboBitRate.InsertString(6,L"19200");
		m_cboBitRate.InsertString(7,L"28800");
		m_cboBitRate.InsertString(8,L"38400");
		m_cboBitRate.InsertString(9,L"56000");
		m_cboBitRate.InsertString(10,L"57600");
		m_cboBitRate.InsertString(11,L"115200");
		m_cboBitRate.InsertString(12,L"128000");
		m_cboBitRate.InsertString(13,L"256000");
		
		m_cboBitRate.SetCurSel(6);
		// ComboBox Data Bit
		m_cboDataBit.ResetContent();
		m_cboDataBit.AddString(L"5");
		m_cboDataBit.AddString(L"6");
		m_cboDataBit.AddString(L"7");
		m_cboDataBit.AddString(L"8");

		m_cboDataBit.SetCurSel(3);

		// ComboBox Stop Bit
		m_cboStopBit.ResetContent();
		m_cboStopBit.AddString(L"1");
		m_cboStopBit.AddString(L"1.5");
		m_cboStopBit.AddString(L"2");

		m_cboStopBit.SetCurSel(0);
		
		// ComboBox Parity Bit
		m_cboParityBit.ResetContent();
		m_cboParityBit.InsertString(0,L"None");
		m_cboParityBit.InsertString(1,L"Old");
		m_cboParityBit.InsertString(2,L"Even");
		m_cboParityBit.InsertString(3,L"Mark");
		m_cboParityBit.InsertString(4,L"Space");
		
		m_cboParityBit.SetCurSel(0);
		
		// ComboBox Handshaking
		m_cboHandshaking.ResetContent();
		m_cboHandshaking.InsertString(0,L"None");
		m_cboHandshaking.InsertString(1,L"XON/XOFF");
		m_cboHandshaking.InsertString(2,L"RTS");
		m_cboHandshaking.InsertString(3,L"RTS/CTS + XON/XOFF");

		m_cboHandshaking.SetCurSel(0);
}


void CRobotVisionDlg::Settings(void)
{
	// if port is already opened then close port.
		if( m_mscomm1.get_PortOpen()) 
				m_mscomm1.put_PortOpen(false);
		// Setting comport
		m_mscomm1.put_CommPort(m_cboComPort.GetCurSel()+ 1);  
		// Setting Handshaking
		m_mscomm1.put_Handshaking(m_cboHandshaking.GetCurSel()); 
		
	// Thiet lap tan so bit du lieu bit stop
		CString strBitRate = getCurStrInCombobox(m_cboBitRate);
		CString strParity  = getCurStrInCombobox(m_cboParityBit);
		CString strDataBit = getCurStrInCombobox(m_cboDataBit);
		CString strStopBit = getCurStrInCombobox(m_cboStopBit);
		
		CString strSetting;
		strSetting.Format(L"%s,%c,%s,%s",strBitRate,strParity[1],strDataBit,strStopBit);
		m_mscomm1.put_Settings(strSetting); //"9600,N,8,1");
		m_mscomm1.put_RThreshold(1);  // Doc du lieu ngay khi co trong buffer
		// set for input direction
		m_mscomm1.put_InputLen(1); // Moi lan doc mot ky tu
		m_mscomm1.put_InBufferSize(1024);
		m_mscomm1.put_InputMode(0); //  0- text mode, 1- binary mode
		m_mscomm1.put_OutBufferSize(1024);
		m_mscomm1.put_PortOpen(true); // mo cong
}


CString CRobotVisionDlg::getCurStrInCombobox(const CComboBox &a)
{
	CString str;
    a.GetLBText(a.GetCurSel(),str);
	return str;
}


void CRobotVisionDlg::OnBnClickedButtonExit()
{
// Neu cong con mo thi dong lai
if(m_mscomm1.get_PortOpen())
	m_mscomm1.put_PortOpen(false);
	OnOK();
}


void CRobotVisionDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
 UpdateData(TRUE);
 Settings();
 //send data
 m_mscomm1.put_Output(COleVariant(m_strTransfer));//strOutput));	
 UpdateData(false);
}


void CRobotVisionDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
 UpdateData();
 m_strReceive="";
 UpdateData(false);
}
BEGIN_EVENTSINK_MAP(CRobotVisionDlg, CDialogEx)
	ON_EVENT(CRobotVisionDlg, IDC_MSCOMM1, 1, CRobotVisionDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

int numchar = 0;	
void CRobotVisionDlg::OnCommMscomm1()
{

	
	UpdateData();
	numchar+=1;
	VARIANT data;
	switch (m_mscomm1.get_CommEvent()){
	case 1: // comEvSend
		break;
	case 2: // comEvReceive
		data =m_mscomm1.get_Input();
		m_strReceive += (CString)data.bstrVal;
			if (numchar==100){
				m_strReceive="";
				numchar=0;
			} 
		//	UpdateData(FALSE);		
		break;
	case 3:	// comEvCTS
		break;
	case 4:	// ComEvDSR
		break;
	case 5: // comEvCD
		break;
	case 6: // comEvRing
		break;
	case 7: // comEvEOF
		break;
	default:	break;
	};
	UpdateData(false);
}



CString data_send_RS232;
COleVariant tmp(data_send_RS232);

void CRobotVisionDlg::OnBnClickedButtonForward()
{
	data_send_RS232= "f";
	UpdateData(TRUE);
	Settings();
	m_mscomm1.put_Output(COleVariant(data_send_RS232));//strOutput));	
	UpdateData(false);
}


void CRobotVisionDlg::OnBnClickedButtonStop()
{
	data_send_RS232= "s";
	UpdateData(TRUE);
	Settings();
	m_mscomm1.put_Output(COleVariant(data_send_RS232));//strOutput));	
	UpdateData(false);
}


void CRobotVisionDlg::OnBnClickedButtonRight()
{
	data_send_RS232= "r";
	UpdateData(TRUE);
	Settings();
	m_mscomm1.put_Output(COleVariant(data_send_RS232));//strOutput));	
	UpdateData(false);
}


void CRobotVisionDlg::OnBnClickedButtonLeft()
{
	data_send_RS232= "l";
	UpdateData(TRUE);
	Settings();
	m_mscomm1.put_Output(COleVariant(data_send_RS232));//strOutput));	
	UpdateData(false);
}


void CRobotVisionDlg::OnBnClickedButtonBackward()
{
	data_send_RS232= "b";
	UpdateData(TRUE);
	Settings();
	m_mscomm1.put_Output(COleVariant(data_send_RS232));//strOutput));	
	UpdateData(false);
}


void CRobotVisionDlg::OnBnClickedButtonUpdate()
{
	UpdateData(TRUE);
	Settings();
}


USHORT DistanceToHip;

void CRobotVisionDlg::OnBnClickedButtonTest()
{
	//Initiate com port
	UpdateData(TRUE);
	Settings();
	data_send_RS232 = "s";
	m_mscomm1.put_Output(COleVariant(data_send_RS232));
	//Initiate Kinect
	kinect::nui::Kinect kinect;
	kinect.Initialize( NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON );

	kinect::nui::ImageStream& video = kinect.VideoStream();
	video.Open( NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480 );

	kinect::nui::ImageStream& depth = kinect.DepthStream();
	depth.Open( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, NUI_IMAGE_RESOLUTION_320x240 );

	kinect::nui::SkeletonEngine& skeleton = kinect.Skeleton();
	skeleton.Enable();

	// OpenCV settings
	cvNamedWindow( "Kinect Control Robot" );
	cvNamedWindow( "Kinect Depth" );
	IplImage* videoImg = cvCreateImage( cvSize(video.Width(), video.Height()), IPL_DEPTH_8U, 4 );
	IplImage* depthImg = cvCreateImage( cvSize(depth.Width(), depth.Height()), IPL_DEPTH_16U, 1 );
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1, 10);

	//To get time interval
	DWORD prevTime = GetTickCount();

	while ( 1 ) {
		// Get next frame
		kinect.WaitAndUpdateAll();
		kinect::nui::VideoFrame videoMD( video );
		kinect::nui::DepthFrame depthMD( depth );

		// Copy
		memcpy( videoImg->imageData, (BYTE*)videoMD.Bits(), videoImg->widthStep * videoImg->height );
		//Copy depth to buffer
		memcpy( depthImg->imageData, (BYTE*)depthMD.Bits(), depthImg->widthStep * depthImg->height );
		cvShowImage( "Kinect Depth", depthImg );
		

		// get next frame
		kinect::nui::SkeletonFrame skeletonMD = skeleton.GetNextFrame();

		// when found frame
		if ( skeletonMD.IsFoundSkeleton() ) {
			skeletonMD.TransformSmooth();

			for ( int i = 0; i < kinect::nui::SkeletonFrame::SKELETON_COUNT; ++i ) {
				// Move Kinect follow centre hip
				if ( skeletonMD[i].TrackingState() == NUI_SKELETON_TRACKED ) {
					int trac = NUI_SKELETON_POSITION_SPINE; //NUI_SKELETON_POSITION_HAND_RIGHT
					kinect::nui::SkeletonData::Point p = skeletonMD[i].TransformSkeletonToDepthImage( trac ); //return floating -point x&y coordinate in depth to skeleton position
					CvPoint pt = cvPoint( (UINT)((p.x * video.Width()) + 0.5f), (UINT)((p.y * video.Height()) + 0.5f ));
					cvCircle( videoImg, pt, 5,  cvScalar( 255, 0, 0 ), -1 );

					POINT c = { pt.x, pt.y };
					DistanceToHip = (depthMD( pt.x/2, pt.y/2 ) >> 3);

					stringstream ss;
					ss << DistanceToHip << "mm";
					cvPutText( videoImg, ss.str().c_str(), pt, &font, cvScalar(0, 0, 255) );

					moveRobot( kinect, c );
				}
			}
		}

		data_send_RS232 = "s";
		m_mscomm1.put_Output(COleVariant(data_send_RS232));

		cvShowImage( "Kinect Control Robot", videoImg );

		int key = cvWaitKey( 10 );
		if ( key == 27 ) {
			break;
		}

	}

	cvDestroyAllWindows();
	cvReleaseImage(&videoImg);
	cvReleaseImage(&depthImg);
	kinect.Shutdown();
}

DWORD timeDelay = 600;
void CRobotVisionDlg::moveRobot( kinect::nui::Kinect& kinect, const POINT& pt )
{
	kinect::nui::ImageStream& video = kinect.VideoStream();

	const RECT place[] = {
		{ 0, 0, video.Width()/3, video.Height()},
		{ video.Width()/3,0, video.Width()/3*2, video.Height() },
		{ video.Width()/3*2,0, video.Width(), video.Height() },
	};

	// Move to the left
	if ( PtInRect( &place[0], pt ) ) {
		data_send_RS232= "r";
		m_mscomm1.put_Output(COleVariant(data_send_RS232));
		Sleep(timeDelay);
	}

	// Do nothing in the middle
	else if ( PtInRect( &place[1], pt ) ) {
			if(DistanceToHip >= 1200 && DistanceToHip < 1500) {
				data_send_RS232= "s";
				m_mscomm1.put_Output(COleVariant(data_send_RS232));
				Sleep(timeDelay);
			}

			else if(DistanceToHip >= 1500){
				data_send_RS232= "f";
				m_mscomm1.put_Output(COleVariant(data_send_RS232));
				Sleep(timeDelay);
			}
			else if(DistanceToHip < 1200){
				data_send_RS232= "b";
				m_mscomm1.put_Output(COleVariant(data_send_RS232));
				Sleep(timeDelay);
			}
	}

	// Move to the right
	else if ( PtInRect( &place[2], pt ) ) {
		data_send_RS232= "l";
		m_mscomm1.put_Output(COleVariant(data_send_RS232));
		Sleep(timeDelay);
	}
}
