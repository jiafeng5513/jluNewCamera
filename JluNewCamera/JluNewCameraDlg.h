
// JluNewCameraDlg.h : 头文件
//

//#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "stdlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "afxdialogex.h"
#include "calib.h"
#include "match.h"
#include "Point_Analyze.h"
#include "string.h"
#include "cvaux.h"
#include "cxcore.h"
#include "highgui.h"
#include "cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "camerads.h"

#include "CvvImage.h"
#include "calib.h"
//#include "StereoMatch.h"
//#include "PointCloudAnalyzer.h"

using namespace std;
using namespace cv;
// CJluNewCameraDlg 对话框
static cv::Point moupoint;
class CJluNewCameraDlg : public CDialogEx
{
// 构造
public:
	CJluNewCameraDlg(CWnd* pParent = NULL);	// 标准构造函数
	void FixDisp(Mat_<float> & disp,int numofdisp);
// 对话框数据
	enum { IDD = IDD_JLUNEWCAMERA_DIALOG };
	
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
private:
	
	
	/***
	 *	全局私有变量
	 */
	//CCameraDS lfCam;
	//CCameraDS riCam;
//	VideoCapture lfCam;
//	VideoCapture riCam;
	cv::Mat m_lfImage;
	cv::Mat m_riImage;
	cv::Mat m_disparity;
	calib m_stereoCalibrator;
//	StereoMatch m_stereoMatcher;
//	int m_lfCamID;
//	int m_riCamID;
//	int m_nCamCount;
	int m_ProcMethod;
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nImageChannels;
	CString m_workDir;

	#pragma region 控件关联变量
	int m_nCornerSize_X;
	int m_nCornerSize_Y;
	int m_nBoards;
//	int m_nDelayTime;
	int m_nMinDisp;
	int m_nMaxDisp;
	int m_nSADWinSiz;
	int m_nTextThres;
	int m_nDisp12MaxDiff;
	int m_nPreFiltCap;
	int m_nUniqRatio;
	int m_nSpeckRange;
	int m_nSpeckWinSiz;
	int m_P1;
	int m_P2;
	UINT m_nID_RAD;
//	BOOL m_bFullDP;
//	BOOL m_bSaveFrame;
	float m_nSquareSize;
	double m_ObjectWidth;
	double m_ObjectHeight;
	double m_ObjectDistance;
	double m_ObjectDisparity;

/*	CButton* m_pCheck;
	CComboBox m_CBNCamList;
	CComboBox m_CBNMethodList;
	CComboBox m_CBNResolution;
	CSpinButtonCtrl m_spinMinDisp;
	CSpinButtonCtrl m_spinMaxDisp;
	CSpinButtonCtrl m_spinSADWinSiz;
	CSpinButtonCtrl m_spinTextThres;
	CSpinButtonCtrl m_spinDisp12MaxDiff;
	CSpinButtonCtrl m_spinPreFiltCap;
	CSpinButtonCtrl m_spinUniqRatio;
	CSpinButtonCtrl m_spinSpeckRange;
	CSpinButtonCtrl m_spinSpeckWinSiz;*/
		/***
	 *	功能函数
	 */
//	void DoShowOrigFrame(void);
	void DoStereoCalib(void);
//	void DoFrameProc(Mat& src, Mat& dst);
//	void DoParseOptionsOfCameraCalib(OptionCameraCalib& opt);
//	void DoParseOptionsOfStereoMatch(OptionStereoMatch& opt);
	void DoClearParamsOfStereoMatch(void);
	vector<CStringA> DoSelectFiles(LPCTSTR	lpszDefExt, DWORD	dwFlags, LPCTSTR	lpszFilter, LPCWSTR	lpstrTitle, LPCWSTR	lpstrInitialDir);
	void DoUpdateStateBM(void);
	void DoUpdateStateSGBM(int imgChannels);
	CString F_GetAppExecPath();
	void F_Gray2Color(Mat& gray_mat, Mat& color_mat);
	void F_Saveframe(Mat& lfImg, Mat&riImg, Mat& lfDisp);
	void F_ShowImage(Mat& src, Mat& des, UINT ID);
//	void F_EdgeDetectCanny(Mat& src, Mat& des);
#pragma endregion 控件关联变量
public:
	afx_msg void OnEnChangeBoardheight();
	afx_msg void OnEnChangeSquaresize();
	afx_msg void OnEnChangeBoardwidth();
	afx_msg void OnBnClickedBnDefaultcamcalibparam();
	afx_msg void OnBnClickedBndetectag();
	afx_msg void OnBnClickedBn2stereocalib();
	typedef enum { STEREO_BM, STEREO_SGBM } STEREO_METHOD;
	static void CJluNewCameraDlg::On_Mouse(int event,int x,int y,int flags,void *)
    {
		switch(event)
		{
		case CV_EVENT_LBUTTONDOWN:
			{
				
				moupoint.x=x;
				moupoint.y=y;
//				AfxMessageBox(_T("起来了"));
			}
			break;
		case CV_EVENT_LBUTTONUP:
			{
			}
			break;
		}
    }
	struct OptionStereoMatch
	{
		bool			readLocalImage;		//是否读入本地图像进行立体匹配
		bool			generatePointCloud;	//是否生成三维点云
		bool			useStereoRectify;	//是否使用双目校正算法
		STEREO_METHOD	stereoMethod;		//选择的立体匹配算法
		calib::RECTIFYMETHOD	rectifyMethod;		//选择的双目校正算法
	};

	struct OptionCameraCalib
	{
		int				numberBoards;		//棋盘检测次数
		int				flagCameraCalib;	//单目定标标志符
		int				flagStereoCalib;	//双目定标标志符
		int				numberFrameSkip;	//角点检测的帧间间隔数
		bool			doStereoCalib;		//是否进行双目标定
		bool			readLocalImage;		//是否从本地读入棋盘图片
		double			squareSize;			//棋盘方块大小
		cv::Size		cornerSize;			//棋盘角点数
		calib::RECTIFYMETHOD	rectifyMethod;		//选择的双目校正算法
	};
	
	afx_msg void OnBnClickedBnStereodefparam();
	afx_msg void OnBnClickedBngivedisp();
	afx_msg void OnBnClickedBnCompdisp();
	afx_msg void OnBnClickedRadBm();
	afx_msg void OnBnClickedRadSgbm();
	afx_msg void OnBnClickedBnMouseon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedFacedetect();
	afx_msg void OnBnClickedOnlydisp();
	afx_msg void OnBnClickedSgbmtest();
};
